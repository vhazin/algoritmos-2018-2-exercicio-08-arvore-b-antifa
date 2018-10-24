#include <stdio.h>
#include <stdlib.h>

typedef struct node {  // estrutura do nó
    int folha;  // flag de verificação se é folha ou não
    int n;   //numero chaves atualmente
    struct node * pai;  // ponteiro para o node pai
    int fatherOfSplit;
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


Node * splitNode(Node * origin,int G){
    
    int childsSize = floor(G/2);
    int middle = childsSize+1;

    Node * left = createNode(childsSize);
    Node * right = createNode(childsSize);

    for(int i = 0;i<childsSize;i++){
        left->keys[i] = origin->keys[i];
        left->childs[i] = origin->childs[i];

        right->keys[i+1] = origin->keys[childsSize+i];
    }

    Node * parent = createNode(G);
    parent->keys[middle] = origin->keys[middle];
    parent->childs[0] = left;
    parent->childs[1] = right;

    return parent;
}
Node * insert(Node * no, int value,int G){  // função para inserir que recebe o no a ser inserido, a chave e o grau da arvore
    Node * newNode = no;
    
    if(newNode->folha == 1){ // verifica se o no a ser inserido é folha
        newNode->keys[newNode->n] = value;   // se for folha insere a chave
        
        newNode->n += 1;   // incrementa o numero de chaves atualmente no nó
    }else{ 
        Node * comingFromRecursion;
        int posicaoQueEntrou;

        if(value> no->keys[no->n]){
            
            posicaoQueEntrou = no->n+1;
            comingFromRecursion = insert(newNode->childs[posicaoQueEntrou],value, G); 
            
        }else{
            for(int i = 0 ; i < G;i++){
                if(value<no->keys[i]){
                    comingFromRecursion = insert(newNode->childs[i],value, G); 
                    posicaoQueEntrou = i;
                }
                break;
            }
        }
        
        if(comingFromRecursion->fatherOfSplit == 1){
            //TODO Insere no Nó
            
        }else{
            no->childs[posicaoQueEntrou] = comingFromRecursion;
        }
        
    }
    

    if(newNode->n ==G){
        Node * father = createNode(2);
        father = splitNode(newNode,G);
        father->fatherOfSplit = 1;
        return father;
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
    masterNode->folha = 0;
    masterNode->keys[0] = 10;

    Node * child = createNode(G);
    child->folha = 1;
    masterNode->childs[0] = child;
    
    while(1){
        int value;
        printf("Digite o elemento para inserir >>");
        scanf("%d",&value);
        masterNode =  insert(masterNode,value,G);
        printTree(masterNode);
        
    }
    
    
    return 0;
}
