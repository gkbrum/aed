#include "bTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


indexHeader_t *read_idxHeader(FILE *idxFile){
    if( fseek(idxFile, 0, SEEK_SET) ) { fprintf(stderr, "Erro em readIdxHeader()"); }

    indexHeader_t *header = (indexHeader_t*)malloc(sizeof(indexHeader_t)); 
    fread(header, sizeof(indexHeader_t), 1, idxFile);

    if( !header ){ fprintf(stderr, "Erro em readIdxHeader()"); }
    return header;
}

void write_idxHeader(FILE *idxFile, indexHeader_t *header){
    if( fseek(idxFile, 0, SEEK_SET) ) { fprintf(stderr, "Erro em writeIdxHeader()"); }
 
    if( fwrite(header, sizeof(indexHeader_t), 1, idxFile) != 1 ){ fprintf(stderr, "Erro em writeIdxHeader()"); }
}

bTreeNode_t *read_bTreeNode(FILE *idxFile, long offset){
    if( fseek(idxFile, offset, SEEK_SET) ) { fprintf(stderr, "Erro em readNode()"); }
    
    bTreeNode_t *nodeBuffer = (bTreeNode_t*)malloc(sizeof(bTreeNode_t));
    fread(nodeBuffer, sizeof(bTreeNode_t), 1, idxFile);

    if( !nodeBuffer ){ fprintf(stderr, "Erro em readNode()"); }
    return nodeBuffer;
}

long write_bTreeNode(FILE *idxFile, long offset, bTreeNode_t *node){
    if( fseek(idxFile, offset, SEEK_SET) ) { fprintf(stderr, "Erro em wirteNode()"); }
    
    if( fwrite(node, sizeof(bTreeNode_t),1 , idxFile) != 1 ) { fprintf(stderr, "Erro em writeNode()"); }
}

long alloc_btreeNode(FILE *idxFile);