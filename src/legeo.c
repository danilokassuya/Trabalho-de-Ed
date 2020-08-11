#include "legeo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "cidade.h"

int nx = 1000;

Cidade leiaGeo(char diretorio[], No *inicio, char svg[]) {
    
    //Inicializa os parametros padrões de leitura
    
    double height, width, posX, posY, raio;  
    char instrucao[4]; size_t bufz = 32;
    char *frase;
    int lixo[10];
    char id[10], corB[20], corP[20];
    //printf("\nDentro dolergeo \ndiretorio=%s\nsvg=%s\n", diretorio, svg);
    FILE *geo;
    
    geo = fopen(diretorio, "r");
    Cidade cidade = criaCidade();
    //caso o arquivo não se abra
    if (geo==NULL){
        printf("FALHA ao abrir o arquivo GEO\n");
        exit(1);
    }
    printf("Arquvio GEO aberto\n");
    iniciarSVG(svg); //inicia o arquivo SVG

    int i = 0;
    
    /*Inicia a leitura do arquivo GEO*/
    while(i<nx){
        fscanf(geo, "%s", instrucao);
        if(feof(geo)){ // verifica se o arquivo chegou ao final
            printf("Arquivo cheogou ao fim\n");
            break;
            }
        
        // verifica se o comando nx foi lido na variavel instrução e modifica o numero maximo de leituras
        if(strcmp("nx", instrucao) == 0){ 
            fscanf(geo, "%d %d %d %d %d %d %d", &nx, &lixo[0],&lixo[1],&lixo[2],&lixo[3],&lixo[4],&lixo[5]);
            i++;
        } 
        else if(strcmp("c", instrucao) == 0){ 
            fscanf(geo, "%s %lf %lf %lf %s %s", id, &raio, &posX, &posY, corB, corP);
            
            Info info = criarCirculo(id, corB, corP, raio, posX, posY, 3);

            addCirculo(cidade, info);


            
            i++;
        }
    }
    //imprimir(inicio);

    printf("Todos os comandos foram lidos com sucesso!\n");

    fecharSVG(svg);
    printf("Arquivo SVG fechado\n");
    

    fclose(geo);
    printf("Arquivo Geo Fechado\n");


    return cidade;
}



/*FUNÇÃO DE LEITURA DO ARQUIVO QRY*/
/*
No *leiaQry(char prefArq[], char arq[], No *inicio){
    
    //imprimir(inicio);
    //printf("arq = %s\n", arq);
    //printf("prefArq = %s\n", prefArq);
    //printf("%d\n", nx);
    
    FILE *qry;
   

    qry = fopen(arq,"r");

    if(qry == NULL){
        printf("erro ao abrir arquivo qry!\n");
        exit(1);
    }
    printf("Arquivo qry aberto com sucesso!\n");

    No *np1, *np2;
    par *par1, *par2;

    double x, y;
    int j, k;
    char id1[10], id2[10];
    char instrucao[10];
    char suf[20];
    char cor[20];
    char bord[20];
    int tam = 0;
    int i = 0;

    char *svg = (char*) malloc((strlen(prefArq)+10)*sizeof(char));
    sprintf(svg,"%s.svg", prefArq);

    iniciarSVG(svg);

    //Cria o arquivo TXT
    char *txt = (char*) malloc((strlen(prefArq)+10)*sizeof(char));
    sprintf(txt, "%s.txt", prefArq);

    FILE *texto;
    texto = fopen(txt, "w");
    if (texto == NULL){
        printf("Erro ao criar TXT\n");
    }
    fclose(texto);


    //Le o QRY e altera os elementos da lista
    while(1)
    {
        //Le o comando há ser executado
        fscanf(qry, "%s", instrucao);
        if(feof(qry)){
            printf("Arquivo QRY chegou ao fim\n");
            break;
        }
        //Execução do comando O?
        if(strcmp("o?", instrucao)==0) {
            fscanf(qry, "%d %d", &j, &k);
            np1 = buscarInt(inicio, j);
            np2 = buscarInt(inicio, k);
            checar_colisao(np1, np2, txt, svg, inicio);
        //Execução do comando I?
        } else if (strcmp("i?",instrucao)==0) {
            fscanf(qry, "%d %lf %lf", &j, &x, &y);
            //printf("i?\n");
            np1 = buscarInt(inicio, j);
            //printf("saiu np1= %lf \n", np1->par->posX);
            if(np1 != NULL){
                internoVEF(np1, x, y, txt, inicio);    
            }
        //Execução do comando PNT
        } else if (strcmp("pnt", instrucao)==0){
            fscanf(qry, "%d %s %s", &j, bord, cor);
            np1 = buscarInt(inicio, j);
            if (np1 != NULL){
                printf("%s\n%s\n", np1->par->corB , np1->par->corP);
                mudarCor(np1, bord, cor, txt);
            }
        //Execução do comando PNT*
        } else if (strcmp("pnt*", instrucao) ==0){
            fscanf(qry,"%d %d %s %s", &j, &k, bord, cor);
            //printf("pnt*?\n");
            for( j; j<=k; j++){
                np1 = buscarInt(inicio, j);
                if(np1 != NULL){
                    mudarCores(np1, bord, cor, txt);
                }
            }
        //Execução do comando DELF
        } else if (strcmp("delf", instrucao)== 0){

            fscanf(qry, "%s", id1);
            np1 = buscar(inicio, id1);
            if(np1 != NULL){
                //printf(" np1 = %s\n", np1->par->id);
                
                removerForma(np1, txt);
            }
        //Execução do comando DELF*
        } else if(strcmp("delf*", instrucao)==0){
            //printf("delf*?\n");

            fscanf(qry, "%d %d", &j, &k);

            for( j; j<=k; j++){
                np1 = buscarInt(inicio, j);
                if(np1 != NULL){
                    removerFormas(np1 ,txt);
                }
            }
        }
    }

    //Imprime o SVG final
    No *aux;
    aux = inicio;

    //Imprime no SVG todas as formas ja modificadas pelo arquivo QRY
     while (aux != NULL)
    {
        if(aux->par->tipo == 'r'){
            criarRet(svg, aux->par->height, aux->par->width, aux->par->posX, aux->par->posY, aux->par->corB, aux->par->corP);
        } else if(aux->par->tipo == 'c'){
            criarCirculo(svg, aux->par->raio, aux->par->posX, aux->par->posY, aux->par->corB, aux->par->corP);
        } else if(aux->par->tipo == 't'){
            adicionarTexto(svg, strtok(aux->par->texto, "\n"), aux->par->posX, aux->par->posY, aux->par->corB, aux->par->corP );
        } else if(aux->par->tipo == 'b' && strcmp(aux->par->id, "-1")==0){
            criarBorda(svg, "-1", aux->par->height, aux->par->width, aux->par->posX, aux->par->posY);
        } else if(aux->par->tipo == 'b' && strcmp(aux->par->id, "-2")==0){
            criarBorda(svg, "-2", aux->par->height, aux->par->width, aux->par->posX, aux->par->posY);
        } else if(aux->par->tipo == 'l'){
            criarLinha(svg, aux->par->posX, aux->par->posY, aux->par->width, aux->par->height, aux->par->corB, aux->par->corP);
        }

        aux = aux->prox;

    }

    fecharSVG(svg);
    printf("SVG finalizado\n");

    
    free(txt);
    
    fclose(qry);
	printf("O arquivo Qry foi fechado\n");

    return inicio;
},
*/