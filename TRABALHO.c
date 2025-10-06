#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void bubbleSort(char **nomes, int tam);
int main()
{
FILE *arquivo;
char linha[100];
char **nomes = NULL;
int contador = 0;
int capacidade = 100;
int i;
time_t inicio, fim;
nomes = malloc(capacidade * sizeof(char*));
if (!nomes)
{
printf("Sem memoria para alocacao!\n\n");
return 1;
}
arquivo = fopen("nomes.txt", "r");
if (arquivo == NULL)
{
printf("Erro ao abrir o arquivo!\n\n");
free(nomes);
exit(1);
}
while (!feof(arquivo))
{
fgets(linha, sizeof(linha), arquivo);
linha[strcspn(linha, "\n")] = '\0';
printf("Nome lido do arquivo = %s\n", linha);
if (contador >= capacidade)
{
capacidade = capacidade + 10;
nomes = realloc(nomes, capacidade * sizeof(char*));
if (nomes == NULL)
{
printf("Sem memoria para realocacao!\n\n");
fclose(arquivo);
exit(1);
}
}
nomes[contador] = malloc((strlen(linha) + 1) * sizeof(char));
if (nomes[contador] == NULL)
{
printf("Sem memoria para armazenamento de um nome!\n\n");
fclose(arquivo);
return 1;
}
strcpy(nomes[contador], linha);
contador++;
}
fclose(arquivo);
printf("Quantidade de nomes lidos do arquivo = %d\n", contador);
time(&inicio);
bubbleSort(nomes, contador);
time(&fim);
printf("\nApresentando os nomes ordenados\n");
for (i = 0; i < contador; i++)
{
printf("%s\n", nomes[i]);
}
printf("\nTempo de ordenacao = %.6f segundos\n\n", difftime(fim, inicio));
for (i = 0; i < contador; i++)
{
free(nomes[i]);
}
free(nomes);
return 0;
}
void bubbleSort(char **nomes, int tam)
{
int i, j;
char temp[100];
for (i = 0; i < tam-1; i++)
{
for (j = tam - 1; j > i; j--)
{
if (strcmp(nomes[j], nomes[j-1]) < 0)
{
strcpy(temp, nomes[j]);
strcpy(nomes[j], nomes[j-1]);
strcpy(nomes[j-1], temp);
}
}
}
}
