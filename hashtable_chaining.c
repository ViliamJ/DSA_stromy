#include<stdio.h>
#include<stdlib.h>

#define size 7

// https://www.log2base2.com/algorithms/searching/open-hashing.html


struct Chain_node
{
    int data;
    struct Chain_node *next;
};

struct Chain_node *chain[size];

void init_chain()
{
    int i;
    for(i = 0; i < size; i++)
        chain[i] = NULL;
}

void insert_chain_hash(int value)
{
    //create a newnode with value
    struct Chain_node *newNode = malloc(sizeof(struct Chain_node));
    newNode->data = value;
    newNode->next = NULL;

    //calculate hash key
    int key = value % size;

    //check if chain[key] is empty
    if(chain[key] == NULL)
        chain[key] = newNode;
        //collision
    else
    {
        //add the node at the end of chain[key].
        struct Chain_node *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

void print_chain()
{
    int i;

    for(i = 0; i < size; i++)
    {
        struct Chain_node *temp = chain[i];
        printf("chain[%d]-->",i);
        while(temp)
        {
            printf("%d -->",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

/*
 * return 1, search found
 * return 0, Otherwise
 */
int search_chain(int value)
{
    int key = value % size;
    struct Chain_node *temp = chain[key];
    while(temp)
    {
        if(temp->data == value)
            return 1;
        temp = temp->next;
    }
    return 0;
}
