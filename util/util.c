#include "util.h"
#include <stdio.h>

#include <stdlib.h>

int mdc(int a, int b)
{
    int resto;
    int n_maior, n_menor;

    if(a == 0 || b == 0)
    {
        return 1;
    }

    if(a == 1 || b == 1)
    {
        return 1;
    }

    if(a > b)
    {
        n_maior = a;
        n_menor = b;

    } else{
        n_maior = b;
        n_menor = a;
    }

    resto = n_maior % n_menor;

    if(resto == 0)
    {
        return n_menor;
    }

    return mdc(n_menor, resto);
}
