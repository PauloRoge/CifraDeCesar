#include <stdio.h>  //Entrada e saída padrão.
#include <stdlib.h> //Necessário para função system.
#include <string.h> //Necessário para armazenar um texto em variável.
#include <locale.h> //Para o uso de acentos.

#define MAX_SIZE 100

//ESTRUTURAS
enum TipoChar { NUMERO, MAIUSCULO, MINUSCULO, ESPECIAL }; //Especifica o tipo de caractere.
enum Operacao { DESCRIPTOGRAFAR, CRIPTOGRAFAR };

//PROTÓTIPOS
int RetornaTipoChar(unsigned char caracter); //Retorna o tipo do caracter fornecido. 
void CifrarMensagem(char* mensagem, int chave, int criptografar); //Percorre o vetor de caracteres da mensagem e atualiza os valores dos caracteres.
int ProcessarArquivos(char* nomeArquivoEntrada, char* nomeArquivoSaida, int chave, int criptografia); //Salva mensagem criptografada em um arquivo.

int main() {
    setlocale(LC_ALL, "portuguese"); //para fazer uso de acento e letras especiais

    char nomeArquivoSaida[MAX_SIZE]; //Declara um variável para armazenar o nome do arquivo de saída.
    int escolha = 1; //Armazena a opção do menu.
    int operacao = 0; //Armazena inteiro usado como decisão de codificar ou decodificar.
    int chave = 0; //Armazena o número de casas que todas as letras do alfabeto devem se deslocar.

    do
    {
        system("cls"); //limpar a tela do console no ambiente Windows.

        if (escolha != 1 && escolha != 2) //Condição para imprimir um aviso de entrada inválida.
            printf("Opção inválida. Por favor, escolha 1 para criptografar ou 2 para descriptografar.\n\n");

        printf("Escolha uma opção:\n");
        printf("1 - Criptografar\n");
        printf("2 - Descriptografar\n");
        scanf("%d", &escolha);

    } while (escolha != 1 && escolha != 2); //Repete o loop enquanto a entrada não for válida.

    (escolha == 1) ? (operacao = CRIPTOGRAFAR) : (operacao = DESCRIPTOGRAFAR); //Atribui uma operação a cada escolha.

    system("cls");

    printf("Escolha uma opção:\n");
    printf("1 - %s texto de um arquivo .txt\n", (operacao) ? "Criptografar" : "Descriptograr");
    printf("2 - Ler do teclado e salvar em um arquivo .txt\n");

    do
    {
        scanf("%d", &escolha);
    } while (escolha != 1 && escolha != 2);

    if (escolha == 2) {

        char mensagem[MAX_SIZE]; //Declara variável para armazenar mensagem.

        system("cls");

        printf("%s > Ler do teclado e salvar em um arquivo.\n\n", (operacao) ? "Criptografar" : "Descriptograr");

        printf("Digite a chave (um número inteiro): ");
        scanf("%d", &chave);
        getchar(); // pegar o caractere de nova linha pendente do scanf anterior

        system("cls");
        printf("Digite a mensagem:\n");
        fgets(mensagem, sizeof(mensagem), stdin);


        printf("Digite o nome do arquivo de saída: ");
        scanf("%s", nomeArquivoSaida);
        strcat(nomeArquivoSaida, ".txt"); //função para concatenar string lida do teclado com o tipo de arquivo.

        FILE* arquivoSaida = fopen(nomeArquivoSaida, "w"); //Abre o arquivo
        if (arquivoSaida == NULL) {
            printf("Não foi possível criar o arquivo de saída.\n");
            return 1;
        }

        CifrarMensagem(mensagem, chave, operacao); // Criptografar a mensagem

        fprintf(arquivoSaida, "%s", mensagem);// grava a mensagem criptografada no arquivo.txt

        fclose(arquivoSaida); //Fecha o arquivo após salvar a mensagem.
        printf("Texto criptografado e salvo com sucesso no arquivo de saída.\n");
        return 0;
    }

    system("cls");
    printf("%s > Ler do arquivo.\n\n", (operacao) ? "Criptografar" : "Descriptograr");
    printf("Digite a chave (um número inteiro): ");
    scanf("%d", &chave);

    char nomeArquivoEntrada[MAX_SIZE];
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArquivoEntrada);
    strcat(nomeArquivoEntrada, ".txt");

    printf("Digite o nome do arquivo de saída que será criado: ");
    scanf("%s", nomeArquivoSaida);
    strcat(nomeArquivoSaida, ".txt");

    return ProcessarArquivos(nomeArquivoEntrada, nomeArquivoSaida, chave, operacao); //Caso não seja possível criar ou abrir arquivo retorna 1.
}

int RetornaTipoChar(unsigned char caracter) {
    if (caracter >= '0' && caracter <= '9')
        return NUMERO;
    else if (caracter >= 'A' && caracter <= 'Z')
        return MAIUSCULO;
    else if (caracter >= 'a' && caracter <= 'z')
        return MINUSCULO;

    return ESPECIAL;
}

//criptografar ou descriptografar uma mensagem
void CifrarMensagem(char* mensagem, int chave, int criptografar) {
    int tamanhoDaMensagem = strlen(mensagem);

    for (int i = 0; i < tamanhoDaMensagem; i++) {

        if (RetornaTipoChar(mensagem[i]) == MAIUSCULO) {
            if (criptografar) {
                mensagem[i] = ((mensagem[i] - 'A' + chave) % 26) + 'A';
            }
            else {
                mensagem[i] = ((mensagem[i] - 'A' - chave + 26) % 26) + 'A';
            }
        }
        else if (RetornaTipoChar(mensagem[i]) == MINUSCULO) {
            if (criptografar) {
                mensagem[i] = ((mensagem[i] - 'a' + chave) % 26) + 'a';
            }
            else {
                mensagem[i] = ((mensagem[i] - 'a' - chave + 26) % 26) + 'a';
            }
        }
        else if (RetornaTipoChar(mensagem[i]) == NUMERO) {
            if (criptografar) {
                mensagem[i] = ((mensagem[i] - '0' + chave) % 10) + '0';
            }
            else {
                mensagem[i] = ((mensagem[i] - '0' - chave) % 10) + '0';
            }
        }
    }
}

int ProcessarArquivos(char* nomeArquivoEntrada, char* nomeArquivoSaida, int chave, int criptografia) {
    FILE* arquivoEntrada = fopen(nomeArquivoEntrada, "r");
    if (arquivoEntrada == NULL) {
        printf("Não foi possível abrir o arquivo de entrada.\n");
        return 1;
    }

    FILE* arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL) {
        printf("Não foi possível criar o arquivo de saída.\n");
        fclose(arquivoEntrada);
        return 1;
    }

    char linha[1000]; // Usada para armazenar temporariamente as linhas lidas de um arquivo
    while (fgets(linha, sizeof(linha), arquivoEntrada)) {
        CifrarMensagem(linha, chave, criptografia);
        fprintf(arquivoSaida, "%s", linha);
    }

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Operação concluída com sucesso.\n");
    return 0;
}