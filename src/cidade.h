#ifndef __CIDADE_H
#define __CIDADE_H

#include "lista.h"

typedef void *Cidade;

/*
 *Cria a struct Cidade e suas listas
 *----indefinido por enquanto-----
 *Retorna uma struct cidade e suas listas
*/
Cidade criaCidade();

/*
 *Adiciona um circuloa à lista
 *Requer duas structs uma com a lista e outra com as informações validas
 *retorna a execução da função que adiciona um circulo no final da lista
*/
int addCirculo(Cidade cid, Info info);

/*
 *Apaga a struct cidade
 *Requere a struct a ser removida
 *Não retorna nenhuma informação
*/
void removeCidade(Cidade cid);

/*
 *Adiciona um retangulo à lista
 *Requer duas structs uma com a lista e outra com as informações validas
 *retorna a execução da função que adiciona um retangulo no final da lista
*/
int addRetangulo(Cidade cid, Info info);

#endif