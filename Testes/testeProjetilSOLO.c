#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <SOIL/SOIL.h>

GLuint texturaProjetil;

void setup(){
  texturaProjetil = SOIL_load_OGL_texture(
    "Stickman_P1.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );
  if (texturaProjetil == 0) printf("Erro carregamento textura\n");
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

typedef struct projetil{
  float x;
  float y;
  float t;
  float color[3];
}projetil;

projetil p1 = {.x=0,.y=1,.t=0,.color = {0,0,0}};

int v = 20;
float angulo = M_PI/3;

void setaPosProj(){
  p1.x = v*cos(angulo)*p1.t;
  p1.y = v*sin(angulo)*p1.t - 0.5*10*p1.t*p1.t;
  p1.t +=0.05;
  glutPostRedisplay();
}

void desenhaProjetil(projetil p){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texturaProjetil);
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(1, 0); glVertex3f(p.x,p.y,0);
    glTexCoord2f(1, 1); glVertex3f(p.x,p.y+10,0);
    glTexCoord2f(0, 1); glVertex3f(p.x+10,p.y+10,0);
    glTexCoord2f(0, 0); glVertex3f(p.x+10,p.y,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}


void desenhaCanvas(){
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaProjetil(p1);
  glFlush();
  if(p1.y > 0)
    glutTimerFunc(50,setaPosProj,50);
}

void redimensionar(int largura , int altura){
  glViewport(0, 0, largura, altura);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 100.0, 0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char** argv){
  glutInit(&argc, argv);

  glutInitContextVersion(1, 1);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);

  glutCreateWindow("Projetil Solo");

  setup();

  glutDisplayFunc(desenhaCanvas);
  glutReshapeFunc(redimensionar);
  //glutKeyboardFunc(teclaPressionada);
  //setup();

  glutMainLoop();
  return 0;
}
