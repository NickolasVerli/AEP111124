#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_USUARIOS 100
#define MAX_NOME 50
#define MAX_EMAIL 50
#define MAX_SENHA 50
#define SHIFT 3  

typedef struct {
    int id;
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char senha[MAX_SENHA];
} Usuario;

void incluirUsuario(Usuario usuarios[], int *quantidade);
void alterarUsuario(Usuario usuarios[], int quantidade);
void excluirUsuario(Usuario usuarios[], int *quantidade);
void listarUsuarios(Usuario usuarios[], int quantidade);
void salvarDados(Usuario usuarios[], int quantidade);
void cifraCesar(char *texto, int deslocamento);

int main() {
    Usuario usuarios[MAX_USUARIOS];
    int quantidadeUsuarios = 0;
    int opcao;

    do {
        printf("\n*** Menu de Usuarios ***\n");
        printf("1. Incluir Usuario\n");
        printf("2. Alterar Usuario\n");
        printf("3. Excluir Usuario\n");
        printf("4. Listar Usuarios\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  

        switch(opcao) {
            case 1:
                incluirUsuario(usuarios, &quantidadeUsuarios);
                break;
            case 2:
                alterarUsuario(usuarios, quantidadeUsuarios);
                break;
            case 3:
                excluirUsuario(usuarios, &quantidadeUsuarios);
                break;
            case 4:
                listarUsuarios(usuarios, quantidadeUsuarios);
                break;
            case 5:
                salvarDados(usuarios, quantidadeUsuarios);
                printf("Saindo... Ate logo!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

void incluirUsuario(Usuario usuarios[], int *quantidade) {
    if (*quantidade >= MAX_USUARIOS) {
        printf("Limite de usuarios atingido. Nao e possível adicionar mais usuarios.\n");
        return;
    }

    Usuario novo;
    novo.id = *quantidade + 1;
    printf("Digite o nome do usuario: ");
    fgets(novo.nome, MAX_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; 

    printf("Digite o email do usuario: ");
    fgets(novo.email, MAX_EMAIL, stdin);
    novo.email[strcspn(novo.email, "\n")] = '\0'; 

    char senha[MAX_SENHA];
    int senhaValida = 0;
    while (!senhaValida) {
        printf("Digite a senha do usuario (deve conter pelo menos uma letra maiuscula, uma letra minuscula, um numero e um simbolo):\n ");
        fgets(senha, MAX_SENHA, stdin);
        senha[strcspn(senha, "\n")] = '\0'; 

        int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
        for (int i = 0; senha[i] != '\0'; i++) {
            if (isupper(senha[i])) hasUpper = 1;
            else if (islower(senha[i])) hasLower = 1;
            else if (isdigit(senha[i])) hasDigit = 1;
            else if (ispunct(senha[i])) hasSpecial = 1;
        }

        if (hasUpper && hasLower && hasDigit && hasSpecial) {
            senhaValida = 1;
            strcpy(novo.senha, senha);
        } else {
            printf("Senha invalida! A senha deve conter uma letra maiuscula, uma minuscula, um numero e um simbolo.\n");
        }
    }

    usuarios[*quantidade] = novo;
    (*quantidade)++;
    printf("Usuario %s adicionado com sucesso!\n", novo.nome);
}

void alterarUsuario(Usuario usuarios[], int quantidade) {
    int id;
    printf("Digite o ID do usuario a ser alterado: ");
    scanf("%d", &id);
    getchar();  

    if (id <= 0 || id > quantidade) {
        printf("Usuario não encontrado.\n");
        return;
    }

    Usuario *usuario = &usuarios[id - 1];  
    printf("Alterando usuario: %s\n", usuario->nome);

    printf("Digite o novo nome (atualmente: %s): ", usuario->nome);
    fgets(usuario->nome, MAX_NOME, stdin);
    usuario->nome[strcspn(usuario->nome, "\n")] = '\0';  

    printf("Digite o novo email (atualmente: %s): ", usuario->email);
    fgets(usuario->email, MAX_EMAIL, stdin);
    usuario->email[strcspn(usuario->email, "\n")] = '\0';  

    printf("Digite a nova senha (atualmente: %s): ", usuario->senha);
    char novaSenha[MAX_SENHA];
    fgets(novaSenha, MAX_SENHA, stdin);
    novaSenha[strcspn(novaSenha, "\n")] = '\0';

    int senhaValida = 0;
    while (!senhaValida) {
        int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
        for (int i = 0; novaSenha[i] != '\0'; i++) {
            if (isupper(novaSenha[i])) hasUpper = 1;
            else if (islower(novaSenha[i])) hasLower = 1;
            else if (isdigit(novaSenha[i])) hasDigit = 1;
            else if (ispunct(novaSenha[i])) hasSpecial = 1;
        }

        if (hasUpper && hasLower && hasDigit && hasSpecial) {
            senhaValida = 1;
            strcpy(usuario->senha, novaSenha);
        } else {
            printf("Senha invalida! A senha deve conter uma letra maiuscula, uma minuscula, um numero e um simbolo.\n");
            printf("Digite novamente: ");
            fgets(novaSenha, MAX_SENHA, stdin);
            novaSenha[strcspn(novaSenha, "\n")] = '\0';
        }
    }

    printf("Usuario alterado com sucesso!\n");
}

void excluirUsuario(Usuario usuarios[], int *quantidade) {
    int id;
    printf("Digite o ID do usuario a ser excluído: ");
    scanf("%d", &id);
    getchar();  

    if (id <= 0 || id > *quantidade) {
        printf("Usuario não encontrado.\n");
        return;
    }

    for (int i = id - 1; i < *quantidade - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }

    (*quantidade)--;  
    printf("Usuario excluido com sucesso!\n");
}

void listarUsuarios(Usuario usuarios[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    printf("\nLista de Usuarios:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("ID: %d, Nome: %s, Email: %s\n", usuarios[i].id, usuarios[i].nome, usuarios[i].email);
    }
}

void salvarDados(Usuario usuarios[], int quantidade) {
    FILE *file = fopen("usuarios.txt", "w");
    if (!file) {
        printf("Erro ao salvar os dados.\n");
        return;
    }

    
    for (int i = 0; i < quantidade; i++) {
        cifraCesar(usuarios[i].nome, SHIFT);
        cifraCesar(usuarios[i].email, SHIFT);
        cifraCesar(usuarios[i].senha, SHIFT);
    }

    fwrite(&quantidade, sizeof(int), 1, file);
    fwrite(usuarios, sizeof(Usuario), quantidade, file);
    fclose(file);
    printf("Dados salvos com sucesso!\n");
}

void cifraCesar(char *texto, int deslocamento) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha(texto[i])) {  
            char base = (isupper(texto[i])) ? 'A' : 'a';
            texto[i] = (texto[i] - base + deslocamento) % 26 + base;
        }
    }
}
