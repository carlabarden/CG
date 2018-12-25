#ifndef _CIDADE_H_
#define _CIDADE_H_

#include <GL/gl.h>
#include "vetor.h"
#include "cor.h"
#include "cubo.h"

class Cidade {

private:

    void grama();
    void arvore(Vetor pos);
    void asfalto();
    void predio(Vetor pos, Cor cor);
    void quadra();
    void grama_quadra(Vetor pos, Vetor esc);

public:

    Cidade();
    void draw();
};

#endif //_CIDADE_H_