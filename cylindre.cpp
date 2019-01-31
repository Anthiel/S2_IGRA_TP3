#include "cylindre.h"
#include <GL/glu.h>
#include <QDebug>
#include <math.h>


Cylindre::Cylindre(GLdouble ep_cyl, GLdouble r_cyl, GLint nb_fac)
{
    this->ep_cyl = ep_cyl; // epaisseur AB
    this->r_cyl = r_cyl; //rayon AC
    this->nb_fac = nb_fac; // nombre de facettes
}

void Cylindre::setColor(int r, int v, int b){
    color[0] = r; // rouge
    color[1] = v; // vert
    color[2] = b; // bleu
}

void Cylindre::dessiner_cylindre(GLint colorCylindre[3]){
    float alphaDecal = 360/nb_fac;
        printf("alphaDecal = %f\n", alphaDecal);
        for (int i = 0; i < nb_fac; ++i)
        {
            glPushMatrix();

           /* switch(sens){ // faire tourner les deux pièces avec 'espace'
                case 0 : glRotatef (angleAnima, 0, 0, 1); break;
                default : glRotatef (-angleAnima, 0, 0, 1); break;
            }
            */

            glRotatef (360*i/nb_fac, 0, 0, 1);

            dessiner_rayon();


            glPopMatrix();
        }
}

void Cylindre::dessiner_rayon(){
    GLfloat alpha = 2 * M_PI/nb_fac;

    GLfloat face1[] = {
        0,					0,					ep_cyl/2,           //face 1
        r_cyl,				0,					ep_cyl/2,           //face 1
        r_cyl*cos(alpha),	r_cyl*sin(alpha),	ep_cyl/2,           //face 1
        0,					0,					-ep_cyl/2,          //face 2
        r_cyl,				0,					-ep_cyl/2,          //face 2
        r_cyl*cos(alpha),	r_cyl*sin(alpha),	-ep_cyl/2,          //face 2
        r_cyl,				0,					ep_cyl/2,           //facette1
        r_cyl,				0,					-ep_cyl/2,          //facette1
        r_cyl*cos(alpha),	r_cyl*sin(alpha),	ep_cyl/2,           //facette1
        r_cyl*cos(alpha),	r_cyl*sin(alpha),	ep_cyl/2,           //facette2
        r_cyl*cos(alpha),	r_cyl*sin(alpha),	-ep_cyl/2,          //facette2
        r_cyl,				0,					-ep_cyl/2,          //facette2
    };

    GLfloat colors1[] = {
        color[0]/255.0f,            color[1]/255.0f,            color[2]/255.0f,            //face 1
        color[0]/255.0f,            color[1]/255.0f,            color[2]/255.0f,            //face 1
        color[0]/255.0f,            color[1]/255.0f,            color[2]/255.0f,            //face 1
        color[0]/255.0f,            color[1]/255.0f,            color[2]/255.0f,            //face 2
        color[0]/255.0f,            color[1]/255.0f,            color[2]/255.0f,            //face 2
        color[0]/255.0f,            color[1]/255.0f,            color[2]/255.0f,            //face 2
        (color[0]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     //facette1
        (color[0]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     //facette1
        (color[0]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     //facette1
        (color[0]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     //facette2
        (color[0]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     //facette2
        (color[0]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     (color[1]/255.0f)*0.8f,     //facette2
    };


}
