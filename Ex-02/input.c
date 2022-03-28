#include <stdio.h>
#include<stdbool.h>

int main()
{
    int a = 8;
    double b = 9.5;

    char c = 'x';
    char d[] = "Hello!";
    
    int e = 9;
    int f = e & f | ++e - f;

    // Single line Comment

    if (a > b && a != b)
    {
        printf("a greater than b\n");
    }
    else if (a >= b)
    {
        printf("a equal to b\n");
    }
    else
    {
        printf("a lesser than b\n");
    }

    /*
        Multiline Comment
    */

    return 0;
}
