#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "lista.h"
#include <math.h>
#include "legeo.h"


//INICIALIZAÇÃO DAS FUNÇÕES 
char *tratarDir(char arg[]);
char *tratarBar(char arg[]);
char* vefponto(char p[]);
char* vefpontobarra(char p[]);
char* ini_tratarBar(char * p);

int main( int argc, char *argv[] ) {

    int i = 1;

    No *ini;
    ini = iniciar();

    //Inicialização dos ponteiros
    char *dirBaseENT = NULL; char *SVG = NULL;
    char *desCid = NULL; char *arqConsul = NULL;
    char *consu = NULL; char *arqGeo = NULL;
    char *dirSaida = NULL; char *preGeo = NULL;
    char *preQRY = NULL; char *preArq = NULL;

    //Inicia o tratamento e a leitura dos parametros do Argv
     printf("==============LENDO ARGUMENTOS============\n");
    while (i<argc){ 
        //Tratamento do comando -E 
        if (strcmp("-e", argv[i]) == 0) { 
            i++;   
            if(argv[i] == NULL){
                printf("\nFALHA! Nenhum diretório-base foi adicionado ao parametro -E\n");

            }
            dirBaseENT = (char *) malloc((strlen(argv[i]) + 3 )* sizeof(char));
            //Copia o ArgV para um ponteiro
            strcpy(dirBaseENT, argv[i]);
        }
        //Tratamento do comando -F
        else if (strcmp("-f", argv[i]) == 0) { 
            i++;
            if(argv[i] == NULL){
                printf("\nFALHA! Parametro foi adicionado parametros apos o -F\n");
                exit(1);
            }
            desCid = (char *) malloc((strlen(argv[i]) +1 )* sizeof(char));
            //Copia o ArgV para um ponteiro
            strcpy(desCid, argv[i]);
        }
        //Tratamento do comando -O
        else if (strcmp("-o",argv[i])==0){ 
            i++;
            if (argv[i] == NULL){
                printf("\n!Erro! Sem parametros em -o");
                exit(1);
            }

            dirSaida = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(dirSaida,argv[i]);
            //Copia o ArgV para um ponteiro
            dirSaida =tratarBar(dirSaida);
        }
        //Tratamento do parametro -Qs
       else if (strcmp("-q", argv[i]) ==0) {
           i++;
            if (argv[i] == NULL){ 
                printf("\n!Erro! Sem parametros em -q");
            }
            consu = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            //Copia o ArgV para um ponteiro
            strcpy(consu,argv[i]);
       }
        i++;   
    }
     printf("Consul = %s\nDirBaseEnt = %s\ndirSaida = %s\ndesCid= %s\n", consu, dirBaseENT, dirSaida, desCid);
     printf("==============FIM ARGUMENTOS============\n");

    // CONCATENAÇÃO DOS ARGUMENTOS '-e' e '-f'
    if (dirBaseENT != NULL){
        printf("Preparando o -e :\nANTES: dirBaseENT=%s\ndesCID %s\n", dirBaseENT, desCid);
        dirBaseENT = tratarBar(dirBaseENT);
        desCid = ini_tratarBar(desCid);
 
        arqGeo = (char *) malloc((strlen(desCid) + strlen(dirBaseENT) + 9) * sizeof(char));

        dirBaseENT = vefpontobarra(dirBaseENT);
        sprintf(arqGeo,"%s/%s", dirBaseENT, desCid);
        
        //printf("Arqgeo %s\n", arqGeo);
        //printf("Arqgeo aftervefPONTO %s\n", arqGeo);

        //Verifica se houve arquivo de consulta
        if (consu !=NULL){
            arqConsul = (char *) malloc((strlen(consu) + strlen(dirBaseENT) + 2) * sizeof(char));
            consu = ini_tratarBar(consu);
            sprintf(arqConsul, "%s/%s", dirBaseENT, consu);
        }

    } else {
        arqGeo = (char *) malloc((strlen(desCid) + 4)*sizeof(char));
        sprintf(arqGeo,desCid);

        if(consu!=NULL){ // ESSE IF TIROU OUTRO ERRO
            arqConsul = (char *)malloc((strlen(consu)+1)* sizeof(char));
            strcpy(arqConsul, consu);
        }
       
    }
    
    //printf("antes do vefpontobarra %s\n", dirSaida );
    dirSaida = vefpontobarra(dirSaida);
    //printf("dps do vefpontobarra %s\n", dirSaida );
    printf("==-=-=-=-=-PREP=-=-=-=-==-\n"); 
    preGeo = (char *) malloc((strlen(desCid)+1)*sizeof(char));
    printf("preGeo1 = %s\n", preGeo);
    preGeo = tratarDir(desCid);
    printf("preGeo2 = %s\n", preGeo);


    // Inicia a leitura do Arquivo SVG
    printf("dirSaida = %s\n", dirSaida);
    SVG = (char *) malloc((strlen(dirSaida)+ strlen(preGeo)+8)* sizeof(char)); 

    printf("dirsaidantesSVG = %s\n", dirSaida);
    sprintf(SVG, "%s/%s.svg", dirSaida, preGeo);
    
    //printf("SVG = %s\n", SVG);
    
    //SVG = ini_tratarBar(SVG);

    /*CASO QUEIRA TESTAR O ARQUIVO NO WINDOWS COMENTE A LINHA DE CIMA E DESCOMENTE A DE BAIXO*/
    //sprintf(SVG, ".%s.svg", preGeo);
    
    
    printf("SVG = %s\n", SVG);

    
    
    printf("\n---------GEO Inicializado------------\n");
        ini = lerGeo(arqGeo, ini, SVG);
    printf("\n---------GEO Finalizado  ------------\n");

    //inicia a leitura do arquivo QRY
    
    if(consu!=NULL){ //ESSE IF TIROU O ERRO
            preQRY = (char *) malloc((strlen(consu)+1)*sizeof(char));
            preQRY = tratarDir(consu);
        }
    if(preQRY!= NULL){

        preArq = (char *) malloc((strlen(SVG)+strlen(preQRY)+6)*sizeof(char));
        sprintf(preArq, "%s/%s-%s", dirSaida, preGeo, preQRY);

        //printf("preaqr = %s\n", preArq);

        printf("\n---------QRY Inicializado------------\n");
            arqConsul = vefpontobarra(arqConsul);
            //printf("%s\n", arqConsul);
            ini = leiaQry(preArq, arqConsul, ini);
        printf("\n---------QRY Finalizado  ------------\n");
    } 
    else 
        printf("Nao houve arquivo QRY\n");


    //Finaliza memorias abertas
    desalocar(ini);
    printf("Lista desalocada\n");

    free(preArq);
    free(dirBaseENT); 
    free(SVG);
    free(desCid); 
    free(arqConsul);
    free(consu);
    free(arqGeo);
    free(dirSaida);
    free(preQRY);
    free(preGeo);
    printf("Ponteiros finalizados\n");

    printf("========= Programa finalizado ========\n");

    return 0;
}

char* tratarBar(char * p)
{
    char* pDest = (char*) malloc((strlen(p)+1) * sizeof(char)) ;
    int tam = strlen(p);
    int i;
    for(i =0; i<tam; i++){
        if(i== tam-1 && p[tam-1]== '/')
            continue;
        else pDest[i] = p[i];
    }
    pDest[i] = '\0';
    return pDest;
}

char* vefponto(char p[])
{
    char* pDest = (char*) malloc((strlen(p)+3) * sizeof(char)) ;
    int tam = strlen(p);
    int i;
    if (p[0] != '.'){
        pDest[0] = '.';
        for(i =1; i<=tam; i++){
            pDest[i] = p[i-1];
        }
        pDest[i] = '\0';
        return pDest;
    }
    else 
         return p;
}

char *tratarDir(char arg[]){ //funcao que trata o 
    int i, tam = strlen(arg); 
    int x, y;

    char caraceter; 
    char *pref;

    for(i = tam; i>=0; i--){
        caraceter = arg[i];
        if(caraceter=='/'){
            y = tam - i;
            pref = (char*) malloc(y*sizeof(char));
            for(x=0; x<=y;x++){
                pref[x] = arg[i+1];
                i++;
            }
            return strtok(pref, ".");
        }
    }
     return strtok(arg, ".");
}

char* ini_tratarBar(char * p)
{
    char* pDest = (char*) malloc((strlen(p)+1) * sizeof(char)) ;
    int tam = strlen(p);
    int i, j=0;
    for(i =0; i<tam; i++){
        if(i== 0 && p[0]== '/'){
            continue;
        }
        if(i==0 && p[0]=='.'){
            if(i== 0 && p[1]== '/')
                i++;
            continue;
        }
        else { pDest[j] = p[i];
            j++;
        }
    }
    pDest[j] = '\0';
    return pDest;
}

char* vefpontobarra(char p[])
{
  char* pDest = (char*) malloc((strlen(p)+8) * sizeof(char)) ;
    int tam = strlen(p);
    int i, j=0;
    if(p[0] == '.')
        return p;

    if (p[0] != '/'){
        pDest[0] = '.';
        i = 1; 
        if(p[1] != '/') {
            pDest[1] = '/';
            i = 2;
        }
        for(i; i<=tam+1; i++){
            pDest[i] = p[i-2];        
        }
        pDest[i] = '\0';
        printf("%s\n", pDest);
        return pDest;
    }
    else if (p[0] == '/'){
        pDest[0] = '.';
        pDest[1] = '/';
        i = 2; 
        for(i; i<=tam; i++){
            pDest[i] = p[i-1];
        }
        pDest[i] = '\0';
        printf("%s\n", pDest);
        return pDest;
    }


}
