//--------------------------------------------------------------------------------------------------------
//Inclusão da biblioteca Hash Table
//--------------------------------------------------------------------------------------------------------
#include "HT.h"
//--------------------------------------------------------------------------------------------------------
//Função que realiza operações sobre a Hast Table
//--------------------------------------------------------------------------------------------------------
int main(){
    int op,ok,i;
    char word[53];
    AVLNode* temp;
    HT hashTable[TAM+1];
    for(i=0;i<TAM;i++){
        hashTable[i].root = NULL;
        hashTable[i].size = 0;
    }
    while(1){
        /*system("clear");
        printf(" ------------------------------------------------------\n");
        printf("| 1 - Inserir um elemento                               |\n");
        printf("| 2 - Buscar um elemento                                |\n");
        printf("| 3 - Remover um elemento                               |\n");
        printf("| 4 - Imprimir todos elementos                          |\n");
        printf("| 5 - Imprimir os elementos de uma posição              |\n");
        printf("| 6 - Calcular a quantidade de elementos                |\n");
        printf("| 7 - Calcular a quantidade de elementos de uma posição |\n");
        printf("| 8 - Destruir a HashTable                              |\n");
        printf("| 9 - Destruir uma posição da HashTable                 |\n");
        printf(" -------------------------------------------------------\n");
        printf("\nOperação: ");*/
        scanf("%d",&op);
        getchar();
        if(op==1){
            fgets(word,53,stdin);
            word[strlen(word)-1] = 0;
            ok = insertHT(hashTable,word);
            //if(ok==1) printf("true\n");
            //else printf("false\n");
            //printf("Inserido na posição : %d\n",ok);
        }
        else if(op==2){
            fgets(word,53,stdin);
            word[strlen(word)-1] = 0;
            temp = searchHT(hashTable,word);
            if(temp!=NULL) printf("true\n");
            else printf("\nfalse\n");
        }
        else if(op==3){
            fgets(word,53,stdin);
            word[strlen(word)-1] = 0;
            ok = deleteHT(hashTable,word);
            //if(ok==1) printf("true\n");
            //else printf("false\n");
            //printf("deletado na posição : %d\n",ok);
        }
        else if(op==4) printHT(hashTable);
        else if(op==5){
            scanf("%d",&i);
            getchar();
            printPos(hashTable,i);
            printf("\n");
        }
        else if(op==6) printf("%d\n",weightHT(hashTable));
        else if(op==7){
            scanf("%d",&i);
            getchar();
            printf("%d\n",posWeightHT(hashTable,i));
        }
        else if(op==8) destroyHT(hashTable);
        else if(op==9){
            scanf("%d",&i);
            getchar();
            posDestroyHT(hashTable,i);
        }
        else{
            destroyHT(hashTable);
            return 0;
        }
        //printf("\nPressione enter para continuar...\n");
        //getchar();
    }
}
//--------------------------------------------------------------------------------------------------------
