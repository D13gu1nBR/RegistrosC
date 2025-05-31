#include <stdio.h>
#include <string.h>

struct DadosEstado {
    char nome[20];
    int numVeiculos;
    int Acidentes;
};

void coletarDados(struct DadosEstado d[]) {
    for (int i = 0; i < 26; i++) {
        printf("Digite o nome do Estado: ");
        fgets(d[i].nome, 20, stdin);
        d[i].nome[strcspn(d[i].nome, "\n")] = '\0';
        
        printf("Digite o número de veículos do estado: ");
        scanf("%d", &d[i].numVeiculos);
        getchar();
        
        printf("Digite o número de Acidentes no estado: ");
        scanf("%d", &d[i].Acidentes);
        getchar();
    }
}

void encontrarExtremos(struct DadosEstado d[], int *maior, int *menor) {
    *maior = 0;
    *menor = 0;
    for (int i = 1; i < 26; i++) {
        if (d[i].Acidentes > d[*maior].Acidentes) *maior = i;
        if (d[i].Acidentes < d[*menor].Acidentes) *menor = i;
    }
}

double percentualAcidentes(struct DadosEstado d[], char nomeEstado[]) {
    for (int i = 0; i < 26; i++) {
        if (strcmp(nomeEstado, d[i].nome) == 0) {
            return (d[i].Acidentes / (double)d[i].numVeiculos) * 100.0;
        }
    }
    return -1.0;
}

double mediaAcidentes(struct DadosEstado d[]) {
    int somatorio = 0;
    for (int i = 0; i < 26; i++) {
        somatorio += d[i].Acidentes;
    }
    return (double)somatorio / 26.0;
}

void acimaDaMedia(struct DadosEstado d[], double media) {
    for (int i = 0; i < 26; i++) {
        if (d[i].Acidentes > media) {
            printf("O Estado %s tem acidentes acima da media\n", d[i].nome);
        }
    }
}

int main() {
    struct DadosEstado Dados[26];
    coletarDados(Dados);
    
    int maior, menor;
    encontrarExtremos(Dados, &maior, &menor);
    printf("Estado com mais acidentes: %s\n", Dados[maior].nome);
    printf("Estado com menos acidentes: %s\n", Dados[menor].nome);
    
    char nome[20];
    printf("Digite o nome do estado para o percentual: ");
    fgets(nome, 20, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n'
    
    double percentual = percentualAcidentes(Dados, nome);
    if (percentual >= 0) {
        printf("Percentual de acidentes em %s: %.2lf%%\n", nome, percentual);
    } else {
        printf("Estado nao encontrado!\n");
    }
    
    double media = mediaAcidentes(Dados);
    printf("Media de acidentes no pais: %.2lf\n", media);
    acimaDaMedia(Dados, media);
    
    return 0;
}