#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "myhashmap.c"
#include "avl_tree.c"
#include "hashtable_chaining.c"

#define COUNT 10


void print2DUtil(struct Node *root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(struct Node *root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

void free_avl_tree(struct Node * node){
    if (node != NULL) {
        free_avl_tree(node->right);
        free_avl_tree(node->left);
        free(node);
    }
}

void shuffle(int *array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}



void timer_detection(void (*f)(int, int, int, int), char  *func_name, int a, int b, int table_size, int choice)
{

    clock_t t2;
    t2 = clock();

    (*f)(a,b, table_size,choice);

    t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds

    printf("Function (%s) took %f seconds to execute \n",func_name, time_taken2);

    printf("collision my hash: %d |  collision chain: %d | avl_rotation: %d \n", collision_my_hash, collision_chain, avl_rotation);

    collision_chain = 0;
    collision_my_hash = 0;
    avl_rotation = 0;
}

void test_sorted_nonrandom(int a, int b, int table_size, int choice){ // je nutne pozmenit manualne velkost tabulky v prevzatej hash table chaining
    struct MyHash table_probing;
    initialize_hashtable(&table_probing, table_size, 0); // myhashmap linear probing
    init_chain(); // chaining hashmap
    struct Node* avl_root = NULL; // AVL tree root init

    printf("Testing numbers from %d to %d, hashtable size %d\n", a, b, table_size);

    if (choice == 1){
        printf("1. Testing my hashtable linear probing \n");
    }

    if (choice == 2){
        printf("2. Testing chaining table \n");
    }

    if (choice == 3){
        printf("3. Testing AVL tree \n");
    }

    clock_t t1;
    t1 = clock();

    for (int i = a; i < b; i++) {
        if (choice == 1){
            insert_hash(i, &table_probing);
        }

        if (choice == 2){
            insert_chain_hash(i);
        }
        if (choice == 3){
            avl_root = insert(avl_root, i);
        }
    }

    t1 = clock() - t1;
    double time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds
    printf("Sorted insert took: %f\n", time_taken1);


    clock_t t2;
    t2 = clock();

    for (int i = a; i < b; i++) {
        if (choice == 1){
            if (search_hash(i, &table_probing) == 0)
                printf("nenaslo cislo %d", i);
        }

        if (choice == 2){
            if (search_chain(i) == 0)
                printf("nenaslo cislo %d", i);
        }

        if (choice == 3){
            search(avl_root, i);
        }
    }

    t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds
    printf("Sorted search took: %f\n", time_taken2);
}


void kolizie_rotatice_random(int table_size, int real_table_size){ // otestovanie kolizii aj časov, ( v chain hastable, treba tabulku manualne pozmenit velkost na dany table_size )
    int array[table_size];


    for (int i = 0; i < table_size; i++) {
        array[i] = rand();
        //printf("nahodne cislo :%d\n", array[i]);
    }





    struct MyHash table_probing;
    initialize_hashtable(&table_probing, real_table_size, 0);

    struct Node* avl_root = NULL;
    init_chain();

    //1.  test INSERT my hash
    clock_t t1;
    t1 = clock();

    for (int i = 0; i < table_size; i++) {
        insert_hash(array[i], &table_probing);
        //insert_chain_hash(array[i]);
        //avl_root = insert(avl_root, array[i]);
    }

    t1 = clock() - t1;
    double time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds
    printf("Myhast insert took: %f\n", time_taken1);

    // 2. test INSERT chain hash
    clock_t t3;
    t3 = clock();
    for (int i = 0; i < table_size; i++) {
        //insert_hash(array[i], &table_probing);
        insert_chain_hash(array[i]);
        //avl_root = insert(avl_root, array[i]);
    }

    t3 = clock() - t3;
    double time_taken3 = ((double)t3)/CLOCKS_PER_SEC; // in seconds
    printf("Chain insert took: %f\n", time_taken3);


    // 3. test INSERT AVL
    clock_t t4;
    t4 = clock();
    for (int i = 0; i < table_size; i++) {
        //insert_hash(array[i], &table_probing);
        //insert_chain_hash(array[i]);
        avl_root = insert(avl_root, array[i]);
    }
//
    t4 = clock() - t4;
    double time_taken4 = ((double)t4)/CLOCKS_PER_SEC; // in seconds
    printf("AVL insert took: %f\n", time_taken4);


    printf("\n");
    //shuffle(array, table_size); // porozhadtujem naplnene pole nahodnych cisel, aby sa tazsie hladali prvky pri search

    // 4. test SEARCH myHash
    clock_t t5;
    t5 = clock();

    for (int i = 0; i < table_size; i++) {
        search_hash(array[i], &table_probing);
        //search_chain(array[i]);
        //search(avl_root, array[i]);
    }

    t5 = clock() - t5;
    double time_taken5 = ((double)t5)/CLOCKS_PER_SEC; // in seconds
    printf("Myhash search took: %f\n", time_taken5);

    // 5. test SEARCH chain hash
    clock_t t6;
    t6= clock();

    for (int i = 0; i < table_size; i++) {
        //search_hash(array[i], &table_probing);
        search_chain(array[i]);
        //search(avl_root, array[i]);
    }

    t6 = clock() - t6;
    double time_taken6 = ((double)t6)/CLOCKS_PER_SEC; // in seconds
    printf("ChainHash search took: %f\n", time_taken6);


    // 6. test SEARCH AVL
   // clock_t t7;
   // t7= clock();
//
   // for (int i = 0; i < table_size; i++) {
   //     //search_hash(array[i], &table_probing);
   //     //search_chain(array[i]);
   //     search(avl_root, array[i]);
   // }
//
   // t7 = clock() - t7;
   // double time_taken7 = ((double)t7)/CLOCKS_PER_SEC; // in seconds
   // printf("AVL search took: %f\n", time_taken7);

    printf("collision my hash: %d |  collision chain: %d | avl_rotation: %d \n", collision_my_hash, collision_chain, avl_rotation);

    collision_chain = 0;
    collision_my_hash = 0;
    avl_rotation = 0;

}

void test_my_hashmap_functionality(){

    struct MyHash table_probing;
    initialize_hashtable(&table_probing, 10, 0);

    insert_hash(777,&table_probing);
    insert_hash(456,&table_probing);
    insert_hash(9512,&table_probing);
    insert_hash(951215,&table_probing);
    insert_hash(0,&table_probing);
    insert_hash(6984,&table_probing);
    insert_hash(15,&table_probing);
    insert_hash(11,&table_probing);
    insert_hash(11,&table_probing);

    if (search_hash(11,&table_probing) == 1)
        printf("nasiel prvok %d\n", 11);



    for (int i = 0; i < table_probing.alloced_size; ++i) {
        if (table_probing.array[i] == NULL) {
            printf("Index: %d prazdny\n", i);
        } else {
            printf("index: %i item: %d\n", i, *(table_probing.array[i]));
        }
    }
}

int main(int argc, char *argv[]) {

    srand(time(0)); // zabezpečuje aby vždy boli nahodne cisla kazdykrat co sa spusti program


    //timer_detection(test_sorted_nonrandom,"My hash probing", 0,  1000000, 200000000,1);
    //timer_detection(test_sorted_nonrandom,"Chaining", 0,  1000000, 200000000,2);
    //timer_detection(test_sorted_nonrandom,"AVL", 0,  1000000, 200000000,3);


    //timer_detection(test_sorted_nonrandom,"My hash probing", 1000000,  10000000, 200000000,1);
    //timer_detection(test_sorted_nonrandom,"Chaining", 1000000,  10000000, 200000000,2);
    //timer_detection(test_sorted_nonrandom,"AVL", 1000000,  10000000, 200000000,3);

    //timer_detection(test_sorted_nonrandom,"My hash probing", 0,  200000000, 200000000,1);
    //timer_detection(test_sorted_nonrandom,"Chaining", 0,  200000000, 200000000,2);
    //timer_detection(test_sorted_nonrandom,"AVL", 0,  200000000, 200000000,3);

    //timer_detection(test_sorted_nonrandom,"My hash probing", 1000000000,  1200000000, 200000000,1);
    //timer_detection(test_sorted_nonrandom,"Chaining", 1000000000,  1200000000, 200000000,2);
    //timer_detection(test_sorted_nonrandom,"AVL", 1000000000,  1200000000, 200000000,3);

    //timer_detection(test_sorted_nonrandom,"My hash probing", 10000000,  100000000, 200000000,1);
    //timer_detection(test_sorted_nonrandom,"Chaining", 10000000,  100000000, 200000000,2);
    //timer_detection(test_sorted_nonrandom,"AVL", 10000000,  100000000, 200000000,3);

    // povodne to bolo takto
    //kolizie_rotatice_random(1997);
    //kolizie_rotatice_random(25000);
    //kolizie_rotatice_random(50000,50000);
    //kolizie_rotatice_random(100000);
    //kolizie_rotatice_random(500000,500051);
    //kolizie_rotatice_random(200000);
    //kolizie_rotatice_random(250000,250000);

    // nove upravene
    // povodne to bolo takto
    //kolizie_rotatice_random(1997,200000000);
    //kolizie_rotatice_random(25000,200000000);
    //kolizie_rotatice_random(50000,200000000);
    //kolizie_rotatice_random(100000,200000000);
    //kolizie_rotatice_random(150000,200000000);
    //kolizie_rotatice_random(200000,200000000);
    //kolizie_rotatice_random(250000,200000000);
    //kolizie_rotatice_random(500000,200000000);

    struct Node* avl_root = NULL;
    avl_root = insert(avl_root, 10);
    avl_root = insert(avl_root, 7);
    avl_root = insert(avl_root, 3);
    avl_root = insert(avl_root, 6);
    avl_root = insert(avl_root, 5);
    avl_root = insert(avl_root, 9);
    avl_root = insert(avl_root, 13);
    avl_root = insert(avl_root, 12);
    avl_root = insert(avl_root, 11);
    avl_root = insert(avl_root, 4);
    avl_root = insert(avl_root, 1);
//
    print2D(avl_root);




    //test_my_hashmap_functionality();
    return 0;


}