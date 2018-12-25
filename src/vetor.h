#ifndef __VETOR_H
#define __VETOR_H

#include <math.h>

#define PI  3.1415926535
#define PI2 6.2831853071

class Vetor {
private:
    float x, y, z;

public:
    inline float grau_rad(float angulo);
    Vetor();
    Vetor (float x, float y, float z);
    //construtor de copia
    Vetor (const Vetor &v);
    void set_vetor (float x, float y, float z);
    void set_vetor (Vetor v);
    void set_x (float x);
    void set_y (float y);
    void set_z (float z);
    Vetor get_vetor();
    float get_x();
    float get_y();
    float get_z();

    float ajusta_angulo(float angulo);
    //soma e subtração
    Vetor operator + (const Vetor v);
    Vetor operator - (const Vetor v);
    //produto e divisão por escalar
    Vetor operator * (float s);
    Vetor operator / (float s);
    //produto escalar (interno)
    float operator * (const Vetor v);
    //produto vetorial
    Vetor operator ^ (const Vetor v);
    //norma (tamanho) do vetor
    float norma();
    //distância entre dois vetores
    float distancia (const Vetor v);
    //normalizar vetor
    Vetor normalizar();
    //rotaciona x
    Vetor rotacionar_x (float angulo);
    //rotaciona y
    Vetor rotacionar_y (float angulo);
    //rotaciona z
    Vetor rotacionar_z (float angulo);
};

#endif  //VETOR_H
