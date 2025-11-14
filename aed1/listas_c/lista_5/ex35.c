#include <stdio.h>
#include <string.h>

void ContarChar( char *c, char *string, int *quantidade );
void LimparBuffer();
void LerString( char *destino, int tamanho );
void TrocarPrimeiroChar( char *string, char *c1, char *c2);
void GerarSubstring( char *string1, char *string2, int *posIni, int *posFim);
int Menu();

int main() {

    int op, num1, num2;
    char string1[100], string2[100], c1, c2;

    do{
        op = Menu();

        switch ( op ) {
            case 1:
                printf( "Digite a string S1:" );
                LerString( string1, 20 );
                break;
            
            case 2:
                printf( "Tamanho da string S1: %lld\n", strlen( string1 ) );
                break;

            case 3:
                printf( "Digite a string S2:" );
                LerString( string2, 100 );

                printf( "Resultado da comparacao: %d\n", strcmp( string1, string2 ) );
                if( strcmp( string1, string2 ) == 0 ){
                    printf( "As strings sao iguais.\n" );
                } else {
                    printf( "As strings sao diferentes.\n" );
                }
                break;

            case 4:
                printf( "Digite a string S2:" );
                LerString( string2, 80 );

                printf( "Resultado da concatenacao: %s\n", strcat( string1, string2 ) );
                break;
            
            case 5:
                for ( int i = strlen( string1 ) - 1; i >= 0; i-- ){
                    printf( "%c", string1[i] );
                }
                printf( "\n" );
                break;

            case 6:
                printf( "Digite um caracter: " );
                scanf( "%c", &c1 );
                LimparBuffer();

                ContarChar( &c1, string1, &num1 );
            
                if ( num1 != 0 ){   
                    printf( "O caracter %c ocorre na string S1 %d vezes.\n", c1, num1 );
                } else {
                    printf( "O caracter %c nao ocorre na string S1.\n", c1 );
                }
                break;

            case 7:
                printf( "Digite o caracter C1: " );
                scanf( "%c", &c1 );
                LimparBuffer();
                printf( "Digite o caracter C2: " );
                scanf( "%c", &c2 );
                LimparBuffer();

                TrocarPrimeiroChar( string1, &c1, &c2 );
                break;

            case 8:
                printf( "Digite a string S2: " );
                LerString( string2 , 20 );

                if  (strstr( string1, string2 ) ){
                    printf( "A string '%s' e substring de '%s'.\n", string2, string1 );
                } else {
                    printf( "A string '%s' NAO e substring de '%s'.\n", string2, string1 );
                }
                break;

            case 9:
                printf( "Digite a posicao que a substring deve iniciar: (0 ~ 20)\n" );
                scanf( "%d", &num1 );
                LimparBuffer();

                printf( "Digite o tamanho que a substring deve ter:\n" );
                scanf( "%d", &num2 );
                LimparBuffer();

                GerarSubstring( string1, string2, &num1, &num2 );
                break;


            case 10:
                printf( "Saindo...\n" );
                break;
        
            default:
                printf( "Opcao Invalida.\n" );
        }
    } while ( op != 10 );
}

void ContarChar( char *c, char *string, int *quantidade ){
    *quantidade = 0;
    int len = strlen( string );
    
    for ( int i = 0; i < len; i++ ){
        if ( string[i] == *c ){
            (*quantidade)++;
        }
    }
}

void LimparBuffer(){
    int c;
    while ( ( c = getchar() ) != '\n' && c != EOF );
}

void LerString( char *destino, int tamanho ){
    fgets( destino, tamanho, stdin );
    destino[ strcspn( destino, "\n" ) ] = '\0';
}

void TrocarPrimeiroChar( char *string, char *c1, char *c2 ){
    char *pos = strchr( string, *c1 );
    if ( pos ){
        *pos = *c2;
        printf( "String S1 apos a substituicao: %s\n", string );

    } else {
        printf( "O caracter '%c' nao esta presente na string S1.\n", *c1 );
    }
}

void GerarSubstring( char *string1, char *string2, int *posIni, int *tamanho){
    memcpy( string2, string1 + *posIni, sizeof(char) * *tamanho );

    printf( "A substring gerada: %s", string2 );
}

int Menu() {
    int op;

    printf( "\nEscolha uma opcao:\n\n" );
    printf( "1. Inserir string S1.\n" );
    printf( "2. Imprimir tamanho de S1.\n" );
    printf( "3. Comparar string S1 com nova string.\n" );
    printf( "4. Concatenar S1 a uma nova string.\n" );
    printf( "5. Imprimir S1 ao contrario.\n" );
    printf( "6. Contar quantas vezes um caracter aparece na string S1.\n" );
    printf( "7. Substituir a primeira ocorrencia de C1 por C2 na string S1.\n" );
    printf( "8. Verificar se S2 e substring de S1.\n" );
    printf( "9. Gerar substring de S1.\n" );
    printf( "10. Sair do programa.\n\n" );

    printf( "Digite sua opcao: " );
    scanf( "%d", &op );
    LimparBuffer();

    return op;
}