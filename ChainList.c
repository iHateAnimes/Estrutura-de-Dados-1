#include "Clist.h"

void createCList(node** first, node** last,int value){
    *first = (node *)malloc(sizeof(node));
    if(!(*first)) return;
    *last = *first;
    (*first)->next = *first;
    (*first)->value = value;
    return;
}
node* createNode(int value){
    node* newnode;
    newnode = (node *)malloc(sizeof(node));
    if(!newnode) return NULL;
    newnode->next = NULL;
    newnode->value = value;
    return newnode;
}
void insertFirst(node** first, node** last,int value){
    node* aux;
    if(!first){
        createCList(first,last,value);
        return;
    }
    node* newnode = createNode(value);
    if(!newnode) return;
    aux = *first;
    newnode->next = *first;
    (*last)->next = newnode;
    *first = newnode;
    return;
}
void insertLast(node* first,node** last,int value){
    if(!first){
        createCList(&first,last,value);
    }
    node* newnode = createNode(value);
    if(!newnode) return;
    (*last)->next = newnode;
    newnode->next = first;
    (*last) = newnode;
    return;
}
void deleteFirst(node** first, node** last){
    if(!(*first)) return;
    if(*first==*last){
        node* aux = *first;
        free(aux);
        *first = NULL;
        *last  = NULL;
        return;
    }
    node* aux = *first;
    (*first) = (*first)->next;
    (*last)->next = *first;
    free(aux);
    return;
}
void deleteLast(node** first, node** last){
    if(!(*first)) return;
    if(*first==*last){
        node* aux = *first;
        *first = NULL;
        *last = NULL;
        free(aux);
        return;
    }
    node* aux = *first;
    while(aux->next!=*last){
        aux= aux->next;
    }
    aux->next = *first;
    free(*last);
    *last = aux;
    return;
}
void deleteKey(node** first, node** last,int key){
    if(!(*first)) return;
    if((*first)->value==key){
        deleteFirst(first,last);
        return;
    }
    if((*last)->value==key){
        deleteLast(first,last);
        return;
    }
    node* aux = *first;
    node* aux2;
    while( aux->next->value!=key){
        if(aux->next==*last) return;
        aux = aux->next;
    }
    aux2 = aux->next;
    aux->next = aux->next->next;
    free(aux2);
    return;
}
void printlist(node* first, node* last){
    node* aux;
    if(!first) return;
    printf("\n");
    aux = first;
    while(aux->value!=last->value){
        printf("[%d] ",aux->value);
        aux = aux->next;
    }
    printf("[%d]",last->value);
    printf("\n");
    return;
}
int main(){
    int op,value;
    node* first=NULL;
    node* last;
    while(1){
        system("clear");
        printf("\n -----------------------------------");
        printf("\n| 1 - Criar lista                   |");
        printf("\n| 2 - Inserir um elemento no inicio |");
        printf("\n| 3 - Inserir um elemento no fim    |");
        printf("\n| 4 - Imprimir a lista              |");
        printf("\n| 5 - Deletar uma informação        |");
        printf("\n| 6 - Deletar um elemento no inicio |");
        printf("\n| 7 - Deletar um elemento no fim    |");
        printf("\n| 0 - Sair                          |");
        printf("\n -----------------------------------");
        printf("\n");
        scanf("%d",&op);
        if(op==1){
            if(first){
                printf("A lista ja existe!\nPressione enter para continuar...");
                getchar();
                getchar();
            }
            else{
                printf("\nDigite o elemento de informação: ");
                scanf("%d",&value);
                createCList(&first,&last,value);
            }
        }
        else if(op==2){
            printf("\nDigite o elemento de informação: ");
            scanf("%d",&value);
            insertFirst(&first,&last,value);
        }
        else if(op==3){
            printf("\nDigite o elemento de informação: ");
            scanf("%d",&value);
            insertLast(first,&last,value);
            printf("%d",last->value);
        }
        else if(op==4){
            printlist(first,last);
            printf("Pressione enter para continuar...");
            getchar();
            getchar();
        }
        else if(op==5){
            int key;
            printf("\nDigite a chave a ser excluída: ");
            scanf("%d",&key);
            deleteKey(&first,&last,key);
        }
        else if(op==6){
            deleteFirst(&first,&last);
        }
        else if(op==7){
            deleteLast(&first,&last);
        }
        else return 0;
    }
}
