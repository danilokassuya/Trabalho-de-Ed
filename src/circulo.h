#ifndef __CIRCULO_H
#define __CIRCULO_H


typedef void *Circulo;

/*
 *Cria uma struct do tipo circulo
 *Requer a informações que formam o circulo como id, cor, posição, etc
 *Devolve uma struct com valores definidos
*/
Circulo criaCirculo(char id[20], char corB[20], char corP[20], double raio, double x, double y, double espessura);


#endif