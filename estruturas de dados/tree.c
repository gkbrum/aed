#include <stdlib.h>

typedef struct {
    int val;
    TreeNode *left;
    TreeNode *right;
} TreeNode;

void pushTree( TreeNode *node, int val ){
    if(node == NULL){
        node = ( TreeNode * )malloc( sizeof( TreeNode ) );
        node->val = val;
        node->left = node->right = NULL;
        return;
    }else if( val < node->val ){
        pushTree( node->left, val );
        return;
    }else if( val > node->val ){
        pushTree( node->right, val );
        return;
    }
}

void preOrderTree( TreeNode* node ){
    printf( "%d", node->val );
    
    if( node->left == NULL && node->right == NULL){
        return;
    }else if( node->left != NULL ){
        preOrderTree( node->left );
        return;
    }else{
        preOrderTree( node->left );
        return;
    }
    return;
}