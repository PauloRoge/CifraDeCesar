#include <stdio.h>  //Entrada e sa�da padr�o.
#include <stdlib.h> //Necess�rio para fun��o system.
#include <string.h> //Necess�rio para armazenar um texto em vari�vel.
#include <locale.h> //Para o uso de acentos.

#define MAX_SIZE 100

//ESTRUTURAS
enum TipoChar { NUMERO, MAIUSCULO, MINUSCULO, ESPECIAL }; //Especifica o tipo de caractere.
enum Operacao { DESCRIPTOGRAFAR, CRIPTOGRAFAR };

//PROT�TIPOS
int RetornaTipoChar(unsigned char caracter); //Retorna o tipo do caracter fornecido. 
void CifrarMensagem(char* mensagem, int chave, int criptografar); //Percorre o vetor de caracteres da mensagem e atualiza os valores dos caracteres.
int ProcessarArquivos(char* nomeArquivoEntrada, char* nomeArquivoSaida, int chave, int criptografia); //Salva mensagem criptografada em um arquivo.

int main() {
    setlocale(LC_ALL, "portuguese"); //para fazer uso de acento e letras especiais

    char nomeArquivoSaida[MAX_SIZE]; //Declara um vari�vel para armazenar o nome do arquivo de sa�da.
    int escolha = 1; //Armazena a op��o do menu.
    int operacao = 0; //Armazena inteiro usado como decis�o de codificar ou decodificar.
    int chave = 0; //Armazena o n�mero de casas que todas as letras do alfabeto devem se deslocar.

    do
    {
        system("cls"); //limpar a tela do console no ambiente Windows.

        if (escolha != 1 && escolha != 2) //Condi��o para imprimir um aviso de entrada inv�lida.
            printf("Op��o inv�lida. Por favor, escolha 1 para criptografar ou 2 para descriptografar.\n\n");

        printf("Escolha uma op��o:\n");
        printf("1 - Criptografar\n");
        printf("2 - Descriptografar\n");
        scanf("%d", &escolha);

    } while (escolha != 1 && escolha != 2); //Repete o loop enquanto a entrada n�o for v�lida.

    (escolha == 1) ? (operacao = CRIPTOGRAFAR) : (operacao = DESCRIPTOGRAFAR); //Atribui uma opera��o a cada escolha.

    system("cls");

    printf("Escolha uma op��o:\n");
    printf("1 - %s texto de um arquivo .txt\n", (operacao) ? "Criptografar" : "Descriptograr");
    printf("2 - Ler do teclado e salvar em um arquivo .txt\n");

    do
    {
        scanf("%d", &escolha);
    } while (escolha != 1 && escolha != 2);

    if (escolha == 2) {

        char mensagem[MAX_SIZE]; //Declara vari�vel para armazenar mensagem.

        system("cls");

        printf("%s > Ler do teclado e salvar em um arquivo.\n\n", (operacao) ? "Criptografar" : "Descriptograr");

        printf("Digite a chave (um n�mero inteiro): ");
        scanf("%d", &chave);
        getchar(); // pegar o caractere de nova linha pendente do scanf anterior

        system("cls");
        printf("Digite a mensagem:\n");
        fgets(mensagem, sizeof(mensagem), stdin);


        printf("Digite o nome do arquivo de sa�da: ");
        scanf("%s", nomeArquivoSaida);
        strcat(nomeArquivoSaida, ".txt"); //fun��o para concatenar string lida do teclado com o tipo de arquivo.

        FILE* arquivoSaida = fopen(nomeArquivoSaida, "w"); //Abre o arquivo
        if (arquivoSaida == NULL) {
            printf("N�o foi poss�vel criar o arquivo de sa�da.\n");
            return 1;
        }

        CifrarMensagem(mensagem, chave, operacao); // Criptografar a mensagem

        fprintf(arquivoSaida, "%s", mensagem);// grava a mensagem criptografada no arquivo.txt

        fclose(arquivoSaida); //Fecha o arquivo ap�s salvar a mensagem.
        printf("Texto criptografado e salvo com sucesso no arquivo de sa�da.\n");
        return 0;
    }

    system("cls");
    printf("%s > Ler do arquivo.\n\n", (operacao) ? "Criptografar" : "Descriptograr");
    printf("Digite a chave (um n�mero inteiro): ");
    scanf("%d", &chave);

    char nomeArquivoEntrada[MAX_SIZE];
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArquivoEntrada);
    strcat(nomeArquivoEntrada, ".txt");

    printf("Digite o nome do arquivo de sa�da que ser� criado: ");
    scanf("%s", nomeArquivoSaida);
    strcat(nomeArquivoSaida, ".txt");

    return ProcessarArquivos(nomeArquivoEntrada, nomeArquivoSaida, chave, operacao); //Caso n�o seja poss�vel criar ou abrir arquivo retorna 1.
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
        printf("N�o foi poss�vel abrir o arquivo de entrada.\n");
        return 1;
    }

    FILE* arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL) {
        printf("N�o foi poss�vel criar o arquivo de sa�da.\n");
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

    printf("Opera��o conclu�da com sucesso.\n");
    return 0;
}