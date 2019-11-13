#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
const float TAMANHOARCO =0.25;//1 = 1 circulo inteiro
const int NUMEROLINHASARCO =1000;
const int RAIOARCO = 10;

float posInicialAngulo[2];
float anguloAtual;
int sentidoAngulo;//-1 = <-  e 1 = -> indica direção que o personagem esta olhando

void desenhaAngulo(){
	int lado;

	glPushMatrix();
	glTranslatef(posInicialAngulo[0],posInicialAngulo[1],0);
	//girando o angulo caso o personagem esteja olhando para a esquerda
	if(sentidoAngulo == -1){
		glRotatef(90,0,0,1);
	}
	//desenha arco
	glBegin(GL_LINE_LOOP);
		glColor3f(0,0,0);
		float a = (2*M_PI)/NUMEROLINHASARCO;
		glVertex3f(0,0, 0);
		for(lado = 0;lado <= NUMEROLINHASARCO*TAMANHOARCO;lado++){
			glVertex3f(cos(a*lado)*RAIOARCO, sin(a*lado)*RAIOARCO, 0);
		}
	glEnd(); 

	glPopMatrix();
	glPushMatrix();
	glTranslatef(posInicialAngulo[0],posInicialAngulo[1],0);
	//desenha seletor
	glBegin(GL_LINES);
		glVertex3f(cos(anguloAtual)*RAIOARCO, sin(anguloAtual)*RAIOARCO, 0);
		glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();
}

void inicializaAngulo(float xPosicaoInicial,float yPosicaoInicial,int sentido){
	posInicialAngulo[0] = xPosicaoInicial;
	posInicialAngulo[1] = yPosicaoInicial;
	sentidoAngulo = sentido;
	anguloAtual = (M_PI/2)+(-1*sentido*M_PI/4);
}

void moveAngulo(float xPosicaoPlayer,float yPosicaoPlayer,int sentido){
	posInicialAngulo[0] = xPosicaoPlayer;
	posInicialAngulo[1] = yPosicaoPlayer;
	if(sentidoAngulo != sentido){
		anguloAtual = M_PI - anguloAtual;
		sentidoAngulo = sentido;
	}
}

/*direcao:
*	1 = aumentando;(subindo)
* -1 = diminuindo;(descendo)
*/
void mudaAngulo(int direcao){
	if(sentidoAngulo == 1){
		if(direcao == 1){
			if(anguloAtual < M_PI/2){
				anguloAtual+=0.1;
			}
		}else{
			if(anguloAtual > 0){
				anguloAtual-=0.1;
			}
		}
	}else{
		if(direcao == 1){
			if(anguloAtual > M_PI/2){
				anguloAtual-=0.1;
			}
		}else{
			if(anguloAtual < M_PI){
			anguloAtual+=0.1;
			}
		}
	}	
}