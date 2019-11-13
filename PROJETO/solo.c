#include "esqueleto.c"
#include <time.h>
#include <stdlib.h>


const float TAMANHOBLOCO[2] = {10, 5};

int NUMEROBLOCOSSOLO;

typedef struct blocoSolo{
	esqueleto esqueleto;
}blocoSolo;

blocoSolo solo[10000];

void setNumBlocosSolo();
float geraSolo(int modo,int posicaoSolo);

void inicializaBlocoSolo(blocoSolo solo[],int posicaoSolo,int modoSolo){
	solo[posicaoSolo].esqueleto.x = posicaoSolo*TAMANHOBLOCO[0];
	solo[posicaoSolo].esqueleto.y = 0;
	solo[posicaoSolo].esqueleto.w = TAMANHOBLOCO[0];
	solo[posicaoSolo].esqueleto.h = geraSolo(modoSolo,posicaoSolo);
	solo[posicaoSolo].esqueleto.color[0] = 0.7;
	solo[posicaoSolo].esqueleto.color[1] = 0.2;
	solo[posicaoSolo].esqueleto.color[2] = 0.2;
	solo[posicaoSolo].esqueleto.texturaGl = SOIL_load_OGL_texture(
		"Textures/Solo.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
}


void inicializaSolo(){
	setNumBlocosSolo();
	int i;
	srand(time(NULL));
	int modo = rand()%6;
	for(i=0;i<NUMEROBLOCOSSOLO;i++){
		inicializaBlocoSolo(solo,i,modo);
	}
}

void desenhaSolo(){
	int i;
	for(i=0;i<NUMEROBLOCOSSOLO;i++){
		desenhaEsqueleto(solo[i].esqueleto);
	}
}