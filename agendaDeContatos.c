#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 100

typedef struct {
    char nome[50];
    char telefone[15];
    char email[50];
} Contato;

// Busca os contatos do arquivo agenda
int carregarContatos(Contato *contatos) {
    FILE *arquivo = fopen("agenda.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum contato encontrado.\n");
        return 0;
    }
    
    int totalContatos = 0;
    
    while (fscanf(arquivo, "%s\n%s\n%s\n", contatos[totalContatos].nome, contatos[totalContatos].telefone, contatos[totalContatos].email) != EOF) {
        totalContatos++;
    }
    
    fclose(arquivo);
    return totalContatos;
}

// Exibir os contatos carregados do arquivo
void exibirContatos(Contato *contatos, int totalContatos) {
    printf("\n=== Lista de Contatos ===\n");

    if(totalContatos == 0) {
        printf("Lista vazia!\n");
        return;
    }

    for (int i = 0; i < totalContatos; i++) {
        printf("Contato %d:\n", i + 1);
        printf("Nome: %s\n", contatos[i].nome);
        printf("Telefone: %s\n", contatos[i].telefone);
        printf("Email: %s\n\n", contatos[i].email);
    }
}

// Adiciona um novo contato ao array de contatos
void adicionarContato(Contato *contatos, int *totalContatos) {
    if (*totalContatos >= MAX_CONTATOS) {
        printf("Agenda cheia! Não é possível adicionar mais contatos.\n");
        return;
    }
    
    Contato novoContato;
    
    printf("Digite o nome: ");
    getchar(); // Limpa o buffer do scanf da atribuição de opção
    fgets(novoContato.nome, 50, stdin);
    novoContato.nome[strcspn(novoContato.nome, "\n")] = 0; // Remover o char \n que fica ao final do nome 
    
    printf("Digite o telefone: ");
    fgets(novoContato.telefone, 15, stdin);
    novoContato.telefone[strcspn(novoContato.telefone, "\n")] = 0;
    
    printf("Digite o email: ");
    fgets(novoContato.email, 50, stdin);
    novoContato.email[strcspn(novoContato.email, "\n")] = 0;
    
    contatos[*totalContatos] = novoContato;
    (*totalContatos)++;
    
    printf("Contato adicionado com sucesso!\n");
}

// Remove um contato do array de contatos
void removerContato(Contato *contatos, int *totalContatos) {
    int index;
    
    printf("Digite o numero do contato que deseja remover: ");
    scanf("%d", &index);
    
    if (index < 1 || index > *totalContatos) {
        printf("Contato inválido!\n");
        return;
    }
    
    index--; // Ajustar para índice de base 0
    
    for (int i = index; i < *totalContatos - 1; i++) {
        contatos[i] = contatos[i + 1];
    }
    
    (*totalContatos)--;
    printf("Contato removido com sucesso!\n");
}

// Editar um contato existente no array de contatos
void editarContato(Contato *contatos, int totalContatos) {
    int index;
    
    printf("Digite o numero do contato que deseja editar: ");
    scanf("%d", &index);
    
    if (index < 1 || index > totalContatos) {
        printf("Contato inválido!\n");
        return;
    }
    
    index--; // Ajustar para índice de base 0
    
    printf("Editando o contato %d:\n", index + 1);
    printf("Nome atual: %s\n", contatos[index].nome);
    printf("Digite o novo nome (ou pressione Enter para manter o atual): ");
    
    getchar(); // Limpar buffer do scanf do scanf do index
    char novoNome[50];
    fgets(novoNome, 50, stdin);
    if (strcmp(novoNome, "\n") != 0) {
        novoNome[strcspn(novoNome, "\n")] = 0;
        strcpy(contatos[index].nome, novoNome);
    }
    
    printf("Telefone atual: %s\n", contatos[index].telefone);
    printf("Digite o novo telefone (ou pressione Enter para manter o atual): ");
    
    char novoTelefone[15];
    fgets(novoTelefone, 15, stdin);
    if (strcmp(novoTelefone, "\n") != 0) {
        novoTelefone[strcspn(novoTelefone, "\n")] = 0;
        strcpy(contatos[index].telefone, novoTelefone);
    }
    
    printf("Email atual: %s\n", contatos[index].email);
    printf("Digite o novo email (ou pressione Enter para manter o atual): ");
    
    char novoEmail[50];
    fgets(novoEmail, 50, stdin);
    if (strcmp(novoEmail, "\n") != 0) {
        novoEmail[strcspn(novoEmail, "\n")] = 0;
        strcpy(contatos[index].email, novoEmail);
    }
    
    printf("Contato editado com sucesso!\n");
}

// Salvar os contatos do array de contatos no arquivo agenda
void salvarContatos(Contato *contatos, int totalContatos) {
    FILE *arquivo = fopen("agenda.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    for (int i = 0; i < totalContatos; i++) {
        fprintf(arquivo, "%s\n%s\n%s\n", contatos[i].nome, contatos[i].telefone, contatos[i].email);
    }
    
    fclose(arquivo);
    printf("Contatos salvos no arquivo com sucesso!\n");
}

int main() {

    Contato contatos[MAX_CONTATOS];
    int totalContatos = carregarContatos(contatos);
    int continuar = 1;

    while(continuar == 1) {
        int opcao;

        printf("\n=== Agenda de Contatos ===\n");
        printf("1 - Ver agenda \n");
        printf("2 - Adicionar novo contato \n");
        printf("3 - Remover um contato \n");
        printf("4 - Editar um contato \n");
        printf("5 - Salvar e sair \n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                exibirContatos(contatos, totalContatos);
                break;
            case 2:
                adicionarContato(contatos, &totalContatos);
                break;
            case 3:
                removerContato(contatos, &totalContatos);
                break;
            case 4:
                editarContato(contatos, totalContatos);
                break;
            case 5:
                salvarContatos(contatos, totalContatos);
                continuar = 0;
                break;
            default:
                printf("Opção inválida!\n");
        }
    } 

    return 0;
}