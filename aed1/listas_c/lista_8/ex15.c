#include <stdio.h>

float calcula( int n ){
    if ( n == 1 ){
        return 2;
    } else {
        return ( ( (1.0 + n * n) / n ) + calcula( n - 1 ) );
    }
}

int main() {
    printf( "resultado: %f", calcula( 15 ) );
}