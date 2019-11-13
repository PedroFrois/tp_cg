#include "testeAngulo.c"

void desenhaCanvas(){
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaBarra();
  desenhaAngulo();
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
      glutDisplayFunc(desenhaMovimentoProjetil);
      glutPostRedisplay();
    break;
    case 'w':
      limpaSeletorAngulo();
      angulo +=0.01;
      desenhaAngulo();
    break;
    case 's':
      limpaSeletorAngulo();
      angulo -=0.01;
      desenhaAngulo();
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