#ifndef __LISTA_H
#define __LISTA_H

typedef void* No;
typedef void* Lista;
typedef void* Info;
typedef void* Posic;


/*
 *Cria o primeiro termo da lista
 *Não requer nada
 *retorna o primeiro termo e uma lista vazia
*/
Lista createList();

/*
 *Retorna o tamanho da lista
 *Requer uma lista valida
 *Retorna o tamanho da lista
*/
int getLength(Lista lista);

/*
 *Insere um novo termo ao fim da lista
 *Requer a lista na qual se vai adicionar um novo valor
 *------indefinido no momento-------
*/
Posic insertFinal(Lista lista, Info info);

/*
 *Insere um novo termo antes da posição especificado
 *Requer a lista na qual se vai adicionar um novo valor e uma posição
 *Retorna o termo inserido
*/
Posic insertBefore(Lista lista, Info info, Posic p);

/*
 *Insere um novo termo após a posição especificado
 *Requer a lista na qual se vai adicionar um novo valor e uma posição
 *Retorna o termo inserido
*/
Posic insertAfter(Lista lista, Info info, Posic p);

/*
 *imprimi a lista se ela não estiver vazia
 *Requer uma lista valida
 *Retorna nenhum valor
*/
void printLista(Lista lista);

/*
 *Remove no da lista
 *Requer uma lista e a posiçãoa ser removida
 *Retorna nenhum valor
*/
void removeNo(Lista lista, Posic position);

/*
 *Procura a posição do termo pedido
 *Requer uma termo a ser procurado e a lista a ser procurada
 *Retorna a posição do termo procurado
*/
Posic getPosic(Lista lista, char id[20]);

/*
 *Pega o ultimo termo da lista
 *Requer a lista procurada
 *Retorna o ultima termo dessa lista
*/
Posic getLast(Lista lista);

/*
 *Pega o primeiro termo da lista
 *Requer a lista procurada
 *Retorna o primeiro termo dessa lista
*/
Posic getFirst(Lista lista);

/*
 *Procura a informação na posição requisitada
 *Requer a posição na lista
 *Retorna o valor nessa posição
*/
Info getInfos(Posic p);

/*
 *Pega o proximo no da lista
 *Necessita da lista e da posição na lista
 *Retorna a proxima posição na lista
*/
Posic getNext(Lista lista, Posic p);

/*
 *Pega o no anterior da lista
 *Necessita da lista e da posição na lista
 *Retorna a posição anterior na lista
*/
Posic getPrevious(Lista lista, Posic p);

/*
 *Apaga a lista
 *Requer a lista
 *Não devolve nenhum valor
*/
void freeList(Lista lista);

#endif