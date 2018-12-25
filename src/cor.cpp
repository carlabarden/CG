#include "cor.h"

Cor::Cor(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

Cor::Cor(){
    this->r = 0.0;
    this->g = 0.0;
    this->b = 0.0;
}

Cor Cor::get_cor(){
    Cor aux;
    aux.r = this->r;
    aux.g = this->g;
    aux.b = this->b;
    return aux;
}

float Cor::get_r(){
    return this->r;
}

float Cor::get_g(){
    return this->g;
}

float Cor::get_b(){
    return this->b;
}

void Cor::set_cor(Cor cor){
    this->r = cor.r;
    this->g = cor.g;
    this->b = cor.b;
}

void Cor::set_r(float r){
    this->r = r;
}

void Cor::set_g(float g){
    this->g = g;
}

void Cor::set_b(float b){
    this->b = b;
}

float Cor::get_alpha(){
    return this->alpha;
}

void Cor::set_alpha(float alpha){
    this->alpha = alpha;
}

void Cor::gl_set_cor(){
    glColor3f(this->r, this->g, this->b);
}
