#ifndef _STRUCT_H
#define _STRUCT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1000

typedef struct parametros{
    char id[10]; //identificador do objeto
    double raio; //Raio do circulo
    double posX; //Posição X no plano
    double posY; //Posição Y no plano
    double height; // Altura que o obj ter[a]
    double width; // Largura que o obj terá
	char corB[20]; // Cor da borda
    char corP[20]; // Cor do preenchimento
    char tipo; // Se sera um retangulo R ou um circulo C
    char texto[MAX]; //se tiver um texto
}par;

typedef struct figura{
    struct parametros *par;
    struct figura *prox;
}No;

#endif