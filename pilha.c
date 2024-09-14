#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento {
    int valor;
    struct Elemento *anterior;
} Elemento;

typedef struct  {
    struct Elemento *topo;
} Pilha;


Elemento push(Pilha *pilha, int valor) {
    //Teste pilha vazia
    struct Elemento *novoElemento = (struct Elemento*) malloc(sizeof(struct Elemento));
    novoElemento->valor = valor;
    if(pilha->topo == 0) {
        pilha->topo = novoElemento;
    } else {
        novoElemento->anterior = pilha->topo;
        pilha->topo = novoElemento;
    }
    return *novoElemento;
}

void pop(Pilha *pilha) {

    if(pilha->topo == NULL) {
        printf("Pilha Vazia");
        return;
    }
    
    pilha->topo = pilha->topo->anterior;
}

int main() {
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));;
    pilha->topo = NULL;
    int continuar = 1, opcao;
    printf("=== Bem vindo ao gerenciador de pilha ===\n\n");
    while(continuar) {
        printf("1 - Ver pilha atual\n");
        printf("2 - Empilhar novo numero\n");
        printf("3 - Tirar elemento da pilha\n");
        printf("4 - Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao)
        {
        case 1:
            if(pilha->topo == NULL) {
                printf("Fila Vazia!!\n");
            } else {
                printf("Listando itens (topo ate o fundo): \n");
                Elemento *elementoAtual = pilha->topo;
                while(elementoAtual != NULL) {
                    if(elementoAtual->anterior == NULL) {
                        printf("%d\n", elementoAtual->valor);
                        elementoAtual = elementoAtual->anterior;
                    } else {
                        printf("%d <- ", elementoAtual->valor);
                        elementoAtual = elementoAtual->anterior;
                    } 
                }
            }
            break;
        case 2:
            printf("Escolha um numero para empilhar: ");
            int num;
            scanf("%d", &num);
            push(pilha, num);
            printf("%d entrou para o topo pilha!\n", num);
            break;
        case 3:
            pop(pilha);
            printf("Elemento retirado do topo da pilha!\n");
            break;
        case 4:
            printf("Fim do programa!\n");
            continuar = 0;
            break;
        default:
            printf("Opcao invalida tente novamente!");
            break;
        }
    }
}   