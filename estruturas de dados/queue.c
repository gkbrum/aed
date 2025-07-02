#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    node_t *next;
} node_t;

typedef struct {
    node_t *first;
    node_t *last;
    int size;
} queue_t;

queue_t *resetQueue(){
    queue_t *q = ( queue_t * )malloc( sizeof( queue_t ) );

    q->first = NULL;
    q->last = NULL;
    q->size = 0;

    return q;
}

void pushQueue( queue_t *queue, int value ){
    if( queue->size == 0 ){
        node_t *node = ( node_t * )malloc( sizeof( node_t ) );
        node->value = value;
        node->next = NULL;

        queue->first = queue->last = node;
        queue->size++;
    }else{
        node_t *node = ( node_t * )malloc( sizeof( node_t ) );
        node->value = value;
        node->next = NULL;

        queue->last->next = node;
        queue->last = node;
        queue->size++;
    }
}

node_t *popQueue( queue_t *q ){
    if( q->size == 0 ){
        return NULL;
    }else{
        node_t *popped = q->first;
        q->first = popped->next;
        q->size--;
        return popped;
    }
    
    return NULL;
}

node_t *peekQueue( queue_t *q ){
    if( q->size == 0 ){
        return NULL;
    }else{
        return q->first;
    }
}

int sizeQueue( queue_t *q ){
    return q->size;
}

bool isEmptyQueue( queue_t *q ){
    if( q->size > 0 ){
        return false;
    }else{
        return true;
    }
}