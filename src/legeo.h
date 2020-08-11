#ifndef __LEGEO_H
#define __LEGEO_H

#include "struct.h"

//Le o arquivo Geo gerando um SVG e insere os elementos lido numa lista
No *lerGeo(char diretorio[], No *inicio, char svg[]);
//Le o arquivo QRY e juntamente gera um arquivo SVG e TXT com as alterações
No  *leiaQry(char prefArq[], char arq[], No *inicio);


#endif