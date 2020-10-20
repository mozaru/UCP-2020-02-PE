# Sub-Rotinas

São comandos criados pelo usuario da linguagem (programador)
Também podem ser vistos como trechos de código rotulados e configuráveis através de parametros.


ex:
~~~C
#include <stdio.h>
void limparTela() {
    int i;
    for(i=0;i<60;i++)
        printf("\n");
}

int lerInt(char msg[])
{
    int n;
    do {
        printf("%s: ", msg);
        scanf("%i", &n);
    } while (n<=0);
    return n;    
}

int main()
{
    int x;
    limparTela();
    x = lerInt("Entre com o valor inteiro positivo para X");
    limparTela();
    printf("x = %i\n",x);
    return 0;
}
~~~

## Tipos de Subrotinas

1. Procedimentos

    Procedimentos são subrotinas que não retornam (representam) um valor
  
    *sintaxe*: 
    ~~~ C
    void nome_procedimento(parametros) 
    { 
        .......
    }
    ~~~

2. Funções

    Funções são subrotinas que retornam (representam) um valor.

    *sintaxe*: 
    ~~~ C
    tipo nome_procedimento(parametros) 
    { 
        ....... 
        return valor_compativel_com_o_tipo 
    }
    ~~~


## Parametros

    Todas as subrotinas (procedimentos ou funções) podem receber parametros que podem ser passados de duas formas: **por valor** ou **por referência**

*sintaxe*: tipo nome1, tipo nome2, tipo nome3.....

ex:
~~~C
int somar(int x, int y, int z)
{
    return x+y+z;
}

float media(float n1, float n2)
{
    return (n1+n2)/2.0;
}

void exemplo(char nome[], char op, int a, int b, float x)
{
    ...
}
~~~


1. por valor

   O argumento é uma copia do valor passado por parametro.

    ex:
    ~~~c
    #include<stdio.h>

    void incremento(int x)
    {
        x = x + 1;
    }

    int main(void)
    {
        int a;
        a=10;
        incremento(a);
        printf("%i", a);// qual o valor escrito?
        return 0;
    }
    ~~~
    obs: escreve 10 na tela


2. por referência

    O argumento é uma referência a variavel passada por parametro.

    ex:
    ~~~c
    #include<stdio.h>

    void incremento(int *x)
    {
        *x = *x + 1;
    }

    int main(void)
    {
        int a;
        a=10;
        incremento( &a );
        printf("%i", a);// qual o valor escrito?
        return 0;
    }
    ~~~
    obs: escreve 11 na tela

## Recursividade

    Ocorre quando uma subrotina, recorre(chama) a ela mesma direta ou indiretamente.

    ex: fatorial onde:
        fat(1) = 1
        fat(2) = 2 * 1          -> 2*fat(1)
        fat(3) = 3 * 2 * 1      -> 3*fat(2)
        fat(4) = 4 * 3 * 2 * 1  -> 4*fat(3)
        ...
        fat(n) = n*fat(n-1)  

    Para criar uma função recursiva:
    1. base da recursão: valores conhecidos
        fat(1) => 1
    2. caso geral: deve convergir para a base da recursão
        fat(n) => n*fat(n-1)

~~~C
    #include<stdio.h>

    int fat(int n)
    {
        if (n<1)
           return 0;
        else if (n==1)
            return 1;
        else
            return n*fat(n-1);
    }

    int main()
    {
        int n;
        printf("entre com o valor de n: ");
        scanf("%i", &n);
        printf("Fat(%i) = %i\n", n, fat(n));
        return 0;
    }
~~~
