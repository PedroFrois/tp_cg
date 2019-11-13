#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

void setup(){
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void redimensionar(int largura , int altura){
  glViewport(0, 0, largura, altura);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void teclaPressionada(unsigned char tecla, int x, int y){
  switch(tecla){
    case 27:
      exit(0);
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
