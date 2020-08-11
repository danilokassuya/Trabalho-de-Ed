#include "qry.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista.h"
#include "struct.h"

void colisaoRR(No *pt1, No *pt2, char txt[], char svg[], No *inicio);
double qmax(double n1, double n2);
double qmin(double n1, double n2);
int interno(double px, double py, double rx, double ry, double h, double w);
void colisaoCR(No *pt1, No *pt2, char txt[], char svg[], No *inicio);
void colisaoCC(No *pt1, No *pt2, char txt[], char svg[], No *inicio);
void internoRET(No *forma, double x, double y, char txt[] ,No *inicio);
void internoCIR(No *forma, double x, double y, char txt[] ,No *inicio);

double qmax(double n1, double n2){
    if(n1 > n2)
        return n1;
    else
        return n2;
}

double qmin(double n1, double n2){
    if(n1 < n2)
        return n1;
    else
        return n2;
}

float distancia(double x1, double y1, double x2, double y2){
    double dx = x2 - x1;
    double dy = y2 - y1;

    return sqrt((dx * dx) + (dy * dy));
}



void checar_colisao(No *pt1, No *pt2, char txt[], char svg[], No *inicio){
   
    if (pt1->par->tipo == 'c' && pt2->par->tipo == 'r') {
                colisaoCR(pt1, pt2, txt, svg, inicio);
            } else if (pt1->par->tipo == 'r' &&  pt2->par->tipo == 'c') {
                colisaoCR(pt2, pt1, txt, svg, inicio);
            } else if (pt1->par->tipo == 'c' &&  pt2->par->tipo == 'c') {
                colisaoCC(pt1, pt2, txt, svg, inicio);
            } else if (pt1->par->tipo == 'r' &&  pt2->par->tipo == 'r') {
                colisaoRR(pt1, pt2, txt, svg, inicio);
            }
}

//Ira checar se dois Retangulos irá se colidir
void colisaoRR(No *pt1, No *pt2, char txt[], char svg[], No *inicio){
    FILE *arq;
    //FILE *arqsvg;

    arq = fopen(txt, "a");
    //arqsvg = fopen(svg, "a");
    
    double x = qmin(pt1->par->posX, pt2->par->posX);
    double y = qmin(pt1->par->posY,pt2->par->posY);
    double w = qmax(pt1->par->posX+pt1->par->width, pt2->par->posX+pt2->par->width) - qmin(pt1->par->posX, pt2->par->posX);
    double h = qmax(pt1->par->posY+pt1->par->height, pt2->par->posY+pt2->par->height) - qmin(pt1->par->posY, pt2->par->posY);

    if(pt1->par->posX<pt2->par->posX+pt2->par->width && pt1->par->posX+pt1->par->width>pt2->par->posX && pt1->par->posY<pt2->par->posY+pt2->par->height && pt1->par->posY+pt1->par->height>pt2->par->posY){
        fprintf(arq, "o? %s %s\nSIM\n", pt1->par->id, pt2->par->id);
        //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,w,h);
        //BORDA PRETA 00001
        inicio = inserir(inicio, "-1", 0, x, y, h, w, "none", "black", 'b', NULL);

    }else{
        fprintf(arq, "o? %s %s\nNAO\n", pt1->par->id, pt2->par->id);
        //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,w,h);
        //BORDA TRACEJADA 00002 CODIGO
        inicio = inserir(inicio, "-2", 0, x, y, h, w, "none", "black", 'b', NULL);
        
    }
    //fclose(arqsvg);
    fclose(arq);
}
/*Ira checar se um Circulo e um  Retangulos irá se colidir
Sendo pt1 o circulo e pt2 retangulo*/
void colisaoCR(No *pt1, No *pt2, char txt[], char svg[], No *inicio){
    FILE *arq;
    //FILE *arqsvg;

    arq = fopen(txt, "a");
    //arqsvg = fopen(svg, "a");

    double x = qmin(pt2->par->posX,pt1->par->posX-pt1->par->raio);
    double y = qmin(pt2->par->posY, pt1->par->posY - pt1->par->raio);
    double wc = qmax(pt2->par->posX + pt2->par->width, pt1->par->posX + pt1->par->raio) - qmin(pt2->par->posX, pt1->par->posX - pt1->par->raio);
    double hc = qmax(pt2->par->posY + pt2->par->height, pt1->par->posY + pt1->par->raio)-qmin(pt2->par->posY, pt1->par->posY - pt1->par->raio);

    if(pt1->par->posX >= pt2->par->posX && pt1->par->posX <= pt2->par->posX + pt2->par->width && pt1->par->posY >= pt2->par->posY - pt1->par->raio && pt1->par->posY <= pt2->par->posY + pt2->par->height + pt1->par->raio){
        fprintf(arq, "o? %s %s\nSIM\n", pt1->par->id, pt2->par->id);
        
        //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
        inicio = inserir(inicio, "-1", 0, x, y, hc, wc, "none", "black", 'b', NULL);

    } else if(pt1->par->posY >= pt2->par->posY && pt1->par->posY <= pt2->par->posY + pt2->par->height && pt1->par->posX >= pt2->par->posX - pt1->par->raio && pt1->par->posX <= pt2->par->posX + pt2->par->width + pt1->par->raio) {
        fprintf(arq, "o? %s %s\nSIM\n", pt1->par->id, pt2->par->id);
        //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
        inicio = inserir(inicio, "-1", 0, x, y, hc, wc, "none", "black", 'b', NULL);

    } else if(pt1->par->posX >= pt2->par->posX - pt1->par->raio && pt1->par->posX < pt2->par->posX && pt1->par->posY >= pt2->par->posY - pt1->par->raio && pt1->par->posY < pt2->par->posY) {
        if(distancia(pt1->par->posX, pt1->par->posY, pt2->par->posX, pt2->par->posY) <= pt1->par->raio){
            fprintf(arq, "o? %s %s\nSIM\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
            inicio = inserir(inicio, "-1", 0, x, y, hc, wc, "none", "black", 'b', NULL);

        } else {
            fprintf(arq, "o? %s %s\nNAO\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"<\n\trect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
            inicio = inserir(inicio, "-2", 0, x, y, hc, wc, "none", "black", 'b', NULL);
        }
    } else if(pt1->par->posX >= pt2->par->posX - pt1->par->raio && pt1->par->posX < pt2->par->posX && pt1->par->posY > pt2->par->posY + pt2->par->height && pt1->par->posY <= pt2->par->posY + pt2->par->height + pt1->par->raio) {
        if(distancia(pt1->par->posX,pt1->par->posY,pt2->par->posX,pt2->par->posY + pt2->par->height) <= pt1->par->raio){
            fprintf(arq, "o? %s %s\nSIM\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
            inicio = inserir(inicio, "-1", 0, x, y, hc, wc, "none", "black", 'b', NULL);
        } else {
            fprintf(arq, "o? %s %s\nNAO\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
            inicio = inserir(inicio, "-2", 0, x, y, hc, wc, "none", "black", 'b', NULL);
        }
    } else if(pt1->par->posX > pt2->par->posX + pt2->par->width && pt1->par->posX <= pt2->par->posX + pt2->par->width + pt1->par->raio && pt1->par->posY >= pt2->par->posY - pt1->par->raio && pt1->par->posY < pt2->par->posY) {
        if(distancia(pt1->par->posX,pt1->par->posY,pt2->par->posX + pt2->par->width, pt2->par->posY) <= pt1->par->raio){
            fprintf(arq, "o? %s %s\nSIM\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
            inicio = inserir(inicio, "-1", 0, x, y, hc, wc, "none", "black", 'b', NULL);

        } else {
            fprintf(arq, "o? %s %s\nNAO\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
            inicio = inserir(inicio, "-2", 0, x, y, hc, wc, "none", "black", 'b', NULL);

        }
    } else if(pt1->par->posX > pt2->par->posX + pt2->par->width && pt1->par->posX <= pt2->par->posX + pt2->par->width + pt1->par->raio && pt1->par->posY > pt2->par->posY + pt2->par->height && pt1->par->posY <= pt2->par->posY + pt2->par->height + pt1->par->raio) {                             
        if(distancia(pt1->par->posX,pt1->par->posY,pt2->par->posX + pt2->par->width, pt2->par->posY + pt2->par->height) <= pt1->par->raio){
            fprintf(arq, "o? %s %s\nSIM\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
            inicio = inserir(inicio, "-1", 0, x, y, hc, wc, "none", "black", 'b', NULL);

        } else {
            fprintf(arq, "o? %s %s\nNAO\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
            inicio = inserir(inicio, "-2", 0, x, y, hc, wc, "none", "black", 'b', NULL);

        }
    } else {
            fprintf(arq, "o? %s %s\nNAO\n", pt1->par->id, pt2->par->id);
            //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,pt2->par->width, pt2->par->height);
            inicio = inserir(inicio, "-2", 0, x, y, hc, wc, "none", "black", 'b', NULL);
    }

    fclose(arq);
    //fclose(arqsvg);
}
/*Ira checar a colisao entre 2 cirulos*/
void colisaoCC(No *pt1, No *pt2, char txt[], char svg[], No *inicio){
    FILE *arq;
    //FILE *arqsvg;

    arq = fopen(txt, "a");
    //arqsvg = fopen(svg, "a");

    double x = qmin(pt1->par->posX, pt2->par->posX)- qmax(pt1->par->raio, pt2->par->raio);
    double y = qmin(pt1->par->posY, pt2->par->posY) - qmax(pt1->par->raio, pt2->par->raio);
    double w = qmax(pt1->par->posX, pt2->par->posX) - qmin(pt1->par->posX, pt2->par->posX) + pt1->par->raio + pt2->par->raio;
    double h = qmax(pt1->par->posY, pt2->par->posY) - qmin(pt1->par->posY, pt2->par->posY) + pt1->par->raio + pt2->par->raio;
   
    if(distancia(pt1->par->posX, pt1->par->posY, pt2->par->posX, pt2->par->posY) <= pt1->par->raio + pt2->par->raio){
        fprintf(arq, "o? %s %s\nSIM\n", pt1->par->id, pt2->par->id);
        //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,w,h);
        inicio = inserir(inicio, "-1", 0, x, y, h, w, "none", "black", 'b', NULL);

    } else {
        fprintf(arq, "o? %s %s\nNAO\n", pt1->par->id, pt2->par->id);
        //fprintf(arqsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,w,h);
        inicio = inserir(inicio, "-2", 0, x, y, h, w, "none", "black", 'b', NULL);

    }

    fclose(arq);
    //fclose(arqsvg);
}

void internoVEF(No *forma, double x, double y, char txt[] ,No *inicio){
    
    if(forma->par->tipo == 'r'){
        internoRET(forma, x, y, txt ,inicio);

    } else if(forma->par->tipo == 'c'){
        internoCIR(forma, x, y, txt, inicio);
        
    }
}

void internoRET(No *forma, double x, double y, char txt[] ,No *inicio){
    FILE *arq;
    arq = fopen(txt, "a");
    double posX = forma->par->posX;
    double posY = forma->par->posY;
    double width = forma->par->width;
    double height = forma->par->height;
    double centroX = (width / 2) + posX;
    double centroY = (height / 2) + posY;

    if(posX> x && x < posX + width && y > posY && y < posY + height){
        //insere o circulo dentro do Retangulo
        inicio = inserir(inicio, "0", 4, x, y, 0, 0, "blue", "blue", 'c', NULL);
        //insere no txt o comando
        fprintf(arq, "i? %s %lf %lf\nSIM\n", forma->par->id, x, y);

    } else {
        //insere a linha 
        inicio = inserir(inicio, "0", 0, centroX, centroY, y, x, "magenta", "magenta", 'l', NULL);
        //insere o circulo
        inicio = inserir(inicio, "0", 4, x, y, 0, 0, "magenta", "magenta", 'c', NULL);
        // Insere no txt o comando
        fprintf(arq, "i? %s %lf %lf\nNAO\n", forma->par->id, x, y );
    }

    fclose(arq);
}

void internoCIR(No *forma, double x, double y, char txt[] ,No *inicio){
    FILE *arq;

    arq = fopen(txt, "a");
    double posX = forma->par->posX;
    double posY = forma->par->posY;
    double raio = forma->par->raio;

    if(x > posX - raio && x < posX + raio  && y > posY - raio && y < posY + raio){
        inicio = inserir(inicio, "0", 4, x, y, 0, 0, "blue", "blue", 'p', NULL);
        fprintf(arq, "i? %s %lf %lf\nSIM\n", forma->par->id, x, y);

    } else {
        //insere a linha 
        inicio = inserir(inicio, "0", 0, posX, posY, y, x, "magenta", "magenta", 'l', NULL);
        //insere o circulo
        inicio = inserir(inicio, "0", 4, x, y, 0, 0, "magenta", "magenta", 'c', NULL);
        // Insere no txt o comando
        fprintf(arq, "i? %s %lf %lf\nNAO\n", forma->par->id, x, y );
    }

    fclose(arq);

}

void mudarCor(No *forma, char bord[], char cor[], char txt[]){
    FILE *arq;

    arq = fopen(txt, "a");

    if(arq == NULL){
        printf("nao foi possivel abrir arquivo TXT\n");
        exit(1);        
    }
   
        fprintf(arq, "pnt %s %lf %lf.\n", forma->par->id, forma->par->posX, forma->par->posY);
  
    strcpy(forma->par->corB, bord);
    strcpy(forma->par->corP, cor);
    fclose(arq);

}
//Repeti a mesma funçãos, pois por algum motivo quando fazia o pnt e pnt* na mesma função o programa crashava
//Caso não consiga arrumar deixar assim c:
void mudarCores(No *forma, char bord[], char cor[], char txt[]){
    FILE *arq;

    arq = fopen(txt, "a");

    if(arq == NULL){
        printf("nao foi possivel abrir arquivo TXT\n");
        exit(1);        
    }
     
        fprintf(arq, "pnt* %s %lf %lf.\n", forma->par->id, forma->par->posX, forma->par->posY);
    
    strcpy(forma->par->corB, bord);
    strcpy(forma->par->corP, cor);
    fclose(arq);

}

void removerForma(No *forma, char txt[]){
    FILE *arq;
    arq = fopen(txt, "a");
    if(arq == NULL){
        printf("nao foi possivel abrir arquivo TXT\n");
        exit(1);        
    }

    if(forma->par->tipo == 'c'){

        fprintf(arq, "delf %c %s %lf %lf %lf %s %s.\n",
    forma->par->tipo,
    forma->par->id,  
    forma->par->raio,
    forma->par->posX,
    forma->par->posY,
    forma->par->corB, forma->par->corP);

    }else if(forma->par->tipo == 'r'){
        fprintf(arq, "delf %c %s %lf %lf %lf %lf %s %s.\n",
    forma->par->tipo,
    forma->par->id,    
    forma->par->width,
    forma->par->height,
    forma->par->posX,
    forma->par->posY,
    forma->par->corB, 
    forma->par->corP);

    } else if(forma->par->tipo == 't'){
        fprintf(arq, "pnt %c %s %lf %lf %s %s\n\t%s.\n",
        forma->par->tipo,
        forma->par->id,
        forma->par->posX,
        forma->par->posY,
        forma->par->corB, 
        forma->par->corP, forma->par->texto);
    }
    forma->par->tipo = 'z';
    fclose(arq);
}

void removerFormas(No *forma, char txt[]){
    FILE *arq;
    arq = fopen(txt, "a");
    if(arq == NULL){
        printf("nao foi possivel abrir arquivo TXT\n");
        exit(1);        
    }

    if(forma->par->tipo == 'c'){

        fprintf(arq, "delf* %c %s %lf %lf %lf %s %s.\n",
    forma->par->tipo,
    forma->par->id,  
    forma->par->raio,
    forma->par->posX,
    forma->par->posY,
    forma->par->corB, forma->par->corP);

    }else if(forma->par->tipo == 'r'){
        fprintf(arq, "delf* %c %s %lf %lf %lf %lf %s %s.\n",
    forma->par->tipo,
    forma->par->id,    
    forma->par->width,
    forma->par->height,
    forma->par->posX,
    forma->par->posY,
    forma->par->corB, 
    forma->par->corP);

    } else if(forma->par->tipo == 't'){
        fprintf(arq, "delf* %c %s %lf %lf %s %s\n\t%s.\n",
        forma->par->tipo,
        forma->par->id,
        forma->par->posX,
        forma->par->posY,
        forma->par->corB, 
        forma->par->corP, forma->par->texto);
    }
    forma->par->tipo = 'z';
    fclose(arq);
}