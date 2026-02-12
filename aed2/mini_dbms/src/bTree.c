#include "bTree.h"

bTreeNode_t *readNode(FILE *idxFile, long offset){
    if( fseek(idxFile, offset, SEEK_SET) ) { fprintf(stderr, "Erro em readNode()"); }
    
    bTreeNode_t *nodeBuffer = malloc(sizeof(bTreeNode_t));
    fread(nodeBuffer, sizeof(bTreeNode_t), 1, idxFile);

    if( !nodeBuffer ){ fprintf(stderr, "Erro em readNode()"); }
    return nodeBuffer;
}