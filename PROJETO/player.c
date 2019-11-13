#include "projetil.c"

const int TAMANHOPLAYER = 6;//sempre quadrado

const float DISTANCIAPROJETILPLAYER = 0.1;//constante necessária para corrigir erro de colisão ao lançar projetil
const int LIMITEDEPASSOS = 15;
const int VIDAMAXIMA = 3;

typedef struct marcadoresVida{
  int vida;
  float x;
  float y;
  float h;
  float w;
}marcadoresVida;

typedef struct player{
  esqueleto esqueleto;
  int sentido;
  int passosRestantes;
  GLuint texturaNome;
  marcadoresVida vida;
}player;

player players[2];
int playerAtual =1;

int colisaoPlayer();
void mortePlayer(int playerMorto);

int reduzVidaPlayer(int indexPlayer){
  players[indexPlayer].vida.vida--;
  if(players[indexPlayer].vida.vida == 0) mortePlayer(indexPlayer);
}

void lancaProjetil(float forca,float angulo){
  float yProjetil = players[playerAtual].esqueleto.y+players[playerAtual].esqueleto.h+DISTANCIAPROJETILPLAYER;
  float xProjetil = players[playerAtual].esqueleto.x+(players[playerAtual].esqueleto.w/2) - (TAMANHO_PROJETIL[0]/2);

  setProjetilAtual(xProjetil,yProjetil,forca,angulo);
}

void togglePlayerAtual(){
  if(playerAtual == 0){
    playerAtual = 1;
  }else{
    playerAtual = 0;
  }
  players[playerAtual].passosRestantes = LIMITEDEPASSOS;
}

void inicializaPlayers(int posIniP1,int posIniP2){

  playerAtual = 0;

  esqueleto soloP1 = solo[posIniP1].esqueleto;

  esqueleto soloP2 = solo[posIniP2].esqueleto;

  //somar isso ao x do player para inicializar ele no centro do bloco
  //float centralizadorPlayer = (TAMANHOBLOCO[0]/TAMANHOPLAYER);

  players[0].esqueleto.x = posIniP1*TAMANHOBLOCO[0]; //+ centralizadorPlayer;
  players[0].esqueleto.y = soloP1.y + soloP1.h;
  players[0].esqueleto.h = TAMANHOPLAYER;
  players[0].esqueleto.w = TAMANHOPLAYER + 2;
  players[0].esqueleto.texturaGl = SOIL_load_OGL_texture(
    "Textures/Relampago.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );
  players[0].sentido = 1;
  players[0].passosRestantes = LIMITEDEPASSOS;
  players[0].texturaNome = SOIL_load_OGL_texture(
    "Textures/Nome Relampago.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  players[1].esqueleto.x = posIniP2*TAMANHOBLOCO[0];// + centralizadorPlayer;
  players[1].esqueleto.y = soloP2.y + soloP2.h;
  players[1].esqueleto.h = TAMANHOPLAYER;
  players[1].esqueleto.w = TAMANHOPLAYER + 2;
  players[1].esqueleto.texturaGl = SOIL_load_OGL_texture(
    "Textures/Tiki Riks.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );
  players[1].sentido = -1;
  players[1].passosRestantes = LIMITEDEPASSOS;
  players[1].texturaNome = SOIL_load_OGL_texture(
    "Textures/Nome Tiki.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );
}

void inicializaMarcadoresVida(float xBarra1, float yBarra1,float xBarra2, float yBarra2, float w, float h){
  players[0].vida.x = xBarra1;
  players[0].vida.y = yBarra1;
  players[0].vida.h = h;
  players[0].vida.w = w;
  players[0].vida.vida = VIDAMAXIMA;

  players[1].vida.x = xBarra2;
  players[1].vida.y = yBarra2;
  players[1].vida.h = h;
  players[1].vida.w = w;
  players[1].vida.vida = VIDAMAXIMA;

}

//sentido =  1 -> move para a direita
//sentido = -1 -> move para a esquerda
int movimentaPlayer(int sentido){
  players[playerAtual].esqueleto.x += sentido;
  int retorno =0;
  players[playerAtual].sentido = sentido;
  if(colisaoPlayer())
    players[playerAtual].esqueleto.x -= sentido;
  else{
    if(players[playerAtual].passosRestantes > 0){
      int posicaoSoloEsquerda = floor(players[playerAtual].esqueleto.x/TAMANHOBLOCO[0]);
      int posicaoSoloDireita = floor((players[playerAtual].esqueleto.x+players[playerAtual].esqueleto.w)/TAMANHOBLOCO[0]);
      
      while (players[playerAtual].esqueleto.y >= solo[posicaoSoloEsquerda].esqueleto.y + solo[posicaoSoloEsquerda].esqueleto.h+0.01 &&
      players[playerAtual].esqueleto.y >= solo[posicaoSoloDireita].esqueleto.y + solo[posicaoSoloDireita].esqueleto.h+0.01){//teste para não verificar com o solo logo abaixo do player
        players[playerAtual].esqueleto.y-=0.01;
      }
      players[playerAtual].passosRestantes--;
      glutPostRedisplay();
    }else{
      players[playerAtual].esqueleto.x -= sentido;
    }
  }
}

void desenhaPlayers(){
  desenhaEsqueleto(players[0].esqueleto);
  desenhaEsqueleto(players[1].esqueleto);
}

void desenhaMarcadoresVida(){
  //marcador player 1
  glPushMatrix();
  glTranslatef(players[0].vida.x,players[0].vida.y,0);
  //fundo
  glColor3f(0,0,0);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    glVertex3f(0,players[0].vida.h,0);
    glVertex3f(players[0].vida.w,players[0].vida.h,0);
    glVertex3f(players[0].vida.w,0,0);
  glEnd();
  //vida
  glColor3f(1,0,0);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    glVertex3f(0,players[0].vida.h*players[0].vida.vida/VIDAMAXIMA,0);
    glVertex3f(players[0].vida.w,players[0].vida.h*players[0].vida.vida/VIDAMAXIMA,0);
    glVertex3f(players[0].vida.w,0,0);
  glEnd();

  //contorno
  glColor3f(1,1,1);
  glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(0,players[0].vida.h,0);
    glVertex3f(players[0].vida.w,players[0].vida.h,0);
    glVertex3f(players[0].vida.w,0,0);
  glEnd();
  glPopMatrix();

  //nome
  glPushMatrix();
  glTranslatef(players[0].vida.x*0.5,(players[0].vida.y+players[0].vida.h),0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, players[0].texturaNome);
  glColor3f(1,1,1);
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0); glVertex3f(0,0,0);
    glTexCoord2f(0, 1); glVertex3f(0,players[0].vida.h*0.7,0);
    glTexCoord2f(1, 1); glVertex3f(3*players[0].vida.w,players[0].vida.h*0.7,0);
    glTexCoord2f(1, 0); glVertex3f(3*players[0].vida.w,0,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  //marcador player 2
  glPushMatrix();
  glTranslatef(players[1].vida.x,players[1].vida.y,0);
  //fundo
  glColor3f(0,0,0);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    glVertex3f(0,players[1].vida.h,0);
    glVertex3f(players[1].vida.w,players[1].vida.h,0);
    glVertex3f(players[1].vida.w,0,0);
  glEnd();
  //vida
  glColor3f(1,0,0);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    glVertex3f(0,players[1].vida.h*players[1].vida.vida/VIDAMAXIMA,0);
    glVertex3f(players[1].vida.w,players[1].vida.h*players[1].vida.vida/VIDAMAXIMA,0);
    glVertex3f(players[1].vida.w,0,0);
  glEnd();
  //contorno
  glColor3f(1,1,1);
  glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(0,players[1].vida.h,0);
    glVertex3f(players[1].vida.w,players[1].vida.h,0);
    glVertex3f(players[1].vida.w,0,0);
  glEnd();
  glPopMatrix();

  //nome
  glPushMatrix();
  glTranslatef(players[1].vida.x*0.94,(players[1].vida.y+players[1].vida.h),0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, players[1].texturaNome);
  glColor3f(1,1,1);
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0); glVertex3f(0,0,0);
    glTexCoord2f(0, 1); glVertex3f(0,players[1].vida.h*0.7,0);
    glTexCoord2f(1, 1); glVertex3f(3*players[1].vida.w,players[1].vida.h*0.7,0);
    glTexCoord2f(1, 0); glVertex3f(3*players[1].vida.w,0,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}