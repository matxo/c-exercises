/*
Exercise 4-4. Add the commands to print the top elements of the stack without
popping, to duplicate it, and to swap the top two elements. Add a command to
clear the stack.

matxo
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for  atof()

#define MAXOP   100 // max size of operand or operator
#define NUMBER  '0' // signal that a number was found
#define COMMAND 'c' // signal that a command was found

int getop(char []);

void execute_cmd(char s[]);

void push(double f);
double pop();
double get_top();
void duplicate();
void swap();
void clear();

// reverse Polish calculator
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
        break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((long int)pop() % (long int)op2);
            else
                printf("error: zero divisor\n");
        break;
        case '\n':
            printf("\t%.8g\n", pop());
        break;
        case COMMAND:
            execute_cmd(s);
        break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// execute_cmd: executes command specified in string s
void execute_cmd(char s[])
{
    if (strcmp(s, "top") == 0)          // print top element
        printf("\t%.8g\n", get_top());
    else if (strcmp(s, "dup") == 0)     // duplicate top element
        duplicate();
    else if (strcmp(s, "swap") == 0)    // swap top two elements
        swap();
    else if (strcmp(s, "clear") == 0)   // clear stack
        clear();
    else
        printf("error: unknown command %s\n", s);
}

#define MAXVAL  100     // maximum depth of val stack

int sp = 0;             // next free stack position
double val[MAXVAL];     // value stack

// push: push f onto value stack
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value from stack
double pop()
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// get_top: return top element of stack without popping it
double get_top()
{
    if (sp > 0)
        return val[sp-1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// duplicate: duplicate top element of the stack
void duplicate() {
    if (sp > 0) {
        push(get_top());
    }
    else {
        printf("error: stack empty\n");
    }
}

// swap: swap two top elements of the stack
void swap() {
    if (sp > 1) {
        double tmp = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = tmp;
    }
    else {
        printf("error: stack contains fewer then two elements\n");
    }
}

// clear: clear stack
void clear()
{
    sp = 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

// getop: get next character or numeric operand
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isalnum(c) && c != '.') {
        if (c == '+' || c == '-') {
            int t = getch();
            ungetch(t);
            if (!isalnum(t) && t != '.') {
                return c;   // not a number
            }
        } else {
            return c;       // not a number
        }
    }

    i = 0;
    // command
    if (isalpha(c)) { // collect command string
        s[i] = tolower(s[i]);
        while (isalpha(s[++i] = c = tolower(getch())))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return COMMAND;
    }

    // number
    if (c == '+' || c == '-')
        s[++i] = c = getch();
    if (isdigit(c))     // collect integer part
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')       // collect fraction part
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  // buffer for ungetch
int bufp = 0;       // next free position in buf

int getch(void)     // get a (possibly pushed-back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
