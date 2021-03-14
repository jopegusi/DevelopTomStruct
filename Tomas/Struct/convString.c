#include <stdio.h>
#include <stdlib.h>

void long2string ( long i , char *idstring )
{
    sprintf(idstring, "%010ld", i);
    //printf ("decimal: %s\n",idstring);
}

// Converte um numero inteiro numa string
// com zeros à esquerda
void int2string ( int i , char *idstring )
{
    sprintf(idstring, "%010d", i);
}

// Converte uma string com zeros à esquerda
// para numero inteiro
int string2int ( char *idstring )
{
    int num = atoi( idstring );
    return num;
}

int main ()
{
    //int i = 7;
    char buffer[200];
    //itoa(buffer, i, 10);

    int2string (311, buffer );
    printf ("decimal: %s\n",buffer);

    int i=2345289;
    int2string ( i , buffer );
    printf ("decimal: %s\n",buffer);

    long l=123456789;
    long2string ( l , buffer );
    printf ("decimal: %s\n",buffer);

    int2string ( 11 , buffer );
    printf ("decimal: %s\n",buffer);

    printf ("-----imprime direto \n");

     int num = atoi(buffer);

     printf ("decimal: %d\n",num);

    printf ("-----imprime usando funcao \n");
     num = string2int ( buffer );
     printf ("decimal: %d\n",num);

     printf ("-----teste com sprintf  \n");

    sprintf ( buffer ,  "caracteristicas.%d.txt", num );

    printf ("---teste com sprintf---- (%s)\n",buffer);



    return 0;
}
