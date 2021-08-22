#include <stdio.h>
#include <stdlib.h>

// vlastna metoda linear probing

int collision_my_hash = 0;

struct MyHash{
    int **array; // pole v ktorom sa budu nachadzat data typu (int*)
    int alloced_size; // velkost array
    int full; // obsadenost policok
    int bool_resize; // boolean ci sa ma alebo nema spustit zvacsovanie tabulky
};


int hash_function(int key, int size){ // hashovacia funkcia
    return key % size;
}

void initialize_hashtable(struct MyHash *hashtable, int initial, int bool_resize){ // inicializacia tabulky vopred
    hashtable->array =(int**)malloc(sizeof(int*) * initial);
    hashtable->alloced_size = initial;

    memset(hashtable->array,0,sizeof(int*) * hashtable->alloced_size);

    hashtable->full = 0;
    hashtable->bool_resize = bool_resize;
}

void insert_hash(int key,struct MyHash *hashtable){

    int hashIndex = hash_function(key, hashtable->alloced_size);
    int *item = malloc(sizeof(int));
    *item = key;


    double ratio = (double )hashtable->full / hashtable->alloced_size ;

    int **temporary;

    int original_size = hashtable->alloced_size;

    if (hashtable->bool_resize == 1){ // zvacsovanie tabulky
        if (ratio >= 0.5){ // zvacsenie hash funkcie 2 nasobne

            hashtable->alloced_size *= 2;

            temporary = (int**)malloc(sizeof(int*) * hashtable->alloced_size); // temporary predstavuje pole v ktorom docasne budu ulozene hodnoty z novo preheshovanej tabulky

            memset(temporary,0,sizeof(int*) * hashtable->alloced_size);

            for (int i = 0; i < original_size; ++i) { // znovu prehashovanie zvacsenej tabulky
                if (hashtable->array[i] != NULL){
                    int new_hash_index = hash_function(*hashtable->array[i], hashtable->alloced_size);
                    //printf("new_hash_index %d, item: %d\n", new_hash_index, *hashtable->array[i]);

                    while(temporary[new_hash_index] != NULL) {
                        ++new_hash_index;
                        new_hash_index %= hashtable->alloced_size;
                    }

                    temporary[new_hash_index] = hashtable->array[i];
                }
            }
            free(hashtable->array); // uvolnenie povodnej
            hashtable->array = temporary;
        }
    }

    int hash_code1 = hashIndex;

    while(hashtable->array[hashIndex] != NULL) {

        ++hashIndex;

        if (hashIndex >= hashtable->alloced_size){
            hashIndex = 0;
        }

        //hashIndex %= hashtable->alloced_size;
    }

    int hash_code2 = hashIndex;

    if (hash_code1 != hash_code2){ // pocitadlo kolizii
        collision_my_hash++;
    }

    hashtable->array[hashIndex] = item;

    hashtable->full++;

    //printf("hasindex : %d\n", hashIndex);
}

int search_hash(int key, struct MyHash *hashtable){

    int hashIndex = hash_function(key, hashtable->alloced_size);


    while(hashtable->array[hashIndex] != NULL) {


        if (key == *hashtable->array[hashIndex]){
            return 1;
        }

        ++hashIndex;

        if (hashIndex >= hashtable->alloced_size){
            hashIndex = 0;
        }
        //hashIndex %= hashtable->alloced_size;
    }
    return 0;
}