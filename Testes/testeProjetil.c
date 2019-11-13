#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

float forca =0;
float angulo = M_PI/2;
void desenhaMovimentoProjetil();
typedef struct projetil{
  double x;
  double y;
  double t;
  float color[3];
}projetil;

projetil p1 = {.x=0,.y=1,.t=0,.color = {0,0,0}};

/*void setaPosProj(){
  p1.x = forca*cos(angulo)*p1.t;
  p1.y = forca*sin(angulo)*p1.t - 0.5*10*p1.t*p1.t;
  p1.t += 0.02;
  desenhaMovimentoProjetil();
}*/

void setaPosProj(int tempo){
  float x = forca*cos(angulo)*p1.t;
  float y = forca*sin(angulo)*p1.t - 0.5*10*p1.t*p1.t;
  p1.t += 0.05;
  glPushMatrix();
  glTranslatef(x,y,0);
  desenhaMovimentoProjetil();
  glPopMatrix();
}

void desenhaProjetil(projetil p){
  glColor3fv(p.color);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(p.x,p.y,0);
    glVertex3f(p.x,p.y+2,0);
    glVertex3f(p.x+2,p.y+2,0);
    glVertex3f(p.x+2,p.y,0);
  glEnd();
}


void desenhaMovimentoProjetil(){
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaProjetil(p1);
  glFlush();
//  if(p1.y > 0)
    glutTimerFunc(20,setaPosProj,20);
}
