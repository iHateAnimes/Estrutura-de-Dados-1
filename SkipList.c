//------------------------------------------Implmentação da SkipList-------------------------------------------------------//

//Uarlley do Nascimento Amorim
//Estrutura de Dados I
//Ciência da Computação

//---------------------------------------------------------------------------------------------------------------------------
#include "skiplist.h" //Inclusão da biblioteca personalizada

//---------------------------------------------------------------------------------------------------------------------------
//Definição da função responsável em criar a Skip List
//Esta função nao possui parâmetros e retorna um ponteiro para Skip List

SkipList* createList(){
    int i;                                           //Declaração de uma variável auxiliar
    SkipList *newlist = NULL;                        //Declaração da Nova Skip List
    newlist = (SkipList *)malloc(sizeof(SkipList));  //Alocação de memória para a estrutura
    if(newlist!=NULL){                               //Condição para caso a alocação de memória tenha sucesso
        for(i=0;i<MAXLEVELS;i++){                    
            newlist->head[i] = NULL;                 //Definindo os ponteiros para NULL
            newlist->size[i] = 0;                    //Definindo a quantidade de elementos de cada nível para 0
        }
    }
    return newlist;                                  //Retorno da Skip List
}
//---------------------------------------------------------------------------------------------------------------------------
//Função responsável na criação dos nós da Skip List
//Recebe o elemento de informação do novo nó e retorna um ponteiro para um o mesmo

node* createNode(int value){
    int i;                                                 //Declaração de uma variável auxiliar
    node *newnode = NULL;                                  //Declaração do novo nó
    newnode = (node *)malloc(sizeof(node));                //Alocação de memória para a estrutura do nó
    if(newnode!=NULL){                                     //Condição para caso a alocação tenha sucesso
        for(i=0;i<MAXLEVELS;i++) newnode->next[i] = NULL;  //Definindo os apontamentos para NULL
        newnode->value = value;                            //Definindo o elemento de informação do novo nó
    }
    return newnode;                                        //Retorno do novo nó
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que verifica se o elemento procurado existe na lista utilizando os ponteiros da função SearchList 
//Recebe um vetor de endereços para nós, e uma chave a ser buscada e retorna 0 ou 1, (true ou false)

int found(node* result[MAXLEVELS],int key){
    int i;                                       //Variável auxiliar criada para percorrer os níveis de cada
    for(i=0;i<MAXLEVELS;i++){                    //Loop para percorrer os ponteiros do retorno da função SearchList
        if(result[i]!=NULL){                     //Condição para caso o ponteiro esteja apontando para um campo válido
            if(result[i]->value==key) return 1;  //Caso o elemento seja encontrado retorna 1
            if(result[i]->next[i]!=NULL && result[i]->next[i]->value==key) return 1;
        }   
    }
    return 0;                                    //Caso não seja encontrado retorna 0
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que apenas retorna se a skiplist está vazia ou não
//Recebe um ponteiro para Skip List e retorna 1 caso a skiplist esteja vázia e 0 caso o contrário

int isEmpty(SkipList *list){
    if(list==NULL || list->size[0]==0) return 0;    //Retorna 0 caso o tamanho da skiplist não exista ou esteja de fato vazia
    else return 1;                                  //Retorna 1 caso contrário
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que busca uma chave em cada nível da Skip List
//Recebe como parâmetros um ponteiro para Skip List, um vetor de endereços para nós, a chave a ser buscada, e parâmetro para impressão
//A função retorna um inteiro 1 caso a chave seja encontrada e 0 caso o contrario e altera os endereços do vetor de entrada

int searchList(SkipList *list,node *result[MAXLEVELS],int key,int print){
    if(list==NULL) return 0;                        //Condição para caso a skiplist não exista
    int i,ok;node* aux;                             //Declaração de variáveis e ponteiros auxíliares
    for(i=MAXLEVELS-1;i>=0;i--){                    //Loop para a procura da chave, iniciando do nível superior, finalizando no nível inferior
        if(i<(MAXLEVELS-1) && result[i+1]!=NULL && result[i+1]->value<key) aux = result[i+1]; //Condição que indica por qual nó a busca ser iniciada
        else aux = list->head[i];                   //Caso não seja possivel definir por onde iniciar a busca, ela é feita do inicio
        while(aux!=NULL && aux->next[i]!=NULL && aux->next[i]->value<key) aux = aux->next[i]; //Loop para percorrer a lista
        result[i] = aux;                            //O endereço da chave buscada é armazenada no vetor
    }
    ok = found(result,key);                         //Chamada da função found para verificar se o elemento foi encontrado
    if(print==1){                                   //Caso o parâmetro seja verdadeiro, imprime os elementos de informação relativos a busca
        for(i=MAXLEVELS-1;i>=0;i--){
            if(result[i]!=NULL){
                printf("%d %d\n",result[i]->value,i);
            }
        }
        if(ok==1){                                  //Imprime o elemento novamente caso o mesmo for encontrado
            if(result[0]->value==key) printf("%d 0\n",result[0]->value);
            else printf("%d 0\n",result[0]->next[0]->value);
        }
    }
    if(ok==1) printf("true\n");                     //Imprime true se o elemento foi encontrado
    else printf("false\n");                         //Imprime false caso contrário
    return ok;                                      //Retorno do resultado da busca
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que insere um novo nó na skiplist
//Esta função recebe como parâmetro um ponteiro para Skip List, um elemento de informação e um inteiro para o nível 
//Retorna um inteiro, 1 caso a inserção seja bem sucedida e 0 caso o contrário

int insertList(SkipList *list,int value,int h){
    int i,ok;                                                  //Declaração das variáveis auxíliares
    node* result[MAXLEVELS];                                   //Criação do vetor de endereços para receber os resultados da função searchList
    ok = searchList(list,result,value,0);                      //Variável que recebe o retorno da função searchList
    if(list==NULL || ok==1) return 0;                          //Condição para caso a skiplist não exista ou o elemento já exista
    node *newnode = createNode(value);                         //Criação do novo nó
    if(newnode==NULL) return 0;                                //Condição para caso a criação do novo nó falhe
    for(i=0;i<h;i++){                                          //Loop para inserção do novo nó em cada nível e sub-nível da skiplist
        if(i!=0 && list->size[i]>=(list->size[i-1])/2) break;  //Caso o nível não esteja balanceado a inserção é finalizada
        else if(result[i]==NULL || result[i]->value>value){    //Caso o elemento salvo seja menor do que o buscado
            newnode->next[i] = result[i];
            list->head[i] = newnode;
        }
        else{                                                  //Condição para inserir no meio da skiplist
            newnode->next[i] = result[i]->next[i];
            result[i]->next[i] = newnode;
        }
        list->size[i]++;                                       //Incremento da quantidade de elementos no nível
    }
    return 1;                                                  //Retorna 1 pois a inserção teve sucesso
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que remove um elemento da SkipList
//Esta função recebe como parametros um ponteiro para SkipList, e uma chave a ser removida
//retorna 1 caso a remoção do elemento foi bem sucedida ou 0 caso o contrário

int removeList(SkipList *list,int key){
    int i,ok;                                                    //Declaração de variáveis auxiliares;
    node* result[MAXLEVELS],*aux;                                //Criação do vetor de ponteiros para a função SearchList
    ok = searchList(list,result,key,0);                          //Chamada da função SearchList
    if(ok==0) return 0;                                          //Retorna 0 caso o elemento não esteja na SkipList
    for(i=0;i<MAXLEVELS;i++){                                    //Loop para a remoção do elemento em cada nível
        if(result[i]==NULL || result[i]->value>key) continue;    //Pula a iteração caso o elemento não esteja no nível atual
        else if(result[i]->value==key){                          //Condição para caso o ponteiro da SearchList aponte para elemento buscado
            list->head[i] = result[i]->next[i];
            aux = result[i];
        }
        else{                                                    //Condição para remoção no meio da skiplist
            aux = result[i]->next[i];
            result[i]->next[i] = result[i]->next[i]->next[i];
        }
        list->size[i]--;                                          //Decrementa a quantidade de elementos do nível
    }
    free(aux);                                                    //Deleta o elemento e libera a memória alocada
    return 1;                                                     //Retorna 1 pois o elemento foi removido com sucesso
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que imprime apenas um nível da SkipList
//Recebe um ponteiro para SkipList e um inteiro para o nível que deve ser impresso e não possui retorno

void printHeight(SkipList *list,int h){
    node* aux = list->head[h];                     //Criação de um ponteiro auxiliar para apontar para o primeiro nó do nível
    while(aux!=NULL){                              //Loop para percorrer o nível e imprimir os elementos de informação
        printf("%d %d\n",aux->value,h);
        aux = aux->next[h];
    }
    return;                                        //Fim da função
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que imprime todos os níveis da Skiplist
//Recebe um ponteiro para SkipList e não possui retorno

void printList(SkipList *list){
    if(list==NULL || list->size[0]==0) return;        //Condição para caso a Skiplist não exista ou a mesma esteja vazia
    int i;                                            //Criação de uma variável auxiliar
    for(i=MAXLEVELS-1;i>=0;i--) printHeight(list,i);  //Chamada da função printHeight
    return;                                           //Fim da função
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que deleta a SkipList
//Recebe apenas um ponteiro para Skip List e não possui retorno

void freeList(SkipList *list){
    node *aux;                                    //Criação de um ponteiro auxiliar
    while(list->head[0]!=NULL){                   //Loop para percorrer apenas o primeiro nível da SkipList e deletar os cada nó
        aux = list->head[0];
        list->head[0] = list->head[0]->next[0];
        free(aux);                                //Deleta o nível liberando a memória alocada
    }
    free(list);                                   //Deleta a SkipList liberando a memória alocada
    return;                                       //Fim da função
}
//---------------------------------------------------------------------------------------------------------------------------
//Função que realiza as operações sobre a SkipList

int main(){
    int i,key,ok,lvl;                              //Declaração das variáveis auxiliares
    char op;
    SkipList *list;                                //Declaração do ponteiro para Skiplist;
    node* result[MAXLEVELS];                       //Criação do vetor de ponteiros da SkipList
    list = createList();                           //Criação da SkipList
    while(scanf("%c",&op)){                        //Loop para as operações
        getchar();
        if(op=='I'){                               //Opção para operação de inserção
            scanf("%d%d",&key,&lvl);
            ok = insertList(list,key,lvl+1);       //Chamada a função insert List
            if(ok==1) printf("true\n");            //Imprime true se o elemento foi inserido
            else printf("false\n");                //Imprime 0 caso contrário
            getchar();
        }
        else if(op=='A'){                         //Opção para operação de impressão da SkipList
            printList(list);                      //Chamada da função printList
        }
        else if(op=='B'){                         //Opção para operação de busca de uma chave na SkipList
            scanf("%d",&key);
            ok = searchList(list,result,key,1);   //Chamada da função searchList
            getchar();
        }
        else if(op=='R'){                         //Opção para operação de remoção de um nó da SkipList
            scanf("%d",&key);           
            ok = removeList(list,key);            //Chamada da função removeList
            if(ok==1) printf("true\n");           //Imprime 1 caso o elemento foi removido
            else printf("false\n");               //Imprime 0 caso contrário
            getchar();
        }
        else if(op=='P'){                         //Opção para operação de impressão de um nível da SkipList
            scanf("%d",&lvl);
            printHeight(list,lvl);                //Chamada da função printHeight
            getchar();
        }
        else break;                               //Caso nenhuma das opções seja selecionada a lista é deletada e o programa é encerrado
    }
    freeList(list);                               //Liberação da lista
    return 0;                                     //Fim da função
}

//---------------------------------------------Relatório do Trabalho-----------------------------------------------//
/*O objetivo do trabalho implementado acima consiste na implementação da denominada SkipList, que é uma 
lista ordenada cujo a eficiêcia na inserção, remoção e busca é maior do que em uma lista simplesmente 
encadeada tradicional, devido a sua capacidade de acessar elementos em qualquer posição da lista em tempo O(1)
utilizando a busca por níveis.

Nesta implementação, a quantidade máxima de níveis é definida na variável global MAXLEVELS, que atualmente
está definida como 1000.

Estruturas utilizadas na implementação:

     - Struct Node : esta estrutura é um pouco diferente da estrutura de nós tradicional, pois além de
     possuir o campo para a chave, possui um vetor estático, com tamanho baseado na quantidade de níveis da
     lista , de ponteiros para o elemento posterior, ou seja, um ponteiro para cada nível.
     
     - Struct SkipList : esta estrutura possui, assim como na estrutura para nós, um vetor estático, com
     tamanho beseado na quantidade de níveis, de ponteiros para o primeiro nó da lista, e um campo para
     contabilizar a quantidade total de elementos de cada nível da SkipList, afim de manter a lista balanceada.
     
Funções implementadas:

    - CreateList : esta função não possui parâmetros e retorna um ponteiro para SkipList. Nela, o espaço
    de memória necessário para a estrutura SkipList é alocado, e então o campo que contabiliza a quantidade de 
    elementos é definido como 0 e os ponteiros para os primeiros elementos são direcionados para nulo.
    
    - CreateNode : esta função recebe como parâmetro um elemento de informação e retorna um ponteiro 
    para um nó. Nela, o espaço de memória necessário para a estrutura Node é alocado, e então o campo
    do elemento de informação é definido para o parâmetro da função, e os ponteiros para os nós 
    posteriores são direcionados para nulo.
    
    - Found : função que verifica, a partir do vetor de ponteiros da SearchList, se o elemento buscado existe ou não
    na lista, caso sim retorna true, false caso contrário.

    - SearchList : esta função recebe como parâmetros um ponteiro para SkipList, uma chave a ser buscada, um 
    vetor de ponteiros para nó com tamanho baseado na quantidade de níveis da SkipList, e um parametro que 
    define se os resultados da busca devem ser impressos. Retorna um inteiro 1 caso a chave seja encontrada
    e 0 caso contrário.
    Nela, a busca é realizada de forma que, a complexidade seja menor do que em uma lista simplesmente 
    encadeada tradicional. A busca se inicia pelo nível mais superior da lista e caso o elemento não esteja
    no nível, a busca reinicia no nível [atual-1] porém começando do menor elemento mais proxímo da chave
    a ser buscada. Caso um elemento maior ou igual ao buscado é encontrado, um ponteiro para o elemento anterior à
    este é armazenado no vetor de ponteiros, e o processo é repetido até o menor nível da SkipList.
    Após o termino da busca a função found é chama, e, se o elemento foi encontrado é impresso e retornado true, ou false caso 
    contrario . Caso o parametro para impressão for 1, os resultados na busca em cada nível são impressos antes do retorno
    da função.

    - isEmpty : Função que verifica o tamanho da lista no nível 0 e retorna true se o mesmo for igual a 0, ou false caso
    contrário.

    - InsertList : esta função recebe como parâmetros um ponteiro para SkipList, um inteiro como elemento de 
    informação e um inteiro para o nível em que o elemento deve ser inserido.
    A fim de manter a lista ordenada, o elemento é inserido baseando-se nos ponteiros da função SearchList e é inserido
    apenas se, a função SearchList retornar 0, para que não exista nenhum elemento repetido. Além disso, caso a 
    inserção em um determinado nível comprometa o balanceamento da lista, o elemento é inserido apenas nos 
    níveis inferiores à este.
    Caso a inserção seja feita, a quantidade de elementos em cada nível menor ou igual ao nível cujo elemento foi inserido
    é incrementado em uma unidade e a função retorna true. Retorna false caso contrário.
    
    - RemoveList : esta função recebe como parâmetros um ponteiro para SkipList e uma chave a ser removida.
    Caso a chamada da função SearchList retorne 0, a função é finalizada de maneira imediata retornando false,
    caso contrário, utilizando os ponteiros da SearchList, são feitos alguns reapontamentos em cada nível
    ,e então o elemento de fato é eliminado liberando a memória alocada, o tamanho em cada nível é decrementado
    em uma unidade e então é retornado true.
    
    - PrintHeight : esta função recebe como parâmetros um ponteiro para SkipList e um inteiro para o nível que deve ser
    impresso. A função apenas imprime os elementos presentes em cada nível, do primeiro ao ultimo. A função não possui 
    retorno.

    - PrintList : esta função recebe como parâmetro apenas um ponteiro para SkipList e utiliza da função printHeight
    para imprimir cada nível da SkipList, do superior ao inferior. A função não possui retorno.
    
    - Freelist: função que deleta os elementos da SkipList e então, libera a SkipList de fato. É utilizada toda vez que
    o programa é finalizado, para que toda memória utilizada seja liberada. Como o nível 0 concentra todos os elementos a lista,
    a liberação da lista é realizada apenas neste nível.

    - Main : a Main é a função principal do programa que realiza apenas a chamada das outras funções, utilizando um código para
    cada função, I para inserção, B para busca, R para remoção, P para impressão de um nível e A para impressão de toda SkipList.
    Caso nenhuma das opções for escolhida, é chamada a função FreeList e então o programa é finalizado.

    //----------------------------------------------------Conclusões---------------------------------------------------------//

    A SkipList é uma versão bem mais otimizada da Lista simples, fazendo com que ela seja mais eficaz e mais viável em projetos e
    programas que preferem trabalhar com pouco uso de memória.
    Nesta implementanção, a função mais importante de todo o programa é a SearchList, que é usada na inserção e na remoção de um
    elemento mantendo a lista ordenada, diminuindo a complexidade de uma busca normal. Além disso, com algumas condições implementas,
    o balanceamento dos níveis é sempre mantido.
    Uma das maiores complicações na implementação foi entender de fato como a SkipList funciona, após isso bastou apenas entender
    cada caso base, erro e algumas condições específicas. A atenção ao longo da implementação foi crucial, pois como as funções de 
    inserção, remoção e busca dependem uma da outra, quando um erro ocorria, era muito difícil de identificar em qual das funções 
    o erro estav presente, o que levava tempo e paciência.
    No geral a construção do programa foi uma ótima experiência de aprendizado pessoal, paciência e organização.
    */
