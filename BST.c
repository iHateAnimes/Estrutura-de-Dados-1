
//Inclusão da Biblioteca BST.H
//--------------------------------------------------------------------------------------------------------
#include "BST.h"
//--------------------------------------------------------------------------------------------------------
//Função principal que realiza as operações sobre a BST
//--------------------------------------------------------------------------------------------------------
int main(){
    int op,value,ok;
    BSTNode* temp;
    BSTNode* root = NULL;
    node* preOrder = NULL;
    node* inOrder = NULL;
    node* posOrder = NULL;
    node* levelOrder = NULL;
    while(1){
        system("clear");
        printf("\n ----------------------------------------------");
        printf("\n|  1 - Inserir um elemento                     |");
        printf("\n|  2 - Buscar um elemento                      |");
        printf("\n|  3 - Remover um elemento                     |");
        printf("\n|  4 - Imprimir caminho pre ordem              |");
        printf("\n|  5 - Imprimir caminho em ordem               |");
        printf("\n|  6 - Imprimir caminho pre ordem              |");
        printf("\n|  7 - Imprimir por níveis                     |");
        printf("\n|  8 - Imprimir a altura da árvore             |");
        printf("\n|  9 - Calcular caminho pré ordem              |");
        printf("\n| 10 - Calcular caminho em ordem               |");
        printf("\n| 11 - Calcular caminho pós ordem              |");
        printf("\n| 12 - Calcular caminho por níveis             |");
        printf("\n| 13 - Encontrar o maior elemento              |");
        printf("\n| 14 - Encontrar o menor elemento              |");
        printf("\n| 15 - Espelhar a árvore                       |");
        printf("\n| 16 - Construir a arvore utilizando caminhos  |");
        printf("\n| 17 - Calcular o peso da árvore               |");
        printf("\n| 18 - Calcular a quantidade de nós externos   |");
        printf("\n| 19 - Calcular a quantidade de nos internos   |");
        printf("\n| 20 - Verificar se a árvore está ordenada     |");
        printf("\n| 21 - Calcular a altura de um nó              |");
        printf("\n| 22 - Destruir a árvore                       |");
        printf("\n ----------------------------------------------");
        printf("\nOperação: ");
        scanf("%d",&op);
        if(op==1){
            printf("\nElemento de informação: ");
            scanf("%d",&value);
            root = insertBST(root,value);
        }
        else if(op==2){
            printf("\nElemento de informação: ");
            scanf("%d",&value);
            temp = searchBST(root,value);
            if(temp!=NULL) printf("\ntrue\n");
            else printf("\nfalse\n");
        }
        else if(op==3){
            Info* inf;
            printf("\nElemento de informação: ");
            scanf("%d",&value);
            inf = createInfo(value);
            root = deleteBST(root,inf);
            free(inf);
        }
        else if(op==4) PreOrderprintBST(root);
        else if(op==5) InOrderprintBST(root);
        else if(op==6) PosOrderprintBST(root);
        else if(op==7) PrintLevel(root);
        else if(op==8) printf("\nAltura: %d\n",heightBST(root));
        else if(op==9){
            preOrder = freeList(preOrder);
            preOrderTravesalBST(&preOrder,root);
            printList(preOrder);
        }
        else if(op==10){
            inOrder = freeList(inOrder);
            inOrderTravesalBST(&inOrder,root);
            printList(inOrder);
        }
        else if(op==11){
            posOrder = freeList(posOrder);
            posOrderTravesalBST(&posOrder,root);
            printList(posOrder);
        }
        else if(op==12){
            levelOrder = freeList(levelOrder);
            levelOrderTravesalBST(&levelOrder,root);
            printList(levelOrder);
        }
        else if(op==13){
            temp = findLargerstElement(root);
            if(temp!=NULL) printf("\nMaior elemento: %d\n",rootBST(temp)->value);
        }
        else if(op==14){
            temp = findSmallestElement(root);
            if(temp!=NULL) printf("\nMenor elemento: %d\n",rootBST(temp)->value);
        }
        else if(op==15) root = mirrorBST(root);
        else if(op==16) root = TreeFromInOrderPreOrderBST(root);
        else if(op==17) printf("\nPeso da árvore: %d\n",weightBST(root));
        else if(op==18) printf("\nQuantidade de nós externos: %d\n",totalExternalNodes(root));
        else if(op==19) printf("\nQuantidade de nós internos: %d\n",totalInternalNodes(root));
        else if(op==20){
            ok = isOrderedBST(root);
            if(ok==1) printf("\ntrue\n");
            else printf("\nfalse\n");
        }
        else if(op==21){
            scanf("%d",&value);
            printf("\nAltura do nó: %d\n",nodeHeight(root,value));
        }
        else if(op==22) root = destroyBST(root);
        else{
            root = destroyBST(root);
            preOrder = freeList(preOrder);
            inOrder = freeList(inOrder);
            posOrder = freeList(posOrder);
            levelOrder = freeList(levelOrder);
            printf("\n");
            return 0;
        }
        printf("\nPressione enter para continuar...");
        getchar();
        getchar();
    }
}
