#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _TAM_NOME_ 30
/*1. criar uma estrutura/registro para representar uma
   disciplina*/
typedef struct {
  int codigo;
  char nome[_TAM_NOME_];
  int creditos, semestre, ano;
  float nota1,nota2;
  char professor[_TAM_NOME_];
} Disciplina;

/*2. criar uma estrutura/registro para representar 
  o historico (conjunto de disciplinas)*/
typedef struct {
  Disciplina vet[100];
  int qtd;
} Historico;


/*3. criar as subrotinas para a estrutura disciplina
   3.1 - ler -> para ler os dados de uma disciplina*/
void lerDisciplina( Disciplina *d )
{
    system("cls");
    printf("Codigo:");      scanf("%d", & (*d).codigo);    fflush(stdin);
    printf("Nome:");        gets((*d).nome);
    printf("Creditos:");    scanf("%i", & (*d).creditos);
    printf("Semestre:");    scanf("%i", & (*d).semestre);
    printf("Ano:");         scanf("%i", & (*d).ano);
    printf("Nota1:");       scanf("%f", & (*d).nota1);
    printf("Nota2:");       scanf("%f", & (*d).nota2);      fflush(stdin);
    printf("Professor:");    gets((*d).professor);
}

/*   3.2 - media -> retorna a media de uma disciplina*/
float mediaDisciplina( Disciplina d )
{
    return (d.nota1+d.nota2)/2;
}

/*  3.3 - mostrar -> mostra os dados de uma disciplina*/
void mostrarDisciplina( Disciplina d )
{
    system("cls");
    printf("Codigo:%i\n", d.codigo);
    printf("Nome:%s\n", d.nome);
    printf("Creditos:%i\n", d.creditos);
    printf("Semestre:%i\n", d.semestre);
    printf("Ano:%i\n", d.ano);
    printf("Nota1:%5.2f\n", d.nota1);
    printf("Nota2:%5.2f\n", d.nota2);
    printf("Professor:%s\n",d.professor);
    system("pause");
}


/*4. criar as subrotinas para o historico
   4.1 - inicializar -> inicializa um historico como vazio*/
void inicializarHistorico(Historico *h)
{
    (*h).qtd = 0;
}

/* 4.2 - inserir -> inserir uma disciplina (so insere nao le e nao escreve nada na tela)*/
void inserirHistorico(Historico *h, Disciplina d)
{
    (*h).vet[ (*h).qtd ] = d;
    (*h).qtd++;
}

/* 4.3 - remover -> remove uma disciplina do historico (so remove nao le e nao escreve nada na tela)*/
int obterIndiceHistorico( Historico h, int codDisciplina)
{
    int achou,i;
    achou = 0;//falso
    i=0;//primeiro elemento
    while (!achou && i<h.qtd)
        if (h.vet[i].codigo == codDisciplina)
            achou = 1;// verdadeiro
        else
            i++;//vai para o proximo elemento    
    return achou ? i : -1;
}

void removerHistorico(Historico *h, int codDisciplina)
{
    int pos = obterIndiceHistorico(*h, codDisciplina);
    if (pos>-1)
    {
        (*h).vet[pos] = (*h).vet[(*h).qtd-1];
        (*h).qtd--;
    }
}

/* 4.4 - alterar -> altera os dados de uma disciplina (so substitui, nao le e nao escreve nada na tela)*/
void alterarHistorico(Historico *h, int codDisciplina, Disciplina d)
{
    int pos = obterIndiceHistorico(*h, codDisciplina);
    if (pos>-1)
        (*h).vet[pos] = d;
}

/* 4.5 - listar -> lista todas as disciplinas na tela*/
void listarHistorico(Historico h)
{
    int i;
    printf("%-30s %5s %4s %4s %5s\n", "Nome", "Cred.", "Sem.", "Ano", "Media");
    for(i=0;i<h.qtd; i++)
    {
        Disciplina d = h.vet[i];
        printf("%-30s %5i %4i %4i %5.2f\n", d.nome, d.creditos, d.semestre, d.ano, mediaDisciplina(d));
    }
}
/* 4.6 - cr -> calcula e retorna o valor do CR, (nao le e nao escreve nada na tela)*/
float crHistorico(Historico h)
{
    int i,creditos;
    float soma;
    creditos = 0;
    soma = 0;
    for(i=0;i<h.qtd;i++)
    {
        soma = soma + h.vet[i].creditos*mediaDisciplina(h.vet[i]);
        creditos = creditos + h.vet[i].creditos;
    }  
    return creditos==0 ? 0 : soma/creditos;
}
/* 4.7 - historico -> lista e mostra o CR*/
void mostrarHistorico(Historico h)
{
    system("cls");
    listarHistorico(h);
    printf("Coeficiente de Rendimento: %5.2f\n",crHistorico(h));
    system("pause");
}

int existeHistorico(Historico h, int codDisciplina)
{
    return obterIndiceHistorico(h,codDisciplina) != -1;
}

/*5.0 - programa principal*/

int menu()
{
    int opc;
    do{
        system("cls");
        printf("1-Inserir\n");
        printf("2-Remover\n");
        printf("3-Alterar\n");
        printf("4-Historico\n");
        printf("5-Sair\n");
        printf("Entre com uma das opcoes acima:");
        scanf("%i", &opc);
    }while (opc<0 ||opc>5);
    system("cls");
    return opc;
}

void msg(char texto[])
{
    printf("%s\n",texto);
    system("pause");
}

int main()
{
    Historico hist;
    Disciplina ficha;
    int fim=0, cod;

    inicializarHistorico(&hist);
    while (!fim)
        switch(menu())
        {
            case 1: //inserir
                lerDisciplina(&ficha);
                inserirHistorico(&hist, ficha);
                msg("Inserido com sucesso!");
                break;
            case 2: //remover
                printf("Entre com o codigo:");
                scanf("%i",&cod);
                if (existeHistorico(hist,cod))
                {
                    removerHistorico(&hist, cod);
                    msg("Disciplina removida com sucesso!");
                } else {
                    msg("Disciplina nao encontrada!");
                }
                break;
            case 3: //alterar
                printf("Entre com o codigo:");
                scanf("%i",&cod);
                if (existeHistorico(hist,cod))
                {
                    lerDisciplina(&ficha);
                    alterarHistorico(&hist, cod, ficha);
                    msg("Disciplina alterada com sucesso!");
                } else {
                    msg("Disciplina nao encontrada!");
                }
                break;
            case 4: //historico
                mostrarHistorico(hist);
                break;
            case 5://sair
                fim=1;//verdadeiro
                break;           
        }    

    return 0;
}

