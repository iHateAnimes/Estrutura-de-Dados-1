//--------------------------------------------------------------------------------------------------------
//Inclusão das bibliotecas padrões do C
//--------------------------------------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <cstring>
//--------------------------------------------------------------------------------------------------------
//Definição da estrutura Info, que segura os elementos de informação
//--------------------------------------------------------------------------------------------------------
typedef struct{
    char* word;
}Info;
//--------------------------------------------------------------------------------------------------------
//Definição da estrutura AVLNode 
//--------------------------------------------------------------------------------------------------------
typedef struct tnode{
    struct tnode *left;
    struct tnode *right;
    int height;
    Info *info;
}AVLNode;
//--------------------------------------------------------------------------------------------------------
//Função que calcula o valor inteiro de cada palavra
//--------------------------------------------------------------------------------------------------------
int wordValue(char* word){
    int soma=0,i;
    for(i=0;i<strlen(word);i++) soma+=(int)(word[i]);
    return soma;
}
//--------------------------------------------------------------------------------------------------------
//Função que cria um elemento de informação para a AVL
//--------------------------------------------------------------------------------------------------------
Info* createInfo(char *word){
    Info* newInfo = (Info *)malloc(sizeof(Info));
    if(newInfo!=NULL){
        newInfo->word = (char *)malloc(strlen(word)*sizeof(char)+1);
        strcpy(newInfo->word,word);
    }
    return newInfo;
}
//--------------------------------------------------------------------------------------------------------
//Função que cria um no para uma AVL
//--------------------------------------------------------------------------------------------------------
AVLNode* createAVLNode(char* word){
    AVLNode* newnode;
    Info* info = createInfo(word);
    if(info!=NULL){
        newnode = (AVLNode *)malloc(sizeof(AVLNode));
        if(newnode!=NULL){
            newnode->info = info;
            newnode->left = newnode->right = NULL;
        }
    }
    return newnode;
}
//--------------------------------------------------------------------------------------------------------
//Função que retorna um ponteiro para o elemento a direita de um AVLNode
//--------------------------------------------------------------------------------------------------------
AVLNode* rightAVL(AVLNode* root){
    return root->right;
}
//--------------------------------------------------------------------------------------------------------
//Função que retorna um ponteiro para o elemento a esquerda de um AVLNode
//--------------------------------------------------------------------------------------------------------
AVLNode* leftAVL(AVLNode* root){
    return root->left;
}
//--------------------------------------------------------------------------------------------------------
//Função que retorna um ponteiro para o elemento de informação de um AVLNode
//--------------------------------------------------------------------------------------------------------
Info* rootAVL(AVLNode* root){
    return root->info;
}
//--------------------------------------------------------------------------------------------------------
//Função que retorna se a AVL está vazia ou não
//--------------------------------------------------------------------------------------------------------
int isEmpty(AVLNode* root){
    if(root!=NULL) return 0;
    return 1;
}
//--------------------------------------------------------------------------------------------------------
//Função que calcula a altura de uma AVL
//--------------------------------------------------------------------------------------------------------
int heightAVL(AVLNode* root){
    int lH = 0,rH = 0;
    if(root==NULL) return 0;
    lH = 1 + heightAVL(leftAVL(root));
    rH = 1 + heightAVL(rightAVL(root));
    if(rH>lH) return rH;
    else return lH;
}
//--------------------------------------------------------------------------------------------------------
//Função que calcula o peso de uma AVL
//--------------------------------------------------------------------------------------------------------
int weightAVL(AVLNode* root){
    if(root==NULL) return 0;
    return 1 + weightAVL(leftAVL(root)) + weightAVL(rightAVL(root));
}
//--------------------------------------------------------------------------------------------------------
//Função que imprime uma AVL por níveis
//--------------------------------------------------------------------------------------------------------
void auxPrintLevel(AVLNode* ref,int level){
    if(!ref) return;
    int i = 0;
    if(level==1) printf("%s ",rootAVL(ref)->word);
    else if(level>1){
        auxPrintLevel(leftAVL(ref),level-1);
        auxPrintLevel(rightAVL(ref),level-1);
    }
    return;
}
void PrintLevel(AVLNode* root){
    int levels = heightAVL(root);
    int i,j;
    for(i=1;i<=levels;i++){
        printf("\nNível %d: ",i);
        auxPrintLevel(root,i);
    }
    printf("\n");
}
//--------------------------------------------------------------------------------------------------------
//Função que imprime os nível de cada AVLNode
//--------------------------------------------------------------------------------------------------------
void auxPrintHeights(AVLNode* ref,int level){
    if(!ref) return;
    int i = 0;
    if(level==1){
        printf("%d ",ref->height);
    }
    else if(level>1){
        auxPrintHeights(leftAVL(ref),level-1);
        auxPrintHeights(rightAVL(ref),level-1);
    }
    return;
}
void printHeights(AVLNode* root){
    int levels = heightAVL(root);
    int i,j;
    for(i=1;i<=levels;i++){
        printf("\nNível %d: ",i);
        auxPrintHeights(root,i);
    }
    printf("\n");
}
//--------------------------------------------------------------------------------------------------------
//Função que busca um elemento numa AVL
//--------------------------------------------------------------------------------------------------------
AVLNode* searchAVL(AVLNode* root,char* word){
    AVLNode* ref;
    if(root==NULL || strcmp(rootAVL(root)->word,word)==0){
        return root;
    }
    else{
        if(strcmp(rootAVL(root)->word,word)>0) ref = searchAVL(leftAVL(root),word);
        else ref = searchAVL(rightAVL(root),word);
    }
    return ref;
}
//--------------------------------------------------------------------------------------------------------
//Função que busca o menor elemento de uma AVL
//--------------------------------------------------------------------------------------------------------
AVLNode* findSmallestElement(AVLNode* root){
    if(leftAVL(root)==NULL) return root;
    return findSmallestElement(leftAVL(root));
}
//--------------------------------------------------------------------------------------------------------
//Função que busca o maior elemento de uma AVL
//--------------------------------------------------------------------------------------------------------
AVLNode* findLargerstElement(AVLNode* root){
    if(rightAVL(root)==NULL) return root;
    else return findLargerstElement(rightAVL(root));
}
//--------------------------------------------------------------------------------------------------------
//Função que destrói uma AVL
//--------------------------------------------------------------------------------------------------------
void destroyAVL(AVLNode* root){
    if(root==NULL) return;
    destroyAVL(rightAVL(root));
    destroyAVL(leftAVL(root));
    free(root->info->word);
    free(root->info);
    free(root);
}
//--------------------------------------------------------------------------------------------------------
//Função que define o balanço da AVL
//--------------------------------------------------------------------------------------------------------
void setHeightAVL(AVLNode *root){
    if(root==NULL) return;
    setHeightAVL(rightAVL(root));
    setHeightAVL(leftAVL(root));
    root->height =  heightAVL(leftAVL(root)) - heightAVL(rightAVL(root));
    return;
}
//--------------------------------------------------------------------------------------------------------
//Função que realiza uma rotação LL
//--------------------------------------------------------------------------------------------------------
void rotationLL(AVLNode **root){
    AVLNode* aux;
    aux = leftAVL(*root);
    (*root)->left = aux->right;
    aux->right = *root;
    (*root) = aux;
}
//--------------------------------------------------------------------------------------------------------
//Função que realiza uma rotação RR
//--------------------------------------------------------------------------------------------------------
void rotationRR(AVLNode **root){
    AVLNode* aux;
    aux = rightAVL(*root);
    (*root)->right = aux->left;
    aux->left = *root;
    (*root) = aux;
}
//--------------------------------------------------------------------------------------------------------
//Função que realiza uma rotação LR
//--------------------------------------------------------------------------------------------------------
void rotationLR(AVLNode **root){
    rotationRR(&(*root)->left);
    rotationLL(root);
}
//--------------------------------------------------------------------------------------------------------
//Função que realiza uma rotação RL
//--------------------------------------------------------------------------------------------------------
void rotationRL(AVLNode **root){
    rotationLL(&(*root)->right);
    rotationRR(root);
}
//--------------------------------------------------------------------------------------------------------
//Função que balanceia uma AVL
//--------------------------------------------------------------------------------------------------------
void BalanceAVL(AVLNode** root){
    if((*root)->height==2){
        if((*root)->left!=NULL && (*root)->left->height<=-1) rotationLR(root);
        else rotationLL(root);
    }
    else if((*root)->height==-2){
        if((*root)->right!=NULL && (*root)->right->height>=1) rotationRL(root);
        else rotationRR(root);
    }
    (*root)->height = heightAVL((*root)->left) - heightAVL((*root)->right);
    return;
}
//--------------------------------------------------------------------------------------------------------
//Função que insere um elemento em uma AVL
//--------------------------------------------------------------------------------------------------------
AVLNode* auxInsertAVL(AVLNode *root,char* word){
    if(root==NULL) return createAVLNode(word);
    else if(strcmp(word,rootAVL(root)->word) < 0) root->left = auxInsertAVL(leftAVL(root),word);
    else root->right = auxInsertAVL(rightAVL(root),word);
    root->height = heightAVL(root->left) - heightAVL(root->right);
    if(abs(root->height)==2) BalanceAVL(&root);
    return root;
}
AVLNode* insertAVL(AVLNode *root,char *word){
    root = auxInsertAVL(root,word);
    setHeightAVL(root);
    return root;
}
//--------------------------------------------------------------------------------------------------------
//Função que deleta um elemento de uma AVL
//--------------------------------------------------------------------------------------------------------
AVLNode* auxDeleteAVL(AVLNode* root,char* word){
    if(root==NULL) return root;
    if(strcmp(word,rootAVL(root)->word) > 0) root->right = auxDeleteAVL(rightAVL(root),word);
    else if(strcmp(word,rootAVL(root)->word) < 0) root->left = auxDeleteAVL(leftAVL(root),word);
    else{
        AVLNode* temp;
        if(leftAVL(root)==NULL){
            temp = root->right;
            free(root->info->word);
            free(root->info);
            free(root);
            return temp;
        }
        else if(rightAVL(root)==NULL){
            temp = root->left;
            free(root->info->word);
            free(root->info);
            free(root);
            return temp;
        }
        else{
            temp = findLargerstElement(leftAVL(root));
            strcpy(root->info->word,temp->info->word);
            root->left = auxDeleteAVL(leftAVL(root),temp->info->word); 
        }
    }
    root->height = heightAVL(root->left) - heightAVL(root->right);
    if(abs(root->height)==2) BalanceAVL(&root);
    return root;
}

AVLNode* deleteAVL(AVLNode* root,char* word){
    root = auxDeleteAVL(root,word);
    setHeightAVL(root);
    return root;
}
//--------------------------------------------------------------------------------------------------------
