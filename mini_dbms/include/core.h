#ifndef CORE_H
#define CORE_H

#include <stdbool.h>

//define as restrições da bTree
#define B_TREE_DEGREE 3
#define MAX_KEYS (2 * B_TREE_DEGREE - 1)
#define MIN_KEYS (B_TREE_DEGREE - 1)
#define MAX_CHILDREN (2 * B_TREE_DEGREE)

//define as estruturas a serem usadas para persistencia
typedef struct {
    //135 Bytes
    int registration;
    char name[50];
    char address[50];
    char phone[15];
    int entryYear;
    char entryPeriod;
    char birthDate[10];
    bool active;
} student_t;

typedef struct {
    //51 Bytes
    char code[6];
    char name[44];
    bool active;
} discipline_t;

typedef struct {
    //27 Bytes
    int id;
    int registration;
    char discipline[6];
    int year;
    char period;
    float finalGrade;
    bool active;
} studentRegistration_t;

//define as estruturas a serem usadas para a bTree
typedef struct {
    int keyCount;
    char keys[MAX_KEYS][10];
    long dataOffset[MAX_KEYS];
    long childOffset[MAX_CHILDREN];
    bool isLeaf;
} bTreeNode_t;

typedef struct {
    long rootOffset;
    long nextFreeNode_offset;
    int nextSeq_id;
} indexHeader_t;

#endif