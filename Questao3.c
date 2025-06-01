#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[15];
    float saldo;
} Conta;

Conta corrente[MAX_CONTAS];
Conta poupanca[MAX_CONTAS];
int qtd_corrente = 0;
int qtd_poupanca = 0;

int buscar(Conta cadastro[], int tamanho, int numero_conta) {
    if (tamanho == 0) return -1;
    for (int i = 0; i < tamanho; i++) {
        if (cadastro[i].numero == numero_conta) return i;
    }
    return -2;
}

void cadastrarConta(Conta cadastro[], int *tamanho, const char *tipo) {
    if (*tamanho >= MAX_CONTAS) {
        printf("ERRO: Limite de contas atingido!\n");
        return;
    }
    
    int numero;
    scanf("%d", &numero);
    
    int pos = buscar(cadastro, *tamanho, numero);
    if (pos >= 0) {
        printf("ERRO: Conta ja existe!\n");
        return;
    }
    
    Conta nova;
    nova.numero = numero;
    scanf(" %[^\n]s", nova.nome);
    scanf("%s", nova.cpf);
    scanf("%s", nova.telefone);
    nova.saldo = 0.0;
    
    cadastro[*tamanho] = nova;
    (*tamanho)++;
    printf("SUCESSO: Conta %s cadastrada!\n", tipo);
}

void consultarSaldo(Conta cadastro[], int tamanho, const char *tipo) {
    int numero;
    scanf("%d", &numero);
    
    int pos = buscar(cadastro, tamanho, numero);
    if (pos == -1) printf("ERRO: Nenhuma conta %s cadastrada!\n", tipo);
    else if (pos == -2) printf("ERRO: Conta %s nao encontrada!\n", tipo);
    else printf("SALDO: R$ %.2f\n", cadastro[pos].saldo);
}

void depositar(Conta cadastro[], int tamanho, const char *tipo) {
    int numero;
    float valor;
    scanf("%d%f", &numero, &valor);
    
    int pos = buscar(cadastro, tamanho, numero);
    if (pos < 0) {
        printf(pos == -1 ? "ERRO: Nenhuma conta %s cadastrada!\n" : "ERRO: Conta %s nao encontrada!\n", tipo);
        return;
    }
    
    if (valor <= 0) {
        printf("ERRO: Valor invalido!\n");
        return;
    }
    
    cadastro[pos].saldo += valor;
    printf("SUCESSO: Deposito realizado! Novo saldo: R$ %.2f\n", cadastro[pos].saldo);
}

void sacar(Conta cadastro[], int tamanho, const char *tipo) {
    int numero;
    float valor;
    scanf("%d%f", &numero, &valor);
    
    int pos = buscar(cadastro, tamanho, numero);
    if (pos < 0) {
        printf(pos == -1 ? "ERRO: Nenhuma conta %s cadastrada!\n" : "ERRO: Conta %s nao encontrada!\n", tipo);
        return;
    }
    
    if (valor <= 0) {
        printf("ERRO: Valor invalido!\n");
        return;
    }
    
    if (valor > cadastro[pos].saldo) {
        printf("ERRO: Saldo insuficiente!\n");
        return;
    }
    
    cadastro[pos].saldo -= valor;
    printf("SUCESSO: Saque realizado! Novo saldo: R$ %.2f\n", cadastro[pos].saldo);
}

void listarContas(Conta cadastro[], int tamanho, const char *tipo) {
    printf("=== CONTAS %s ===\n", tipo);
    if (tamanho == 0) {
        printf("Nenhuma conta cadastrada\n");
    } else {
        for (int i = 0; i < tamanho; i++) {
            printf("Conta: %d\n", cadastro[i].numero);
            printf("Titular: %s\n", cadastro[i].nome);
            printf("Telefone: %s\n\n", cadastro[i].telefone);
        }
    }
    printf("=====================\n");
}

int main() {
    char comando[30];
    
    printf("=== BANCO DINHEIRO CERTO ===\n");
    printf("SISTEMA INICIADO - COLE OS COMANDOS:\n");
    
    while (1) {
        scanf("%s", comando);
        
        if (strcmp(comando, "CADASTRAR_CORRENTE") == 0) {
            cadastrarConta(corrente, &qtd_corrente, "CORRENTE");
        }
        else if (strcmp(comando, "CADASTRAR_POUPANCA") == 0) {
            cadastrarConta(poupanca, &qtd_poupanca, "POUPANCA");
        }
        else if (strcmp(comando, "CONSULTAR_SALDO_CORRENTE") == 0) {
            consultarSaldo(corrente, qtd_corrente, "CORRENTE");
        }
        else if (strcmp(comando, "CONSULTAR_SALDO_POUPANCA") == 0) {
            consultarSaldo(poupanca, qtd_poupanca, "POUPANCA");
        }
        else if (strcmp(comando, "DEPOSITAR_CORRENTE") == 0) {
            depositar(corrente, qtd_corrente, "CORRENTE");
        }
        else if (strcmp(comando, "DEPOSITAR_POUPANCA") == 0) {
            depositar(poupanca, qtd_poupanca, "POUPANCA");
        }
        else if (strcmp(comando, "SACAR_CORRENTE") == 0) {
            sacar(corrente, qtd_corrente, "CORRENTE");
        }
        else if (strcmp(comando, "SACAR_POUPANCA") == 0) {
            sacar(poupanca, qtd_poupanca, "POUPANCA");
        }
        else if (strcmp(comando, "LISTAR_CORRENTE") == 0) {
            listarContas(corrente, qtd_corrente, "CORRENTE");
        }
        else if (strcmp(comando, "LISTAR_POUPANCA") == 0) {
            listarContas(poupanca, qtd_poupanca, "POUPANCA");
        }
        else if (strcmp(comando, "SAIR") == 0) {
            break;
        }
        else {
            printf("ERRO: Comando invalido!\n");
            // Limpeza do buffer de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    printf("Sistema encerrado\n");
    return 0;
}