#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int folha;
    int n;
    struct node * pai;
    struct node ** childs;
    int * keys;
}Node;


Node * createNode(int g){

    Node * no = malloc(sizeof(Node));
    no->keys = (int *) malloc(sizeof(int)*(g-1));
    no->childs = (Node **) malloc(sizeof(int)*g);
    no->n = 0;

    return no;

}

Node * insert(Node * no, int value,int G){
    Node * newNode = no;

    if(no->folha == 1){
        newNode->keys[newNode->n] = value;
        printf("%d",no->keys[newNode->n]);
        newNode->n += 1;
    }else{
        
    }

    if(no->n == G){
        Node * lNode = createNode(G);
        Node * rNode = createNode(G);

        int middle = ((no->n)/2)+1;
        for(int i = 0; i <middle;i++){
            lNode->keys[i] = no->keys[i];
        }

        for(int i = 0;i<middle;i++){
            rNode->keys[i] = no->keys[middle+1];
        }
        
        if(no->pai == NULL){
            newNode->keys = newNode->keys[middle]; 
            newNode->childs[0] = lNode;
            lNode->pai = newNode;
            rNode->pai = newNode;
            newNode->childs[1] = rNode;
            newNode->folha = 0;
        }else{
            no->pai->keys[no->pai->n] = no->keys[middle];
            no->pai->childs[no->pai->n-1] = lNode;
            no->pai->childs[no->pai->n] = rNode;
        }
        
        
    }
    return newNode;
}

int main(void){

    int G;
    printf("Insira o grau>> ");
    scanf("%d",&G);

    Node * masterNode = createNode(G);
    masterNode->pai = NULL;
    masterNode->folha = 1;
    
    while(1){
        int value;
        printf("Digite o elemento para inserir >>");
        scanf("%d",&value);
        masterNode =  insert(masterNode,value,G);
        
    }


    return 0;
}