#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

typedef struct projetil{
  float x;
  float y;
  float t;
  float color[3];
}projetil;

float forca = 0;
int forcaSubindo = 1;
int forcaFixa = 0;

void desenhaBarraForca(){
  glColor3f(0,0,1);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(10,80,0);
    glVertex3f(10,85,0);
    glVertex3f(40,85,0);
    glVertex3f(40,80,0);
  glEnd();
  glColor3f(0,0,0);
  glBegin(GL_LINE_LOOP);
    glVertex3f(10,80,0);
    glVertex3f(10,85,0);
    glVertex3f(40,85,0);
    glVertex3f(40,80,0);
  glEnd();
}

void desenhaCanvas();

void desenhaSeletorForca(){
  glColor3f(1,1,1);
  glBegin(GL_LINE_LOOP);
    glVertex3f(10+forca,80,0);
    glVertex3f(10+forca,85,0);
  glEnd();
  glFlush();
  if(forcaSubindo == 1)
    forca+=0.2;
  else
    forca-=0.2;

  if(forca >= 30)
    forcaSubindo = -1;
  else if(forca <= 0)
    forcaSubindo = 1;

  if(forcaFixa == 0){
    glutTimerFunc(20,desenhaCanvas,20);
  }
}

void desenhaCanvas(){
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaBarraForca();
  desenhaSeletorForca();
  glFlush();
}

void setup(){
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void redimensionar(int largura , int altura){
  glViewport(0, 0, largura, altura);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 100.0, 0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void teclaPressionada(unsigned char key, int x, int y){
  switch(key){
    case 13:
      forcaFixa=1;
      printf("%f",forca );
    break;
    default:
    break;
  }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);

  glutInitContextVersion(1, 1);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);

  glutCreateWindow("Poligonos_Regulares");

  glutDisplayFunc(desenhaCanvas);
  glutReshapeFunc(redimensionar);
  glutKeyboardFunc(teclaPressionada);
  setup();

  glutMainLoop();
  return 0;
}