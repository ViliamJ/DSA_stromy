//
// Created by Viliam on 08.02.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000

// metoda linear probing

struct MyHash{
    int **array;
    int alloced_size; // velkost array
    int full; // obsadenost policok
};


int hash_function(int key, int size){ // najjednoduchsia
    return key % size;
}

void initialize_hashtable(struct MyHash *hashtable){
    hashtable->array =(int**)malloc(sizeof(int*) * 4);
    hashtable->alloced_size = 4;

    memset(hashtable->array,0,sizeof(int*) * hashtable->alloced_size);

    hashtable->full = 0;
}

void insert_hash(int key,struct MyHash *hashtable){

    int hashIndex = hash_function(key, hashtable->alloced_size);
    int *item = malloc(sizeof(int));
    *item = key;


    double ratio = (double )hashtable->full / hashtable->alloced_size ;

    int **temporary;

    int original_size = hashtable->alloced_size;

    if (ratio >= 0.5){ // zvacsenie hash funkcie 2 nasobne

        hashtable->alloced_size *= 2;

        temporary = (int**)malloc(sizeof(int*) * hashtable->alloced_size);

        memset(temporary,0,sizeof(int*) * hashtable->alloced_size);

        for (int i = 0; i < original_size; ++i) {
            if (hashtable->array[i] != NULL){
                int new_hash_index = hash_function(*hashtable->array[i], hashtable->alloced_size);
                printf("new_hash_index %d, item: %d\n", new_hash_index, *hashtable->array[i]);

                while(temporary[new_hash_index] != NULL) {
                    ++new_hash_index;
                    new_hash_index %= hashtable->alloced_size;
                }

                temporary[new_hash_index] = hashtable->array[i];
            }
        }
        free(hashtable->array);
        hashtable->array = temporary;
    }



    while(hashtable->array[hashIndex] != NULL) {
        ++hashIndex;
        hashIndex %= hashtable->alloced_size;
    }

    hashtable->array[hashIndex] = item;
    hashtable->full++;

    //printf("hasindex : %d\n", hashIndex);
}

int search_hash(int key, struct MyHash *hashtable){

    int hashIndex = hash_function(key, hashtable->alloced_size);


    while(hashtable->array[hashIndex] != NULL) {


        if (key == *hashtable->array[hashIndex]){
            printf("naslo");
            return 1;
        }

        ++hashIndex;
        hashIndex %= hashtable->alloced_size;



    }
    return 0;
}