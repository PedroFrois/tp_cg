#include <math.h>
#include <stdio.h>
#include "solo.c"
#include <time.h>
#include <limits.h>


const float TAMANHO_PROJETIL[2] = {3,3};
const float GRAVIDADE = 10;
const int MAXVENTO = 3;
float VENTO = 0;

typedef struct projetil{
  float xInicial;
  float yInicial;
  esqueleto esqueleto;
  float t;
  float forca;
  float angulo;
  int movimento;
}projetil;

void desenhaMovimentoProjetil();


//deve retornar 1 se o projetil colidiu com algo
//deve retornar 0 se o projetil não colidiu com nada
int colisaoProjetil();

projetil projetilAtual;

void setaPosProj(){
  projetilAtual.esqueleto.x = projetilAtual.xInicial+projetilAtual.forca*cos(projetilAtual.angulo)*projetilAtual.t
  - 0.5*VENTO*projetilAtual.t*projetilAtual.t;
  projetilAtual.esqueleto.y = projetilAtual.yInicial+projetilAtual.forca*sin(projetilAtual.angulo)*projetilAtual.t
  - 0.5*GRAVIDADE*projetilAtual.t*projetilAtual.t;
  projetilAtual.t += 0.05;
  desenhaMovimentoProjetil();
}

void desenhaProjetil(){
  if(projetilAtual.movimento){
    desenhaEsqueleto(projetilAtual.esqueleto);
  }
}

void setProjetilAtual(float x,float y,float forca,float angulo){
  projetilAtual.movimento = 1;
  projetilAtual.xInicial = projetilAtual.esqueleto.x = x;
  projetilAtual.yInicial = projetilAtual.esqueleto.y = y;
  projetilAtual.forca = forca;
  projetilAtual.angulo = angulo;
  projetilAtual.esqueleto.texturaGl = SOIL_load_OGL_texture(
    "Textures/Projetil.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );
  if(projetilAtual.esqueleto.texturaGl == 0)
    printf("Erro projetil %s\n", SOIL_last_result());
  projetilAtual.esqueleto.w = TAMANHO_PROJETIL[0];
  projetilAtual.esqueleto.h = TAMANHO_PROJETIL[1];
  projetilAtual.t=0;
  desenhaMovimentoProjetil();
}

void desenhaMovimentoProjetil(){
  glutPostRedisplay();
  if(colisaoProjetil() == 0)
    glutTimerFunc(20,setaPosProj,0);
  else
    projetilAtual.movimento = 0;
}

void mudaVento(){
  srand(time(NULL));
  float auxiliar = VENTO;
  while(VENTO == auxiliar){
    auxiliar = (float)(rand()%((2*MAXVENTO)*10))/10;//randomiza valores de 0 -> max
    auxiliar-=MAXVENTO;//faz o gerado variar de -MAX -> + MAX
  }
  VENTO = auxiliar;
}