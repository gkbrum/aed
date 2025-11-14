#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    
    void *pBuffer = InitBuffer();


    do{
        ShowMenu( I );
        
        switch ( *I )
        {
        case 1:
            pBuffer = AddPerson( pBuffer );
            
            *I = 1;
            break;
        
        case 2:
            pBuffer = DeletePerson( pBuffer );

            *I = 2;
            break;

        case 3:
            char *name = SearchPerson( pBuffer );
            PrintPerson( name );

            *I = 3;
            break;
        
        case 4:

            ListAll( pBuffer );

            *I = 4;
            break;
            
        default:
            break;
        }
    }while( *(I) != 5 );

    printf( "\n\nDesligando.\n\n" );
    free( pBuffer );
    
    return 0;
}
