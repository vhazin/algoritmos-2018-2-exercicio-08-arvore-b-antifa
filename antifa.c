#include <stdio.h>
#include <stdlib.h>

typedef struct node {  // estrutura do nó
    int folha;  // flag de verificação se é folha ou não
    int n;   //numero chaves atualmente
    struct node * pai;  // ponteiro para o node pai
    struct node ** childs;  // ponteiro para os ponteiros de filhos
    int * keys;  //ponteiro para o array de chaves do nó
}Node;


Node * createNode(int g){
    
    Node * no = malloc(sizeof(Node));
    no->keys = (int *) malloc(sizeof(int)*(g-1)); // cria dinamicamente um array de chaves
    no->childs = (Node **) malloc(sizeof(int)*g); // cria dinamicamente o array de ponteiros para filhos
    no->n = 0;  // numero de chaves atualmente no nó
    return no;
    
}

Node * insert(Node * no, int value,int G){  // função para inserir que recebe o no a ser inserido, a chave e o grau da arvore
    Node * newNode = no;
    
    if(no->folha == 1){ // verifica se o no a ser inserido é folha
        no->keys[no->n] = value;   // se for folha insere a chave
        
        no->n += 1;   // incrementa o numero de chaves atualmente no nó
    }else{  // se não for um nó folha...
        if(value>newNode->keys[G-1]){
            newNode->childs[G] = insert(newNode->childs[G],value, G);
        }
        for(int i = 0 ; i < G;i++){
            if(value<no->keys[i]){
                newNode->childs[i] = insert(newNode->childs[i],value, G); // recursividade para inserir na folha dentro do nó chave
                break;
            }
        }
        
    }
    
    return newNode;
}

void printTree(Node * no){
    for(int i = 0; i<no->n;i++){
        printf("%d",no->keys[i]);
    }
    printf("\n");
    if(no->folha == 0){
        for(int i = 0; i<(no->n+1);i++){
            printTree(no->childs[i]);
        }
    }
}

int main(void){
    
    int G;
    printf("Insira o grau>> ");
    scanf("%d",&G);
    
    Node * masterNode = createNode(G); //cria a arvore
    masterNode->pai = NULL;
    masterNode->folha = 1;
    
    while(1){
        int value;
        printf("Digite o elemento para inserir >>");
        scanf("%d",&value);
        masterNode =  insert(masterNode,value,G);
        printTree(masterNode);
        
    }
    
    
    return 0;
}
