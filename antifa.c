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
        printf("%d",no->keys[no->n]);
        no->n += 1;   // incrementa o numero de chaves atualmente no nó
    }else{  // se não for um nó folha...
        for(int i = 0 ; i < G;i++){
            if(value<no->keys[i]){
                newNode = insert(newNode,value, G); // recursividade para inserir na folha dentro do nó chave
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
    
    Node * masterNode = createNode(G); //cria a arvore
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
