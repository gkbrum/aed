#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowMenu( int *op ){
    printf( "\n1. Adicionar Pessoa.\n" );
    printf( "2. Remover Pessoa.\n" );
    printf( "3. Buscar Pessoa.\n" );
    printf( "4. Listar Tudo.\n" );
    printf( "5. Sair.\n" );
    printf( "\nEscolha uma opcao:" );
    scanf( "%d", op );
    while( getchar() != '\n' );
}

void *InitBuffer(){
    void *pBuffer = malloc( ( sizeof( int ) * 3 ) + ( sizeof( char ) * 200 ) );

    int *numPersons = NUM_PERSONS;
    int *size = BUFFER_SIZE;
    int *i = I;

    *numPersons = 0;
    *size = 212;
    *i = 0;

    return pBuffer;
}

void *AddPerson( void *pBuffer ){
    
    //usei macros antes do realloc por que com ponteiros estava gerando warnings

    //le o nome e email da pessoa
    printf( "\nDigite o nome:" );
    fgets( TEMP_NAME, 100, stdin );
    TEMP_NAME[ strlen( TEMP_NAME ) - 1 ] = '\0';

    printf( "\nDigite o e-mail:" );
    fgets( TEMP_EMAIL, 100, stdin );
    TEMP_EMAIL[ strlen( TEMP_EMAIL ) - 1 ] = '\0';

    //realoca o ponteiro e testa
    pBuffer = realloc( pBuffer, *( BUFFER_SIZE ) +                  //tamanho atual do buffer
    ( strlen( TEMP_NAME ) + 1 * sizeof( char ) ) +                  //espaço para a string nome
    ( strlen( TEMP_EMAIL ) + 1 * sizeof( char ) ) +                 //espaço para a string email
    sizeof( int ) );                                                //espaço para a idade

    if( pBuffer == NULL ){
        printf( "Falha ao alocar memoria." );
    }

    //inicializa ponteiros auxiliares após o realloc
    int *numPersons = NUM_PERSONS;
    char *tempName = TEMP_NAME;
    char *tempEmail = TEMP_EMAIL;
    int *size = BUFFER_SIZE;

    //atribui os dados ao espaço alocado
    char *newString = ( char * )pBuffer + *size;
    strcpy( newString, tempName );

    newString = newString + strlen( tempName ) + 1;                 //move o ponteiro para o espaço do email
    strcpy( newString, tempEmail );

    int *newAge = ( int * )( ( char * )newString + strlen( tempEmail ) + 1 );

    //le a idade da pessoa
    printf( "\nDigite a idade:" );
    scanf( "%d", newAge );
    while( getchar() != '\n' );

    //calcula o novo tamanho do buffer e atualiza no buffer
    *size = *size + strlen( tempName ) + 1 + strlen( tempEmail ) + 1 + 4;

    //incrementa o numero de pessoas
    ( *numPersons )++;

    return pBuffer;
}

void *SearchPerson( void *pBuffer ){
    
    //incializa ponteiros auxiliares
    int *numPersons = NUM_PERSONS;
    int *i = I;
    char *tempName = TEMP_NAME;
    char *current = HEAD;

    //le o nome a ser buscado
    printf("\nDigite o nome a ser procurado:");
    fgets( tempName, 100, stdin );
    tempName[ strlen( tempName ) - 1 ] = '\0';

    for( *i = 0; *i < *numPersons; (*i)++ ){
        if( strcmp( current, tempName ) == 0 ){
            return current;                                 //retorna o ponteiro para o nome que foi solicitado
        }

        //passa o ponteiro current para a posição da proxima pessoa
        current = current + strlen( current ) + 1;          //current passa a apontar para o email
        current = current + strlen( current ) + 1;          //current passa a apontar para a idade
        current = current + sizeof( int );                  //current passa a apontar para o nome da proxima pessoa
    }
    
    printf("Nao foi possivel encontrar o nome.");

    return NULL;
}

void *DeletePerson( void *pBuffer ){
    char *person = SearchPerson( pBuffer );                   //ponteiro para o nome da pessoa a ser exckuida
    void *final = ( char * )pBuffer + *( BUFFER_SIZE );
    int *aux = I;

    if( !person ) return pBuffer;

    printf( "\nTem certeza que deseja deletar essa pessoa?\n" );
    PrintPerson( person );
    printf( "\n1. Sim\n0. Nao\n" );
    scanf( "%d", aux );
    while( getchar() != '\n' );

    if( *aux != 1 ) return pBuffer;

    if( person ){                                                                   //testa se SearchPerson encontrou o nome
        char *email = person + strlen( person ) + 1;                                //ponteiro para o email
        char *nextPerson = email + strlen( email ) + 1 + sizeof( int );             //ponteiro para a proxima pessoa 

        *aux = ( int )( ( char * )final - nextPerson );                     //tamanho restante após a remoçao da pessoa

        person = memmove( person, nextPerson, *aux );                       //move o restante do buffer para cima da pessoa a ser deletada

        *aux = ( int )( nextPerson - person );                              //tamanho da pessoa deletada
        *BUFFER_SIZE = *BUFFER_SIZE - *aux;                                 //atualiza o tamanho do buffer   
        pBuffer = realloc( pBuffer, *BUFFER_SIZE );                         //remove a memoria em excesso no final do buffer

        ( *NUM_PERSONS )--;
    }

    return pBuffer;
}

void ListAll( void *pBuffer ){
    char *name = HEAD;
    
    for( *I = 0; *I < *NUM_PERSONS; (*I)++ ){
        PrintPerson( name );

        //passa o ponteiro name para a posição da proxima pessoa
        name = name + strlen( name ) + 1;          //name passa a apontar para o email
        name = name + strlen( name ) + 1;          //name passa a apontar para a idade
        name = name + sizeof( int );               //name passa a apontar para o nome da proxima pessoa
    }
}

void PrintPerson( char *name ){
    if( !name ) return;
    
    char *email = name + strlen( name ) + 1;
    int *age = ( int * )( email + strlen( email ) + 1 );
    
    printf( "\nNome: %s", name );
    printf( "\nE-mail: %s", email );
    printf( "\nIdade: %d\n", *age );
}