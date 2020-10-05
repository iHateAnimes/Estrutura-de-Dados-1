#include "poly.h"
node* createNode(int coeff,int num){
    node* newnode=NULL;
    newnode = (node *)malloc(sizeof(node));
    if(newnode==NULL) return NULL;
    newnode->coeff = coeff;
    newnode->num = num;
    newnode->next = NULL;
    return newnode;
}
void split(node* start,node** front,node** back){
    node* slow;
    node* fast;
    slow = start;
    fast = slow->next;
    while(fast->next!=NULL){
        fast = fast->next;
        if(fast->next!=NULL){
            fast = fast->next;
            slow = slow->next;
        }
    }
    *front = start;
    *back = slow->next;
    slow->next = NULL;
    return;
}
node* merge(node* front,node* back){
    node* result;
    if(front==NULL) return back;
    if(back==NULL) return front;
    if(front->num>=back->num){
        result = front;
        result->next = merge(front->next,back);
    }
    else{
        result = back;
        result->next = merge(front,back->next);
    }
    return result;
}
void mergesort(node** start){
    if((*start)==NULL || (*start)->next==NULL) return;
    node *front,*back;
    split(*start,&front,&back);
    mergesort(&front);
    mergesort(&back);
    *start = merge(front,back);
    return;
}
void deletePoly(node** start){
    node* aux = *start;
    if(*start==NULL) return;
    if((*start)->coeff==0){
        aux = (*start);
        (*start) = (*start)->next;
        free(aux);
    }
    if((*start)==NULL) return;
    aux = *start;
    node* aux2;
    while(aux->next!=NULL){
        if(aux->next->coeff==0){
            aux2 = aux->next;
            aux->next = aux->next->next;
            free(aux2);
        }
        aux = aux->next;
    }
    return;
}
void insertPoly(node** start,int coeff, int num){
    if((*start)==NULL){
        *start  = createNode(coeff,num);
        return;
    }
    node* aux  = *start;
    while(aux!=NULL){
        if(aux->num==num){
            aux->coeff+=coeff;
            return;
        }
        aux = aux->next;
    }
    node* newnode = NULL;
    newnode = createNode(coeff,num);
    if(newnode==NULL) return;
    aux = *start;
    *start = newnode;
    newnode->next  = aux;
    mergesort(start);
    return;

}
node* freeList(node* start){
    node* aux;
    while(start!=NULL){
        aux = start;
        start = start->next;
        free(aux);
    }
    return NULL;
}
void printaUni(int num){
    char superscript[10][4] = {"\u2070", "\u00B9", "\u00B2", "\u00B3", "\u2074",
                           "\u2075", "\u2076", "\u2077", "\u2078", "\u2079"};
    while(num>9){
        printf("%.3s)",superscript[num%10]);
        num = num/10;
    }
    printf("%.3s)",superscript[num]);
    return;
}
void printList(node* start){
    node* aux  = start;
    while(aux!=NULL){
        printf("(%dx",aux->coeff);
        if(aux->next==NULL) printaUni(aux->num);

        else{
            printaUni(aux->num);
            printf(" + ");
        }
        aux = aux->next;
    }
    return;
}
node* addPoly(node* start1,node* start2,node* start3){
    while(start1!=NULL){
        insertPoly(&start3,start1->coeff,start1->num);
        start1 = start1->next;
    }
    while(start2!=NULL){
        insertPoly(&start3,start2->coeff,start2->num);
        start2 = start2->next;
    }
    return start3;
}
node *subPoly(node* start1,node* start2,node* start3){
    while(start1!=NULL){
        insertPoly(&start3,start1->coeff,start1->num);
        start1 = start1->next;
    }
    while(start2!=NULL){
        insertPoly(&start3,(-1)*start2->coeff,start2->num);
        start2 = start2->next;
    }
    return start3;
}
node* multPoly(node *start1,node *start2,node* start3){
    node* aux;
    while(start1!=NULL){
        aux = start2;
        while(aux!=NULL){
            insertPoly(&start3,(start1->coeff)*(aux->coeff),(start1->num)+(aux->num));
            aux = aux->next;
        }
        start1 = start1->next;
    }
    return start3;
}
void divPoly(node* start1,node* start2){
    node* aux,*temp;
    if(start1==NULL || start1==NULL || start1->num<start2->num){
        printf("\nNão é possivel dividir...\nPressione enter para continuar...");
        getchar();
        getchar();
        return;
    }
    node *rest=NULL,*result=NULL;
    rest = addPoly(start1,NULL,rest);
    while(rest->num>=start2->num){
        insertPoly(&result,rest->coeff/start2->coeff,rest->num-start2->num);
        temp = createNode(rest->coeff/start2->coeff,rest->num-start2->num);
        aux = multPoly(start2,temp,NULL);
        rest = subPoly(rest,aux,NULL);
        deletePoly(&rest);
        aux = freeList(aux);
    }
    printf("Resultado da divisão: ");
    printList(result);
    printf("\nResto da divisão: ");
    printList(rest);
    printf("\nPressione enter para continuar...");
    getchar();
    getchar();
    return;
}
int main(){
    node *start1=NULL,*start2=NULL,*start3=NULL,*aux;
    int p,op,coeff,num,key;
    while(1){
        start3 = freeList(start3);
        system("clear");
        printf("\n ----------------------------------");
        printf("\n| 1 - Inserir um novo elemento    |");
        printf("\n| 2 - Somar dois polinomios       |");
        printf("\n| 3 - Subtrair dois polinômios    |");
        printf("\n| 4 - Multiplicar dois polinômios |");
        printf("\n| 5 - Dividir dois polinomios     |");
        printf("\n| 6 - Imprimir um polinômio       |");
        printf("\n ---------------------------------");

        printf("\nDigite a operação que deseja realizar: ");
        scanf("%d",&op);
        if(op==1 || op==6 ){
            printf("\n-------------------");
            printf("\n| 1 - Polinômio 1  |");
            printf("\n| 2 - Polinômio 2  |");
            printf("\n ------------------");
            printf("\nDigite em qual dos polinômios deseja realizar a operação: ");
            scanf("%d",&p);
        }
        if(op==1){
            printf("\nDigite o coeficiente do termo: ");
            scanf("%d",&coeff);
            printf("\nDigite a potência do termo: ");
            scanf("%d",&num);
            if(p==1){
                insertPoly(&start1,coeff,num);  
                mergesort(&start1);
                deletePoly(&start1);
            }
            else{
                insertPoly(&start2,coeff,num);
                mergesort(&start2);
                deletePoly(&start2);
            }
        }
        else if(op==2){
            start3 = addPoly(start1,start2,start3);
            deletePoly(&start3);
            printList(start3);
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }
        else if(op==3){
            start3 = subPoly(start1,start2,start3);
            deletePoly(&start3);
            printList(start3);
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }
        else if(op==4){
            start3 = multPoly(start1,start2,start3);
            deletePoly(&start3);
            printList(start3);
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }
        else if(op==5){
            divPoly(start1,start2);
        }
        else if(op== 6){
            if(p==1) printList(start1);
            else printList(start2);
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }
        else{
            node* aux;
            while(start1!=NULL){
                aux = start1;
                start1 = start1->next;
                free(aux);
            }
            while(start2!=NULL){
                aux = start2;
                start2= start2->next;
                free(aux);
            }
            return 0;
        }
    }
}
