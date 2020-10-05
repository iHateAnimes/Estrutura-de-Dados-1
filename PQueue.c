#include <stdio.h>
#include <stdlib.h>

typedef struct tnode{
    struct tnode *next;
    int value;
}node;

typedef struct tpriority{
    int prior;
    struct tpriority *next;
    node* first;
}priority;

typedef struct pqueue{
    priority *head;
    int size;
}Pqueue;

Pqueue *createPqueue(){
    Pqueue *pqueue = NULL;
    pqueue  = (Pqueue *)malloc(sizeof(Pqueue));
    if(pqueue !=NULL){
        pqueue->head = NULL;
        pqueue->size = 0;
    }
    return pqueue;
}
priority *createPrior(int prior){
    priority *newprior = NULL;
    newprior = (priority *)malloc(sizeof(priority));
    if(newprior!=NULL){
        newprior->first = NULL;
        newprior->next = NULL;
        newprior->prior = prior;
    }
    return newprior;
}

node *createNode(int value){
    node *newnode = NULL;
    newnode  = (node *)malloc(sizeof(node));
    if(newnode!=NULL){
        newnode->next = NULL;
        newnode->value = value;
    }
    return newnode;
}
int insertPqueue(Pqueue *pqueue,int value,int prior){
    if(pqueue == NULL) return 0;
    priority *newprior = createPrior(prior);
    if(newprior==NULL) return 0;
    node *newnode = createNode(value);
    if(newnode==NULL) return 0;
    if(pqueue->head ==NULL){
        pqueue->head = newprior;
        newprior->first = newnode;
    }
    else{
        priority *aux = pqueue->head;
        while(aux->next!=NULL && aux->prior!=prior) aux = aux->next;
        if(aux->prior==prior){
            if(aux->first==NULL) aux->first = newnode;
            else{
                node *aux2 = aux->first;
                while(aux2->next!=NULL) aux2 = aux2->next;
                aux2->next = newnode;
            }
        }
        else {
            aux->next = newprior;
            newprior->first = newnode;
        }
    }
    pqueue->size++;
    return 1;
}
int removePqueue(Pqueue *pqueue, int prior){
    if(pqueue==NULL || pqueue->head==NULL) return 0;
    priority *aux = pqueue->head;
    while(aux!=NULL && aux->prior!=prior) aux = aux->next;
    if(aux!=NULL){
        node *aux2 = aux->first;
        aux->first = aux->first->next;
        free(aux2);
    }
    else return 0;
    pqueue->size--;
    return 1;
}
void freePqueue(Pqueue *pqueue){
    priority *aux;
    node* aux2;
    if(pqueue==NULL || pqueue->head==NULL) return;
    while(pqueue->head!=NULL){
        while(pqueue->head->first!=NULL){
            aux2 = pqueue->head->first;
            pqueue->head->first = pqueue->head->first->next;
            free(aux2);
        }
        aux = pqueue->head;
        pqueue->head = pqueue->head->next;
        free(aux);
    }
    return;
}
void printPqueue(Pqueue *pqueue){
    if(pqueue==NULL || pqueue->head==NULL) return;
    priority *aux = pqueue->head;
    node *aux2;
    while(aux!=NULL){
        printf("\nPiority %d :",aux->prior);
        aux2 = aux->first;
        while(aux2!=NULL){
            printf(" [%d]",aux2->value);
            aux2 = aux2->next;
        }
        aux = aux->next;
    }
    return;
}
int main(){
    int prior,value,op,ok;
    Pqueue *pqueue = createPqueue();
    if(pqueue==NULL) return 0;
    while(1){
        printf("\n| 1 - insert queue  |");
        printf("\n| 2 - print queue   |");
        printf("\n| 3 - remove pqueue |");
        printf("\nOption: ");
        scanf("%d",&op);
        if(op==1){
            printf("\ninsert the value and the priority: ");
            scanf("%d%d",&value,&prior);
            ok = insertPqueue(pqueue,value,prior);
            if(ok==1) printf("\ntrue");
            else printf("\nfalse");
        }
        else if(op==2) printPqueue(pqueue);
        else if(op==3){
            printf("\nInsert the priority: ");
            scanf("%d",&prior);
            ok = removePqueue(pqueue,prior);
            if(ok==1) printf("\ntrue");
            else printf("\nfalse");
        }
        else{
            freePqueue(pqueue);
            return 0;
        }
    }
}
