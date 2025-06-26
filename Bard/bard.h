#pragma once

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct Node{
        char *word;
        int len;
        int rank;
        int times;
        struct Node *next;
} Node;

extern Node *table[100];

void create_table(void);

void rank_ll(void);
