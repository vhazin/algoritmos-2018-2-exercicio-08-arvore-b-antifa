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
        no->keys[no->n] = value;
        printf("%d",no->keys[no->n]);
        no->n += 1;
    }else{
        for(int i = 0 ; i < G;i++){
            if(value<no->keys[i]){
                newNode = insert(newNode,value, G);
                break;
            }
        }
    }

    if(newNode->n == G){
        Node * lNode = createNode(G);
        Node * rNode = createNode(G);
        
        int middle = newNode->n/2;
        for(int i = 0; i <middle;i++){
            lNode->keys[i] = newNode->keys[i];
        }

        for(int i = 0;i<middle;i++){
            rNode->keys[i] = newNode->keys[middle+1];
        }
        
        if(newNode->pai == NULL){
            newNode->keys[0] = newNode->keys[middle]; 
            newNode->childs[0] = lNode;
            lNode->pai = newNode;
            newNode->childs[1] = rNode;
            rNode->pai = newNode;
            newNode->folha = 0;
            
        }else{
            newNode->pai->keys[no->pai->n] = newNode->keys[middle];
            newNode->pai->childs[no->pai->n-1] = lNode;
            newNode->pai->childs[no->pai->n] = rNode;
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