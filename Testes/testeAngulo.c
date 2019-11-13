
#include "testeBarra.c"

void desenhaArco(){
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

void limpaSeletorAngulo(){
  glColor3f(1,1,1);
  glBegin(GL_LINES);
    glVertex3f(cos(angulo)*10+40, sin(angulo)*10+40, 0);
    glVertex3f(40, 40, 0);
  glEnd();
}

void desenhaAngulo(){
  desenhaArco();
  desenhaSeletorAngulo();
  glFlush();
}

/*
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
*/