//
// Created by Viliam on 08.02.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000

struct MyHash{
    int key;
    int data;

};

//struct MyHash* hashArray[SIZE];

int hash_function(int key, int size){
    return key % size;
}

void insert_hash(int key, int data, struct MyHash **array, int size){



    struct MyHash *item = (struct MyHash*) malloc(sizeof(struct MyHash));
    item->data = data;
    item->key = key;




    //get the hash
    int hashIndex = hash_function(key, size);



    while(array[hashIndex] != NULL) {
        //go to next cell
        ++hashIndex;

        hashIndex %= size;
    }
    printf("wut %d\n", hashIndex);
    array[hashIndex] = item;


}


void myprint(struct MyHash **array){
    struct MyHash *k;
    k = array[12];
    printf("please %d", k->data);
    int i = 0;


    while (1){
        if(array[i] == NULL){
            ++i;
        }
        if(i == 99){
            break;
        }
        printf("array key: %d data: %d \n", array[i]->key, array[i]->data);
        i++;
    }
}

struct MyHash *search_hash(int key, struct MyHash ** array, int size){
//get the hash
    int hashIndex = hash_function(key, size);

    printf("jebo %d \n", hashIndex);

    //move in array until an empty
    while(array[hashIndex] != NULL) {

        //struct MyHash *item = (struct MyHash *) array[0];
        struct MyHash *item = (struct MyHash*) malloc(sizeof(struct MyHash));
        item = array[hashIndex];

        printf("juj %d\n", item->key);


        if(item->key == key) {
            printf("blitzna");
            return array[hashIndex];
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return NULL;
}