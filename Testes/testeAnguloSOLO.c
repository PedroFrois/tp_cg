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

float angulo = M_PI/2;

void desenhaAngulacao(){
  glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    float a = (2*M_PI)/1000;
    glVertex3f(40,40, 0);
    for(int lado = 0;lado <= 250;lado++){
      glVertex3f(cos(a*lado)*10+40, sin(a*lado)*10+40, 0);
    }
  glEnd();  
}

void desenhaSeletorAngulo(){
  glColor3f(0,0,0);
  glBegin(GL_LINES);
    glVertex3f(cos(angulo)*10+40, sin(angulo)*10+40, 0);
    glVertex3f(40, 40, 0);
  glEnd();
}

void desenhaCanvas(){
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaAngulacao();
  desenhaSeletorAngulo();
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
    break;
    case 'w':
      angulo +=0.01;
      glutPostRedisplay();
    break;
    case 's':
      angulo -=0.01;
      glutPostRedisplay();
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