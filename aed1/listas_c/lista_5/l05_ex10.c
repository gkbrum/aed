#include <stdio.h>
#include <string.h>

void ImprimeContrario( char *palavra );

int main() {
    char palavra[100];

    printf( "Digite uma string: " );
    fgets( palavra, 100, stdin );

    ImprimeContrario( palavra );

    return 0;
}

void ImprimeContrario( char *palavra ){
    for ( int i = strlen( palavra ) ; i >= 0 ; i-- ){ 
        printf( "%c", palavra[i] );
    }
}