#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento {
    int valor;
    struct Elemento *proximo;
} Elemento;

typedef struct  {
    struct Elemento *ultimo;
    struct Elemento *primeiro;
} Fila;


Elemento Enfileirar(Fila *fila, int valor) {
    //Teste fila vazia
    struct Elemento *novoElemento = (struct Elemento*) malloc(sizeof(struct Elemento));
    novoElemento->valor = valor;
    if(fila->ultimo == 0) {
        fila->ultimo = novoElemento;
        fila->primeiro = novoElemento;
    } else {
        novoElemento->proximo = fila->ultimo;
        fila->ultimo = novoElemento;
    }
    return *novoElemento;
}

void Desinfileirar(Fila *fila) {

    if(fila->primeiro == fila->ultimo && fila->primeiro == NULL) {
        printf("Fila Vazia");
        return;
    } else if(fila->primeiro == fila->ultimo) {
        fila->primeiro = NULL;
        fila->ultimo = NULL;
    }
    
    Elemento *atualTemp = (struct Elemento*) malloc(sizeof(struct Elemento));
    Elemento *proxTemp = (struct Elemento*) malloc(sizeof(struct Elemento));
    
    atualTemp = fila->ultimo;
    proxTemp = atualTemp->proximo;
    do {
        atualTemp = atualTemp->proximo;
        proxTemp = atualTemp->proximo;
    } while(proxTemp->proximo != NULL);
    atualTemp->proximo = NULL;
    fila->primeiro = atualTemp;
}

int main() {
    Fila *fila = (Fila*) malloc(sizeof(Fila));;

    int continuar = 1, opcao;
    printf("=== Bem vindo ao gerenciador de fila ===\n\n");
    while(continuar) {
        printf("1 - Ver fila atual\n");
        printf("2 - Enfileirar novo numero\n");
        printf("3 - Desenfileirar\n");
        printf("4 - Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao)
        {
        case 1:
            if(fila->primeiro == NULL) {
                printf("Fila Vazia!!\n");
            } else {
                printf("Listando (ultimo ate o primeiro): \n");
                Elemento *elementoAtual = fila->ultimo;
                while(elementoAtual != NULL) {
                    if(elementoAtual->proximo == NULL) {
                        printf("%d\n", elementoAtual->valor);
                        elementoAtual = elementoAtual->proximo;
                    } else {
                        printf("%d -> ", elementoAtual->valor);
                        elementoAtual = elementoAtual->proximo;
                    } 
                }
            }
            break;
        case 2:
            printf("Escolha um numero para enfileirar: ");
            int num;
            scanf("%d", &num);
            Enfileirar(fila, num);
            printf("%d entrou para a fila!\n", num);
            break;
        case 3:
            Desinfileirar(fila);
            printf("Elemento da primeira posicao, desinfileirado!\n");
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