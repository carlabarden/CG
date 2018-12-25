#include "vetor.h"

float Vetor::grau_rad(float angulo){
    return ((angulo * PI)/180);
}

float Vetor::ajusta_angulo(float angulo){
    if (angulo > 360) angulo = 0;
    if (angulo < 0) angulo = 360;
    return angulo;
}

Vetor::Vetor (float x, float y, float z){

    this->x = x;
    this->y = y;
    this->z = z;
}

Vetor::Vetor(){
    Vetor(0.0, 0.0, 0.0);
}

Vetor::Vetor(const Vetor &v){

    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

void Vetor::set_vetor (float x, float y, float z){

    this->x = x;
    this->y = y;
    this->z = z;
}

void Vetor::set_vetor (Vetor v){

    this->x = v.get_x();
    this->y = v.get_y();
    this->z = v.get_z();
}

void Vetor::set_x (float x){
    this->x = x;
}

void Vetor::set_y (float y){
    this->y = y;
}

void Vetor::set_z (float z){
    this->z = z;
}

Vetor Vetor::get_vetor(){
    Vetor aux(*this);
    return aux;
}

float Vetor::get_x(){
    float aux = this->x;
    return aux;
}

float Vetor::get_y(){
    float aux = this->y;
    return aux;
}

float Vetor::get_z(){
    float aux = this->z;
    return aux;
}

Vetor Vetor::operator+ (const Vetor v){
    Vetor aux(this->x + v.x,
              this->y + v.y,
              this->z + v.z);
    return aux;
}

Vetor Vetor::operator- (const Vetor v){
    Vetor aux(this->x - v.x,
              this->y - v.y,
              this->z - v.z);
    return aux;
}

Vetor Vetor::operator* (float s){
    Vetor aux(this->x * s,
              this->y * s,
              this->z * s);
    return aux;
}

Vetor Vetor::operator/ (float s){
    Vetor aux(this->x / s,
              this->y / s,
              this->z / s);
    return aux;
}

float Vetor::operator* (const Vetor v){
    float aux = this->x * v.x +
                this->y * v.y +
                this->z * v.z;
    return aux;
}

Vetor Vetor::operator^ (const Vetor v){
    Vetor aux(this->y * v.x - this->z * v.y,
              this->z * v.y - this->x * v.z,
              this->x * v.z - this->y * v.x);
    return aux;
}

float Vetor::norma(){
    return (float) (sqrt(this->x * this->x +
                         this->y * this->y +
                         this->z * this->z));
}

float Vetor::distancia (const Vetor v){
    return ((*this - v).norma());
}

Vetor Vetor::normalizar(){
    return ((this->get_vetor()) / (this->norma()));
}

Vetor Vetor::rotacionar_x (float angulo){

    Vetor aux = this->get_vetor();
    aux = aux.normalizar();

    float y_aux = aux.get_y();

    aux.set_y( cos(grau_rad(angulo)) * y_aux - sin(grau_rad(angulo)) * aux.get_z());
    aux.set_z( sin(grau_rad(angulo)) * y_aux + cos(grau_rad(angulo)) * aux.get_z());

    return aux;
}

Vetor Vetor::rotacionar_y (float angulo){

    Vetor aux = this->get_vetor();
    aux = aux.normalizar();

    float x_aux = aux.get_x();

    aux.set_x( cos(grau_rad(angulo)) * x_aux + sin(grau_rad(angulo)) * aux.get_z());
    aux.set_z( -sin(grau_rad(angulo)) * x_aux + cos(grau_rad(angulo)) * aux.get_z());

    return aux;
}

Vetor Vetor::rotacionar_z (float angulo){

    Vetor aux = this->get_vetor();
    aux = aux.normalizar();

    float x_aux = aux.get_x();

    aux.set_x( cos(grau_rad(angulo)) * x_aux - sin(grau_rad(angulo)) * aux.get_y());
    aux.set_y( sin(grau_rad(angulo)) * x_aux + cos(grau_rad(angulo)) * aux.get_y());

    return aux;
}