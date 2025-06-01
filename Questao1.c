#include <stdio.h>
#include <string.h>

#define ESTADOS 26

struct DadosEstado {
    char nome[20];
    int numVeiculos;
    int Acidentes;
};

void coletarDados(struct DadosEstado d[]) {
    char lista_estados[ESTADOS][20] = {
        "Acre", "Alagoas", "Amapa", "Amazonas", "Bahia", "Ceara",
        "Espirito Santo", "Goias", "Maranhao", "Mato Grosso", "Mato Grosso do Sul",
        "Minas Gerais", "Para", "Paraiba", "Parana", "Pernambuco", "Piaui", "Rio de Janeiro",
        "Rio Grande do Norte", "Rio Grande do Sul", "Rondonia", "Roraima", "Santa Catarina", "Sao Paulo",
        "Sergipe", "Tocantins"
    };
    
    for (int i = 0; i < ESTADOS; i++) {
        strcpy(d[i].nome, lista_estados[i]);
        scanf("%d", &d[i].numVeiculos);
        scanf("%d", &d[i].Acidentes);
    }
}

void encontrarExtremos(struct DadosEstado d[], int *maior, int *menor) {
    *maior = 0;
    *menor = 0;
    for (int i = 1; i < ESTADOS; i++) {
        if (d[i].Acidentes > d[*maior].Acidentes) *maior = i;
        if (d[i].Acidentes < d[*menor].Acidentes) *menor = i;
    }
}

double percentualAcidentes(struct DadosEstado estado) {
    if (estado.numVeiculos == 0) return 0.0;
    return (estado.Acidentes * 100.0) / estado.numVeiculos;
}

double mediaAcidentes(struct DadosEstado d[]) {
    int total = 0;
    for (int i = 0; i < ESTADOS; i++) {
        total += d[i].Acidentes;
    }
    return (double)total / ESTADOS;
}

void acimaDaMedia(struct DadosEstado d[], double media) {
    for (int i = 0; i < ESTADOS; i++) {
        if (d[i].Acidentes > media) {
            printf("%s\n", d[i].nome);
        }
    }
}

int main() {
    struct DadosEstado Dados[ESTADOS];
    int indice_maior, indice_menor;
    double media;
    
    printf("Cole os comandos necessários: ");
    coletarDados(Dados);
    
    encontrarExtremos(Dados, &indice_maior, &indice_menor);
    printf("\n\nEstado com mais acidentes: %s\n", Dados[indice_maior].nome);
    printf("Estado com menos acidentes: %s\n", Dados[indice_menor].nome);
    
    printf("Percentual de acidentes por veiculo em cada estado:\n");
    for (int i = 0; i < ESTADOS; i++) {
        double percentual = percentualAcidentes(Dados[i]);
        printf("%s: %.2f%%\n", Dados[i].nome, percentual);
    }
    
    media = mediaAcidentes(Dados);
    printf("Media de acidentes: %.2f\n por estado.\n", media);
    
    printf("Estados com acidentes acima da media:\n");
    acimaDaMedia(Dados, media);
    
    return 0;
}