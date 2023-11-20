#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <time.h>

// definição da estrutura 'carro'
struct Carro {
    char marca[50];
    char modelo[50];
    int ano;
};

// função para salvar um carro no arquivo
void salvarCarro(struct Carro *carro) {
    FILE *arquivo = fopen("carros.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de carros.\n");
        exit(1);
    }

    fprintf(arquivo, "%s %s %d\n", carro->marca, carro->modelo, carro->ano);

    fclose(arquivo);
}

// função para carregar carros do arquivo
void carregarCarros(struct Carro **carros, int *quantidadeCarros) {
    FILE *arquivo = fopen("carros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de carros.\n");
        exit(1);
    }

    int i = 0;
    while (fscanf(arquivo, "%s %s %d", (*carros)[i].marca, (*carros)[i].modelo, &(*carros)[i].ano) == 3) {
        i++;
        *carros = (struct Carro *)realloc(*carros, (i + 1) * sizeof(struct Carro));
    }

    *quantidadeCarros = i;

    fclose(arquivo);
}

// função para exibir carros disponíveis
void exibirCarros(struct Carro *carros, int quantidadeCarros) {
    printf("\n=== CARROS DISPONÍVEIS ===\n");
    for (int i = 0; i < quantidadeCarros; i++) {
        printf("%d. Marca: %s, Modelo: %s, Ano: %d\n", i + 1, carros[i].marca, carros[i].modelo, carros[i].ano);
    }
}

// função para reservar um carro
void reservarCarro(struct Carro *carros, int *quantidadeCarros) {
    int opcao;

    exibirCarros(carros, *quantidadeCarros);

    printf("Escolha um carro para reservar (digite o número): ");
    scanf("%d", &opcao);

    if (opcao >= 1 && opcao <= *quantidadeCarros) {
        printf("Carro %d reservado: %s %s, Ano: %d\n", opcao, carros[opcao - 1].marca, carros[opcao - 1].modelo, carros[opcao - 1].ano);

        // for para remover o carro reservado da lista
        for (int i = opcao - 1; i < *quantidadeCarros - 1; i++) {
            carros[i] = carros[i + 1];
        }

        (*quantidadeCarros)--;

        // atualizar o arquivo após a reserva
        FILE *arquivo = fopen("carros.txt", "w");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo de carros.\n");
            exit(1);
        }

        for (int i = 0; i < *quantidadeCarros; i++) {
            fprintf(arquivo, "%s %s %d\n", carros[i].marca, carros[i].modelo, carros[i].ano);
        }

        fclose(arquivo);
    } else {
        printf("Opção inválida.\n");
    }
}

// função para exibir os créditos
void exibirCreditos() {
    printf("\n=== CRÉDITOS ===\n");
    printf("Desenvolvido por:\n");
    printf(" - Patrick Duarte\n");
    printf(" - Yasmin Cabral\n");
    printf(" - Victor Gabriel\n");
    printf(" - Mirela Ferraz\n");
    printf(" - Nicolas Brito\n");
}

int main() {
    setlocale(0, "Portuguese");
    struct Carro *carros = NULL;
    int quantidadeCarros = 0;
    int opcao;

	// menu da locadora
    do {
        printf("\n=== MENU ===\n");
        printf("1. Adicionar carro\n");
        printf("2. Ver carros disponíveis\n");
        printf("3. Reservar carro\n");
        printf("4. Créditos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // adicionar carro
                if (carros == NULL) {
                    carros = (struct Carro *)malloc(sizeof(struct Carro));
                } else {
                    carros = (struct Carro *)realloc(carros, (quantidadeCarros + 1) * sizeof(struct Carro));
                }

                printf("Marca do carro: ");
                scanf("%s", carros[quantidadeCarros].marca);

                printf("Modelo do carro: ");
                scanf("%s", carros[quantidadeCarros].modelo);

                printf("Ano do carro: ");
                scanf("%d", &carros[quantidadeCarros].ano);

                salvarCarro(&carros[quantidadeCarros]); // salvar o carro adicionado no arquivo
                quantidadeCarros++;
                break;
            case 2:
                // ver carros disponíveis
                carregarCarros(&carros, &quantidadeCarros); // carregar carros do arquivo atualizado
                exibirCarros(carros, quantidadeCarros);
                break;
            case 3:
                // reservar carro
                carregarCarros(&carros, &quantidadeCarros); // carregar carros do arquivo
                reservarCarro(carros, &quantidadeCarros);
                break;
            case 4:
                // exibir créditos
                exibirCreditos();
                break;
            case 5:
                // sair
                printf("Obrigado por usar o programa!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    // liberar memória alocada para carros
    free(carros);

	return 0;
}
