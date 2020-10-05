#include "cod.h"

node* createNode(char chr){
    node* newnode = NULL;
    newnode = (node *)malloc(sizeof(node));
    if(!newnode) return NULL;
    newnode->chr = chr;
    return newnode;
}
void insertLast(node** last,char chr){
    node* newnode;
    newnode = createNode(chr);
    if(newnode==NULL) return;
    newnode->prev = (*last);
    (*last)->next = newnode;
    (*last) = newnode;
    return;
}
void printList(node* first){
    node* aux = first;
    printf("\n");
    while(aux!=NULL){
        printf("%c",aux->chr);
        aux = aux->next;
    }
    printf("\n");
    return;
}
void reverseList(node** firstRef,node **lastRef){
    node *prev,*cur,*next;
    prev = (*firstRef)->prev;
    cur = *firstRef;
    while(cur!=NULL){
        next = cur->next;
        cur->next = prev;
        cur->prev = next;
        prev = cur;
        cur = next;
    }
    *lastRef = *firstRef;
    *firstRef = prev;
    return;
}
void reverseSublist(node *firstRef, node *lastRef){
    node* aux1=NULL;
    node* aux2=NULL;
    printf("\nAntes de inverter: ");
    printf("\n%c    - primeiro",firstRef->chr);
    printf("\n%c    - ultimo",lastRef->chr);
    if(firstRef->prev!=NULL){
        printf("Entro");
        aux1 = firstRef->prev;
        aux1->next = NULL;
    }
    if(lastRef->next!=NULL){
        aux2 = (lastRef)->next;
        aux2->prev = NULL;
    }
    firstRef->prev = NULL;
    lastRef->next = NULL;
    reverseList(&firstRef,&lastRef);
    if(aux1!=NULL){
        (firstRef)->prev = aux1;
        aux1->next = (firstRef);
    }
    if(aux2!=NULL){
        (lastRef)->next = aux2;
        aux2->prev = (lastRef);
    }
    return;
}
void readText(node** first,node** last){
    char chr;
    while(1){
        scanf("%c",&chr);
        if(chr=='\n'){
            return;
        }
        if(*first==NULL){
            *first = createNode(chr);
            *last = *first;
        }
        else insertLast(last,chr);
    }
}
int isNonVogal(char chr){
    int i;
    char vogals[] = "aeiouAEIOU";
    for(i=0;i<10;i++){
        if(chr==vogals[i]) return 0;
    }
    return 1;
}
void findSeq(node* firstRef,node* lastRef){
    node *aux1,*aux2;
    while(firstRef!=NULL){
        if(isNonVogal(firstRef->chr)==1){
            lastRef = firstRef;
            while(lastRef->next!=NULL && isNonVogal(lastRef->next->chr)==1){
                lastRef = lastRef->next;
            }
            if(lastRef!=firstRef){
                aux1 = firstRef;
                aux2 = lastRef;
                reverseSublist(aux1,aux2);
            }
        }
        firstRef = firstRef->next;
    }

}
int main(){
    node* first=NULL;
    node* last=NULL;
    readText(&first,&last);
    printList(first);
    node* aux = first;
    node* aux2 = aux;
    findSeq(aux,aux2);
    reverseList(&first,&last);
    printList(first);
    return 0;
}
