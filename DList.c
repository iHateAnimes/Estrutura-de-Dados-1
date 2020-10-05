#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* next;
    struct node* prev;
    int value;
}node;

typedef struct{
    node* head;
    int size;
}dlist;

dlist* createList(){
    dlist* list = (dlist *)malloc(sizeof(dlist));
    if(!list) return NULL;
    list->head = NULL; 
    list->size = 0;
    return list;
}
node* createNode(){
    node* no= (node *)malloc(sizeof(node));
    if(!no) return NULL;
    no->next=NULL;
    no->prev =NULL;
    printf("\nDigite o elemento de informação: ");
    scanf("%d",&no->value);
    return no;
}
void insertDlist(dlist* list,int pos){
    node* no = createNode();
    if(list->head==NULL){
        list->head=no;
        list->size++;
        return;
    }
    if(pos<=1){
        list->head->prev = no;
        no->next = list->head;
        list->head = no;
        no->prev = NULL;
        list->size++;
        return;
    }
    int i=1;
    node* aux = list->head;
    if(pos >= list->size){
        while(aux->next!=NULL) aux = aux->next;
        aux->next = no;
        no->prev = aux->next;
        list->size++;
        return;
    }
    while(i!=pos){
        aux = aux->next;
        i++;
    }
    no->next = aux;
    no->prev = aux->prev;
    aux->prev = no;
    no->prev->next = no;
    list->size++;
    return;    
}
void split(node* head,node** back,node** front){
    node* fast;
    node* slow;
    slow = head;
    fast  = head->next;
    while(fast!=NULL){
        fast  = fast->next;
        if(fast!=NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    *back = head;
    *front = slow->next;
    slow->next = NULL;
}
node* merge(node* front, node* back){
    if(front==NULL) return back;
    if(back==NULL) return front;
    if(front->value <= back->value){
        front->next = merge(front->next,back);
        front->next->prev = front;
        front->prev = NULL;
        return front;
    }
    else{
        back->next = merge(front,back->next);
        back->next->prev = back;
        back->prev = NULL;
        return back;
    }
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
void erasePos(dlist* list, int pos){
    node* aux = list->head;
    int i=1;
    if(aux==NULL) return;
    if(list->size==1){
        free(list->head);
        list->head=NULL;
        return;
    }
    if(pos<=1){
        list->head = list->head->next;
        free(list->head->prev);
        list->head->prev = NULL;
        list->size--;
        return;
    }
    else if(pos>=list->size){
        while(aux->next!=NULL){
            aux = aux->next;
        }
        aux->prev->next = aux->next;
        free(aux);
        list->size--;
        return;

    }
    else{
        while(i!=pos){
            aux = aux->next;
            i++;
        }
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
        free (aux);
        list->size--;
        return;
    }
}
void eraseList(dlist* list){
    node* aux;
    if(list->head==NULL) return;
    while(list->head!=NULL){
        aux = list->head;
        list->head = list->head->next;
        free(aux);
    }
    list->size = 0;
    return;
}
void printDlist(node* head){
    node* aux = head;
    printf("\n");
    while(aux!=NULL){
        printf("[%d] ",aux->value);
        aux = aux->next;
    }
    printf("\n");
    return;
}
int isempty(dlist* list){
    if(list->size==0) return 1;
    else return 0;
}
int size(dlist* list){
    return list->size;
}
int main(){
    dlist* lista = createList();
    int pos;
    int op;
    while(1){
        system("clear");
        printf("\n ------------------------------------");
        printf("\n| 1 - Inserir um elemento no inicio  |");
        printf("\n| 2 - Inserir um elemento na posição |");
        printf("\n| 3 - Inserir um elemento no fim     |");
        printf("\n| 4 - Imprimir a lista               |");
        printf("\n| 5 - Ordenar a lista                |");
        printf("\n| 6 - Deletar um elemento no início  |");
        printf("\n| 7 - Deletar um elemento no fim     |");
        printf("\n| 8 - Deletar um elemento na posição |");
        printf("\n| 9 - Verificar se a lista é vazia   |");
        printf("\n|10 - Verificar o tamanho da lista   |");
        printf("\n|11 - Deletar a lista                |");
        printf("\n ------------------------------------\n");
        printf("Digite a operação: ");
        scanf("%d",&op);
        if(op==1){
            insertDlist(lista,1);
        }
        else if(op==2){
            printf("\nDigite a posição que deseja inserir: ");
            scanf("%d",&pos);
            insertDlist(lista,pos);
        }
        else if(op==3){
            insertDlist(lista,lista->size);
        }
        else if(op==4){
            printDlist(lista->head);
            printf("Pressione enter para continuar...");
            getchar();
            getchar();
        }
        else if(op==5){
            mergeSort(&lista->head);
        }
        else if(op==6){
            erasePos(lista,1);
        }
        else if(op==7){
            erasePos(lista,lista->size);
        }
        else if(op==8){
            printf("\nDigite a posição que deseja deletar:");
            scanf("%d",&pos);
            getchar();
            erasePos(lista,pos);
        }
        else if(op==9){
            if(isempty(lista)==1) printf("\nTrue");
            else printf("\nFalse");
            printf("\n\nPressione enter para continuar...");
            getchar();
            getchar();
        }
        else if(op==10){
            printf("\n%d",size(lista));
        }
        else if(op==11){
            eraseList(lista);
        }
        else return 0;
    }
}
