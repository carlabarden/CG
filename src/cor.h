#ifndef _COR_H_
#define _COR_H_

#include <GL/gl.h>

class Cor{

private:

    float r;
    float g;
    float b;
    float alpha;

public:

    Cor();
    Cor(float r, float g, float b);
    Cor get_cor();
    float get_r();
    float get_g();
    float get_b();
    void set_cor(Cor cor);
    void set_cor(float r, float g, float b);
    void set_r(float r);
    void set_g(float g);
    void set_b(float b);
    float get_alpha();
    void set_alpha(float alpha);
    void gl_set_cor();
};

#endif //_COR_H_
