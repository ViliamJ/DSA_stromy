
// C program to demonstrate insert
// operation in binary
// search tree.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define data_size 10


#define COUNT 10

struct node {
    int key;
    struct node *left, *right;
    int height;
};


struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// A utility function to create a new BST node
struct node* newNode1(int item)
{
    struct node* temp
            = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}


/* A utility function to insert
   a new node with given key in
 * BST */
struct node* insert2(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode1(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert2(node->left, key);
    else if (key > node->key)
        node->right = insert2(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

void print2DUtil(struct Node *root, int space)
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
    printf("%d\n", root->key);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(struct Node *root)
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

void search(struct Node* root, int data){
    struct Node *current = root;

    while(current->key != data){

        if(current != NULL) {
            //printf("%d ",current->key);

            //go to left tree
            if(current->key > data){
                current = current->left;
            }  //else go to right tree
            else {
                current = current->right;
            }

            //not found
            if(current == NULL){
                printf("Nenaslo sa cislo");
                //return NULL;
            }
        }
    }

    printf("Data: %d , hladane cislo: %d, Height : %d", current->key, data, current->height);
    //return current;
}




// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)
            malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}



// Driver Code
int main()
{

    int array[data_size];

    for(int i =0; i < data_size; i++){
        array[i] = i;
    }

    printf("%llu size", sizeof(struct node));

    shuffle(array, data_size);

    printf("\n");

    struct node* root_normal = NULL;


    for (int i = 10; i < 50; i+=10 ){
        root_normal = insert2(root_normal, i);
    }

    root_normal = insert2(root_normal, 25);



    print2D(root_normal);



    /*
     clock_t t;
     t = clock();

     for(int i = 0; i < data_size; i++){
         search(root_normal, i);
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

     */



    for(int i = 0; i < 20; i++){
        printf("\n");
    }




    struct Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    for (int a = 0; a < 1000; a++){

        root = insert(root, a);
    }

    print2D(root);
    search(root, 0);
    return 0;
}