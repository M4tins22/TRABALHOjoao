#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void bubbleSort(char **nomes, int tam);

int main() {
    FILE *arquivo, *log;
    char linha[100];
    char **nomes = NULL;
    int contador = 0;
    int capacidade = 100;
    int i;
    time_t inicio, fim;
    double diferenca;
    struct tm *tempoInicial, *tempoFinal;

    // Inicio do sistema de logging
    printf("Gerando um arquivo de log...\n");
    log = fopen("logs.txt", "wt");
    if (log == NULL) {
        printf("Arquivo de logs nao foi criado!\n");
        exit(1);
    }

    fprintf(log, "Logs de Operacoes do Sistema - Ordenacao de Nomes\n");
    fprintf(log, "=================================================\n\n");

    // Captura tempo inicial total
    inicio = time(NULL);
    tempoInicial = localtime(&inicio);
    printf("Inicio do processo = %s", asctime(tempoInicial));
    fprintf(log, "Inicio do processo = %s", asctime(tempoInicial));

    // Alocacao inicial do array de ponteiros
    nomes = malloc(capacidade * sizeof(char*));
    if (!nomes) {
        printf("Sem memoria para alocacao!\n\n");
        fprintf(log, "ERRO: Sem memoria para alocacao inicial!\n");
        fclose(log);
        return 1;
    }

    // Abertura do arquivo de nomes
    arquivo = fopen("nomes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n\n");
        fprintf(log, "ERRO: Nao foi possivel abrir o arquivo 'nomes.txt'\n");
        free(nomes);
        fclose(log);
        exit(1);
    }

    fprintf(log, "Iniciando leitura do arquivo 'nomes.txt'\n");

    // Leitura dos nomes do arquivo
    while (!feof(arquivo)) {
        fgets(linha, sizeof(linha), arquivo);
        linha[strcspn(linha, "\n")] = '\0';  // Remove quebra de linha

        if (strlen(linha) > 0) {  // Ignora linhas vazias
            printf("Nome lido do arquivo = %s\n", linha);

            // Realocacao se necessario
            if (contador >= capacidade) {
                capacidade = capacidade + 10;
                nomes = realloc(nomes, capacidade * sizeof(char*));
                if (nomes == NULL) {
                    printf("Sem memoria para realocacao!\n\n");
                    fprintf(log, "ERRO: Sem memoria para realocacao!\n");
                    fclose(arquivo);
                    fclose(log);
                    exit(1);
                }
            }

            // Alocacao de memoria para cada nome
            nomes[contador] = malloc((strlen(linha) + 1) * sizeof(char));
            if (nomes[contador] == NULL) {
                printf("Sem memoria para armazenamento de um nome!\n\n");
                fprintf(log, "ERRO: Sem memoria para armazenar o nome: %s\n", linha);
                fclose(arquivo);
                fclose(log);
                return 1;
            }
            strcpy(nomes[contador], linha);
            contador++;
        }
    }
    fclose(arquivo);

    printf("Quantidade de nomes lidos do arquivo = %d\n", contador);
    fprintf(log, "Quantidade de nomes lidos do arquivo = %d\n", contador);

    // Ordenacao com medicao de tempo
    time_t inicio_ordenacao, fim_ordenacao;
    time(&inicio_ordenacao);
    bubbleSort(nomes, contador);
    time(&fim_ordenacao);

    double tempo_ordenacao = difftime(fim_ordenacao, inicio_ordenacao);

    // Apresentacao dos resultados
    printf("\nApresentando os nomes ordenados\n");
    fprintf(log, "\nNomes ordenados:\n");
    for (i = 0; i < contador; i++) {
        printf("%s\n", nomes[i]);
        fprintf(log, "%s\n", nomes[i]);
    }

    printf("\nTempo de ordenacao = %.6f segundos\n", tempo_ordenacao);
    fprintf(log, "\nTempo de ordenacao = %.6f segundos\n", tempo_ordenacao);

    // Captura tempo final total
    fim = time(NULL);
    tempoFinal = localtime(&fim);
    diferenca = difftime(fim, inicio);

    printf("Tempo total de execucao = %.6f segundos\n", diferenca);
    printf("Fim do processo = %s", asctime(tempoFinal));

    fprintf(log, "Tempo total de execucao = %.6f segundos\n", diferenca);
    fprintf(log, "Fim do processo = %s", asctime(tempoFinal));
    fprintf(log, "=================================================\n\n");

    // Liberacao de memoria
    for (i = 0; i < contador; i++) {
        free(nomes[i]);
    }
    free(nomes);

    fclose(log);
    return 0;
}

void bubbleSort(char **nomes, int tam) {
    int i, j;
    char temp[100];

    for (i = 0; i < tam-1; i++) {
        for (j = tam - 1; j > i; j--) {
            if (strcmp(nomes[j], nomes[j-1]) < 0) {
                strcpy(temp, nomes[j]);
                strcpy(nomes[j], nomes[j-1]);
                strcpy(nomes[j-1], temp);
            }
        }
    }
}
