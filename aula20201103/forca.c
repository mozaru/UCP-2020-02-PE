/*10- Faça o jogo da Forca. 
    inicialmente o programa deve ler um frase secreta, limpar a tela e iniciar o jogo. 
    Na tela devem aparacer: As letras chutas, a Frase secreta com _ nas letras nao chutadas, e a qtd de vida, que inicialmente é 5.
    apos 5 erros o jogador perde.
    obs: o usuario so vai chutar letras de A-Z, entao se na frase tivermos qualquer caracter diferente este ja aparece revelado.
         e a Forca nao faz distinção de maiuscula e minuscula*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define _MAX_FRASE_         100
#define _VIDAS_INICIAIS_    5

typedef struct
{
    char FraseSecreta[_MAX_FRASE_];
    char Display[_MAX_FRASE_];
    char Letras[30];
    int  Vidas;
} TForca;

void Inicializar(TForca *f, char Frase[]);
void Processar(TForca *f, char L);
int Morreu(TForca f);
int RevelouTudo(TForca f);
int Acabou(TForca f);

void Mostrar(TForca f);
void LerFraseSecreta(char Frase[]);
void LerFraseSecretaArq(char NomeArq[], int min, int max, char Frase[]);
char PedirLetra();

int main()
{
    TForca  f;
    char Frase[_MAX_FRASE_];
    char Letra;

    //LerFraseSecreta(Frase);
    LerFraseSecretaArq("br-sem-acentos.txt", 10, 30, Frase);
    Inicializar(&f, Frase );
    while (!Acabou(f))
    {
        Mostrar(f);
        Letra = PedirLetra();        
        Processar(&f, Letra);
    }

    Mostrar(f);
    if (Morreu(f)) {
        printf("Voce fracassou misseravelmente!\n\n");
        printf("A Palavra secreta era [%s]\n",f.FraseSecreta);
    } else
        printf("Parabens!, voce descobriu a frase secreta\n\n");
    return 0;
}


void Inicializar(TForca *f, char Frase[])
{
    int tam,i; 
    strcpy((*f).FraseSecreta, Frase);    //(*f).FraseSecreta = Frase;
    strcpy((*f).Letras, "");             //(*f).Letras = "";
    (*f).Vidas = _VIDAS_INICIAIS_; 
    
    strcpy((*f).Display, Frase);         //(*f).Display = Frase;
    tam = strlen(Frase);
    for(i=0;i<tam;i++)
      if (isalpha((*f).Display[i]))
        (*f).Display[i] = '_';
}

void Processar(TForca *f, char L)
{
    int ok,i,tam;
    if (isalpha(L))
    {
        L = toupper(L);
        tam = strlen((*f).FraseSecreta);
        ok = 0;
        for(i=0; i<tam; i++)
            if ( (*f).Display[i]=='_' && toupper((*f).FraseSecreta[i]) == L)
            {
                ok = 1;
                (*f).Display[i]=(*f).FraseSecreta[i];
            }
        
        if (!ok)
            (*f).Vidas--;

        if (strchr((*f).Letras, L) == NULL)
        {
            //strncat((*f).Letras,&L,1);
            tam = strlen((*f).Letras);
            (*f).Letras[tam] = L;
            (*f).Letras[tam+1] = '\0';
        }
    }
}

int Morreu(TForca f)
{
    return f.Vidas <= 0;
}

int RevelouTudo(TForca f)
{
    int revelado = 1;
    int i, tam = strlen(f.FraseSecreta);
    for(i=0;i<tam && revelado;i++)
      if (f.Display[i] != f.FraseSecreta[i] )
        revelado = 0;
    return revelado;
}

int Acabou(TForca f)
{
    return Morreu(f) || RevelouTudo(f);
}

void Mostrar(TForca f)
{
    int i,tam;
    system("cls");
    printf("Vidas: %i \n", f.Vidas);

    printf("Letras: ");
    tam = strlen(f.Letras);
    for(i=0;i<tam;i++)
        printf("%c ", f.Letras[i]);
    printf("\n");

    printf("\n\n");
    tam = strlen(f.Display);
    for(i=0;i<tam;i++)
        printf("%c ", f.Display[i]);
    printf("\n\n");
}

void LerFraseSecreta(char Frase[])
{
    system("cls");
    printf("Entre com a frase secreta:");
    fgets(Frase, _MAX_FRASE_, stdin);
}

int SemAcentos(char palavra[])
{
    int tam,i,ok=1;
    tam = strlen(palavra);
    for(i=0;i<tam && ok; i++)
        if (!isalpha(palavra[i]) && palavra[i]!='-' && palavra[i] != ' ')
            ok = 0;
    return ok;
}

void LerFraseSecretaArq(char NomeArq[], int min, int max, char Frase[])
{
    FILE *arq;
    int tam, ok=0;
    char Linha[100];
    int x = (time(NULL) % 100) * 100;
    srand(x);
    char LetraInicial;

    LetraInicial = (int)(26*((double)rand()/RAND_MAX))+65;
    arq = fopen( NomeArq, "rt" );  //r-readonly t-textfile
    if (arq==NULL)
    {
        printf("Não foi possivel abrir o arquivo [%s]\n", NomeArq);
        exit(0);
    }
    strcpy(Frase,"");
    while ( !feof(arq) && !ok)
    {   
        fgets(Linha, 100, arq);
        tam = strlen(Linha);
        Linha[tam-1]='\0';
        tam--;
        if (tam>=min && tam<=max && toupper(Linha[0]) == LetraInicial)
            if ( ((double)rand()/RAND_MAX) < 0.001 || Frase[0]=='\0')
            {
                strcpy(Frase, Linha);
                if ( ((double)rand()/RAND_MAX) < 0.001)
                    ok = 1;
            }
    }
    fclose(arq);    
}

char PedirLetra()
{
    char l;
    do{
        printf("Entre com uma Letra:");
        l = getchar();
    }while ( !isalpha(l) );
    return l;
}


