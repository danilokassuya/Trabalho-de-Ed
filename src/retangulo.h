  
#ifndef __RETANGULO_H
#define __RETANGULO_H

typedef void *Retangulo;

/*
 *Cria uma struct do tipo retangulo
 *Requer a informações que formam o retangulo como medidas, cor, posição, etc
 *Devolve uma struct com valores definidos
*/
Retangulo criaRetangulo(char id[20], char corB[20], char corP[20], double largura, double altura, double x, double y, double espessura);


#endif