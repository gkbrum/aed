#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 30

int BuscaNome( char **lista, int tam );
char **TrocaNome( char **lista, int pos );
char **CriaLista();
char **AddNome( char **lista, int tam );
char **RemNome( char **lista, int tam, int pos );
int Menu();
void LerString( char *string );
void LimparBuffer();

int main(){
    int op, tamLista = 0, pos;
    char **lista = NULL;

    do{
        op = Menu();

        switch ( op ){
        case 1:
            printf( "\nDigite o nome a ser adicionado:" );
            lista = AddNome( lista, tamLista );
            tamLista++;
            break;
        
        case 2:
            if( tamLista == 0 ){
                printf( "\nLista vazia." );
            } else {
                printf( "\nDigite a posição do nome a ser excluido (1 ~ %d): ", tamLista );
                scanf( "%d", &pos );
                LimparBuffer();

                lista = RemNome( lista, tamLista, pos );
                tamLista--;
            }
            break;

        case 3:
            if( tamLista == 0 ){
                printf( "\nLista vazia." );
            } else {
                printf( "\nDigite a posição a ser alterada (1 ~ %d): ", tamLista );
                scanf( "%d", &pos );
                LimparBuffer();

                lista = TrocaNome( lista, pos );
            }
            break;

        case 4:
            if( tamLista == 0 ){
                printf( "\nLista vazia." );
            } else {
                printf( "\nDigite o nome a ser removido: " );
                pos = BuscaNome( lista, tamLista );
                if( pos == -1 ){
                    printf( "\nEsse nome não esta na lista. " );
                } else {
                    lista = RemNome( lista, tamLista, pos );
                    tamLista--;
                }
            }
            break;

        case 5:
            if( tamLista == 0 ){
                printf( "\nLista vazia." );
            } else {
                printf( "\nDigite a posição a ser mostrada na tela (1 ~ %d): ", tamLista );
                scanf( "%d", &pos );
                LimparBuffer();

                printf( "\n%d. %s.", pos, lista[ pos - 1 ] );
            }
            break;

        case 6:
            if( tamLista == 0 ){
                printf( "\nLista vazia." );
            } else {
                printf( "\n" );
                for( int i = 0; i < tamLista; i++ ){
                    printf( "%d. %s", i + 1, lista[ i ] );
                }
                printf( "\n" );
            } 
            break;
            
        default:
            break;
        }

    }while( op != 0 );

    return 0;
}

int BuscaNome( char **lista, int tam ){
    char nome[30];
    LerString( nome );

    for (int i = 0; i <= tam; i++){
        if ( i == tam ){
            return -1;
        } else if ( strcmp( lista[i], nome ) == 0 ){ 
            return ( i + 1 );
        }
    }
    return -1;
}

char **TrocaNome( char **lista, int pos ){
    printf( "\nDigite um novo nome para a posicao %d:", pos );
    LerString( lista[ pos - 1 ] );
    return lista;
}

char **CriaLista(){
    char **lista;

    lista = ( char ** )malloc( sizeof( char * ) );
    lista[0] = ( char * )malloc( sizeof( char ) * TAM );
    
    return lista;
}

char **AddNome( char **lista, int tam ){
    if( lista ){
        lista = ( char ** )realloc( lista, ( tam + 1 ) * sizeof( char * ) );
        lista[ tam ] = ( char * )malloc( sizeof( char ) * TAM );
        LerString( lista[ tam ] );
        
        return lista;

    } else {
        lista = CriaLista();
        LerString( lista[ tam ] );

        return lista;
    }
}

char **RemNome( char **lista, int tam, int pos ){ 

    for( int i = ( pos - 1 ); i < ( tam - 1 ); i++ ){
        strcpy( lista[ i ], lista[ i + 1 ] );
    }
    free( lista[ tam - 1 ] );

    lista = ( char ** )realloc( lista, ( tam - 1 ) * sizeof( char * ) );

    return lista;
}

int Menu(){
    int op;
    
    printf( "\n\n1. Adicionar nome.\n" );
    printf( "2. Apagar nome em linha especifica.\n" );
    printf( "3. Substituir nome.\n" );
    printf( "4. Buscar e apagar nome.\n" );
    printf( "5. Imprimir nome de linha especifica.\n" );
    printf( "6. Listar tudo.\n" );
    printf( "0. Sair.\n\n" );
    
    printf( "Escolha uma opcao: " );
    scanf( "%d", &op );
    LimparBuffer();

    return op;
}

void LerString( char *string ){
    fgets( string, TAM, stdin );
    string[ strlen( string ) ] = '\0';
}

void LimparBuffer(){
    int c;
    while ( ( c = getchar() ) != '\n' && c != EOF );
}