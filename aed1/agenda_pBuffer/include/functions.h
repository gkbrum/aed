#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define NUM_PERSONS         ( ( int * )pBuffer )
#define BUFFER_SIZE         ( ( int * )( ( char* )pBuffer + sizeof( int ) ) )
#define I                   ( ( int * )( ( char * )pBuffer + ( sizeof( int ) * 2 ) ) )
#define TEMP_NAME           ( ( char * )pBuffer + ( sizeof( int ) * 3 ) )
#define TEMP_EMAIL          ( ( char * )pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( char ) * 100 ) )
#define HEAD                ( ( char * )pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( char ) * 200 ) )

void ShowMenu( int *op );
void *InitBuffer();
void *AddPerson( void *pBuffer );
void *SearchPerson( void *pBuffer );
void *DeletePerson( void *pBuffer );
void ListAll( void *pBuffer );
void PrintPerson( char *name );

#endif