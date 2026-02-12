#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <stdio.h>
#include "core.h"

//prototipos de funções de gerenciamento de .idx
bTreeNode_t *readNode(FILE *idxFile, long offset);
void saveNode(FILE *idxFile, long offset, bTreeNode_t *node);

//prototipos de funções de acesso a bTree

#endif