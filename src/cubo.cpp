#include "cubo.h"

Cubo::Cubo(){
    this->cor = Cor(0.5,0.5,0.5);
}

Cubo::Cubo(Cor cor){
    this->cor.set_cor(cor);
}

void Cubo::draw(Vetor posicao, Vetor escala){

    glPushMatrix();
        this->cor.gl_set_cor();
        glTranslatef (posicao.get_x(), posicao.get_y(),posicao.get_z());
        glScalef (escala.get_x(), escala.get_y(), escala.get_z());
        this->draw_cubo();
    glPopMatrix();
}

void Cubo::draw(){
    this->draw_cubo();
}

void Cubo::draw_cubo(){
    
    glBegin(GL_QUADS);
    
        glNormal3f(0,1,0);
        glVertex3f(TAM_,TAM_,TAM_);
        glVertex3f(TAM_,TAM_,-TAM_);
        glVertex3f(-TAM_,TAM_,-TAM_);
        glVertex3f(-TAM_,TAM_,TAM_);

        glNormal3f(0,-1,0);
        glVertex3f(TAM_,-TAM_,TAM_);
        glVertex3f(TAM_,-TAM_,-TAM_);
        glVertex3f(-TAM_,-TAM_,-TAM_);
        glVertex3f(-TAM_,-TAM_,TAM_);

        glNormal3f(1,0,0);
        glVertex3f(TAM_,TAM_,-TAM_);
        glVertex3f(TAM_,TAM_,TAM_);
        glVertex3f(TAM_,-TAM_,TAM_);
        glVertex3f(TAM_,-TAM_,-TAM_);


        glNormal3f(-1,0,0);
        glVertex3f(-TAM_,TAM_,-TAM_);
        glVertex3f(-TAM_,TAM_,TAM_);
        glVertex3f(-TAM_,-TAM_,TAM_);
        glVertex3f(-TAM_,-TAM_,-TAM_);

        glNormal3f(0,0,1);
        glVertex3f(TAM_,TAM_,TAM_);
        glVertex3f(TAM_,-TAM_,TAM_);
        glVertex3f(-TAM_,-TAM_,TAM_);
        glVertex3f(-TAM_,TAM_,TAM_);

        glNormal3f(0,0,-1);
        glVertex3f(TAM_,TAM_,-TAM_);
        glVertex3f(TAM_,-TAM_,-TAM_);
        glVertex3f(-TAM_,-TAM_,-TAM_);
        glVertex3f(-TAM_,TAM_,-TAM_);

    glEnd();
}
