#ifndef __SVG_H
#define __SVG_H

#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<math.h>


// Cria um arquvio com o nome passado por parametro e adiciona a TAG de inialização do SVG
void iniciarSVG(char arq[]);
// Finaliza o arquvio SVG e adiciona a TAG de fechamento 
void fecharSVG(char arq[]); 
// Cria um retangunlo usando os parametros de Altura, Largura, posição X, posição Y, cor da Borda e cor do preenchimento
void criarRet(char arq[], double height, double width, double posX, double posY, char corB[], char corP[]); 
// Cria um circulo usando os parametros de raio, posição X, posição Y, cor da Borda e cor do preenchimento
void criarCirculo(char arq[], double raio, double posX, double posY, char corB[], char corP[]);
// Cria um texto usando os parametros de texto e posição X e posição Y
void adicionarTexto(char arq[], char texto[], double posX, double posY, char corB[], char corP[]);
// Cria a borda que envolve 2 objetos
void criarBorda(char arq[], char id[2], double height, double width, double posX, double posY);
// Cria uma linha 
void criarLinha(char arq[], double px1, double py1, double px2, double py2, char corB[], char corP[]);

#endif