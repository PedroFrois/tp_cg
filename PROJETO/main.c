#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "player.c"
#include "barraForca.c"
#include "angulo.c"

int pause = -1;
int reset = -1;
int sair = -1;
int morreu = -1;
int ganhador;

const float WORLDLIMITS[4] = {0,200,0,200};
enum WORLDLIMITSINDEX {menorX =0,maiorX,menorY,maiorY} limites;
void atirar();

void bloqueiaTeclaPressionada(unsigned char tecla, int x, int y){}
void inicializaAnguloPlayer(player player);
void inicializaJogo();

void desenhaVento(){
  float moduloVento = VENTO < 0? -VENTO:VENTO;

  float xMaximoSeta = (WORLDLIMITS[maiorX]- WORLDLIMITS[menorX])*0.8;
  float xMinimoSeta = (WORLDLIMITS[maiorX]- WORLDLIMITS[menorX])*0.2;
  float yInicialSeta = (WORLDLIMITS[maiorY]- WORLDLIMITS[menorY])*0.9;

  float wSeta = (xMaximoSeta - xMinimoSeta) * moduloVento/MAXVENTO;
  float hSeta = (WORLDLIMITS[maiorY]- WORLDLIMITS[menorY])*0.05;

  float xInicial = xMinimoSeta + ((xMaximoSeta - xMinimoSeta) - wSeta)/2;
  float xFinal = xMaximoSeta - ((xMaximoSeta - xMinimoSeta) - wSeta)/2;
  glColor3f(0,0,0);
  if(VENTO == 0){    
    glBegin(GL_LINE_LOOP);
      glVertex3f(xMinimoSeta,yInicialSeta,0);
      glVertex3f(xMaximoSeta,yInicialSeta,0);
    glEnd();
  }else if(VENTO < 0){
    glBegin(GL_LINE_STRIP);
      glVertex3f(xInicial,yInicialSeta,0);//.
      glVertex3f(xFinal,yInicialSeta,0);//-
      glVertex3f(xFinal - hSeta ,yInicialSeta + hSeta,0);//-
      glVertex3f(xFinal,yInicialSeta,0);//-
      glVertex3f(xFinal - hSeta ,yInicialSeta - hSeta,0);//-
    glEnd();
  }else if(VENTO > 0){
    glBegin(GL_LINE_STRIP);
      glVertex3f(xFinal,yInicialSeta,0);//-
      glVertex3f(xInicial,yInicialSeta,0);//.
      glVertex3f(xInicial + hSeta ,yInicialSeta + hSeta,0);//-
      glVertex3f(xInicial,yInicialSeta,0);//-
      glVertex3f(xInicial + hSeta ,yInicialSeta - hSeta,0);//-
    glEnd();
  }
}


void teclaPressionada(unsigned char tecla, int x, int y){
  player player;

  if(reset == 1 || sair == 1){
    switch(tecla){
      case 's':
      case 'S':
        if(sair == 1)
          exit(0);
        inicializaJogo();
        reset = -1;
        pause = -1;
      break;
      case 'n':
      case 'N':
        if(morreu == 1)
          exit(0);
        reset = -1;
        sair = -1;
        pause = -1;
        barra.forcaFixa = 0;
        setForcaAtual();
      break;
    }
  }
  else{
    if(pause == 1 && tecla != 'p'){
      tecla = '&';//tecla arbitraria para não habilitar os outros botões
    }
    switch(tecla){
      
      case ' ':
        atirar();
        glutKeyboardFunc(bloqueiaTeclaPressionada);
      break;
      
      case 'W':
      case 'w':
        mudaAngulo(1);
      break;
      
      case 'S':
      case 's':
        mudaAngulo(-1);
      break;
      
      case 'D':
      case 'd':
        movimentaPlayer(1);
        player = players[playerAtual]; 
        moveAngulo(player.esqueleto.x+(player.esqueleto.w/2),player.esqueleto.y+(player.esqueleto.h/2),player.sentido);
        glutPostRedisplay();
      break;
    
      case 'A':
      case 'a':
        movimentaPlayer(-1);
        player = players[playerAtual]; 
        moveAngulo(player.esqueleto.x+(player.esqueleto.w/2),player.esqueleto.y+(player.esqueleto.h/2),player.sentido);
        glutPostRedisplay();
      break;

      case 'P':
      case 'p':
        pause *= -1;
        barra.forcaFixa = barra.forcaFixa?0:1;
        setForcaAtual();
      break;

      case 'R':
      case 'r':
        pause = 1;
        reset = 1;
        barra.forcaFixa = 1;
      break;
      
      case 27:
        pause = 1;
        sair = 1;
        barra.forcaFixa = 1;
      break;
    }
  }
}

void printTelaPause(){
  GLuint texturaPause;
  if(reset == 1){
    if(morreu == 1){
      if(ganhador){
        texturaPause = SOIL_load_OGL_texture(
          "Textures/Vitoria Tiki.png",
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
      );//textura do tiki ricks
      }
      else{
        texturaPause = SOIL_load_OGL_texture(
          "Textures/Vitoria Relampago.png",
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
        );//textura do relampago
      }
    }
    else{
      texturaPause = SOIL_load_OGL_texture(
          "Textures/Reiniciar.png",
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
      );
    }
    //setar textura da tela de reset
  }else if(sair == 1){
    texturaPause = SOIL_load_OGL_texture(
        "Textures/Sair.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    //setar textura da tela de sair
  }else{
    texturaPause = SOIL_load_OGL_texture(
        "Textures/Paused.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    //setar textura da tela de pause
  }

  float xTela = (WORLDLIMITS[maiorX]- WORLDLIMITS[menorX])*0.2;
  float yTela = (WORLDLIMITS[maiorY]- WORLDLIMITS[menorY])*0.25;
  float wTela = (WORLDLIMITS[maiorX]- WORLDLIMITS[menorX])*0.6;
  float hTela = (WORLDLIMITS[maiorY]- WORLDLIMITS[menorY])*0.5;

  glPushMatrix();
  glTranslatef(xTela,yTela,0);
  glColor3f(1,1,1);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texturaPause);

  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(wTela,0,0);
    glTexCoord2f(1,1); glVertex3f(wTela,hTela,0);
    glTexCoord2f(0,1); glVertex3f(0,hTela,0);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);

  glPopMatrix();
}


void desenhaCanvas(){
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaSolo();
  desenhaBarraForca();
  desenhaMarcadoresVida();
  desenhaVento();
  desenhaPlayers();
  desenhaAngulo(); 
  desenhaProjetil();
  if(pause == 1){
    printTelaPause();
  }
  glFlush();
}


void setup(){
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void redimensionar(int largura , int altura){
  glViewport(0, 0, largura, altura);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(WORLDLIMITS[menorX],WORLDLIMITS[maiorX],WORLDLIMITS[menorY],WORLDLIMITS[maiorY], -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void setNumBlocosSolo(){
  NUMEROBLOCOSSOLO = (WORLDLIMITS[maiorX] - WORLDLIMITS[menorX])/TAMANHOBLOCO[0];
}

float geraSolo(int modo,int posicaoSolo){
  float xParabola;
  float raizParabola;
  switch(modo){
    case 0://solo liso
      return TAMANHOBLOCO[1]*2;
    break;
    case 1://escadinha subindo
      return posicaoSolo*TAMANHOBLOCO[1];
    break;
    case 2://escadinha descendo
      return (NUMEROBLOCOSSOLO - posicaoSolo)*TAMANHOBLOCO[1];
    break;
    case 3://parabola para cima
      xParabola = posicaoSolo*TAMANHOBLOCO[0];
      raizParabola= ((WORLDLIMITS[menorX] + WORLDLIMITS[maiorX])/2);

      return pow(xParabola-raizParabola,2)/raizParabola;
    break;
    case 4://parabola para cima
      xParabola = posicaoSolo*TAMANHOBLOCO[0];
      raizParabola= ((WORLDLIMITS[menorX] + WORLDLIMITS[maiorX])/2);

      return -pow(xParabola-raizParabola,2)/raizParabola + raizParabola;
    break;
    default://cenario aleatorio
      srand(time(NULL)*posicaoSolo);
      return rand() % (int)((WORLDLIMITS[menorY] + WORLDLIMITS[maiorY])/2) ;

    break;
  }
}

void atirar(){
  barra.forcaFixa = 1;
  lancaProjetil(barra.forcaAtual,anguloAtual);
  
}

void inicializaAnguloPlayer(player player){
  inicializaAngulo(player.esqueleto.x+(player.esqueleto.w/2),player.esqueleto.y+(player.esqueleto.h/2),player.sentido);
}

void setAnguloForca(){
  float xBarra = (WORLDLIMITS[maiorX]- WORLDLIMITS[menorX])*0.2;
  float yBarra = (WORLDLIMITS[maiorY]- WORLDLIMITS[menorY])*0.8;
  float wBarra = (WORLDLIMITS[maiorX]- WORLDLIMITS[menorX])*0.6;
  float hBarra = (WORLDLIMITS[maiorX]- WORLDLIMITS[menorX])*0.05; 
  float forcaMaxima = (WORLDLIMITS[maiorX]- WORLDLIMITS[menorX])*0.25; 
  inicializaForca(xBarra,yBarra,wBarra,hBarra,forcaMaxima);
  setForcaAtual();
  inicializaAnguloPlayer(players[playerAtual]);
}

void mudaTurno(){
  togglePlayerAtual();
  setAnguloForca();
  glutKeyboardFunc(teclaPressionada);
  mudaVento();
}

void colisaoProjetilSolo(int posicaoBloco){
  solo[posicaoBloco].esqueleto.h -= TAMANHOBLOCO[1];
  if((int)(players[0].esqueleto.x/TAMANHOBLOCO[0]) == posicaoBloco)
    players[0].esqueleto.y -= TAMANHOBLOCO[1];
  if((int)(players[1].esqueleto.x/TAMANHOBLOCO[0]) == posicaoBloco)
    players[1].esqueleto.y -= TAMANHOBLOCO[1];

}

int colisaoProjetil(){
  int alvo;
  int colisao=0;
  if(playerAtual == 0){
    alvo = 1;
  }else{
    alvo =0;
  }
  //caso o player acertou um inimigo;
  if(checaColisao(projetilAtual.esqueleto, players[alvo].esqueleto)){
    colisao = 1;
    reduzVidaPlayer(alvo);
  }else if(checaColisao(projetilAtual.esqueleto, players[playerAtual].esqueleto)){
    //caso o player se acertou
    colisao = 1;
    reduzVidaPlayer(playerAtual);
  }

  //verifica limites laterais do mundo
  else if(projetilAtual.esqueleto.x < WORLDLIMITS[menorX]){
    //excedeu os limites do mundo para a esquerda
    colisao = 1;
  }else if(projetilAtual.esqueleto.x + projetilAtual.esqueleto.w > WORLDLIMITS[maiorX]){
    //excedeu os limites do mundo para a direita
    colisao = 1;
  }

  // verifica limites superiores e inferiores do mundo
  else if(projetilAtual.esqueleto.y < WORLDLIMITS[menorY]){
    //excedeu os limites do mundo para BAIXO
    colisao = 1;
  }
  /*
  else if(projetilAtual.esqueleto.y + projetilAtual.esqueleto.h > WORLDLIMITS[maiorY]){
    //excedeu os limites do mundo para aCIMA
    colisao = 1;
  }
  */

  else{
    //colisao com o solo
    int i;
    for(i = 0; i <= NUMEROBLOCOSSOLO;i++){
      if(checaColisao(projetilAtual.esqueleto,solo[i].esqueleto)){
        colisaoProjetilSolo(i);
        colisao = 1;
      }
    }
  }

  if(colisao){
    mudaTurno();
  }

  return colisao;
}

void mortePlayer(int playerMorto){
  reset = 1;
  pause = 1;
  morreu = 1;
  ganhador = playerMorto?0:1;
}

int colisaoPlayer(){
  int outroPlayer;
  int colisao=0;
  if(playerAtual == 0){
    outroPlayer = 1;
  }else{
    outroPlayer =0;
  }
  //caso o player colidiu com um inimigo;
  if(checaColisao(players[playerAtual].esqueleto, players[outroPlayer].esqueleto)){
    colisao = 1;
  }

  //verifica limites laterais do mundo
  else if(players[playerAtual].esqueleto.x < WORLDLIMITS[menorX]){
    //excedeu os limites do mundo para a esquerda
    colisao = 1;
  }else if(players[playerAtual].esqueleto.x + players[playerAtual].esqueleto.w > WORLDLIMITS[maiorX]){
    //excedeu os limites do mundo para a direita
    colisao = 1;
  }

  // verifica limites superiores e inferiores do mundo
  else if(players[playerAtual].esqueleto.y < WORLDLIMITS[menorY]){
    //excedeu os limites do mundo para baixo
    colisao = 1;
  }
  
  else if(players[playerAtual].esqueleto.y + players[playerAtual].esqueleto.h > WORLDLIMITS[maiorY]){
    //excedeu os limites do mundo para cima
    colisao = 1;
  }
  

  else{
    //colisao com o solo
    int i;
    for(i = 0; i <= NUMEROBLOCOSSOLO;i++){
      if(players[playerAtual].esqueleto.y != solo[i].esqueleto.y + solo[i].esqueleto.h){//teste para não verificar com o solo logo abaixo do player
        if(checaColisao(players[playerAtual].esqueleto,solo[i].esqueleto))
          colisao = 1;
      }
    }
  }
  return colisao;
}

void inicializaJogo(){
  glClearColor(0, 0, 0, 0);

  inicializaSolo();
  inicializaPlayers(0.1*NUMEROBLOCOSSOLO, 0.9*NUMEROBLOCOSSOLO);

  float larguraMundo =  WORLDLIMITS[maiorX] - WORLDLIMITS[menorX];
  float alturaMundo =  WORLDLIMITS[maiorY] - WORLDLIMITS[menorY];

  float wBarra = alturaMundo*0.05;
  float hBarra = alturaMundo*0.1;
  float xBarra1 = larguraMundo*0.1;
  float yBarra1 = alturaMundo*0.6;
  float xBarra2 = larguraMundo*0.9-wBarra;
  float yBarra2 = alturaMundo*0.6;
  inicializaMarcadoresVida(xBarra1, yBarra1, xBarra2, yBarra2, wBarra, hBarra);


  setAnguloForca();

  glutDisplayFunc(desenhaCanvas);
  glutReshapeFunc(redimensionar);
  glutKeyboardFunc(teclaPressionada);

  setup();
}

int main(int argc, char** argv){

  glutInit(&argc, argv);

  glutInitContextVersion(1, 1);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(100, 100);

  glutCreateWindow("Joog Manerio dso Carors");
  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  
  inicializaJogo();

  glutMainLoop();
  return 0;
}
