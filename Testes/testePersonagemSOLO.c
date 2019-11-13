#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <SOIL/SOIL.h>

GLuint texturaPersonagem;

void setup(){
  texturaPersonagem = SOIL_load_OGL_texture(
    "Stickman_P1.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );
  if (texturaPersonagem == 0) printf("Erro carregamento textura\n");
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

typedef struct personagem{
  float x;
  float y;
  float h;
  float w;
  int textura;//trocar por textura
}personagem;

personagem per1 = {0,0,5,5,{1,0,1}};
float timePulo = 0;
float xIniPulo;
float yIniPulo;
// dir =1 vai para direita
// dir =-1 vai para esquerda
void andarPersonagem(personagem* per, int direcao){
  (*per).x += 0.1*direcao;
  glutPostRedisplay();
}

void pularPersonagem(personagem* per){
  (*per).x = xIniPulo +10*cos(M_PI/4)*timePulo;
  (*per).y = yIniPulo +10*sin(M_PI/4)*timePulo - 0.5*10*timePulo*timePulo;
  timePulo += 0.02;
  if((*per).y > 0){
    glutPostRedisplay();
  }else{
    timePulo = 0;
  }
}

void desenhaPersonagem(personagem p){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texturaPersonagem);
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0); glVertex3f(p.x,p.y,0);
    glTexCoord2f(0, 1); glVertex3f(p.x,p.y+p.h,0);
    glTexCoord2f(1, 1); glVertex3f(p.x+p.w,p.y+p.h,0);
    glTexCoord2f(1, 0); glVertex3f(p.x+p.w,p.y,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void timerPulo(){
  pularPersonagem(&per1);
}

void desenhaCanvas(){
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaPersonagem(per1);
  glFlush();
  if(timePulo != 0){
    glutTimerFunc(20,timerPulo,20);
  } 
}

void redimensionar(int largura , int altura){
  glViewport(0, 0, largura, altura);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 100.0, 0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void teclaPressionada(unsigned char key , int x, int y){
  switch(key){
    case 'd':
      andarPersonagem(&per1,1);
    break;
    case 'a':
      andarPersonagem(&per1,-1);
    break;
    case ' ':
      timePulo = 0.1;
      xIniPulo = per1.x;
      yIniPulo = per1.y;
      pularPersonagem(&per1);
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
