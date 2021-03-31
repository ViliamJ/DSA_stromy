
// C program to demonstrate insert
// operation in binary
// search tree.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "myhashmap.c"
#include "red_black.c"
#include "avl_tree.c"

#define data_size 10


#define COUNT 10



// A utility function to create a new BST node

/* A utility function to insert
   a new node with given key in
 * BST */

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







// Driver Code
int main() {

    /*

    int array[data_size];

    for (int i = 0; i < data_size; i++) {
        array[i] = i;
    }

    shuffle(array, data_size);



    struct Node* avl_root = NULL;


    for (int i = 10; i < 100; i+=10 ){
        avl_root = insert(avl_root, i);
    }

    avl_root = insert(avl_root, 25);


    print2D(avl_root);

     clock_t t2;
     t2 = clock();

     for(int i = 10; i < 100; i+=10 ){

         search(avl_root, i);
     }

     t2 = clock() - t2;
     double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds

     printf("Root2 took %f seconds to execute \n", time_taken2);





    /*
    for(int i = 0; i < 20; i++){
        printf("\n");
    }




    struct Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    for (int a = 0; a < 100000000; a++){
        root = insert(root, a);
    }

    //print2D(root);
    //search(root, 9000000);

    struct MyHash *hashArray[100];

    struct MyHash *item = (struct MyHash *) malloc(sizeof(struct MyHash));
    item->data = 10;
    item->key = 15;

    hashArray[1] = item;


    insert_hash(1, 70, hashArray, 100);

    insert_hash(2, 20,hashArray, 100);

   // insert_hash(7, 80, hashArray, 100);
   // insert_hash(4, 25, hashArray, 100);
    insert_hash(12, 44, hashArray, 100);



   // myprint(hashArray);

    //search_hash(42, hashArray, 100);

    printf("Item hashed %d, %d", hashArray[4]->key, hashArray[4]->data );


    struct node* redblack = NULL;


    for (int i = 0; i < 100; ++i)
        insert_redblack(&redblack, i);

    tree_print(redblack);

     */
    struct MyHash table;
    initialize_hashtable(&table);


    insert_hash(1, &table);
    insert_hash(2, &table);
    insert_hash(4, &table);
    insert_hash(9, &table);
    insert_hash(22, &table);
    insert_hash(11, &table);


    search_hash(11,&table);

    // pri hastabulke nasobky 2
    //



    for (int i = 0; i < table.alloced_size; ++i) {
        if (table.array[i] == NULL){
            printf("Index %d prazdny\n", i);
        } else{
            printf("index %i item %d\n",i, *(table.array[i]));
        }
    }

    return 0;
}

