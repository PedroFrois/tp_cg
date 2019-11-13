#include "testeProjetil.c"

void desenhaBarra();

int forcaSubindo = 1;
int forcaFixa = 0;

void desenhaBarraForca(){
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0,1,0);
    glVertex3f(10,80,0);
    glVertex3f(10,85,0);
  glColor3f(1,0,0);
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
    glutTimerFunc(20,desenhaBarra,20);
  }
}

void desenhaBarra(){
  desenhaBarraForca();
  desenhaSeletorForca();
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