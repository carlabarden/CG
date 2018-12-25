#include "cidade.h"

Cidade::Cidade(){}

void Cidade::draw(){

    this->quadra();
    this->asfalto();
    this->grama();
}

void Cidade::quadra(){

    Vetor q_esc(6,0.001,6);
    //coordenadas do centro de cada quadra
    Vetor centro_q1(4.5, -0.09, 4.5);
    Vetor centro_q2(-4.5, -0.09, 4.5);
    Vetor centro_q3(4.5, -0.09, -4.5);
    Vetor centro_q4(-4.5, -0.09, -4.5);

    this->grama_quadra(centro_q1, q_esc);
    this->grama_quadra(centro_q2, q_esc);
    this->grama_quadra(centro_q3, q_esc);
    this->grama_quadra(centro_q4, q_esc);

    this->arvore(centro_q1 + Vetor(1,0,1));
    this->arvore(centro_q1 + Vetor(-1.2,0,0.5));
    this->predio(centro_q1 + Vetor(-1,0,-1.5), Cor(0.22, 0.33, 0.4));
    this->arvore(centro_q2 + Vetor(-1.5,0,1));
    this->predio(centro_q2 + Vetor(1,0,1), Cor(0.3, 0.3, 0.3));
    this->predio(centro_q3 + Vetor(1,0,-1), Cor(0.22, 0.0, 0.1));
    this->predio(centro_q2 + Vetor(-1.5,0, -1.5), Cor(0.0, 0.22, 0.43));
    this->arvore(centro_q3 + Vetor(-1.5,0,1));
    this->arvore(centro_q4 + Vetor(1.5,0,-1.5));
    this->arvore(centro_q4 + Vetor(-1.2,0,0.5));
    this->predio(centro_q4 + Vetor(1,0,1.5), Cor(0.13, 0.12, 0.2)); 
}

void Cidade::grama_quadra(Vetor pos, Vetor esc){

    Cubo c (Cor(0.0, 0.1, 0.0));
    c.draw(pos, esc);
}

void Cidade::grama(){

    Cubo c (Cor(0.0, 0.1, 0.0));
    Vetor pos(0, -0.2, 0.5);
    Vetor esc(100, 0.2, 30);

    c.draw(pos, esc);
}

void Cidade::arvore(Vetor pos){

    Cubo folhas(Cor(0.0, 0.25, 0.0));
    Cubo tronco(Cor(0.2, 0.2, 0.0));
    Vetor post (0, 1.5, 0.0);
    post =  post + pos;
    Vetor esct (0.4, 3, 0.4);
    tronco.draw(post, esct);
    Vetor posf (0, 3, 0.0);
    posf = posf + pos;
    Vetor escf (1.5, 2, 1.5);
    folhas.draw(posf, escf);
}

void Cidade::predio(Vetor pos, Cor cor){

    Cubo c(cor);
    Vetor esc(1.5, 4, 1.5);
    c.draw(pos + Vetor(0,2,0),esc);
}

void Cidade::asfalto(){

    Cubo c (Cor(0.1, 0.1, 0.1));
    Vetor pos(0, -0.1, 0);
    Vetor esc(20, 0.02, 20);

    c.draw(pos, esc);

}
