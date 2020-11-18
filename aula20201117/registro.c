#include<stdio.h>
#include<string.h>

typedef float real;
typedef int inteiro;
typedef char string[30];

typedef struct {
    string nome;
    inteiro idade;
    real peso;
} pessoa;

void lerPessoa( pessoa *p)
{
    strcpy((*p).nome,"Joao da Silva");
    (*p).idade = 10;
    (*p).peso = 45;
}

void mostrarPessoa( pessoa p)
{
    printf("nome: %s\n", p.nome);
    printf("idade: %i\n", p.idade);
    printf("peso: %.2f\n", p.peso);
}
int main(void)
{
    pessoa a,b;

    lerPessoa(&a);
    lerPessoa(&b);
    b.idade = 50;
    b.peso = 76;
    
    mostrarPessoa(a);
    mostrarPessoa(b);

    return 0;
}
