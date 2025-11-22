#include <stdio.h>
#include <stdlib.h>
#include "file_manager.h"

long writeRecord_dat( FILE *datFile, void *record, size_t recordSize ){
    if( fseek(datFile, 0, SEEK_END) ) { fprintf(stderr, "Erro em 'writeRecordFile()'"); };

    long newRecordOffset = ftell(datFile);
    if ( fwrite(record, recordSize, 1, datFile) == 0 ) { fprintf(stderr, "Erro ao escrever um arquivo"); }

    return newRecordOffset;
}

void *readRecord_dat( FILE *datFile, long offset, size_t recordSize ){
    if( fseek(datFile, offset, SEEK_SET) != 0 ) { fprintf(stderr, "Erro em 'readRecordFile()'"); };

    void* buffer = calloc(1, recordSize);               //necessario chamar free() para o ptr retornado ao chamar essa função
    fread(buffer, recordSize, 1, datFile);

    if( !buffer ){ fprintf(stderr, "Erro em readRecordFile"); }
    return buffer;
}

size_t updateRecord_dat( FILE *datFile, long offset, void *record, size_t recordSize ){
    if ( fseek(datFile, offset, SEEK_SET) != 0 ){ fprintf(stderr, "Erro em updateRecordFile()"); }

    size_t writeReturn = fwrite(record, recordSize, 1, datFile);
    if ( writeReturn == 0 ) { fprintf(stderr, "Erro ao atualizar um arquivo"); }

    return writeReturn;
}