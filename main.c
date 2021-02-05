
// C program to demonstrate insert
// operation in binary
// search tree.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define data_size 10


#define COUNT 10

struct node {
    int data;
    struct node *left, *right;
    int height;
};


struct node_avl{
    int data;
    struct node_avl *left;
    struct node_avl *right;
    int depth;
};


// A utility function to create a new BST node
struct node* newNode(int item)
{
    struct node* temp
            = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}


/* A utility function to insert
   a new node with given key in
 * BST */
struct node* insert(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

void print2DUtil(struct node *root, int space)
{
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
    printf("%d\n", root->data);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(struct node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void search(struct node* root, int data){
    struct node *current = root;

    while(current->data != data){

        if(current != NULL) {
            //printf("%d ",current->key);

            //go to left tree
            if(current->data > data){
                current = current->left;
            }  //else go to right tree
            else {
                current = current->right;
            }

            //not found
            if(current == NULL){
                printf("Nenaslo sa cislo");

            }
        }
    }

    //printf("Data: %d , hladane cislo: %d", current->key, data);
    //return current;
}

struct node * new_node(int val){
    struct node* temp = (struct node*)malloc(sizeof (struct node));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;

    temp->height = 1;

    return temp;
}

struct node * insert_avl(struct node *r, int val){
    if(r == NULL){
        return new_node(val);
    }
    if (val < r->data){
        r->left = insert(r->left, val);
    }
}

// Driver Code
int main()
{
    /*
    int array[data_size];

    for(int i =0; i < data_size; i++){
        array[i] = i;
    }

    printf("%llu size", sizeof(struct node));


    shuffle(array, data_size);




    printf("\n");



    struct node* root = NULL;


  for (int i = 0; i < data_size; i++ ){
      root = insert(root, i);
  }




    struct node* root2 = NULL;
    root2 = insert(root2, array[0]);

    for (int i = 1; i < data_size; i++){
        insert(root2, array[i]);
    }





    //inorder(root);
    //print2D(root);

    //printf("Root: %d \n",root2->right->key);



     clock_t t;
     t = clock();

     for(int i = 0; i < data_size; i++){
         search(root, i);
     }

     t = clock() - t;
     double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

     printf("Root1 took %f seconds to execute \n", time_taken);


     clock_t t2;
     t = clock();

     for(int i = 0; i < data_size; i++){

         search(root2, i);
     }

     t = clock() - t;
     double time_taken2 = ((double)t)/CLOCKS_PER_SEC; // in seconds

     printf("Root2 took %f seconds to execute \n", time_taken2);


    //struct node *root = NULL;
    print2D(root);
    for(int i = 0; i < 10; i++){
        printf("\n");
    }
    print2D(root2);

    */

    struct node *root = NULL;

    root = insert_avl(root, 10);
    root = insert_avl(root, 20);
    root = insert_avl(root, 30);
    root = insert_avl(root, 40);
    root = insert_avl(root, 50);
    root = insert_avl(root, 25);

    return 0;
}