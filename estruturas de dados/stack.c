#include <stdbool.h>
#include <stdlib.h>
#define MAX 1000

typedef struct {
    int limit;
    int top;
    int base;
    int value[MAX];
} stack_t;

stack_t *resetStack(){
    stack_t *stack = ( stack_t * )malloc( sizeof( stack_t ) );
    if (!stack) return NULL;

    stack->limit = MAX - 1;
    stack->top = -1;
    stack->base = 0;

    return stack;
}

void pushStack( stack_t *s, int value ){
    if( s->top != s->limit ){
        s->value[ s->top + 1 ] = value;
        s->top++;
    }
}

int popStack( stack_t *s ){
    if( s->top > -1 ){
        return s->value[ s->top-- ];
    }
}

int topStack( stack_t *s ){
    if( s->top > -1 ){
        return s->value[ s->top ];
    }
}

bool isEmptyStack( stack_t *s ){
    if( s->top >= s->base ){
        return false;
    }else{
        return true;
    }
}

bool isFullStack( stack_t *s ){
    if( s->top == s->limit ){
        return true;
    }else{
        return false;
    }
}