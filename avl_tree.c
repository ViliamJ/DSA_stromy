//
// Created by vilia on 21.03.2021.
//

void test1(){
    printf("i love pokemon");
}

struct TreeNode{
    struct TreeNode *left_node, *right_node;
    int data;
};

int get_node_height( struct TreeNode *node ) {
    int height_left = 0;
    int height_right = 0;

    if( node->left_node ) {
        height_left = get_node_height( node->left_node );
    }
    if( node->right_node ){
        height_right = get_node_height( node->right_node );
    }

    if (height_right > height_left){
        return height_right++;
    } else{
        return height_left++;
    }
}

int search_avl(struct TreeNode *node, int item){

    while (node->data != item){
        if (node != NULL){
            if (node->data < item){
                node = node->right_node;
            } else{
                node = node->left_node;
            }

            if (node->data == item){
                return 1;
            }
        } else{
            return 0;
        }
    }

    return 0;
}

struct TreeNode *create_node(int data){
    struct TreeNode *node = (struct TreeNode *)
            malloc(sizeof(struct TreeNode));

    node->data = data;
    node->left_node = NULL;
    node->right_node = NULL;
    return node;

}

struct TreeNode *insert_to_avl(struct TreeNode *root, int new_item){

    if (root == NULL)
        return (create_node(new_item));

    if (new_item < root->data)
        root->left_node = insert_to_avl(root->left_node, new_item);
    else if (new_item > root->data)
        root->right_node = insert_to_avl(root->right_node, new_item);
    else
        return root;


    int balance_facort = get_node_height(root->right_node) - get_node_height(root->left_node);

    if (abs(balance_facort) > 1 && new_item < root->left_node->data){

    }

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }


    return root;
}
