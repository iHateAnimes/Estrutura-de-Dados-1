#include "AVL.h"
int main(){
    int op,ok;
    char word[53];
    AVLNode* temp;
    AVLNode* root = NULL;
    while(1){
        scanf("%d",&op);
        getchar();
        if(op==1){
            fgets(word,53,stdin);
            word[strlen(word)-1] = 0;
            root = insertAVL(root,word);
        }
        else if(op==2){
            fgets(word,53,stdin);
            word[strlen(word)-1] = 0;
            temp = searchAVL(root,word);
            if(temp!=NULL) printf("\ntrue\n");
            else printf("\nfalsezn");
        }
        else if(op==3){
            fgets(word,53,stdin);
            word[strlen(word)-1] = 0;
            root = deleteAVL(root,word);
        }
        else if(op==4) PrintLevel(root);
        else if(op==5) printHeights(root);
        else{
            destroyAVL(root);
            return 0;
        }
    }
}
