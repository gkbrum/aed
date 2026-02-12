#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include "core.h"

long writeRecord_dat( FILE *datFile, void *record, size_t recordSize );
void *readRecord_dat( FILE *datFile, long offset, size_t recordSize );
size_t updateRecord_dat( FILE *datFile, long offset, void *record, size_t recordSize );

#endif