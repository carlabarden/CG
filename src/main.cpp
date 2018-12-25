/*
T4 - Computação Gráfica
Carla de Oliveira Barden - 201713228
Prof: Cesar Tadeu Pozzer - 2018/2 -UFSM/BR

Implementações:

    - Carro andando por uma cidade (OpenGL/Glut):
            w  == acelera
            s  == freia
            a  == vira para a esquerda
            d  == vira para direita
        O carro também desacelera automaticamente se w não for mantido pressionado;

    - Opções de Câmera (em relação ao carro):
            t  == traseira
            f  == frontal
            i  == interna
            c  == em cima
            o  == origem (do sistema de coordenadas);

    - Tipo de Câmera:
            p  == alterna entre perspectiva (padrão) e ortogonal

    - Carros autônomos:
        Carros que andam pelas ruas

    - Detecção de Colisão (rudimentar):
        Aproxima gramados e carros autônomos como círculos para detectar colisões

    - Controle de FPS:
        Conforme demo disponível no site da disciplina
*/

#include <GL/glut.h>
#include "carro.h"
#include "frame.h"
#include "cidade.h"

#define TELA_X 700
#define TELA_Y 700

//parâmetros câmera
float abertura = 50.0;
float znear  = 1;
float zfar   = 1000;
float aspect = 1;
float coord_mundo_x = 10;
float coord_mundo_y = 10;

//funções
void init();
void keyboard(unsigned char key, int x, int y); //x e y p/ callback
void keyboard_up(unsigned char key, int x, int y);
void controle();
void display();
//void redimensionar(int x, int y);
void perspectiva();
void camera();
void reset_cameras();
void colisoes();
void luz();     //trata luz de colisão

//variáveis
Carro carro(Cor(0.0,0.0,0.3));
Carro a(Cor(0.3,0.0,0));
Carro b(Cor(0.0,0.4,0.4));
Cidade city;
Frames frm;
bool key_w, key_s, key_a, key_d;
bool frontal, traseira, interna, cima  = true, origem, tipo_camera = true, luz_vermelha = false; 
//tipo_camera true == perspectiva; false == ortogonal
//luz_vermelha false == normal true == vermelha

int main (int argc, char* argv[]){

    //inicializando glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(TELA_X, TELA_Y);
    glutInitWindowPosition(150,100);
    glutCreateWindow("T4 - Carla Barden");
    init();
    //callbacks
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    //glutReshapeFunc(redimensionar);

    glutMainLoop();

    return 0;
}

void init(){

   a.set_auto_piloto(0.05, Vetor( 9, 0.3, -9), Vetor(0,0,1), 2);
   b.set_auto_piloto(0.02, Vetor(9, 0.3, -9), Vetor(0,0,1), 2);

   //inicializar parâmetros opengl
   GLfloat mat_ambient[] = {0.5, 0.5, 0.5, 1 };
   GLfloat light_position[] = {-3, 10, -7, 0};
   GLfloat light_position2[] = {0, 0, 0, 0};
   GLfloat light_ambient[] = { 1, 1, 1 };
   GLfloat light_ambient2[] = { 1, 0, 0 };

   perspectiva();

   glMatrixMode(GL_MODELVIEW);

   glClearColor(0 , 0.3 , 0.9 , 1);

   glPolygonMode(GL_FRONT, GL_FILL);
   glPolygonMode(GL_BACK, GL_FILL);

   glEnable(GL_COLOR_MATERIAL);

   glFrontFace(GL_CW);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
   glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
   glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient2);
}

void display(){

    frm.getFrames();
    //limpar buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity( );

    controle();
    camera();
    carro.draw();
    city.draw();
    a.auto_piloto();
    a.draw();
    b.auto_piloto();
    b.draw();
    colisoes();
    luz();

    glutSwapBuffers();
}

void colisoes(){

    //flag para controlar colisões
    //se não incrementar, quer dizer que não houve colisão
    int colisao = 0;
    //raio da quadra
    float raio = 3.5;

    //trata colisoes com carros autonomos
    if ((carro.nao_pise_na_grama(a.get_posicao(), 1))) {
        luz_vermelha = true;
        colisao++;
    }

    if ((carro.nao_pise_na_grama(b.get_posicao(), 1))) {
        luz_vermelha = true;
        colisao++;
    }

    //trata colisões com as quadras
    if ((carro.nao_pise_na_grama(Vetor(4.5,0,4.5), raio))) {
        luz_vermelha = true;
        colisao++;
    }

    if ((carro.nao_pise_na_grama(Vetor(4.5,0,-4.5), raio))) {
        luz_vermelha = true;
        colisao++;
    }

    if ((carro.nao_pise_na_grama(Vetor(-4.5,0,-4.5), raio))) {
        luz_vermelha = true;
        colisao++;
    }

    if ((carro.nao_pise_na_grama(Vetor(-4.5,0,4.5), raio))) {
        luz_vermelha = true;
        colisao++;
    }

    //trata colisão com as bordas da cidade
    if (carro.delimitar_posicao()){
        luz_vermelha = true;
        colisao++;
    }

    //desliga luz vermelha se não houver colisao
    if (colisao == 0) luz_vermelha = false;

}


void luz (){

    if(luz_vermelha){
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
    }

    else{
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT0);
    }
}

void keyboard (unsigned char key, int x, int y){

    if (key == 'w') key_w = true;
    if (key == 's') key_s = true;
    if (key == 'a') key_a = true;
    if (key == 'd') key_d = true;
    if (key == 'p') tipo_camera = !tipo_camera;

    if (key == 'f') {
        reset_cameras();
        frontal = true;
    }

    else if (key == 't'){
        reset_cameras();
        traseira = true;
    }

    else if (key == 'i'){
        reset_cameras();
        interna = true;
    }

    else if (key == 'c'){
        reset_cameras();
        cima = true;
    }

    else if (key == 'o'){
        reset_cameras();
        origem = true;
    }
}

void keyboard_up (unsigned char key, int x, int y){

    if (key == 'w') key_w = false;
    if (key == 's') key_s = false;
    if (key == 'a') key_a = false;
    if (key == 'd') key_d = false;

}

void controle(){

    //acelerar
    if (key_w && carro.get_velocidade() < 2)
        carro.acelerar(1/frm.getFrames());

    //desaceleração automática
    else if (!key_w && carro.get_velocidade() > 0)
        carro.acelerar(-1/frm.getFrames());

    //freio
    if (key_s && carro.get_velocidade() > 0)  carro.desacelerar(2.8/frm.getFrames());

    //velocidade = 0 se velocidade < 0;
    if(carro.get_velocidade() < 0)  carro.acelerar(-carro.get_velocidade());

    //vira à esquerda
    if (key_a)  carro.rotacionar(4000/ frm.getFrames());

    //vira à direita
    if (key_d)  carro.rotacionar(-4000/ frm.getFrames());

}

void reset_cameras(){

    frontal  = false;
    traseira = false;
    interna  = false;
    cima     = false;
    origem   = false;
}

void camera(){

    perspectiva();

    Vetor pos = carro.get_posicao();
    Vetor dir = carro.get_direcao();

    if (frontal){

        gluLookAt(pos.get_x() + dir.get_x() * 7, pos.get_y() + 1, pos.get_z() +
                  dir.get_z() * 7, pos.get_x(), pos.get_y(), pos.get_z(), 0, 1, 0);

        //para não dar problema com a câmera em projeção ortográfica
        coord_mundo_x = tipo_camera ? 10 : 1;
        coord_mundo_y = tipo_camera ? 10 : 1;
    }

    else if (traseira){

        gluLookAt(pos.get_x() - dir.get_x() * 7, pos.get_y() + 1, pos.get_z() -
                  dir.get_z() * 7, pos.get_x(), pos.get_y(), pos.get_z(), 0, 1, 0);

        //para não dar problema com a câmera em projeção ortográfica
          coord_mundo_x = tipo_camera ? 10 : 1;
          coord_mundo_y = tipo_camera ? 10 : 1;
    }

    else if (interna){

        dir = dir * 10;
        gluLookAt(pos.get_x(), pos.get_y()+0.3, pos.get_z(),
             pos.get_x() + dir.get_x(), pos.get_y()+ dir.get_y(), pos.get_z()+ dir.get_z(),
             0, 1, 0);

        //para não dar problema com a câmera em projeção ortográfica
          coord_mundo_x = tipo_camera ? 10 : 0.5;
          coord_mundo_y = tipo_camera ? 10 : 0.5;
    }

    else if (cima){

        gluLookAt(0, 30, -0.005, 0, 0, 0, 0, 1, 0);

        coord_mundo_x = 10;
        coord_mundo_y = 10;
     }

    else if (origem){

        gluLookAt(0, 10, -30, 0, 0, 0, 0, 1, 0); //from, to, up

        coord_mundo_x = 10;
        coord_mundo_y = 10;
    }
}

void perspectiva (){

   // -- projeção ortográfica
   if(!tipo_camera){

      glViewport(0, 0, TELA_X, TELA_Y);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-coord_mundo_x, coord_mundo_x, -coord_mundo_y, coord_mundo_y, znear, zfar);
   }

   // -- projeção em perspectiva
   else{

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(abertura, aspect, znear, zfar);
   }
}