/*
                              ->Fundamentos de Programa��o<-
.Prot�tipo de uma aplica��o que permita efetuar a gest�o da situa��o curricular dos estudantes do curso TeSP
.Programadores:
            Manuel Lopes  <2231647@my.ipleiria.pt>
            Diogo Godinho <2231665@my.ipleiria.pt>
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXIMO_ESTUDANTES 150
#define UNIDADES_CURRICULARES 18
#define AVALIACOES 5000

typedef struct
{
    int id_estudante;
    int numero_estudante;
    char nome_estudante[30];
    int codigo_curso;
    char email[30];
} t_estudante;

typedef struct
{
    int id_uc;
    int codigo_uc;
    char nome_uc[70];
    int ano_curricular;
    int semestre;
    int ects;
} t_unidade_curricular;

typedef struct
{
    int id_estudante;
    int id_uc;
    int id_avaliacao;
    char ano_letivo[15];
    char epoca[10];
    char data[15];
    int classificacao_final;
} t_avaliacao;

// Prot�tipos das fun��es

//Ler dados de Input

int ler_numero_inteiro_intervalo(int minimo, int maximo, char mensagem[]);
void ler_string(char string[], char mensagem[]);
int registar_estudantes(t_estudante vetor_alunos[], int total_alunos);
int registar_unidades_curricular(t_unidade_curricular vetor_uc[], int total_uc);
int registar_avaliacoes(t_avaliacao vetor_avaliacoes[], int total_avalicoes, int id_estudante, int id_uc);

//Mostrar output

void mostrar_dados_de_um_estudantes(t_estudante vetor_alunos[], int total_alunos, int numero_estudante);
void mostrar_todos_os_estudantes(t_estudante vetor_alunos[], int total_alunos);
void mostrar_dados_unidades_curriculares(t_unidade_curricular vetor_uc[], int total_uc);
void mostrar_dados_avaliacoes(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, int id_estudante, int id_uc);

//Menus

char menu_opcoes(void);
char menu_mostrar_dados_estudantes(void);
char menu_estatisticas(void);
char confirmar_saida_programa(void);
char confirmar_saida_para_menu(void);

//Outras fun��es

int validar_entrada_avaliacoes(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, int id_uc, int id_estudante);
int procurar_estudante(t_estudante vetor_alunos[], int total_alunos);
int verificar_numero_existente(t_estudante vetor_alunos[], int total_alunos, int num_estudante);
int procurar_id_estudante(t_estudante vetor_alunos[], int total_alunos, int num_estudante);
int procurar_id_uc(t_unidade_curricular vetor_uc[], int total_uc, int codigo_uc);
void aguarda_entrada_usuario(void);

//Estatisticas

void total_ects_aprovados(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, t_unidade_curricular vetor_uc[]);
void media_aritmetica(t_avaliacao vetor_avaliacoes[], int total_avaliacoes);
void percentagem_ects_por_semestre(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, t_unidade_curricular vetor_uc[]);
void mostrar_percentagem_ects_por_semestre(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, t_unidade_curricular vetor_uc[], int id, int total_ects_aprovados_semestre1, int total_ects_aprovados_semestre2, int total_ects_possiveis_semestre1, int total_ects_possiveis_semestre2);

//Ficheiros

void gravar_dados_ficheiro_estudantes(t_estudante vetor_alunos[], int total_alunos);
void gravar_dados_ficheiro_uc(t_unidade_curricular vetor_uc[], int total_uc);
void gravar_dados_ficheiro_avaliacao(t_avaliacao vetor_avaliacoes[], int total_avaliacoes);
int ler_dados_ficheiro_estudantes(t_estudante vetor_alunos[]);
int ler_dados_ficheiro_uc(t_unidade_curricular vetor_uc[]);
int ler_dados_ficheiro_avaliacao(t_avaliacao vetor_avaliacoes[]);


// Fun��o principal

int main()
{
    t_estudante vetor_alunos[MAXIMO_ESTUDANTES];
    t_unidade_curricular vetor_uc[UNIDADES_CURRICULARES];
    t_avaliacao vetor_avaliacoes[AVALIACOES];
    char opcao_saida, opcao_saida_estatisticas, opcao_saida_consultar_estudantes;
    int total_alunos = 0, total_uc = 0, total_avaliacoes = 0, id_estudante = 0, id_uc = 0, numero_estudante, codigo_unidade_curricular;

    do
    {
        system("cls");
        switch (menu_opcoes())
        {
        case 'A':
            total_alunos = registar_estudantes(vetor_alunos, total_alunos);
            break;

        case 'B':
            do
            {
                system("cls");
                switch(menu_mostrar_dados_estudantes())
                {
                case 'A':
                    numero_estudante = ler_numero_inteiro_intervalo(2230000, 2239999, "Qual o numero de estudante: ");
                    mostrar_dados_de_um_estudantes(vetor_alunos, total_alunos, numero_estudante);
                    break;

                case 'B':
                    mostrar_todos_os_estudantes(vetor_alunos, total_alunos);
                    break;

                case 'S':
                    opcao_saida_consultar_estudantes = confirmar_saida_para_menu();
                    break;

                default:
                    printf("Opcao invalida. Tente novamente.\n");
                }
            }
            while(opcao_saida_consultar_estudantes != 'S');
            break;

        case 'C':
            total_uc = registar_unidades_curricular(vetor_uc, total_uc);
            break;

        case 'D':
            mostrar_dados_unidades_curriculares(vetor_uc, total_uc);
            break;

        case 'E':
            numero_estudante = ler_numero_inteiro_intervalo(2230000, 2239999, "Qual o numero de estudante: ");
            id_estudante = procurar_id_estudante(vetor_alunos, total_alunos, numero_estudante);
            codigo_unidade_curricular = ler_numero_inteiro_intervalo(4515101, 4515118, "Codigo da UC: ");
            id_uc = procurar_id_uc(vetor_uc, total_uc, codigo_unidade_curricular);

            if(id_estudante != 0 && id_uc != 0)
            {
                total_avaliacoes = registar_avaliacoes(vetor_avaliacoes, total_avaliacoes, id_uc, id_estudante);
            }
            else if(id_uc == 0 && id_estudante == 0)
            {
                printf("\nNenhuma unidade curricular e numero de estudante foi encontrada.");
                printf("\nPor favor registe uma unidade curricular e um numero de estudante.");
                aguarda_entrada_usuario();
            }
            else if(id_estudante == 0)
            {
                printf("\nO numero de estudante inserido nao se encontra registado.");
                aguarda_entrada_usuario();
            }
            else
            {
                printf("A unidade curricular inserida nao se encontra registada");
                aguarda_entrada_usuario();
            }
            break;

        case 'F':
            mostrar_dados_avaliacoes(vetor_avaliacoes, total_avaliacoes, id_estudante, id_uc);
            break;

        case 'G':
            do
            {
                system("cls");
                switch(menu_estatisticas())
                {
                case 'A':
                    total_ects_aprovados(vetor_avaliacoes, total_avaliacoes, vetor_uc);
                    aguarda_entrada_usuario();
                    break;

                case 'B':
                    media_aritmetica(vetor_avaliacoes, total_avaliacoes);
                    aguarda_entrada_usuario();
                    break;

                case 'C':
                    percentagem_ects_por_semestre(vetor_avaliacoes, total_avaliacoes, vetor_uc);
                    aguarda_entrada_usuario();
                    break;

                case 'S':
                    opcao_saida_estatisticas = confirmar_saida_para_menu();
                    break;

                default:
                    printf("Opcao invalida. Tente novamente.\n");
                }
            }
            while(opcao_saida_estatisticas != 'S');
            break;

        case 'H':
            gravar_dados_ficheiro_estudantes(vetor_alunos, total_alunos);
            gravar_dados_ficheiro_uc(vetor_uc, total_uc);
            gravar_dados_ficheiro_avaliacao(vetor_avaliacoes, total_avaliacoes);
            aguarda_entrada_usuario();
            break;

        case 'I':
            total_alunos = ler_dados_ficheiro_estudantes(vetor_alunos);
            total_uc = ler_dados_ficheiro_uc(vetor_uc);
            total_avaliacoes = ler_dados_ficheiro_avaliacao(vetor_avaliacoes);
            aguarda_entrada_usuario();
            break;

        case 'S':
            opcao_saida = confirmar_saida_programa();
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
    while (opcao_saida != 'S');

    return 0;
}

// Fun��es implementadas pelo programador

int ler_numero_inteiro_intervalo(int minimo, int maximo, char mensagem[])
{
    int numero;
    int leitura;

    do
    {
        printf("%s", mensagem);
        leitura = scanf("%d", &numero);

        if (leitura != 1)
        {
            while (getchar() != '\n');
            printf("Valor invalido. Insira apenas numeros.\n");
        }
        else if (numero < minimo || numero > maximo)
        {
            printf("O numero nao se encontra dentro do intervalo (%d - %d). Tente novamente.\n", minimo, maximo);
        }
    }
    while (leitura != 1 || numero < minimo || numero > maximo);

    return numero;
}

void ler_string(char string[], char mensagem[])
{
    printf("%s", mensagem);
    scanf(" %[^\n]s", string);
}

int registar_estudantes(t_estudante vetor_alunos[], int total_alunos)
{
    if(total_alunos < MAXIMO_ESTUDANTES)
    {
        vetor_alunos[total_alunos].id_estudante = total_alunos +1;
        vetor_alunos[total_alunos].numero_estudante = procurar_estudante(vetor_alunos, total_alunos);
        ler_string(vetor_alunos[total_alunos].nome_estudante, "Nome do estudante: ");
        ler_string(vetor_alunos[total_alunos].email, "Email do estudante: ");

        total_alunos++;
    }
    else
    {
        printf("Limite maximo de estudantes atingido\n");
        getchar();
    }

    return total_alunos;
}

int registar_unidades_curricular(t_unidade_curricular vetor_uc[], int total_uc)
{
    if(total_uc < UNIDADES_CURRICULARES)
    {
        vetor_uc[total_uc].id_uc = total_uc + 1;
        vetor_uc[total_uc].codigo_uc = ler_numero_inteiro_intervalo(4515101, 4515118, "Codigo da UC: ");
        ler_string(vetor_uc[total_uc].nome_uc, "Nome da UC: ");
        vetor_uc[total_uc].ano_curricular = ler_numero_inteiro_intervalo(1, 2, "Ano curricular: ");
        vetor_uc[total_uc].semestre = ler_numero_inteiro_intervalo(1, 2, "Semestre: ");
        vetor_uc[total_uc].ects = ler_numero_inteiro_intervalo(0, 30, "ECTS: ");

        total_uc++;
    }
    else
    {
        printf("Limite maximo de unidades curriculares atingida\n");
        getchar();
    }

    return total_uc;
}

int registar_avaliacoes(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, int id_uc, int id_estudante)
{
    int encontrado = 0;

    if(total_avaliacoes < AVALIACOES)
    {
        encontrado = validar_entrada_avaliacoes(vetor_avaliacoes, total_avaliacoes, id_uc, id_estudante);

        if(!encontrado)
        {
            vetor_avaliacoes[total_avaliacoes].id_avaliacao = total_avaliacoes + 1;
            ler_string(vetor_avaliacoes[total_avaliacoes].ano_letivo, "Ano Letivo: ");
            ler_string(vetor_avaliacoes[total_avaliacoes].epoca, "Epoca de avaliacoes: ");
            ler_string(vetor_avaliacoes[total_avaliacoes].data, "Data da avaliacao (DD/MM/AAAA): ");
            vetor_avaliacoes[total_avaliacoes].classificacao_final = ler_numero_inteiro_intervalo(0, 20, "Classificacao final: ");
            vetor_avaliacoes[total_avaliacoes].id_estudante = id_estudante;
            vetor_avaliacoes[total_avaliacoes].id_uc = id_uc;

            total_avaliacoes++;
        }
        else
        {
            printf("\nEste estudante ja foi registrado para esta unidade curricular.\n");
            aguarda_entrada_usuario();
        }
    }
    else
    {
        printf("Limite maximo de avaliacoes atingido\n");
        getchar();
    }

    return total_avaliacoes;
}

void mostrar_dados_de_um_estudantes(t_estudante vetor_alunos[], int total_alunos, int numero_estudante)
{
    int indice, encontrado = 0;

    printf("\n----------------------------Dados dos estudantes:----------------------------");

    for (indice = 0; indice < total_alunos; indice++)
    {
        if(vetor_alunos[indice].numero_estudante == numero_estudante)
        {
            printf("\n\nID: %d\n", vetor_alunos[indice].id_estudante);
            printf("Numero do estudante: %d\n", vetor_alunos[indice].numero_estudante);
            printf("Nome do estudante: %s\n", vetor_alunos[indice].nome_estudante);
            printf("Codigo de curso: %d\n", vetor_alunos[indice].codigo_curso = 4515);
            printf("Email do estudante: %s\n", vetor_alunos[indice].email);
            encontrado = 1;
        }
    }
    if(!encontrado)
    {
        printf("\n\nEstudante nao existe.\n");
    }
    printf("\n-----------------------------------------------------------------------------\n");
    aguarda_entrada_usuario();
    system("cls");
}

void mostrar_todos_os_estudantes(t_estudante vetor_alunos[], int total_alunos)
{
    int indice;

    printf("\n----------------------------Dados dos estudantes:----------------------------");

    if(total_alunos == 0)
    {
        printf("\n\nNenhum estudante registado no programa.\n");
    }
    else
    {
        for (indice = 0; indice < total_alunos; indice++)
        {
            printf("\n\nID: %d\n", vetor_alunos[indice].id_estudante);
            printf("Numero do estudante: %d\n", vetor_alunos[indice].numero_estudante);
            printf("Nome do estudante: %s\n", vetor_alunos[indice].nome_estudante);
            printf("Codigo de curso: %d\n", vetor_alunos[indice].codigo_curso = 4515);
            printf("Email do estudante: %s\n", vetor_alunos[indice].email);
        }
    }
    printf("\n-----------------------------------------------------------------------------\n");
    aguarda_entrada_usuario();
    system("cls");
}

void mostrar_dados_unidades_curriculares(t_unidade_curricular vetor_uc[], int total_uc)
{
    int indice;

    printf("\n----------------------------Dados das Unidades Curriculares---------------------");

    if(total_uc == 0)
    {
        printf("\n\nNenhuma unidade curricular se encontra registada no programa.\n");
    }
    else
    {
        for (indice = 0; indice < total_uc; indice++)
        {
            printf("\n\nID: %d\n", vetor_uc[indice].id_uc);
            printf("Codigo UC: %d\n", vetor_uc[indice].codigo_uc);
            printf("Nome da UC: %s\n", vetor_uc[indice].nome_uc);
            printf("Ano_curricular: %d\n", vetor_uc[indice].ano_curricular);
            printf("Semestre: %d\n", vetor_uc[indice].semestre);
            printf("ECTS: %d\n", vetor_uc[indice].ects);
        }
    }
    printf("\n-----------------------------------------------------------------------------\n");
    aguarda_entrada_usuario();
    system("cls");
}

void mostrar_dados_avaliacoes(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, int id_estudante, int id_uc)
{
    int indice;

    printf("\n----------------------------Dados das Avaliacoes------------------------------");

    if(total_avaliacoes == 0)
    {
        printf("\n\nNenhuma avaliacao registada no programa.\n");
    }
    else
    {
        for (indice = 0; indice < total_avaliacoes; indice++)
        {
            printf("\n\nID: %d\n", vetor_avaliacoes[indice].id_avaliacao);
            printf("ID do estudante: %d\n", vetor_avaliacoes[indice].id_estudante);
            printf("ID da Unidade Curricular: %d\n", vetor_avaliacoes[indice].id_uc);
            printf("Ano letivo: %s\n", vetor_avaliacoes[indice].ano_letivo);
            printf("Epoca de avaliacoes: %s\n", vetor_avaliacoes[indice].epoca);
            printf("Data da avaliacao: %s\n", vetor_avaliacoes[indice].data);
            printf("Nota: %d\n", vetor_avaliacoes[indice].classificacao_final);
        }
    }
    printf("\n-----------------------------------------------------------------------------\n");
    aguarda_entrada_usuario();
    system("cls");
}

char menu_opcoes()
{
    char opcao;

    do
    {
        system("cls");
        printf("=====================Menu Principal======================\n\n");
        printf("[A] - Registar Estudantes\n");
        printf("[B] - Consultar Estudantes\n");
        printf("[C] - Registar os dados das unidades curriculares\n");
        printf("[D] - Consultar os dados das unidades curriculares\n");
        printf("[E] - Registar avaliacoes\n");
        printf("[F] - Consultar os dados das avaliacoes\n");
        printf("[G] - Estatisticas\n");
        printf("[H] - Guardar ficheiros binarios dos dados da aplicacao\n");
        printf("[I] - Ler ficheiros binarios dos dados da aplicacao\n");
        printf("[S] - Terminar Programa\n");
        printf("\n========================================================\n");
        printf("\nSelecione a opcao: ");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

        if (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E' && opcao != 'F' && opcao != 'G' && opcao != 'H' && opcao != 'I' && opcao != 'S')
        {
            printf("\nOpcao invalida. Por favor, insira uma opcao valida.\n");
            aguarda_entrada_usuario();
        }

    }
    while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E' && opcao != 'F' && opcao != 'G' && opcao != 'H' && opcao != 'I' && opcao != 'S');

    return opcao;
}

char menu_mostrar_dados_estudantes()
{
    char opcao;

    do
    {
        system("cls");
        printf("==================Consultar Estudantes==================\n\n");
        printf("[A] - Consultar apenas 1 estudante\n");
        printf("[B] - Consultar todos os estudantes\n");
        printf("[S] - Voltar ao menu principal\n");
        printf("\n========================================================\n");
        printf("\nSelecione a opcao: ");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

        if (opcao != 'A' && opcao != 'B' && opcao != 'S')
        {
            printf("\nOpcao invalida. Por favor, insira uma opcao valida.\n");
            aguarda_entrada_usuario();
        }

    }
    while (opcao != 'A' && opcao != 'B' && opcao != 'S');

    return opcao;
}

char menu_estatisticas()
{
    char opcao;

    do
    {
        system("cls");
        printf("=============================================Estatisticas============================================\n\n");
        printf("[A] - Total de ECTS aprovados por um estudante\n");
        printf("[B] - Media aritmetica atual das classificacoes nas unidades curriculares aprovadas por um estudante\n");
        printf("[C] - Percentagem de ECTS aprovados em cada semestre letivo por um estudante\n");
        printf("[S] - Voltar ao Menu Principal\n");
        printf("\n=====================================================================================================\n");
        printf("\nSelecione a opcao: ");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

        if(opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'S')
        {
            printf("\nOpcao invalida. Por favor, insira uma opcao valida.\n");
            aguarda_entrada_usuario();
        }

    }
    while(opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'S');

    return opcao;
}

char confirmar_saida_programa(void)
{
    char opcao;

    do
    {
        printf("\nPretende encerrar o programa? (S/N) -> ");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

        if (opcao == 'S')
        {
            printf("A encerrar o programa...\n");
        }
        else if (opcao == 'N')
        {
            printf("O programa vai continuar...\n");
        }
        else
        {
            printf("Opcao invalida. Insira uma opcao valida.\n");
        }
    }
    while (opcao != 'S' && opcao != 'N');

    return opcao;
}

char confirmar_saida_para_menu()
{
    char opcao;

    do
    {
        printf("\nPretende voltar ao menu principal? (S/N) -> ");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

        if(opcao != 'S' && opcao != 'N')
        {
            printf("\n\nOpcao invalida. Insira uma opcao valida.\n\n");
        }

    }
    while(opcao != 'S' && opcao != 'N');

    return opcao;
}

int validar_entrada_avaliacoes(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, int id_uc, int id_estudante)
{
    int encontrado = 0, indice;

    for (indice = 0; indice < total_avaliacoes; indice++)
    {
        if (vetor_avaliacoes[indice].id_uc == id_uc && vetor_avaliacoes[indice].id_estudante == id_estudante)
        {
            encontrado = 1;
        }
    }
    return encontrado;
}

int procurar_estudante(t_estudante vetor_alunos[], int total_alunos)
{
    int numero_estudante;

    do
    {
        numero_estudante = ler_numero_inteiro_intervalo(2230000, 2239999, "Numero do estudante: ");
    }
    while (verificar_numero_existente(vetor_alunos, total_alunos, numero_estudante));

    return numero_estudante;
}

int verificar_numero_existente(t_estudante vetor_alunos[], int total_alunos, int num_estudante)
{
    int indice = 0;
    int numero_existente = 0;

    while (indice < total_alunos)
    {
        if (num_estudante == vetor_alunos[indice].numero_estudante)
        {
            printf("\nO numero introduzido ja existe. Por favor, escolha um numero diferente.\n");
            numero_existente = 1;
        }

        indice++;
    }

    return numero_existente;
}

int procurar_id_estudante(t_estudante vetor_alunos[], int total_alunos, int num_estudante)
{
    int indice, id_estudante, numero_encontrado = 0;

    for(indice = 0; indice < total_alunos; indice++)
    {
        if(vetor_alunos[indice].numero_estudante == num_estudante)
        {
            id_estudante = vetor_alunos[indice].id_estudante;
            numero_encontrado = 1;
        }
    }

    if(!numero_encontrado)
    {
        id_estudante = 0;
    }

    return id_estudante;
}

int procurar_id_uc(t_unidade_curricular vetor_uc[], int total_uc, int codigo_uc)
{
    int indice, id_uc, codigo_uc_encontrado = 0;

    for(indice = 0; indice < total_uc; indice++)
    {
        if(vetor_uc[indice].codigo_uc == codigo_uc)
        {
            id_uc = vetor_uc[indice].id_uc;
            codigo_uc_encontrado = 1;
        }
    }

    if(!codigo_uc_encontrado)
    {
        id_uc = 0;
    }

    return id_uc;
}

void aguarda_entrada_usuario()
{
    printf("\nPrima uma tecla para continuar...");
    getchar();
    getchar();

}

void total_ects_aprovados(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, t_unidade_curricular vetor_uc[])
{
    int id = 0, contador = 0, indice = 0, totalUC = 0, media = 0;

    id = ler_numero_inteiro_intervalo(0, AVALIACOES, "Qual o id do estudante: ");

    for(indice = 0; indice < total_avaliacoes; indice++)
    {
        if(id == vetor_avaliacoes[indice].id_estudante && vetor_avaliacoes[indice].classificacao_final >= 10)
        {
            totalUC = totalUC + vetor_uc[indice].ects;
        }
    }

    printf("O total de ECTS aprovados pelo estudante %d: %d",id, totalUC);
}

void media_aritmetica(t_avaliacao vetor_avaliacoes[], int total_avaliacoes)
{
    int id = 0, contador = 0, indice = 0, total_notas = 0;
    float media = 0;

    id = ler_numero_inteiro_intervalo(0, AVALIACOES, "Qual o id de estudante: ");

    for(indice = 0; indice < total_avaliacoes; indice++)
    {
        if(id == vetor_avaliacoes[indice].id_estudante && vetor_avaliacoes[indice].classificacao_final >= 10)
        {
            contador = contador + vetor_avaliacoes[indice].classificacao_final;
            total_notas++;
        }
    }
    media = (float)contador / total_notas;

    printf("Media aritmetica atual das classificacoes das unidades curriculares aprovadas do estudante com o id %d e: %.2f", id, media);
}

void percentagem_ects_por_semestre(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, t_unidade_curricular vetor_uc[])
{
    int id = 0, contador = 0, indice = 0, total  = 0, total_ects_possiveis_semestre1 = 0, total_ects_possiveis_semestre2 = 0, total_ects_aprovados_semestre1 = 0, total_ects_aprovados_semestre2 = 0;

    id = ler_numero_inteiro_intervalo(0, AVALIACOES, "Qual o id do estudante: ");

    for(indice = 0; indice < total_avaliacoes; indice++)
    {
        if(id == vetor_avaliacoes[indice].id_estudante && vetor_avaliacoes[indice].classificacao_final >= 10 && vetor_uc[indice].semestre == 1)
        {
            total_ects_aprovados_semestre1 += vetor_uc[indice].ects;
        }
        if(id == vetor_avaliacoes[indice].id_estudante && vetor_avaliacoes[indice].classificacao_final >= 10 && vetor_uc[indice].semestre == 2)
        {
            total_ects_aprovados_semestre2 += vetor_uc[indice].ects;
        }

        if (id == vetor_avaliacoes[indice].id_estudante)
        {
            if (vetor_uc[indice].semestre == 1)
            {
                total_ects_possiveis_semestre1 += vetor_uc[indice].ects;
            }
            else if (vetor_uc[indice].semestre == 2)
            {
                total_ects_possiveis_semestre2 += vetor_uc[indice].ects;
            }
        }
    }
    mostrar_percentagem_ects_por_semestre(vetor_avaliacoes, total_avaliacoes, vetor_uc, id, total_ects_aprovados_semestre1, total_ects_aprovados_semestre2, total_ects_possiveis_semestre1, total_ects_possiveis_semestre2);

}

void mostrar_percentagem_ects_por_semestre(t_avaliacao vetor_avaliacoes[], int total_avaliacoes, t_unidade_curricular vetor_uc[], int id, int total_ects_aprovados_semestre1, int total_ects_aprovados_semestre2, int total_ects_possiveis_semestre1, int total_ects_possiveis_semestre2)
{
    float percentagem_semestre1, percentagem_semestre2;

    if(total_ects_possiveis_semestre1 > 0)
    {
        percentagem_semestre1 = (float)total_ects_aprovados_semestre1 / total_ects_possiveis_semestre1 * 100;
        printf("A percentagem de ects aprovados no semestre 1 e: %.2f%%\n", percentagem_semestre1);
    }
    else
    {
        printf("Nao existe avaliacoes registadas no 1 semestre");
    }
    if(total_ects_aprovados_semestre2 > 0)
    {
        percentagem_semestre2 = (float)total_ects_aprovados_semestre2 / total_ects_possiveis_semestre2 * 100;
        printf("A percentagem de ects aprovados no semestre 2 pelo estudante e: %.2f%%\n", percentagem_semestre2);
    }
    else
    {
        printf("Nao existe avaliacoes registadas no 2 semestre");
    }
}

void gravar_dados_ficheiro_estudantes(t_estudante vetor_alunos[], int total_alunos)
{
    FILE *ficheiro_alunos;
    ficheiro_alunos = fopen("estudantes.dat", "wb");

    if(ficheiro_alunos == NULL)
    {
        printf("Nao foi possivel criar o ficheiro de estudantes.");
    }
    else
    {
        fwrite(&total_alunos, sizeof(int), 1, ficheiro_alunos);
        fwrite(vetor_alunos, sizeof(t_estudante), total_alunos, ficheiro_alunos);
        printf("\nGravado os dados de %d aluno(s) em ficheiro com sucesso.\n", total_alunos);
    }
    fclose(ficheiro_alunos);
}

void gravar_dados_ficheiro_uc(t_unidade_curricular vetor_uc[], int total_uc)
{
    FILE *ficheiro_uc;
    ficheiro_uc = fopen("unidade_curricular.dat", "wb");

    if(ficheiro_uc == NULL)
    {
        printf("Nao foi possivel criar o ficheiro sobre as unidades curriculares.");
    }
    else
    {
        fwrite(&total_uc, sizeof(int), 1, ficheiro_uc);
        fwrite(vetor_uc, sizeof(t_unidade_curricular), total_uc, ficheiro_uc);
        printf("\nGravado os dados de %d unidade(s) curriculare(s) em ficheiro com sucesso.\n", total_uc);
    }
    fclose(ficheiro_uc);
}

void gravar_dados_ficheiro_avaliacao(t_avaliacao vetor_avaliacoes[], int total_avaliacoes)
{
    FILE *ficheiro_avaliacoes;
    ficheiro_avaliacoes = fopen("avaliacoes.dat", "wb");

    if(ficheiro_avaliacoes == NULL)
    {
        printf("Nao foi possivel criar o ficheiro sobre as avaliacoes.");
    }
    else
    {
        fwrite(&total_avaliacoes, sizeof(int), 1, ficheiro_avaliacoes);
        fwrite(vetor_avaliacoes, sizeof(t_avaliacao), total_avaliacoes, ficheiro_avaliacoes);
        printf("\nGravado os dados de %d avaliacoes em ficheiro com sucesso.\n", total_avaliacoes);
    }
    fclose(ficheiro_avaliacoes);
}

int ler_dados_ficheiro_estudantes(t_estudante vetor_alunos[])
{
    int total_alunos = 0;
    FILE *ficheiro_alunos;
    ficheiro_alunos = fopen("estudantes.dat", "rb");

    if(ficheiro_alunos == NULL)
    {
        printf("Nao foi possivel ler o ficheiro dos estudantes.");
    }
    else
    {
        fread(&total_alunos, sizeof(int), 1, ficheiro_alunos);
        fread(vetor_alunos, sizeof(t_estudante), total_alunos, ficheiro_alunos);
        printf("\nLeitura dos dados de %d aluno(s) em ficheiro com sucesso.\n", total_alunos);
    }
    fclose(ficheiro_alunos);

    return total_alunos;
}

int ler_dados_ficheiro_uc(t_unidade_curricular vetor_uc[])
{
    int total_uc = 0;
    FILE *ficheiro_uc;
    ficheiro_uc = fopen("unidade_curricular.dat", "rb");

    if(ficheiro_uc == NULL)
    {
        printf("Nao foi possivel ler o ficheiro das unidades curriculares.");
    }
    else
    {
        fread(&total_uc, sizeof(int), 1, ficheiro_uc);
        fread(vetor_uc, sizeof(t_unidade_curricular), total_uc, ficheiro_uc);
        printf("\nLeitura dos dados de %d unidade(s) curriculare(s) em ficheiro com sucesso.\n", total_uc);
    }
    fclose(ficheiro_uc);

    return total_uc;
}

int ler_dados_ficheiro_avaliacao(t_avaliacao vetor_avaliacoes[])
{
    int total_avaliacoes = 0;
    FILE *ficheiro_avaliacoes;
    ficheiro_avaliacoes = fopen("avaliacoes.dat", "rb");

    if(ficheiro_avaliacoes == NULL)
    {
        printf("Nao foi possivel ler o ficheiro das avaliacoes");
    }
    else
    {
        fread(&total_avaliacoes, sizeof(int), 1, ficheiro_avaliacoes);
        fread(vetor_avaliacoes, sizeof(t_avaliacao), total_avaliacoes, ficheiro_avaliacoes);
        printf("\nLeitura dos dados de %d avaliacoes em ficheiro com sucesso.\n", total_avaliacoes);
    }
    fclose(ficheiro_avaliacoes);

    return total_avaliacoes;
}
void alterar_nota_estudante(t_avaliacao vetor_avaliacoes[], int total_avaliacoes)
{
    int id_estudante, id_uc, nota_nova, indice;

    id_estudante = ler_numero_inteiro_intervalo(0, 150, "Introduza o id do estudante: ");
    id_uc = ler_numero_inteiro_intervalo(0, 18, "Introduza o id da uc: ");

    for(indice = 0; indice < total_avaliacoes; indice++)
    {
        if(vetor_avaliacoes[indice].id_estudante == id_estudante && vetor_avaliacoes[indice].id_uc == id_uc)
        {
            printf("Nota atual: %d", vetor_avaliacoes[indice].classificacao_final);
            nota_nova = ler_numero_inteiro_intervalo(0,20, "Insira a nova nota: ");
            printf("Classifica��o alterada com sucesso");
        }
        else
        {
            printf("Estudante ou unidade curricular n�o econtrado!!!");
        }
    }
}
