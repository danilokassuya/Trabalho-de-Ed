#ifndef _QRY_H
#define _QRY_H

#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<math.h>
#include "struct.h"

// Função que verifica se houve colisão entre dois objetos e insere na lista a forma resultante
void checar_colisao(No *pt1, No *pt2, char txt[], char svg[], No *inicio);

// Função que verifica se o ponto é interno e pode inserir na lista duas formas, Linha e ponto
void internoVEF(No *forma, double x, double y, char txt[] ,No *inicio);
//Muda a cor  da borda e do preenchimento de uma fora / Informar o tipo sendo 1 para o comando pnt e 2 para o comando pnt*
void mudarCor(No *forma, char bord[], char cor[], char txt[]);
void mudarCores(No *forma, char bord[], char cor[], char txt[]);
//No *mudarCor(No *forma, char bord[], char cor[], char txt[], int tipo);

//Remove o arquivo da impressao do SVG
void removerForma(No *forma, char txt[]);
//Remove os arquivo da impressao do SVG
void removerFormas(No *forma, char txt[]);
#endif 
