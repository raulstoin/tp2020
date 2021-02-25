/**
    Functia Ackermann - implementare iterativa si recursiva.

    Valorile maxime de incercat: (2, 131072), (3,14), (4,1), (5,0).
    Pentru valori mai mari, una dintre situatii se poate intampla:
        - se va depasi int
        - va duraasdasdasdas mult timp
        - va depasi memoria maxima alocata.

    Varianta recurviva va depasi stiva admisa de program mult mai rapid!

    https://en.wikipedia.org/wiki/Ackermann_function#Table_of_values
*/
#include <stdio.h>
#include <stdlib.h>

/* Fiind o functie cu doua variabile, este necesar ca
 * ambele variabile sa fie memorate pe stiva
 */
typedef struct Ackermann
{
    int x, y;
} Ackermann;

Ackermann st[1 * 1024 * 1024]; // (4+4)*1 MB memorie pentru stiva simulata
int vf = 0;

void push(Ackermann elem)
{
    vf++;
    st[vf] = elem;
}

Ackermann pop()
{
    vf--;
    return st[vf + 1];
}

Ackermann peek()
{
    return st[vf];
}

int ackermannIterativ(int x, int y)
{
    int aFinal = -1;
    Ackermann a;

    a.x = x;
    a.y = y;
    push(a);

    while(vf > 0)
    {
        a = peek();
        if(a.x == 0)
        {
            aFinal = a.y + 1;
            // Varful actual trebuie eliminat, deoarece functia s-a evaluat.
            pop();

            /* Varful anterior trebuie inlocuit de un nou apel.
             * Se simuleaza "return ackermannRecursiv(x - 1, 1);"
             */
            a = pop();
            a.x = a.x - 1;
            a.y = aFinal;
            push(a);
        }
        else if(a.x > 0 && a.y == 0)
        {
            a.x = a.x - 1;
            a.y = 1;
            /* Varful actual trebuie inlocuit de un nou apel.
             * Se simuleaza "return ackermannRecursiv(x - 1, ackermannRecursiv(x, y - 1));"
             */
            pop();
            push(a);
        }
        else if(a.x > 0 && a.y > 0)
        {
            a.x = a.x;
            a.y = a.y - 1;
            push(a);
        }
    }

    return aFinal;
}

int ackermannRecursiv(int x, int y)
{
    if(x == 0)
        return y + 1;
    else if(x > 0 && y == 0)
        return ackermannRecursiv(x - 1, 1);
    else if(x > 0 && y > 0)
        return ackermannRecursiv(x - 1, ackermannRecursiv(x, y - 1));
    return -1;
}

int main()
{
    int x, y;

    printf("x = ");
    scanf("%d", &x);
    printf("y = ");
    scanf("%d", &y);

    printf("Iterativ - Ackerman(%d,%d) = %d\n", x, y, ackermannIterativ(x, y));
    //printf("Iterativ - Ackerman(%d,%d) = %d\n", x, y, ackermannRecursiv(x, y));

    return 0;
}

