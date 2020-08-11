#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"


typedef struct retangulo
{
    char id[20], corP[20], corB[20];
    double x, y, w, h, espessura;
}ItemRe;

Retangulo criaRetangulo(char id[20], char corB[20], char corP[20], double largura, double altura, double x, double y, double espessura)
{
    ItemRe *re;
    re = (ItemRe*) calloc(1, sizeof(ItemRe));
    strcpy(re->id, id);
    strcpy(re->corP, corP);
    strcpy(re->corB, corB);
    re->w = largura;
    re->h = altura;
    re->x = x;
    re->y = y;
    re->espessura = espessura;

    return re;
}

double GetRX(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->x;
}

double GetRY(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->y;
}

double GetRW(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->w;
}

double GetRH(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->h;
}

double GetREspe(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->espessura;
}

char *GetID(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->id;
}

char *GetCorP(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->corP;
}

char *GetCorB(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->corB;
}