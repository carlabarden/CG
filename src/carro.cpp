#include "carro.h"

Carro::Carro(){

    this->escala = Vetor(0.75,0.75,0.5);
    this->posicao = Vetor(0,0,0);
    this->angulo_rotacao = Vetor(0,0,0);
    this->eixo_rotacao = Vetor(0,0,0);
    this->direcao = Vetor(0,0,1);
    this->velocidade = 0.0;
}

Carro::Carro(Cor cor){

    this->escala = Vetor(0.75,0.75,1);
    this->posicao = Vetor(0,0.3,0);
    this->angulo_rotacao = Vetor(0,0,0);
    this->eixo_rotacao = Vetor(0,0,0);
    this->direcao = Vetor(0,0,1);
    this->velocidade = 0.0;
    this->cor = cor;

}

Cor Carro::get_cor(){
    Cor aux(this->cor.get_cor());
    return aux;
}

void Carro::set_cor(Cor cor){
    this->cor.set_cor(cor);
}

Vetor Carro::get_escala(){
    Vetor aux = this->escala;
    return aux;
}

void Carro::set_escala(Vetor s){
    this->escala = s;
}

Vetor Carro::get_posicao(){
    Vetor aux = this->posicao;
    return aux;
}

void Carro::set_posicao(Vetor p){
    this->posicao = p;
}

Vetor Carro::get_angulo_rotacao(){
    Vetor aux = this->angulo_rotacao;
    return aux;
}

void Carro::set_angulo_rotacao(Vetor a){
    this->angulo_rotacao = a;
}

Vetor Carro::get_eixo_rotacao(){
    Vetor aux = this->eixo_rotacao;
    return aux;
}

void Carro::set_eixo_rotacao(Vetor e){
    this->eixo_rotacao = e;
}

Vetor Carro::get_direcao(){
    Vetor aux = this->direcao;
    return aux;
}

void Carro::set_direcao(Vetor d){
    this->direcao = d;
}

float Carro::get_velocidade(){
    float aux = this->velocidade;
    return aux;
}

void Carro::acelerar(float acc){
    this->velocidade += acc;
    if (this->velocidade > 2) this->velocidade = 2;
    ir();
}

void Carro::desacelerar(float desacc){
    this->velocidade -= desacc;
    if (this->velocidade < 0) this->velocidade = 0;
}

void Carro::rotacionar(float angulo){

    this->set_eixo_rotacao(Vetor(0,1,0));
    this->angulo_rotacao = this->angulo_rotacao + Vetor(0,angulo,0);
    this->direcao = this->direcao.rotacionar_y(angulo);

}

void Carro::ir(){

    Vetor aux(0,0,0);
    Vetor dir_aux(this->direcao.get_vetor());
    this->direcao.normalizar();
    aux.set_x(this->direcao.get_x() * this->velocidade);
    aux.set_z(this->direcao.get_z() * this->velocidade);
    this->posicao = this->posicao + aux;

}

void Carro::auto_piloto(){
    //pontos onde se fará curva
    Vetor a, b, c ,d;
    a = Vetor(-9, 0.3, -9);
    b = Vetor(9, 0.3, -9);
    c = Vetor(9, 0.3, 9);
    d = Vetor(-9, 0.3, 9);

    float dist;

    //seta id
    if (this->id == 0)  dist = (this->posicao - a).norma();

    else if (this->id == 1)  dist = (this->posicao - b).norma();

    else if (this->id == 2)  dist = (this->posicao - c).norma();

    else  dist = (this->posicao - d).norma();

    //se aproximar do ponto dado pelos vetores a, b, c e d, faz a curva conforme a direção do id
    if (dist < 0.4){
        this->id++;
        this->rotacionar(-90);

        if (this->id > 3)  this->id = 0;
    }

    this->ir();
}

void Carro::set_auto_piloto(float vel, Vetor pos, Vetor dir, int id){

    this->velocidade = vel;
    this->posicao = pos;
    this->direcao = dir;
    this->id = id; // pra onde o carro vai
}

bool Carro::delimitar_posicao(){

    bool x = false, z = false;
    //para não sair do quadro do asfalto
    if (this->posicao.get_x() >=  9.75){
        this->posicao.set_x( 9.75);
        x = true;
    }

    if (this->posicao.get_x() <= -9.75) {
        this->posicao.set_x(-9.75);
        x = true;
    }

    if (this->posicao.get_z() >=  9.75) {
        this->posicao.set_z( 9.75);
        z = true;
    }

    if (this->posicao.get_z() <= -9.75) {
        this->posicao.set_z(-9.75);
        z = true;
    }

    if (x || z) return true;

    return false;
}

bool Carro::nao_pise_na_grama(Vetor centro_quadra, float raio){

    float distancia;
    //vetor de distância entre a posição do carro e o centro da quadra
    Vetor d = this->posicao - centro_quadra;
    distancia = d.norma();

    if (distancia <= raio){

        d = d.normalizar() * raio;
        this->posicao = d + centro_quadra;
        this->posicao.set_y(0.3);
        return true;
    }

    return false;
}

void Carro::draw(){

    glPushMatrix();
        this->cor.gl_set_cor();
        glTranslatef (this->posicao.get_x(),
                      this->posicao.get_y(),
                      this->posicao.get_z());
        glPushMatrix();
            glRotatef  (this->angulo_rotacao.get_y(),
                        this->eixo_rotacao.get_x(),
                        this->eixo_rotacao.get_y(),
                        this->eixo_rotacao.get_z());
            glScalef (this->escala.get_x(),
                      this->escala.get_y(),
                      this->escala.get_z());
            this->cubo();
        glPopMatrix();

        //glTranslatef (0 ,0.1 , 0);
        glRotatef (this->angulo_rotacao.get_y(),
            this->eixo_rotacao.get_x(),
            this->eixo_rotacao.get_y(),
            this->eixo_rotacao.get_z());
        glScalef (this->escala.get_x() /1.5,
                  this->escala.get_y(),
                  this->escala.get_z() /2);
        glTranslatef (0 ,0.3 , 0.0);
        this->cubo();
    glPopMatrix();

}

void Carro::cubo(){

    glBegin(GL_QUADS);

        glNormal3f(0,1,0);
        glVertex3f(TAM,TAM,TAM);
        glVertex3f(TAM,TAM,-TAM);
        glVertex3f(-TAM,TAM,-TAM);
        glVertex3f(-TAM,TAM,TAM);

        glNormal3f(0,-1,0);
        glVertex3f(TAM,-TAM,TAM);
        glVertex3f(TAM,-TAM,-TAM);
        glVertex3f(-TAM,-TAM,-TAM);
        glVertex3f(-TAM,-TAM,TAM);

        glNormal3f(1,0,0);
        glVertex3f(TAM,TAM,-TAM);
        glVertex3f(TAM,TAM,TAM);
        glVertex3f(TAM,-TAM,TAM);
        glVertex3f(TAM,-TAM,-TAM);


        glNormal3f(-1,0,0);
        glVertex3f(-TAM,TAM,-TAM);
        glVertex3f(-TAM,TAM,TAM);
        glVertex3f(-TAM,-TAM,TAM);
        glVertex3f(-TAM,-TAM,-TAM);

        glNormal3f(0,0,1);
        glVertex3f(TAM,TAM,TAM);
        glVertex3f(TAM,-TAM,TAM);
        glVertex3f(-TAM,-TAM,TAM);
        glVertex3f(-TAM,TAM,TAM);

        glNormal3f(0,0,-1);
        glVertex3f(TAM,TAM,-TAM);
        glVertex3f(TAM,-TAM,-TAM);
        glVertex3f(-TAM,-TAM,-TAM);
        glVertex3f(-TAM,TAM,-TAM);

    glEnd();
}
