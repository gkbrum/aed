#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <stdio.h>
#include "core.h"

//prototipos de funções de gerenciamento de .idx
indexHeader_t *read_idxHeader(FILE *idxFile);
void write_idxHeader(FILE *idxFile, indexHeader_t *header);
bTreeNode_t *read_bTreeNode(FILE *idxFile, long offset);
void write_bTreeNode(FILE *idxFile, long offset, bTreeNode_t *node);
long alloc_btreeNode(FILE *idxFile);

//prototipos de funções de acesso a bTree
long bTree_searchKey(FILE *idxFile, const char *key);
void bTree_insertKey(FILE *idxFile, const char *key, long dataOffset);
void bTree_deleteKey(FILE *idxFile, const char *key);

#endif