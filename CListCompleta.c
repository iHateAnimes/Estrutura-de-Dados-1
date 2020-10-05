#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int num;
}info;

typedef struct _node{
    struct _node *next;
    info *info;
}node;

typedef struct{
    node* head;
    int size;
}list;

list* createList(){
    list* newlist;
    newlist = (list *)malloc(sizeof(list));
    if(newlist){
        newlist->size =0;
        newlist->head = NULL;
        return newlist;
    }
    printf("\nNão foi possível criar a lista\nPressione enter para continuar...");
    getchar();
    return NULL;
}
node* createNode(){
    int valor;
    node* newnode;
    newnode = (node *)malloc(sizeof(node));
    newnode->info = (info *)malloc(sizeof(info));
    if(newnode){
        printf("\nDigite o valor a ser adicionado: ");
        scanf("%d",&newnode->info->num);
        newnode->next = NULL;
        return newnode;
    }
    printf("\nNão foi possivel criar nó\nPressione enter para continuar..");
    getchar();
    getchar();
    return NULL;
}
void insertList(list* list,int pos){
    int i=1;
    node* aux;
    aux = list->head;
    node *node  = createNode();
    if(list->size == 0){
        list->head = node;
        list->size++;
        return;
    }
    else if(pos == 1){
        node->next = list->head;
        list->head = node;
        list->size++;
        return;
    }
    while(i!=pos-1 && aux->next!=NULL){
        aux = aux->next;
        i++;
    }
    node->next = aux->next;
    aux ->next = node;
    list->size++;
    return;
}
void imprime(list* list){
    node* aux;
    aux = list->head;
    printf("\n");
    while(aux!=NULL){
        if(aux->next==NULL){
            printf("[%d]",aux->info->num);
        }
        else printf("[%d]->",aux->info->num);
        aux = aux->next;
    }
    printf("\nPressione enter para continuar...");
    getchar();
    getchar();
    return;
}
void erase(list* list, int val){
    node* step = list->head;
    node* aux;
    if(list->size==0) return;
    else if(list->size==1){
        if(list->head->info->num==val){
            free(list->head->info);
            free(list->head);
            list->head =NULL;
            list->size--;
        }
        return;
    }
    while(step->next!=NULL){
        if(step->next->info->num == val){
            aux = step->next;
            step->next = step->next->next;
            free(aux->info);
            free(aux);
            list->size--;
            return;
        }
        step= step->next;
    }
    return;
}
void erasePos(list* list,int pos){
    node* aux = list->head;
    int i =1;
    if(list->size==0) return;
    else if(list->size==1){
        free(list->head->info);
        free(list->head);
        list->head  = NULL;
        list->size--;
        return;
    }
    else if(pos == 1){
        list->head = list->head->next;
        free(aux->info);
        free(aux);
        list->size--;
        return;
    }
    while(i!=pos-1 && aux->next!=NULL){
        aux = aux->next;
        i++;
    }
    node* aux2 = aux->next;
    aux->next = aux->next->next;
    free(aux2->info);
    free(aux2);
    list->size--;
    return;
}
//inicio merge sort
void split(node* head,node** back,node** front){
    node* slow;
    node* fast;
    slow = head;
    fast = head->next;
    while(fast!=NULL){
        fast = fast->next;
        if(fast!=NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    *back = head;
    *front = slow->next;
    slow->next = NULL;
}
node* merge(node* front,node* back){
    node* result = NULL;
    if(front==NULL) return back;
    if(back==NULL) return front;
    if(front->info->num <= back->info->num){
        result = front;
        result->next = merge(front->next,back);
    }
    else{
        result = back;
        result->next = merge(front,back->next);
    }
    return result;
}
void mergeSort(node** head){
    node* front;
    node* back;
    node* aux = *head;
    if(aux==NULL || aux->next==NULL) return;
    split(aux,&back,&front);
    mergeSort(&front);
    mergeSort(&back);
    *head = merge(front,back);
    return;
}
//fim mergesort

void eraseList(node* head){
    node* aux = head;
    if(head==NULL) return;
    if(head->next == NULL){
        free(head->info);
        free(head);
        return;
    }
    else{
       while(head!=NULL){
           aux = head;
           head = head->next;
           free(aux->info);
           free(aux);
       }      
    }
    return;
}
void invertList(node** head){
    node* aux = *head;
    node* cur;
    node* prev=NULL;
    node* next;
    if(aux==NULL || aux->next==NULL) return;
    cur = aux;
    while(cur!=NULL){
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    *head = prev;
}
int isEmpty(list* lista){
    if (lista->size>0) return 0;
    else return 1;
}
int size(list* lista){
    return lista->size;
}
int main(){
    int op,pos,value;
    list* lista;
    lista = createList();
    while(1){
        system("clear");
        printf("\n -----------------------------------");
        printf("\n| 1 - Inserir um elemento no inicio |");
        printf("\n| 2 - Inserir um elemento no meio   |");
        printf("\n| 3 - Inserir um elemento no fim    |");
        printf("\n| 4 - Imprimir a lista              |");
        printf("\n| 5 - Deletar uma informação        |");
        printf("\n| 6 - Ordenar lista                 |");
        printf("\n| 7 - Deletar um elemento no inicio |");
        printf("\n| 8 - Deletar na posição            |");
        printf("\n| 9 - Deletar um elemento no fim    |");
        printf("\n|10 - Inverter a lista              |");
        printf("\n|11 - Imprimir o tamanho da lista   |");
        printf("\n|12 - Verificar se a lista é vazia  |");
        printf("\n| 0 - Sair                          |");
        printf("\n -----------------------------------");
        printf("\n");
        scanf("%d",&op);
        if(op==1) insertList(lista,1);
        else if(op==2){
            printf("\nDigite a posição em que deseja inserir o elemento: ");
            scanf("%d",&pos);
            insertList(lista,pos);
        }
        else if(op==3) insertList(lista,lista->size);
        else if(op==4) imprime(lista);
        else if(op==5){
            printf("\nDigite o elemento que deseja deletar: ");
            scanf("%d",&value);
            erase(lista,value);
        }
        else if(op==6) mergeSort(&lista->head);
        else if(op==7){
            erasePos(lista,1);
        }
        else if(op==8){
            printf("\nDigite a posição que deseja deletar: ");
            scanf("%d",&pos);
            erasePos(lista,pos);
        }
        else if(op==9){
            erasePos(lista,lista->size);
        }
        else if(op==10){
            invertList(&lista->head);
        }
        else if(op==11){
            printf("\n%d",size(lista));
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }
        else if(op==12){
            if(isEmpty(lista)==1) printf("\nTrue");
            else printf("\nFalse");
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }
        else if(op==0){
            eraseList(lista->head);
            return 0;
        }
    }
}
