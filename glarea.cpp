// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "glarea.h"
#include <GL/glu.h>
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>
#include <math.h>

static const QString vertexShaderFile   = ":/basic.vsh";
static const QString fragmentShaderFile = ":/basic.fsh";


GLArea::GLArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
    qDebug() << "init GLArea" ;

    QSurfaceFormat sf;
    sf.setDepthBufferSize(24);
    sf.setSamples(16);  // nb de sample par pixels : suréchantillonnage por l'antialiasing, en décalant à chaque fois le sommet
                        // cf https://www.khronos.org/opengl/wiki/Multisampling et https://stackoverflow.com/a/14474260
    setFormat(sf);
    qDebug() << "Depth is"<< format().depthBufferSize();

    setEnabled(true);  // événements clavier et souris
    setFocusPolicy(Qt::StrongFocus); // accepte focus
    setFocus();                      // donne le focus

    m_timer = new QTimer(this);
    m_timer->setInterval(50);  // msec
    connect (m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect (this, SIGNAL(radiusChanged(double)), this, SLOT(setRadius(double)));
}

GLArea::~GLArea()
{
    qDebug() << "destroy GLArea";

    delete m_timer;

    // Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
    // dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
    makeCurrent();

    // ici destructions de ressources GL

    doneCurrent();
}


void GLArea::initializeGL()
{
    qDebug() << __FUNCTION__ ;
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    // shaders
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile);  // compile
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile);
    if (! m_program->link()) {  // édition de lien des shaders dans le shader program
        qWarning("Failed to compile and link shader program:");
        qWarning() << m_program->log();
    }

    // récupère identifiants de "variables" dans les shaders
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}

void GLArea::resizeGL(int w, int h)
{
    qDebug() << __FUNCTION__ << w << h;

    // C'est fait par défaut
    glViewport(0, 0, w, h);

    m_ratio = (double) w / h;
    // doProjection();
}

void GLArea::paintGL()
{
    qDebug() << __FUNCTION__ ;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind(); // active le shader program

    QMatrix4x4 matrix;
    GLfloat hr = m_radius, wr = hr * m_ratio;            // = glFrustum
    matrix.frustum(-wr, wr, -hr, hr, 1.0, 5.0);
    //matrix.perspective(60.0f, m_ratio, 0.1f, 100.0f);  // = gluPerspective

    // Remplace gluLookAt (0, 0, 3.0, 0, 0, 0, 0, 1, 0);
    matrix.translate(0, 0, -3.0);

    // Rotation de la scène pour l'animation
    matrix.rotate(m_angle, 0, 1, 0);

    matrix.translate(-m_x, -m_y, -m_z);

    m_program->setUniformValue(m_matrixUniform, matrix);

    GLfloat ep_cyl = 0.25; GLfloat r_cyl = 1; GLint nb_fac = 20;
    GLfloat alpha = 2 * M_PI/nb_fac;

    GLint color[]{
           255, 0, 0,
    };
    GLfloat vertices[c1->nb_fac*36];    //36=3*3*4
    GLfloat colors[c1->nb_fac*36];      //36=3*3*4

    c1->construire_cylindre(vertices,colors);

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);  // rend le VAA accessible pour glDrawArrays
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_TRIANGLES, 0, 12*c1->nb_fac);

    m_program->release();
}

void GLArea::keyPressEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();

    switch(ev->key()) {
        case Qt::Key_4 :
            m_angle += 1;
            if (m_angle >= 360) m_angle -= 360;
            update();
            break;
        case Qt::Key_6 :
            m_angle -= 1;
            if (m_angle <= -1) m_angle += 360;
            update();
            break;
        case Qt::Key_8 :
            m_y += 0.1f;
            update();
            break;
        case Qt::Key_2 :
            m_y -= 0.1f;
            update();
            break;
        case Qt::Key_A :
            if (m_timer->isActive())
                m_timer->stop();
            else m_timer->start();
            break;
        case Qt::Key_R :
            if (ev->text() == "r")
                 setRadius(m_radius-0.05f);
            else setRadius(m_radius+0.05f);
            break;
        case Qt::Key_Z :
            m_z+=0.1f;
            update();
            break;
        case Qt::Key_Q :
            m_x-=0.1f;
            update();
            break;
        case Qt::Key_S :
            m_z-=0.1f;
            update();
            break;
        case Qt::Key_D :
            m_x+=0.1f;
            update();
            break;
    }
}

void GLArea::keyReleaseEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();
}

void GLArea::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void GLArea::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void GLArea::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->x() << ev->y();
}

void GLArea::onTimeout()
{
    qDebug() << __FUNCTION__ ;
    m_anim += 0.01;
    if (m_anim > 1) m_anim = 0;
    update();
}

void GLArea::setRadius(double radius)
{
    qDebug() << __FUNCTION__ << radius << sender();
    if (radius != m_radius && radius > 0.01 && radius <= 10) {
        m_radius = radius;
        qDebug() << "  emit radiusChanged()";
        emit radiusChanged(radius);
        update();
    }
}




