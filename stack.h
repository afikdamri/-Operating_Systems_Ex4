#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t lock;

typedef struct Node{
    char value[1024];
    struct Node* next;
}Node;

void PUSH(Node** root, char value[1024]){
    pthread_mutex_lock(&lock);
    Node* new_node = malloc(sizeof(Node));
    int i = 0;
    if(new_node ==  NULL){
        printf("Error to PUSH");
    }
    new_node->next = NULL;
    while(value[i] != '\0'){
        new_node->value[i] = value[i];
        i++;
    }
    Node* curr = *root;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = new_node;
    pthread_mutex_unlock(&lock);
}

char* TOP(Node** root){
    pthread_mutex_lock(&lock);
    Node* curr = *root;
    while(curr->next != NULL){
        curr = curr->next;
    }
    pthread_mutex_unlock(&lock);
    return curr->value;
}

char* POP(Node** root){
    pthread_mutex_lock(&lock);
    if ((*root) == NULL){
        printf("ERROR: the stack is empty");
        exit(1);
    }
    Node* curr = *root;
    while(curr->next->next != NULL){
        curr = curr->next;
    }
    curr->next = NULL;
    pthread_mutex_unlock(&lock);
    return curr->next->value;
}
void CLEAR(Node** root){
    pthread_mutex_lock(&lock);
    (*root)->next = NULL;
    for(int i = 0; i < 1024; i++){
        (*root)->value[i] = '\0';
    }
    pthread_mutex_unlock(&lock);
}