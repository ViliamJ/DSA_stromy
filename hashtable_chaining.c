//
// https://steemit.com/programming/@drifter1/programming-c-hashtables-with-chaining
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 31 // prime number for size of array
#define h(x) (x % m) //h(x) = x mod m

// Node for List
typedef struct ChainNode{
    int val;
    struct ChainNode *next;
}ChainNode;

//function's declaration
ChainNode *fill_table(ChainNode *table, int table_range, int number);
ChainNode *insert_hash_chain(ChainNode *table, int hash_index, int val);
ChainNode *del(ChainNode *table,int table_range,int val);
void print_table(ChainNode *table, int table_range);
void search_chain_hash(ChainNode *table, int table_range, int val);


int main(){
    ChainNode *table; // hashtable
    int n, i, j, choice, search;
    int hash_num, val;

    // allocate table
    table = (ChainNode*) malloc(N*sizeof(ChainNode));
    //make table "heads" NULL
    for(i = 0; i < N; i++){
        table[i].next = NULL;
    }

    printf("--h(x) = xmod%d--\n",N);
    printf("\n\n");

    while(1){
        printf("1.Insert random numbers\n");
        printf("2.Delete a number\n");
        printf("3.Search a number\n");
        printf("4.Show Hash Table\n");
        printf("0.Exit Programm\n");
        printf("\n--------\n");
        printf("Choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 0: return;
            case 1:
                // insert random numbers
                printf("Lot to insert: ");
                scanf("%d", &n);
                table = fill_table(table, N, n);
                printf("Filled HashTable with %d random values\n", n);
                printf("\n--------\n");
                break;
            case 2:
                // delete a number
                printf("Give a number: ");
                scanf("%d",&search);
                table = del(table, N, search);
                printf("\n--------\n");
                break;
            case 3:
                // search for a number
                printf("Give a number: ");
                scanf("%d",&search);
                search_chain_hash(table, N, search);
                printf("\n--------\n");
                break;
            case 4:
                //print hashtable
                printf("-HASHTABLE-\n\n");
                print_table(table, N);
                printf("\n--------\n");
                break;
        }
    }
    return 0;
}

// FUNCTIONS
ChainNode *fill_table(ChainNode *table, int table_range, int number){
    int i;
    int num;
    for(i=0; i<number; i++){
        num = rand()%10000; // random number from 0 to 9999
        table = insert_hash_chain(table, num % table_range, num);
    }
    return table;
}

void print_table(ChainNode *table, int table_range){
    int i;
    ChainNode* cur;
    for(i = 0; i < table_range; i++){ // for each list
        if(table[i].next == NULL){ // if empty
            printf("Table[%d] is empty!\n", i);
            continue;
        }
        cur = table[i].next;
        printf("Table[%d]", i);
        while(cur!=NULL){ // else print all the values
            printf("->%d",cur->val);
            cur=cur->next; //cur=cur+1;
        }
        printf("\n");
    }
}

ChainNode *insert_hash_chain(ChainNode *table, int hash_index, int val){
    ChainNode *nn, *cur;

    nn = (ChainNode*)malloc(sizeof(ChainNode));
    nn->val=val;
    nn->next=NULL;

    if(table[hash_index].next == NULL){
        table[hash_index].next = nn;
        return table;
    }

    cur = table[hash_index].next;
    while(cur->next != NULL){
        cur=cur->next; //cur=cur+1;
    }
    cur->next = nn;
    return table;
}

void search_chain_hash(ChainNode *table, int table_range, int val){
    int index = val % table_range;
    ChainNode *cur;

    if(table[index].next == NULL){ // if empty
        printf("Value %d not found cause Table[%d] is emtpy!\n", val,index);
        return;
    }

    cur = table[index].next;
    while(cur!=NULL){
        if(cur->val == val){
            printf("Value %d was found!\n", val);
            return;
        }
        cur = cur->next;
    }
    printf("Value %d not found in Hashtable!\n", val);
}