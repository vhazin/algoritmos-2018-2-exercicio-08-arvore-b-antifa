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
    no->childs = malloc(sizeof(Node)*g);
    no->keys = malloc(sizeof(Node)*(g-1));
    no->n = 0;

    return no;

}


Node * insert(Node * no, int value,int G){
    if(no->folha == 1){
        no->keys[no->n] = value;
        no->n += 1;

    }else{
        int index = 0;
        while(no->keys[index] != NULL){
            if(value < no->keys[index]){
                
            }
            index++;
        }
    }

    if(no->n == (G-1)){
        //split
    }

    return no;
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