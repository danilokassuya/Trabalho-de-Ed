#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"

typedef struct circulo {
    double r, x, y; 
    double espessura;
    char id[20], corP[20], corB[20];
} ItemC;

Circulo criaCirculo(char id[20], char corB[20], char corP[20], double raio, double x, double y, double espessura){
    ItemC *c;
    c = (ItemC *)calloc(1, sizeof(ItemC));
    strcpy(c->id, id);
    strcpy(c->corP, corP);
    strcpy(c->corB, corB);
    c->x = x;
    c->y = y;
    c->r = raio;
    c->espessura = espessura;

    return c;
}

