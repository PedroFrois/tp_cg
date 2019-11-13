#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
const int FORCAATUALINICIAL = 0;

void desenhaMovimentoBarra();

typedef struct barraForca{
  int forcaMaxima;
  int forcaSubindo;
  float forcaAtual;
  int forcaFixa;
  float x;
  float y;
  float w;
  float h;
  float cor[3];
  float corSeletor[3];
}barraForca;

barraForca barra ;

void inicializaForca(int x,int y,int w, int h,int forcaMaxima){
  barra.forcaMaxima = forcaMaxima;
  barra.forcaSubindo = 0;
  barra.forcaFixa=0;
  barra.forcaAtual = FORCAATUALINICIAL;
  barra.x = x;
  barra.y = y;
  barra.h = h;
  barra.w = w;
  barra.cor[0] = 0;
  barra.cor[1] = 1;
  barra.cor[2] = 0;
  barra.corSeletor[0] = 1;
  barra.corSeletor[1] = 1;
  barra.corSeletor[2] = 1;
}

void desenhaBarraForca(){
  //desenhaBarra
  glColor3fv(barra.cor);
  glPushMatrix();
  glTranslatef(barra.x,barra.y,0);

  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    glVertex3f(0,barra.h,0);
    glVertex3f(barra.w,barra.h,0);
    glVertex3f(barra.w,0,0);
  glEnd();
  //desenhaContorno
  glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(0,barra.h,0);
    glVertex3f(barra.w,barra.h,0);
    glVertex3f(barra.w,0,0);
  glEnd();
  //desenhaSeletor
  float xSeletor = barra.forcaAtual * barra.w/barra.forcaMaxima;
  glColor3fv(barra.corSeletor);
  glBegin(GL_LINE_LOOP);
    glVertex3f(xSeletor,barra.h,0);
    glVertex3f(xSeletor,0,0);
  glEnd();

  glPopMatrix();
}

void setForcaAtual(){
  if(!barra.forcaFixa){
    float velocidadeSeletor = barra.w/(5*barra.forcaMaxima);
    if(barra.forcaSubindo)
      barra.forcaAtual +=velocidadeSeletor;
    else
      barra.forcaAtual -=velocidadeSeletor;
    
    if(barra.forcaAtual >= barra.forcaMaxima)
      barra.forcaSubindo = 0;
    else if(barra.forcaAtual <= 0)
      barra.forcaSubindo = 1;

    glutTimerFunc(20,desenhaMovimentoBarra,20);
  }
}

void desenhaMovimentoBarra(){
  glutPostRedisplay();
  setForcaAtual();
}