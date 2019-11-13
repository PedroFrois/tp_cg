#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "SOIL.h"

typedef struct esqueleto{
  float x;
  float y;
  float h;
  float w;
  float color[3];
  GLuint texturaGl;//0- projetil 1-p1 2-p2 3-solo
}esqueleto;

//desenha todos os objetos colidiveis. Ex: player, cenario...
void desenhaEsqueleto(esqueleto esqueleto){

  glPushMatrix();
  glTranslatef(esqueleto.x,esqueleto.y,0);

  if(esqueleto.texturaGl == 0){
    glColor3fv(esqueleto.color);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0,0,0);
      glVertex3f(0,esqueleto.h,0);
      glVertex3f(esqueleto.w,esqueleto.h,0);
      glVertex3f(esqueleto.w,0,0);
    glEnd();
  }
  else{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, esqueleto.texturaGl);
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0, 0); glVertex3f(0,0,0);
      glTexCoord2f(0, 1); glVertex3f(0,esqueleto.h,0);
      glTexCoord2f(1, 1); glVertex3f(esqueleto.w,esqueleto.h,0);
      glTexCoord2f(1, 0); glVertex3f(esqueleto.w,0,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  glPopMatrix();
}

//retorna 1 se houver colisao entre os objetos
//retorna 0 se não houver colisao entre os objetos
int checaColisao(esqueleto obj1, esqueleto obj2){
  //objeto 1 esta a direita do objeto 2
  if(obj1.x >= obj2.x+obj2.w) return 0;

  //objeto 1 esta a esquerda do objeto 2
  if(obj2.x >= obj1.x+obj1.w) return 0;

  //objeto 1 esta acima do objeto 2
  if(obj1.y >= obj2.y+obj2.h) return 0;

  //objeto 1 esta abaixo do objeto 2
  if(obj2.y >= obj1.y+obj1.h) return 0;
  return 1;
}