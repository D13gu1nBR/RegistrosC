#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 40
#define TAM_DESCRICAO 100

typedef struct {
    int codigo;
    char descricao[TAM_DESCRICAO];
    double valor_unitario;
    int quantidade_estoque;
} Produto;

void cadastrar_produto(Produto produtos[], int *quantidade_produtos) {
    if (*quantidade_produtos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido (máximo %d).\n", MAX_PRODUTOS);
        return;
    }
    
    printf("\n--- Cadastro de Novo Produto ---\n");
    
    printf("Código: ");
    scanf("%d", &produtos[*quantidade_produtos].codigo);
    getchar();
    
    printf("Descrição: ");
    fgets(produtos[*quantidade_produtos].descricao, TAM_DESCRICAO, stdin);
    produtos[*quantidade_produtos].descricao[strcspn(produtos[*quantidade_produtos].descricao, "\n")] = '\0';
    
    printf("Valor unitário: ");
    scanf("%lf", &produtos[*quantidade_produtos].valor_unitario);
    
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[*quantidade_produtos].quantidade_estoque);
    
    (*quantidade_produtos)++;
    
    printf("Produto cadastrado com sucesso!\n");
}

void alterarValor(Produto produtos[], int quantidade_produtos) {
    int codigo, encontrado = 0;
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);
    
    for(int i = 0; i < quantidade_produtos; i++) {
        if(codigo == produtos[i].codigo) {
            printf("Novo valor para '%s': ", produtos[i].descricao);
            scanf("%lf", &produtos[i].valor_unitario);
            printf("Valor atualizado!\n");
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado) {
        printf("Produto não encontrado!\n");
    }
}

void informarValor(Produto produtos[], int quantidade_produtos) {
    int codigo;
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);
    
    for(int i = 0; i < quantidade_produtos; i++) {
        if(codigo == produtos[i].codigo) {
            printf("Valor unitário: R$ %.2lf\n", produtos[i].valor_unitario);
            return;
        }
    }
    
    printf("Produto não encontrado!\n");
}

void informarEstoque(Produto produtos[], int quantidade_produtos) {
    int codigo;
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);
    
    for(int i = 0; i < quantidade_produtos; i++) {
        if(codigo == produtos[i].codigo) {
            printf("Estoque: %d unidades\n", produtos[i].quantidade_estoque);
            return;
        }
    }
    
    printf("Produto não encontrado!\n");
}

void venderProduto(Produto produtos[], int quantidade_produtos) {
    int codigo, quantidade, encontrado = 0;
    printf("Código do produto: ");
    scanf("%d", &codigo);
    
    for(int i = 0; i < quantidade_produtos; i++) {
        if(codigo == produtos[i].codigo) {
            encontrado = 1;
            printf("Quantidade desejada: ");
            scanf("%d", &quantidade);
            
            if(quantidade <= 0) {
                printf("Quantidade inválida!\n");
                return;
            }
            
            if(produtos[i].quantidade_estoque == 0) {
                printf("Produto sem estoque disponível!\n");
                return;
            }
            
            if(quantidade <= produtos[i].quantidade_estoque) {
                produtos[i].quantidade_estoque -= quantidade;
                double total = produtos[i].valor_unitario * quantidade;
                printf("Venda realizada! Valor total: R$ %.2lf\n", total);
            } else {
                char opcao;
                printf("Quantidade insuficiente! Deseja comprar todo o estoque? (S/N): ");
                scanf(" %c", &opcao);
                
                if(opcao == 'S' || opcao == 's') {
                    double total = produtos[i].valor_unitario * produtos[i].quantidade_estoque;
                    produtos[i].quantidade_estoque = 0;
                    printf("Compra efetivada! Valor total: R$ %.2lf\n", total);
                } else {
                    printf("Compra cancelada!\n");
                }
            }
            break;
        }
    }
    
    if(!encontrado) {
        printf("Produto não encontrado!\n");
    }
}

void atualizarEstoque(Produto produtos[], int quantidade_produtos) {
    int codigo, nova_quantidade, encontrado = 0;
    printf("Código do produto: ");
    scanf("%d", &codigo);
    
    for(int i = 0; i < quantidade_produtos; i++) {
        if(codigo == produtos[i].codigo) {
            encontrado = 1;
            printf("Nova quantidade em estoque: ");
            scanf("%d", &nova_quantidade);
            
            if(nova_quantidade >= 0) {
                produtos[i].quantidade_estoque = nova_quantidade;
                printf("Estoque atualizado!\n");
            } else {
                printf("Quantidade inválida!\n");
            }
            break;
        }
    }
    
    if(!encontrado) {
        printf("Produto não encontrado!\n");
    }
}

void listarProdutos(Produto produtos[], int quantidade_produtos) {
    printf("\n--- Todos os Produtos ---\n");
    if(quantidade_produtos == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    
    for(int i = 0; i < quantidade_produtos; i++) {
        printf("Código: %d | Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
    }
}

void listarEstoqueZero(Produto produtos[], int quantidade_produtos) {
    printf("\n--- Produtos com Estoque Zero ---\n");
    int tem_zero = 0;
    
    for(int i = 0; i < quantidade_produtos; i++) {
        if(produtos[i].quantidade_estoque == 0) {
            printf("Código: %d | Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
            tem_zero = 1;
        }
    }
    
    if(!tem_zero) {
        printf("Nenhum produto com estoque zero!\n");
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int quantidade_produtos = 0;
    int opcao;
    
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1 - Cadastrar novo produto\n");
        printf("2 - Alterar valor unitário\n");
        printf("3 - Consultar valor unitário\n");
        printf("4 - Consultar estoque\n");
        printf("5 - Realizar venda\n");
        printf("6 - Atualizar estoque\n");
        printf("7 - Listar todos os produtos\n");
        printf("8 - Listar produtos sem estoque\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            cadastrar_produto(produtos, &quantidade_produtos);
        } else if (opcao == 2) {
            alterarValor(produtos, quantidade_produtos);
        } else if (opcao == 3) {
            informarValor(produtos, quantidade_produtos);
        } else if (opcao == 4) {
            informarEstoque(produtos, quantidade_produtos);
        } else if (opcao == 5) {
            venderProduto(produtos, quantidade_produtos);
        } else if (opcao == 6) {
            atualizarEstoque(produtos, quantidade_produtos);
        } else if (opcao == 7) {
            listarProdutos(produtos, quantidade_produtos);
        } else if (opcao == 8) {
            listarEstoqueZero(produtos, quantidade_produtos);
        } else if (opcao == 0) {
            printf("Encerrando sistema...\n");
        } else {
            printf("Opção inválida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}