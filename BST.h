//Inclusão das bibliotecas padrões do C
//--------------------------------------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
//--------------------------------------------------------------------------------------------------------
//Definição da estrutura que segura o elemento de informação
//--------------------------------------------------------------------------------------------------------
typedef struct{
    int value;
}Info;
//--------------------------------------------------------------------------------------------------------
//Definição da estrutura BSTNode
//--------------------------------------------------------------------------------------------------------
typedef struct tnode{
    struct tnode *left;
    struct tnode *right;
    Info *info;
}BSTNode;
//--------------------------------------------------------------------------------------------------------
//Função que cria o elemento de informação tanto dos BSTNodes e dos Nodes
//--------------------------------------------------------------------------------------------------------
typedef struct _node{
    struct _node *next;
    struct _node *prev;
    Info* info;
}node;
//--------------------------------------------------------------------------------------------------------
//Função que cria o elemento de informação tanto dos BSTNodes e dos Nodes
//--------------------------------------------------------------------------------------------------------
Info* createInfo(int value){
    Info* newInfo = (Info *)malloc(sizeof(Info));
    if(newInfo!=NULL) newInfo->value = value;
    return newInfo;
}
//--------------------------------------------------------------------------------------------------------
//Função cria um elemento no para lista
//--------------------------------------------------------------------------------------------------------
node* createNode(int value){
    node* newnode;
    newnode = (node *)malloc(sizeof(node));
    if(newnode!=NULL){
        newnode->next = NULL;
        newnode->prev = NULL;
        newnode->info = createInfo(value);
    }
    return newnode;
}
//--------------------------------------------------------------------------------------------------------
//Função que insere um elemento na ultima posição da lista
//--------------------------------------------------------------------------------------------------------
void insertLast(node **first,int value){
    node* newnode = createNode(value);
    if(*first==NULL) *first = newnode;
    else{
        node* aux;
        aux = *first;
        while(aux->next!=NULL){
            aux = aux->next;
        }
        newnode->prev = aux;
        aux->next = newnode;
    }
}
//--------------------------------------------------------------------------------------------------------
//Função que da destroi uma lista
//--------------------------------------------------------------------------------------------------------
node* freeList(node* first){
    node* aux;
    while(first!=NULL){
        aux = first;
        first = first->next;
        free(aux->info);
        free(aux);
    }
    return NULL;
}
//--------------------------------------------------------------------------------------------------------
//Função que imprime uma lista
//--------------------------------------------------------------------------------------------------------
void printList(node* first){
    node* aux = first;
    while(aux!=NULL){
        printf("%d ",aux->info->value);
        aux = aux->next;
    }
    printf("\n");
}   
//--------------------------------------------------------------------------------------------------------
//Função que busca um elemento em uma lista
//--------------------------------------------------------------------------------------------------------
node* findList(node* first,int value){
    node* aux = first;
    while(aux!=NULL && aux->info->value!=value){
        aux  = aux->next;
    }
    return aux;
}
int infoList(node* no){
    return no->info->value;
}
//--------------------------------------------------------------------------------------------------------
//Função que cria um nó para uma BST
//--------------------------------------------------------------------------------------------------------
BSTNode* createBSTNode(int value){
    BSTNode* newnode;
    Info* info = createInfo(value);
    if(info!=NULL){
        newnode = (BSTNode *)malloc(sizeof(BSTNode));
        if(newnode!=NULL){
            newnode->info = info;
            newnode->left = newnode->right = NULL;
        }
    }
    return newnode;
}
//--------------------------------------------------------------------------------------------------------
//Função que retorna um ponteiro para o elemento a direita de um BSTNode
//--------------------------------------------------------------------------------------------------------
BSTNode* rightBST(BSTNode* root){
    return root->right;
}
//--------------------------------------------------------------------------------------------------------
//Função que retorna um ponteiro para o elemento a esquerda de um BSTNode
//--------------------------------------------------------------------------------------------------------
BSTNode* leftBST(BSTNode* root){
    return root->left;
}
//--------------------------------------------------------------------------------------------------------
//Função que retorna um ponteiro para o elemento de informação de um BSTNode
//--------------------------------------------------------------------------------------------------------
Info* rootBST(BSTNode* root){
    return root->info;
}
//--------------------------------------------------------------------------------------------------------
//Função que verifica se uma BST está vazia ou não
//--------------------------------------------------------------------------------------------------------
int isEmpty(BSTNode* root){
    if(root!=NULL) return 0;
    return 1;
}
//--------------------------------------------------------------------------------------------------------
//Função que verifica o caminho entre dois ponteiros
//--------------------------------------------------------------------------------------------------------
int checkPath(node* first,node* last){
    while(first!=NULL){
        if(first==last) return 1;
        first = first->next;
    }
    return 0;
}
//--------------------------------------------------------------------------------------------------------
//Função que calcula a altura de uma BST
//--------------------------------------------------------------------------------------------------------
int heightBST(BSTNode* root){
    int lH = 0,rH = 0;
    if(root==NULL) return 0;
    lH = 1 + heightBST(leftBST(root));
    rH = 1 + heightBST(rightBST(root));
    if(rH>lH) return rH;
    else return lH;
}
//--------------------------------------------------------------------------------------------------------
//Função que calcula o peso de uma BSTs
//--------------------------------------------------------------------------------------------------------
int weightBST(BSTNode* root){
    if(root==NULL) return 0;
    return 1 + weightBST(leftBST(root)) + weightBST(rightBST(root));
}
//--------------------------------------------------------------------------------------------------------
//Função que verifica se uma BST está ordenada
//--------------------------------------------------------------------------------------------------------
int isOrderedBST(BSTNode* root){
    if(root==NULL) return 1;
    if(leftBST(root)!=NULL){
        if(rootBST(leftBST(root))->value > rootBST(root)->value) return 0;
    }
    if(rightBST(root)!=NULL){
        if(rootBST(rightBST(root))->value < rootBST(root)->value) return 0;

    }
    return(isOrderedBST(leftBST(root)) && isOrderedBST(rightBST(root)));
}
//--------------------------------------------------------------------------------------------------------
//Função que calcula a altura de um BSTNode
//--------------------------------------------------------------------------------------------------------
int auxNodeHeight(BSTNode *root,int value){
    if(root==NULL) return 0;
    if(rootBST(root)->value==value) return 1;
    else if(rootBST(root)->value > value) return 1 + auxNodeHeight(leftBST(root),value);
    else return 1 + auxNodeHeight(rightBST(root),value);
}
int nodeHeight(BSTNode* root,int value){
    int height = auxNodeHeight(root,value);
    return heightBST(root) - height;
}
//--------------------------------------------------------------------------------------------------------
//Função que calcula a quantidade de nós externos de uma BST
//--------------------------------------------------------------------------------------------------------
int totalExternalNodes(BSTNode* root){
    if(root==NULL) return 0;
    if(leftBST(root)==NULL && rightBST(root)==NULL) return 1;
    return totalExternalNodes(leftBST(root)) + totalExternalNodes(rightBST(root));
}
//--------------------------------------------------------------------------------------------------------
//Função que calcula a quantidade de nós internos de uma BST
//--------------------------------------------------------------------------------------------------------
int totalInternalNodes(BSTNode* root){
    if(root==NULL) return 0;
    if(leftBST(root)==NULL && rightBST(root)==NULL) return 0;
    return 1 + totalInternalNodes(leftBST(root)) + totalInternalNodes(rightBST(root));
}
//--------------------------------------------------------------------------------------------------------
//Funções que imprime o caminho pré ordem de uma BST
//--------------------------------------------------------------------------------------------------------
void auxPreOrderprintBST(BSTNode* root){
    if(root==NULL) return;
    printf("%d ",rootBST(root)->value);
    auxPreOrderprintBST(leftBST(root));
    auxPreOrderprintBST(rightBST(root));
}
void PreOrderprintBST(BSTNode* root){
    printf("\nCaminho pré-Ordem: ");
    auxPreOrderprintBST(root);
    printf("\n");
}
//--------------------------------------------------------------------------------------------------------
//Funções que imprime o caminho em ordem de uma BST
//--------------------------------------------------------------------------------------------------------
void auxInOrderprintBST(BSTNode* root){
    if(root==NULL) return;
    auxInOrderprintBST(leftBST(root));
    printf("%d ",rootBST(root)->value);
    auxInOrderprintBST(rightBST(root));
}
void InOrderprintBST(BSTNode* root){
    printf("\nCaminho em-Ordem: ");
    auxInOrderprintBST(root);
    printf("\n");
}
//--------------------------------------------------------------------------------------------------------
//Funções que imprime o caminho pos ordem de uma BST
//--------------------------------------------------------------------------------------------------------
void auxPosOrderprintBST(BSTNode* root){
    if(root==NULL) return;
    auxPosOrderprintBST(leftBST(root));
    auxPosOrderprintBST(rightBST(root));
    printf("%d ",rootBST(root)->value);
}
void PosOrderprintBST(BSTNode* root){
    printf("\nCaminho pos-Ordem: ");
    auxPosOrderprintBST(root);
    printf("\n");
}
//--------------------------------------------------------------------------------------------------------
//Funções que imprime uma BST por níveis
//--------------------------------------------------------------------------------------------------------
void auxPrintLevel(BSTNode* ref,int level){
    if(!ref) return;
    int i = 0;
    if(level==1){
        printf("%d ",rootBST(ref)->value);
    }
    else if(level>1){
        auxPrintLevel(leftBST(ref),level-1);
        auxPrintLevel(rightBST(ref),level-1);
    }
    return;
}
void PrintLevel(BSTNode* root){
    int levels = heightBST(root);
    int i,j;
    for(i=1;i<=levels;i++){
        printf("\nNível %d: ",i);
        auxPrintLevel(root,i);
    }
    printf("\n");
}
//--------------------------------------------------------------------------------------------------------
//Função que busca um elemento numa BST
//--------------------------------------------------------------------------------------------------------
BSTNode* searchBST(BSTNode* root,int value){
    BSTNode* ref;
    if(root==NULL || rootBST(root)->value == value){
        return root;
    }
    else{
        if(rootBST(root)->value < value) ref = searchBST(rightBST(root),value);
        else ref = searchBST(leftBST(root),value);
    }
    return ref;
}
//--------------------------------------------------------------------------------------------------------
//Função que busca o menor elemento de uma BST
//--------------------------------------------------------------------------------------------------------
BSTNode* findSmallestElement(BSTNode* root){
    if(leftBST(root)==NULL) return root;
    return findSmallestElement(leftBST(root));
}
//--------------------------------------------------------------------------------------------------------
//Função que busca o maior elemento de uma BST
//--------------------------------------------------------------------------------------------------------
BSTNode* findLargerstElement(BSTNode* root){
    if(rightBST(root)==NULL) return root;
    else return findLargerstElement(rightBST(root));
}
//--------------------------------------------------------------------------------------------------------
//Função que insere um elemento numa BST
//--------------------------------------------------------------------------------------------------------
BSTNode* auxInsertBST(BSTNode *root,int value){
    if(searchBST(root,value)!=NULL) return root;
    if(root==NULL) return createBSTNode(value);
    else if(value < rootBST(root)->value) root->left = auxInsertBST(leftBST(root),value);
    else root->right = auxInsertBST(rightBST(root),value);
    return root;
}
BSTNode* insertBST(BSTNode* root,int value){
    if(searchBST(root,value)!=NULL) return root;
    root = auxInsertBST(root,value);
    return root;
}
//--------------------------------------------------------------------------------------------------------
//Função que destroi uma BST
//--------------------------------------------------------------------------------------------------------
BSTNode* destroyBST(BSTNode* root){
    if(!root) return NULL;
    destroyBST(rightBST(root));
    destroyBST(leftBST(root));
    free(root->info);
    free(root);
    return NULL;
}
//--------------------------------------------------------------------------------------------------------
//Função que deleta um elemento de uma BST
//--------------------------------------------------------------------------------------------------------
BSTNode* auxDeleteBST(BSTNode* root,Info* inf){
    if(root==NULL) return root;
    if(inf->value > rootBST(root)->value) root->right = auxDeleteBST(rightBST(root),inf);
    else if(inf->value < rootBST(root)->value) root->left = auxDeleteBST(leftBST(root),inf);
    else{
        BSTNode* temp;
        if(leftBST(root)==NULL){
            temp = root->right;
            free(root->info);
            free(root);
            return temp;
        }
        else if(rightBST(root)==NULL){
            temp = root->left;
            free(root->info);
            free(root);
            return temp;
        }
        else{
            temp = findLargerstElement(leftBST(root));
            root->info->value= temp->info->value;
            root->left = auxDeleteBST(leftBST(root),temp->info); 
        }
    }
    return root;
}

BSTNode* deleteBST(BSTNode* root,Info* inf){
    BSTNode* aux = searchBST(root,inf->value);
    if(aux != NULL) root = auxDeleteBST(root,inf);
    return root;
}
//--------------------------------------------------------------------------------------------------------
//Função que espelha uma BST
//--------------------------------------------------------------------------------------------------------
BSTNode* auxMirrorBST(BSTNode* root){
    if(root!=NULL){
        BSTNode* aux  = root->left;
        root->left = root->right;
        root->right = aux;
        auxMirrorBST(root->right);
        auxMirrorBST(root->left);
    }
    return root;
}
BSTNode* mirrorBST(BSTNode* root){
    root = auxMirrorBST(root);
    printf("\nArvore espelhada: \n");
    PreOrderprintBST(root);
    InOrderprintBST(root);
    PosOrderprintBST(root);
    PrintLevel(root);
    root = auxMirrorBST(root);
    return root;
}
//--------------------------------------------------------------------------------------------------------
//Função que cria uma lista com o caminho pre ordem da BST
//--------------------------------------------------------------------------------------------------------
void auxPreOrderTravesalBST(node **first,BSTNode* root){
    if(root==NULL) return;
    insertLast(first,rootBST(root)->value);
    auxPreOrderTravesalBST(first,leftBST(root));
    auxPreOrderTravesalBST(first,rightBST(root));
}
void preOrderTravesalBST(node **first, BSTNode *root){
    printf("\nCaminho pré-Ordem: ");
    auxPreOrderTravesalBST(first,root);
}
//--------------------------------------------------------------------------------------------------------
//Função que cria uma lista com o caminho em ordem da BST
//--------------------------------------------------------------------------------------------------------
void auxInOrderTravesalBST(node **first,BSTNode* root){
    if(root==NULL) return;
    auxInOrderTravesalBST(first,leftBST(root));
    insertLast(first,rootBST(root)->value);
    auxInOrderTravesalBST(first,rightBST(root));
}
void inOrderTravesalBST(node **first,BSTNode* root){
    printf("\nCaminho pos-Ordem: ");
    auxInOrderTravesalBST(first,root);
}
//--------------------------------------------------------------------------------------------------------
//Função que cria uma lista com o caminho pos ordem da BST
//--------------------------------------------------------------------------------------------------------
void auxPosOrderTravesalBST(node **first,BSTNode* root){
    if(root==NULL) return;
    auxPosOrderTravesalBST(first,leftBST(root));
    auxPosOrderTravesalBST(first,rightBST(root));
    insertLast(first,rootBST(root)->value);
}
void posOrderTravesalBST(node **first, BSTNode *root){
    printf("\nCaminho pos-Ordem: ");
    auxPosOrderTravesalBST(first,root);
}
//--------------------------------------------------------------------------------------------------------
//Função que cria uma lista com o caminho por nível da BST
//--------------------------------------------------------------------------------------------------------
void auxLevelOrderTravesalBST(BSTNode* ref,node** first,int level){
    if(!ref) return;
    int i = 0;
    if(level==1){
        insertLast(first,rootBST(ref)->value);
    }
    else if(level>1){
        auxLevelOrderTravesalBST(leftBST(ref),first,level-1);
        auxLevelOrderTravesalBST(rightBST(ref),first,level-1);
    }
    return;
}
void levelOrderTravesalBST(node** first,BSTNode* root){
    printf("\nCaminho por níveis: ");
    int levels = heightBST(root);
    int i,j;
    for(i=1;i<=levels;i++) auxLevelOrderTravesalBST(root,first,i);
}
//--------------------------------------------------------------------------------------------------------
//Função que constrói uma BST a partir dos caminhos pré ordem e em ordem
//--------------------------------------------------------------------------------------------------------
BSTNode* auxTreeFromInOrderPreOrderBST(node* in, node** pre, node* inStrt, node* inEnd){
    if (inStrt==NULL || inEnd==NULL || (checkPath(inStrt,inEnd)==0)) return NULL; 
    BSTNode*  newNode = createBSTNode(infoList(*pre)); 
    (*pre) = (*pre)->next;
    if (inStrt == inEnd) 
        return newNode; 
    node* aux = findList(in, rootBST(newNode)->value); 
    newNode->left = auxTreeFromInOrderPreOrderBST(in, pre, inStrt, aux->prev); 
    newNode->right = auxTreeFromInOrderPreOrderBST(in, pre, aux->next, inEnd); 
    return newNode; 
} 
BSTNode* TreeFromInOrderPreOrderBST(BSTNode* root){
    int size,i,value;
    node* pre = NULL, *in = NULL;
    //printf("Quantidade de elementos da árvore: ");
    scanf("%d",&size);
    //printf("\nDigite os elementos da lista pre-ordem: ");
    for(i=0;i<size;i++){
        scanf("%d",&value);
        insertLast(&pre,value);
    }
    printf("\nCaminho pre-Ordem: ");
    printList(pre);
    //printf("\nDigite os elementos da lista em-ordem: ");
    for(i=0;i<size;i++){
        scanf("%d",&value);
        insertLast(&in,value);
    }
    printf("\nCaminho em-Ordem: ");
    printList(in);
    root = destroyBST(root);
    node* aux1,*aux2,*aux3;
    aux3 = pre;
    aux1 = in;
    aux2 = aux1;
    while(aux2->next!=NULL) aux2 = aux2->next;
    root = auxTreeFromInOrderPreOrderBST(in,&pre,aux1,aux2);
    pre = freeList(aux3);
    in = freeList(in);
    return root;
}
//--------------------------------------------------------------------------------------------------------
