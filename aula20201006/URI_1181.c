#include <stdio.h>
int main ()
{
    int linha, i, j;
    char op;
    double soma, M[12][12];
    
    scanf ("%i\n", &linha);
    scanf ("%c", &op);
    
    for (i=0;i<12;i++)
        for (j=0;j<12;j++)
            scanf ("%lf", &M[i][j]);
    
    soma=0;
    for (j=0;j<12;j++)
        soma += M[linha][j]; // += significa que soma recebe soma + a matriz
    
    printf ("%.1lf\n", op == 'S'?soma : soma/12);
    
    return 0;
}
