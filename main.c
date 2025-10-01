#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 101
#define MAX_LINE_SIZE 1024

typedef enum {
    CEREAIS_DERIVADOS,
    FRUTAS,
    VERDURAS_HORTALICAS,
    CARNES,
    LATICINIOS,
    LEGUMINOSAS,
    OUTROS,
} Categoria;

typedef struct {
    int numero;
    char descricao[256];
    float umidade;
    int energia;
    float proteina;
    float carboidrato;
    Categoria categoria;
} Alimento;

Alimento alimentos[MAX_LINES];

// protótipos das funções da lorena
void listar_topN_energia(const Alimento vet[], int tamanho);
void listar_topN_proteina(const Alimento vet[], int tamanho);
void listar_topN_carboidrato(const Alimento vet[], int tamanho);

Categoria categoria_from_string(const char *str) {
    if (strcmp(str, "Cereais e derivados") == 0)
        return CEREAIS_DERIVADOS;
    if (strcmp(str, "Frutas") == 0)
        return FRUTAS;
    if (strcmp(str, "Verduras e hortaliças") == 0)
        return VERDURAS_HORTALICAS;
    if (strcmp(str, "Carnes e derivados") == 0)
        return CARNES;
    if (strcmp(str, "Leite e derivados") == 0)
        return LATICINIOS;
    if (strcmp(str, "Leguminosas e derivados") == 0)
        return LEGUMINOSAS;
    return OUTROS;
}

// Realiza o parsing de cada linha do arquivo
Alimento parse_csv_line(char *line) {
    line[strcspn(line, "\n")] = '\0';

    char *token;
    int field = 0;
    Alimento a;

    token = strtok(line, ";");
    while (token != NULL) {
        switch (field) {
        case 0:
            a.numero = atoi(token);
            break;
        case 1: {
            // Verifica se começa com aspas. Se sim, pula o primeiro caractere
            // ("), e transforma o último (") em um terminator character.
            if (token[0] == '"') {
                token++;
                token[strlen(token) - 1] = '\0';
            }
            // Se o token for igual o tamanho do buffer aqui, strncpy não iria
            // adicionar o terminator character. Por isso, passamos sizeof - 1 e
            // depois fazemos append manual do '\0'.
            strncpy(a.descricao, token, sizeof(a.descricao) - 1);
            a.descricao[sizeof(a.descricao) - 1] = '\0';
            break;
        }
        case 2:
            a.umidade = atof(token);
            break;
        case 3:
            a.energia = atoi(token);
            break;
        case 4:
            a.proteina = atof(token);
            break;
        case 5:
            a.carboidrato = atof(token);
            break;
        case 6:
            a.categoria = categoria_from_string(token);
            break;
        }
        field++;
        token = strtok(NULL, ";");
    }
    return a;
}

// lorena: converte enum Categoria em string para print
const char* categoria_nome(Categoria c) {
    switch (c) {
        case CEREAIS_DERIVADOS:   return "Cereais e derivados";
        case FRUTAS:              return "Frutas";
        case VERDURAS_HORTALICAS: return "Verduras e hortaliças";
        case CARNES:              return "Carnes e derivados";
        case LATICINIOS:          return "Leite e derivados";
        case LEGUMINOSAS:         return "Leguminosas e derivados";
        default:                  return "Outros";
    }
}

int menu() {
    printf("                                        \n");
    printf(
        "===================MENU==========================================\n");
    printf("                                        \n");
    printf("1. LISTAR TODAS AS CATEGORIAS DE ALIMENTO.\n");
    printf("2. *******\n");
    printf("3. ********\n");
    printf("4. *********\n");
    printf("5. *********\n");
    printf("6. *********\n");
    printf("7. *********\n");
    printf("8. *********\n");
    printf("9. *********\n");
    printf(
        "------------------------------------------------------------------\n");

    char selection[100];
    printf("Digite o número da opção desejada:");
    scanf(" %99s", selection);
    printf("-------------------------------------\n");

    if (strlen(selection) > 1) {
        printf("= Você digitou mais de um caractere! Digite apenas um.\n");
        return 0;
    }

    else if (!isdigit(selection[0])) {
        printf("= Entrada Inválida! Tente novamente!\n");
        return 0;
    } else {
        switch (selection[0]) {
        case '1':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '2':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '3':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '4':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '5':
            listar_topN_energia(alimentos, MAX_LINES); // lorena: função e
            break;
        case '6':
            listar_topN_proteina(alimentos, MAX_LINES); // lorena: função f
            break;
        case '7':
           listar_topN_carboidrato(alimentos, MAX_LINES); // lorena: função g
            break;
        case '8':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '9':
            printf("Apague esse printf e coloque sua função\n");
            break;
        default:
            printf("Opção inválida! Digite uma opção válida");
        }
    }
    return 0;
}

// Função auxiliar que realiza o print do nosso vetor de structs (alimentos)
void print_tabela(int line_count) {
    for (int i = 0; i < line_count; i++) {
        printf("%d | %s | %.1f | %d | %.1f | %.1f | %s\n", alimentos[i].numero,
               alimentos[i].descricao, alimentos[i].umidade,
               alimentos[i].energia, alimentos[i].proteina,
               alimentos[i].carboidrato, categoria_nome(alimentos[i].categoria)); // lorena: usei a função categoria_nome para printar o nome
    }
}

// Retorna a quantidade de elementos que o vetor, depois de filtrado com base em
// uma categoria, terá
int tamanho_vetor_filtrado(Alimento vet[], int tamanho_vet,
                           const char *categoria_escolhida) {
    int count = 0;
    for (int i = 0; i < tamanho_vet; i++) {
        if (strcmp(categoria_nome(vet[i].categoria), categoria_escolhida) == 0) { // lorena: categoria_nome para sair em string
            count++;
        }
    }

    return count;
}

int main() {
    FILE *arquivo = fopen("alimentos.csv", "r");
    if (!arquivo) {
        perror("Erro ao tentar abrir arquivo csv.");
        return 1;
    }

    char line[MAX_LINE_SIZE];
    int line_count = 0;

    // lê e descarta a primeira linha do arquivo (header)
    fgets(line, sizeof(line), arquivo);

    while (fgets(line, sizeof(line), arquivo) && line_count < MAX_LINES) {
        alimentos[line_count] = parse_csv_line(line);
        line_count++;
    }

    fclose(arquivo);
    print_tabela(line_count);

    return 0;
}