#include"svg.h"
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

//Cria e inicia um arquivo SVG
void iniciarSVG(char arq[]){
    FILE *file;

    file = fopen(arq, "w");
    if(file == NULL){
        printf("nao foi possivel abrir arquivo SVG\n");
        exit(1);        
    }
    printf("Svg inicializado com sucesso\n");
    fprintf(file, "<svg>\n");
    fclose(file);
}

//Fecha o arquivo SVG
void fecharSVG(char arq[]){
    FILE *file;

    file = fopen(arq, "a+");
    if(file == NULL){
        printf("Arquivo SVG nao foi criado\n");
        exit(1);        
    }
    fprintf(file, "\n</svg>");
    fclose(file);
}

// Função que adiciona um circulo no arquivo SVG
void criarCirculo(char arq[], double raio, double posX, double posY, char corB[], char corP[]) {
    FILE *file;
    file = fopen(arq, "a");

    if(file == NULL){
        printf("Arquivo nao conseguiu ser aberto\n");
        exit(1);
    }
    fprintf(file,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" />", posX, posY, raio, corB, corP);

    fclose(file);
}

void criarBorda(char arq[], char id[2], double height, double width, double posX, double posY){
    FILE *file;
    file = fopen(arq, "a");

    
    if(file == NULL){
        printf("Arquivo nao conseguiu ser aberto\n");
        exit(1);
    }
    //CASO O ID SEJA 2 IRA CRIAR UMA BORDA TRACEJADA
    if(strcmp(id, "-2")== 0)
        fprintf(file,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",posX,posY,width,height);
    //CASO SEJA DIFERENTE DE 2 IRA CRIAR UMA BORDA CONTINUA
    else 
        fprintf(file,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",posX,posY,width,height);

    fclose(file);
}


// Função que adiciona um retangulo no arquivo SVG
void criarRet(char arq[], double height, double width, double posX, double posY, char corB[], char corP[]){
    FILE *file;

    file = fopen(arq, "a");

    if(file == NULL){
        printf("Arquivo nao conseguiu ser aberto\n");
        exit(1);
    }

    fprintf(file, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:%s;stroke:%s\" />", posX, posY, width, height, corP, corB);

    fclose(file);
}

// Função que adiciona um texto no arquivo SVG
void adicionarTexto(char arq[], char texto[], double posX, double posY, char corB[], char corP[]){
    FILE *file;

    file = fopen(arq, "a+");

    fprintf(file, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\">%s</text>", posX, posY, corP, corB ,texto);

    fclose(file);
}

void criarLinha(char arq[], double px1, double py1, double px2, double py2, char corB[], char corP[]){
    FILE *file;

    file = fopen(arq, "a");

    if(file == NULL){
        printf("Arquivo nao conseguiu ser aberto\n");
        exit(1);
    }

    fprintf(file, "\n\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:%s; stroke-width:2\" />" , px1, py1, px2, py2, corP);

    fclose(file);
}
