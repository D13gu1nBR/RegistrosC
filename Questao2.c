#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 40
#define TAM_DESCRICAO 100

typedef struct {
    int codigo;
    char descricao[TAM_DESCRICAO];
    float valor;
    int estoque;
} Produto;

Produto produtos[MAX_PRODUTOS];
int qtd_produtos = 0;

void cadastrar() {
    if (qtd_produtos >= MAX_PRODUTOS) {
        printf("\nERRO: Limite de produtos atingido!\n\n");
        return;
    }
    
    Produto novo;
    scanf("%d", &novo.codigo);
    
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].codigo == novo.codigo) {
            printf("\nERRO: Codigo ja existe!\n\n");
            return;
        }
    }
    
    scanf(" %[^\n]s", novo.descricao);
    scanf("%f", &novo.valor);
    scanf("%d", &novo.estoque);
    
    produtos[qtd_produtos] = novo;
    qtd_produtos++;
    printf("\nSUCESSO: Produto cadastrado!\n\n");
}

void alterarValor() {
    int codigo;
    scanf("%d", &codigo);
    
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            float novo_valor;
            scanf("%f", &novo_valor);
            
            if (novo_valor <= 0) {
                printf("\nERRO: Valor invalido!\n\n");
                return;
            }
            
            produtos[i].valor = novo_valor;
            printf("\nSUCESSO: Valor atualizado!\n\n");
            return;
        }
    }
    
    printf("\nERRO: Produto nao encontrado!\n\n");
}

void consultarValor() {
    int codigo;
    scanf("%d", &codigo);
    
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("\nVALOR: R$ %.2f\n\n", produtos[i].valor);
            return;
        }
    }
    
    printf("\nERRO: Produto nao encontrado!\n\n");
}

void consultarEstoque() {
    int codigo;
    scanf("%d", &codigo);
    
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("\nESTOQUE: %d unidades\n\n", produtos[i].estoque);
            return;
        }
    }
    
    printf("\nERRO: Produto nao encontrado!\n\n");
}

void vender() {
    int codigo, quantidade;
    scanf("%d%d", &codigo, &quantidade);
    
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            if (produtos[i].estoque == 0) {
                printf("\nERRO: Produto sem estoque!\n\n");
                return;
            }
            
            if (quantidade <= 0) {
                printf("\nERRO: Quantidade invalida!\n\n");
                return;
            }
            
            if (quantidade <= produtos[i].estoque) {
                float total = produtos[i].valor * quantidade;
                produtos[i].estoque -= quantidade;
                printf("\nSUCESSO: Venda realizada! Total: R$ %.2f\n\n", total);
            } else {
                char opcao;
                scanf(" %c", &opcao);
                
                if (opcao == 'S' || opcao == 's') {
                    float total = produtos[i].valor * produtos[i].estoque;
                    produtos[i].estoque = 0;
                    printf("\nSUCESSO: Compra efetivada! Total: R$ %.2f\n\n", total);
                } else {
                    printf("\nAVISO: Venda cancelada!\n\n");
                }
            }
            return;
        }
    }
    
    printf("\nERRO: Produto nao encontrado!\n\n");
}

void atualizarEstoque() {
    int codigo, nova_quantidade;
    scanf("%d%d", &codigo, &nova_quantidade);
    
    if (nova_quantidade < 0) {
        printf("\nERRO: Quantidade invalida!\n\n");
        return;
    }
    
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            produtos[i].estoque = nova_quantidade;
            printf("\nSUCESSO: Estoque atualizado!\n\n");
            return;
        }
    }
    
    printf("\nERRO: Produto nao encontrado!\n\n");
}

void listarTodos() {
    printf("\n=== TODOS OS PRODUTOS ===\n");
    if (qtd_produtos == 0) {
        printf("Nenhum produto cadastrado\n");
    } else {
        for (int i = 0; i < qtd_produtos; i++) {
            printf("Codigo: %d | Descricao: %s\n", produtos[i].codigo, produtos[i].descricao);
        }
    }
    printf("=========================\n\n");
}

void listarZerados() {
    printf("\n=== PRODUTOS COM ESTOQUE ZERO ===\n");
    int encontrados = 0;
    
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].estoque == 0) {
            printf("Codigo: %d | Descricao: %s\n", produtos[i].codigo, produtos[i].descricao);
            encontrados = 1;
        }
    }
    
    if (!encontrados) {
        printf("Nenhum produto com estoque zero\n");
    }
    printf("=================================\n\n");
}

int main() {
    char comando[20];
    
    printf("=== PAPELARIA ESCOLAR ===\n");
    printf("SISTEMA INICIADO - COLE OS COMANDOS:\n\n");
    printf("COMANDOS DISPONIVEIS:\n");
    printf("CADASTRAR\n");
    printf("ALTERAR_VALOR\n");
    printf("CONSULTAR_VALOR\n");
    printf("CONSULTAR_ESTOQUE\n");
    printf("VENDER\n");
    printf("ATUALIZAR_ESTOQUE\n");
    printf("LISTAR_TODOS\n");
    printf("LISTAR_ZERADOS\n");
    printf("SAIR\n\n");
    printf("AGUARDANDO COMANDOS...\n\n");

    while (1) {
        scanf("%s", comando);
        
        if (strcmp(comando, "CADASTRAR") == 0) {
            cadastrar();
        }
        else if (strcmp(comando, "ALTERAR_VALOR") == 0) {
            alterarValor();
        }
        else if (strcmp(comando, "CONSULTAR_VALOR") == 0) {
            consultarValor();
        }
        else if (strcmp(comando, "CONSULTAR_ESTOQUE") == 0) {
            consultarEstoque();
        }
        else if (strcmp(comando, "VENDER") == 0) {
            vender();
        }
        else if (strcmp(comando, "ATUALIZAR_ESTOQUE") == 0) {
            atualizarEstoque();
        }
        else if (strcmp(comando, "LISTAR_TODOS") == 0) {
            listarTodos();
        }
        else if (strcmp(comando, "LISTAR_ZERADOS") == 0) {
            listarZerados();
        }
        else if (strcmp(comando, "SAIR") == 0) {
            printf("\nSistema encerrado\n");
            break;
        }
        else {
            printf("\nERRO: Comando invalido! [%s]\n\n", comando);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    return 0;
}