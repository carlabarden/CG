#ifndef _CUBO_H_
#define _CUBO_H_

#include "cor.h"
#include "vetor.h"

#define TAM_ 0.5

class Cubo{

private:

    void draw_cubo();

public:

    Cor cor;
    Cubo();
    Cubo(Cor cor);
    void draw(Vetor posicao, Vetor escala);
    void draw();

};

#endif //_CUBO_H_
