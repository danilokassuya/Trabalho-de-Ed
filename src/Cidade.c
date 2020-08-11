#include <stdio.h>
#include <stdlib.h>
#include "cidade.h"

typedef struct  city{
    Lista listaC;
    Lista listaR;
} cidade;

Cidade criaCidade(){
    Cidade c = calloc(1, sizeof(cidade));
    cidade *city = (cidade *)c;

    city->listaC = createList();
    city->listaR = createList();
    return city;
}

void removeCidade(Cidade cid){
    cidade *city = (cidade*) cid;

    
}

int addCirculo(Cidade cid, Info info){
    cidade *city = (cidade *)cid;
    return insertFinal(city->listaC, info);
}

int addRetangulo(Cidade cid, Info info){
    cidade *city = (cidade *)cid;
    return insertFinal(city->listaR, info);
}