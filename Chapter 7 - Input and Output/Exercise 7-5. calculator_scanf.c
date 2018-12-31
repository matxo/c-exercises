/*
Exercise 5-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or
sscanf to do the input and number conversion.

matxo
*/

#include <stdio.h>

// simple normal calculator (instead of postfix)
int main()
{
    char *help = "input error\n\n"
        "simple calculator help:\n"
        "\tfirst use: [num1][op][num2]\n"
        "\tand after: [num1][op][num2] or [op][num]\n"
        "\tnum = float number\n"
        "\top = [+ * - /]\n";
    char *lineptr = NULL;
    size_t n;
    float num1, num2;
    char op;
    int isfirst = 1;

    while (getline(&lineptr, &n, stdin) != EOF) {
        if (isfirst) {
            if (sscanf(lineptr, "%f%c%f", &num1, &op, &num2) != 3) {
                printf("%s", help);
                continue;
            } else
                isfirst = 0;
        } else {
            if (sscanf(lineptr, "%c%f", &op, &num2) != 2 &&
                sscanf(lineptr, "%f%c%f", &num1, &op, &num2) != 3) 
            {
                printf("%s", help);
                continue;
            }
        }
        switch (op) {
        case '+':
            num1 += num2;
            break;
        case '*':
            num1 *= num2;
            break;
        case '-':
            num1 -= num2;
            break;
        case '/':
            if (num2 != 0.0)
                num1 /= num2;
            else
                printf("division by zero error\n");
        break;
        default:
            printf("%s", help);
            break;
        }
        printf("=%f\n", num1);
    }
    return 0;
}
