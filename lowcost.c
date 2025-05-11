#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

struct tablies
{
    char carro[15];
    char marca[15];
    char  ano[6];
    char cor[10];
    char referencia[25];
    float preco;
    int quantidade;
};

struct vendas
{
    char carro[15];
    char cor[6];
    char ano[6];
    int quantidade;
    float preco;
    char dataVenda[20];
};

void listarVendas()
{
    FILE *fVendas;
    fVendas = fopen("vendas.dat", "rb");
    if(!fVendas)
    {
        printf("erro ao ler arquivo");
        return;
    }
    struct vendas novaVenda;
    float valorTotal = novaVenda.quantidade * novaVenda.preco;
    while(fread(&novaVenda, sizeof(struct vendas), 1, fVendas))
    {
        printf("---------------------------------------\n");
        printf("Venda realizada com sucesso!\n");
        printf("Carro: %s", novaVenda.carro);
        printf("Ano: %s\n", novaVenda.ano);
        printf("Valor:  %.2f\n", novaVenda.preco); // Formato de valor em reais
        printf("Quantidade vendida: %d unidades\n", novaVenda.quantidade);
        printf("---------------------------------------\n");
        printf("valor total: %f\n", valorTotal);
        printf("---------------------------------------\n\n");
    }
    fclose(fVendas);
}

void registrarVenda()
{
    FILE *fTablies;
    fTablies = fopen("tablies.dat", "rb+");
    if(!fTablies)
    {
        printf("Erro ao abrir arquivo");
        return;
    }

    FILE *fVendas;
    fVendas = fopen("vendas.dat", "ab"); // Abrir em modo append (acrescenta as vendas) não escreve por cima
    if(!fVendas)
    {
        printf("Erro ao abrir arquivo");
        return;
    }

    struct tablies info; //declarando o nome da variavel do tipo struct como info e o nome tablies int/char
    struct vendas novaVenda;
    int encontrado = 0;

    printf("Carro: ");
    fgets(novaVenda.carro, 15, stdin); //fgets lê uma linha inteira

    printf("Ano: ");
    scanf("%s", novaVenda.ano); //scanf lê até o primeiro espaço, uma palavra
    while (getchar() != '\n');

    printf("Cor: ");
    scanf("%s", novaVenda.cor);
    while (getchar() != '\n');

    printf("Valor: ");
    scanf("%f", &novaVenda.preco);
    while (getchar() != '\n');

    printf("Quantos foram vendidos: ");
    if (scanf("%d", &novaVenda.quantidade) != 1) {
    printf("Erro: entrada inválida para quantidade.\n");
    return;
    }

    while(fread(&info, sizeof(struct tablies), 1, fTablies))
    {
        if(strcmp(info.carro, novaVenda.carro) == 0 &&
            strcmp(info.cor, novaVenda.cor) == 0 &&
             strcmp (info.ano, novaVenda.ano) == 0)
        {
            if(info.quantidade >= novaVenda.quantidade) // Verifica se há estoque suficiente
            {
                info.quantidade -= novaVenda.quantidade;
                fseek(fTablies, -sizeof(struct tablies),  SEEK_CUR); // Volta o ponteiro de arquivo para atualizar a entrada
                fwrite(&info, sizeof(struct tablies), 1, fTablies);  // Atualiza o estoque no fTablies
                fwrite(&novaVenda, 1, sizeof(struct vendas), fVendas); // Grava a venda no arquivo fVendas
                encontrado = 1;
            }
            else
            {
                printf("Estoque insuficiente!\n");
            }
            break;
        }
    }

    if(!encontrado)
    {
        printf("Tabelie não encontrado\n");
    }

    FILE *tempFile = fopen("tempo.data", "wb");
    if (!tempFile)
    {
        printf("Erro ao criar arquivo temporario");
        fclose(fTablies);
        fclose(fVendas);
        return;
    }

    rewind(fTablies); //move o cursor para o inicio do arquivo

    while(fread(&info, sizeof(struct tablies), 1, fTablies))
    {
        if(info.quantidade > 0)// Apenas copia carros com estoque disponível
        {
            fwrite(&info, sizeof(struct tablies), 1, tempFile);
        }
    }
    fclose(fTablies);
    fclose(fVendas);
    fclose(tempFile);

    remove("tablies.dat");
    rename("tempo.data", "tablies.dat");

}


void toLowerCase(char *str)//função para transformar em minuscula
{
    while(*str) //enquanto o ponteiro nao for nulo
    {
        *str = tolower(*str); //transforma em minuscula
        str++; //vai para o proximo caractere
    }
}

void inserirEstoqueT()
{
    FILE *fTablies;
    fTablies = fopen("tablies.dat", "rb+"); //verificar se ja existe o arquivo, se existir abre para leitura/escrita
    if (!fTablies) //se nao existir, criar
    {
        fTablies = fopen("tablies.dat", "wb"); //Cria um arquivo binário ou sobrescreve um arquivo binário existente
        fclose(fTablies);
        fTablies = fopen("tablies.dat", "rb+");
    }

    int encontrado = 0; //para verificar se axiste arquivos com os memos dados

    if (fTablies)
    {
    struct tablies info, temp;

    printf("Carro: ");
    fgets(info.carro, 15, stdin); //fgets lê uma linha inteira

    printf("Marca: ");
    fgets(info.marca, 15, stdin);

    printf("Ano: ");
    scanf("%s", info.ano); //scanf lê até o primeiro espaço, uma palavra
    while (getchar() != '\n');

    printf("Cor: ");
    scanf("%s", info.cor);
    while (getchar() != '\n');

    printf("Referência: ");
    fgets(info.referencia, 25, stdin);

    printf("Preço: ");
    scanf("%f", &info.preco);
    while (getchar() != '\n');

    printf("Quantidade: ");
    scanf("%d", &info.quantidade);
    while (getchar() != '\n');

    while(fread(&temp, sizeof(struct tablies), 1, fTablies)) //le os dados do tablies.dat e armazenando em temp
    {
        if(!strcmp(temp.carro, info.carro) &&
            !strcmp(temp.marca, info.marca)&&
            !strcmp(temp.cor, info.cor)&&
            !strcmp(temp.ano, info.ano)) //!strcmp == 0 sera igual, 0= falso
        {
            temp.quantidade += info.quantidade;
            fseek(fTablies, -sizeof(struct tablies),  SEEK_CUR);
            fwrite(&temp, sizeof(struct tablies), 1, fTablies);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) //Se encontrado == 0, então !encontrado == 1 (Verdadeiro)
    {
        fseek(fTablies, 0, SEEK_END); //posicionando o cursor no final do arquivo
        fwrite(&info, 1, sizeof(struct tablies), fTablies); //escreve no arquivo
    }
    fclose(fTablies);
    printf("\n\nRegisto Inserido com sucesso!\n\n");
    }

}
void listarEstoqueT()
{
    FILE *fTablies;
    fTablies = fopen("tablies.dat", "rb");
    if (fTablies)
    {
        struct tablies info;
        while (fread(&info, sizeof(struct tablies), 1, fTablies)) // le o arquivo
        {
            printf("---------------------------------------\n");
            printf("Carro: %s", info.carro);
            printf("Marca: %s", info.marca);
            printf("Ano: %s\n", info.ano);
            printf("Cor: %s\n", info.cor);
            printf("Referência: %s", info.referencia);
            printf("Preço: %.2f\n\n", info.preco);
            printf("Quantidade: %d\n", info.quantidade);
            printf("---------------------------------------\n");
        }
        fclose(fTablies);
    }
}
void removerEstoqueT()
{
    FILE *fTablies, * fTemp;
    struct tablies temp;
    char carroRemover[15];
    char corRemover[10];
    char anoRemover[6];
    int encontrado = 0;

    fTablies = fopen("tablies.dat", "rb");
    if(!fTablies)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }

    fTemp = fopen("temp.dat", "wb");
    if(!fTemp)
    {
        printf("erro ao criar arquivo temporario\n");
        fclose(fTablies);
        return;
    }
    printf("O TABELIE de qual carro desejas remover de estoque?\n carro:");
    fgets(carroRemover, 15, stdin); //fgets lê uma linha inteira
    carroRemover[strcspn(carroRemover, "\n")] = 0; // Remove o '\n'

    printf("Cor: \n");
    fgets(corRemover,10, stdin);
    corRemover[strcspn(corRemover, "\n")] = 0;

    printf("Ano: \n");
    fgets(anoRemover, 6, stdin);
    anoRemover[strcspn(anoRemover, "\n")] = 0;

    while (fread(&temp, sizeof(struct tablies), 1, fTablies))
    {
        toLowerCase(carroRemover);//transforma em minuscula para comparar
        toLowerCase(corRemover);
        toLowerCase(anoRemover);

        toLowerCase(temp.carro);
        toLowerCase(temp.cor);
        toLowerCase(temp.ano);

        if(strcmp(temp.carro, carroRemover) != 0 &&
           strcmp(temp.cor, corRemover) != 0&&
           strcmp(temp.ano, anoRemover)!= 0) //caso nao encontre o arquivo é escrito na temporaria normalmente e nao sofre mudanças
        {
            fwrite(&temp, sizeof(struct tablies), 1, fTemp);
        }
        else encontrado = 1; //caso encontre o carro ele é marcado com 1 e depois entrara no if(encontrado) para remoção
    }
    fclose(fTablies);
    fclose(fTemp);
    if(encontrado)
    {
        remove("tablies.dat"); //apaga original que encontrou o arquivo igual,a pagando o arquivo escolhido
        rename("temp.dat", "tablies.dat"); //renomeia o arquivo temporario para o original sem o arquivo removida
    }
    else
    {
        remove("temp.dat");  // Caso não encontre, descarta o arquivo temporário
        printf("Tablie não encontrado no estoque.\n");
    }
}
void pesquisarEstoqueT()
{
    FILE *fTablies;
    fTablies = fopen("tablies.dat", "rb");
    if (!fTablies)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    struct tablies info;
    char carroPesquisa[15];
    char carroLower[15]; // Para comparar sem mexer no original
    int encontrado = 0;


    printf("Carro: ");
    fgets(carroPesquisa, 15, stdin);
    carroPesquisa[strcspn(carroPesquisa, "\n")] = 0; // Remove o '\n' ao final da string
    toLowerCase(carroPesquisa); // Transforma em minúscula para comparar

    printf("Carro pesquisado: '%s'\n", carroPesquisa);  // Exibe o carro pesquisado

    while (fread(&info, sizeof(struct tablies), 1, fTablies))
    {
        // Transforma o carro do arquivo em minúscula para comparação
        strcpy(carroLower, info.carro); // Copia o carro para carroLower
        carroLower[strcspn(carroLower, "\n")] = 0; // Remove o '\n' do final do nome do carro
        toLowerCase(carroLower); // Transforma em minúscula

        int len = strlen(carroLower);
        if (len > 0 && carroLower[len - 1] == ' ') {
            carroLower[len - 1] = '\0'; // Remove o espaço extra no final
        }

        if (strcmp(carroLower, carroPesquisa) == 0) // Comparação entre o carro pesquisado e o carro do arquivo
        {
            printf("---------------------------------------\n");
            printf("Carro: %s", info.carro);  // Exibe o carro encontrado
            printf("Marca: %s", info.marca);
            printf("Ano: %s\n", info.ano);
            printf("Cor: %s\n", info.cor);
            printf("Referência: %s", info.referencia);
            printf("Preço: %.2f\n", info.preco);
            printf("Quantidade: %d\n", info.quantidade);
            printf("---------------------------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Tablie não encontrado no estoque.\n");
    }

    fclose(fTablies);
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao = 0;

    while (opcao != 3)
    {
        printf("Bem-vindo!\n");
        printf("1. Estoque de tabelies\n");
        printf("2. Registo de Vendas\n");
        printf("3. Sair\n");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        int menuTab = 0;
        if (opcao == 1)
        {
            printf("Menu TABLIES\n");
            printf("1. Inserir tablies em estoque\n");
            printf("2. Listar tablies em estoque\n");
            printf("3. Pesquisar tablies em estoque\n");
            printf("4. Excluir tablies em estoque\n");
            printf("5. Voltar\n");
            scanf("%d", &menuTab);
            while (getchar() != '\n');

            if (menuTab == 1) inserirEstoqueT();
            if (menuTab == 2) listarEstoqueT();
            if (menuTab == 3) pesquisarEstoqueT();
            if (menuTab == 4) removerEstoqueT();
            if (menuTab == 5) opcao = 0;
        }
        int menuVenda = 0;
        if (opcao == 2)
        {
            printf("Menu VENDAS\n");
            printf("1. Registrar Venda\n");
            printf("2. Listar Vendas\n");
            printf("3. Voltar\n");
            scanf("%d", &menuVenda);
            while (getchar() != '\n');

            if(menuVenda == 1) registrarVenda();
            if(menuVenda == 2) listarVendas();
            if(menuVenda == 3) opcao = 0;
        }

    }
    printf("Até logo!\n");
    return 0;
}
