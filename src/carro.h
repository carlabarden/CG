#ifndef _CARRO_H_
#define _CARRO_H_

#include "vetor.h"
#include "cor.h"

#define TAM 0.5

class Carro{

private:

    Vetor escala;
    Vetor posicao;
    Vetor angulo_rotacao;   //armazena o ângulo de rotação na posição da coordenada em que ela irá ocorrer
    Vetor eixo_rotacao;
    Vetor direcao;
    Cor cor;
    int id; // para carro autonomo
    float velocidade;
    void ir(); //atualiza posição
    void cubo();


public:

    Carro();
    Carro(Cor cor);

    Cor get_cor();
    void set_cor(Cor cor);
    Vetor get_escala();
    void set_escala(Vetor s);
    Vetor get_posicao();
    void set_posicao(Vetor p);
    Vetor get_angulo_rotacao();
    void set_angulo_rotacao(Vetor a);
    Vetor get_eixo_rotacao();
    void set_eixo_rotacao(Vetor e);
    Vetor get_direcao();
    void set_direcao(Vetor d);
    float get_velocidade();
    void acelerar(float acc);       //atualiza velocidade
    void desacelerar(float desacc); //atualiza velocidade
    void rotacionar(float angulo);
    void draw();
    bool delimitar_posicao();   //não deixa sair da cidade
    bool nao_pise_na_grama(Vetor pos, float raio); //aproximando obj para um círculo
    void set_auto_piloto(float vel, Vetor pos, Vetor dir, int id);
    void auto_piloto();
};

#endif //_CARRO_H_
