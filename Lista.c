#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode{
    struct tnode *next;
    char *string;
}node;

typedef struct{
    node *last,*first;
    node* window;
    int size;
}List;

node *createNode(char *string){
    node* newnode = NULL;
    newnode = (node *)malloc(sizeof(node));
    if(newnode!=NULL){
        newnode->string = (char *)malloc(strlen(string)*sizeof(char));
        strcpy(newnode->string,string);
        newnode->next = NULL;
    }
    return newnode;
}

List* createList(){
    List* newList = NULL;
    newList = (List *)malloc(sizeof(List));
    if(newList!=NULL){
        newList->first=NULL;
        newList->last=NULL;
        newList->window =NULL;
        newList->size = 0;
    }
    return newList;
}

int insertList(List* list,char *string){
    if(list==NULL) return 0;
    node *newnode = createNode(string);
    if(newnode==NULL) return 0;
    if(list->first==NULL){
        list->last = newnode;
        list->first = newnode;
    }
    else{
        printf("\n%s",newnode->string);
        printf("\n%s",list->first->string);
        newnode->next = list->first;
        list->first = newnode;
    }
    list->size++;
    return 1;
}  

void split(node *first,node **begin,node **end){
    node *slow = first;
    node *fast = slow->next;
    while(fast!=NULL){
        fast = fast->next;
        if(fast!=NULL){
            fast = fast->next;
            slow = slow->next;
        }
    }
    (*begin) = first;
    (*end) = slow->next;
    slow->next = NULL;
}

node* merge(node *begin,node* end){
    node* result;
    if(begin==NULL) return end;
    if(end==NULL) return begin;
    if(strcmp(begin->string,end->string)<0){
        result = begin;
        result->next = merge(begin->next,end);
    }
    else{
        result = end;
        result->next = merge(begin,end->next);
    }
    return result;
}
void mergeSort(node** first,node** last){
    if((*first)==NULL || (*first)->next==NULL) return;
    node *begin,*end;
    split(*first,&begin,&end);
    mergeSort(&begin,last);
    mergeSort(&end,last);
    (*first) = merge(begin,end);
    node* aux = *first;
    while(aux->next!=NULL) aux = aux->next;
    (*last) = aux;
    return;
}

void printList(List *list){
    if(list==NULL || list->first==NULL) return;
    node *aux = list->first;
    while(aux!=NULL){
        printf(" [%s]",aux->string);
        aux = aux->next;
    }
    return;
}
void postList(List *list,int pos){
    list->window = list->first;
    int i=1;
    while(i!=pos && list->window!=list->last){
        list->window = list->window->next;
        i++;
    }
    return;
}
int search(List *list,int ini, int fim,char *text){
    int mid;
    if(ini<=fim){
        mid = (ini + fim)/2;
        postList(list,mid);
        if(strcmp(list->window->string,text)==0) return mid;
        else if(strcmp(list->window->string,text)>0) return search(list,ini,mid-1,text);
        else return search(list,mid+1,fim,text);

    }
    return 0;
}
int BinSearch(List* list,char *string){
    return search(list,1,list->size,string);
}
void freeList(List *list){
    if(list==NULL || list->first==NULL) return;
    node *aux;
    while(list->first!=NULL){
        aux = list->first;
        list->first = list->first->next;
        free(aux);
    }
    free(list);
    return;
}
int main(){
    int op,ok;
    char text[100];
    List *list = createList();
    if(list==NULL) return 0;
    while(1){
        printf("\n| 1 - insert list |");
        printf("\n| 2 - print list  |");
        printf("\n| 3 - search list |");
        printf("\n| 4 - sort list   |");
        printf("\n| 5 - search list |");
        printf("\nOption: ");
        scanf("%d",&op);
        getchar();
        if(op==1){
            printf("\nText: ");
            fgets(text,100,stdin);
            text[strlen(text)-1] = 0;
            ok = insertList(list,text);
            if(ok==1) printf("\ntrue");
            else printf("\nfalse");
        }
        else if(op==2){
            printList(list);
        }
        else if(op==4) mergeSort(&(list->first),&(list->last));
        else if(op==5){
            fgets(text,100,stdin);
            text[strlen(text)-1] = 0;
            ok = BinSearch(list,text);
            printf("\n%d",ok);
        }
        else{
            freeList(list);
            return 0;
        }
    }
}
