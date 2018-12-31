/*
Exercise 5-10. Write the program expr, which evaluates a reverse Polish
expression from the command line, where each operator or operand is a separate
argument. For example,
    expr 2 3 4 + *
    evaluates 2 * (3+4).

matxo
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>     // for  atof()
#include <math.h>
#include <stdbool.h>

#define MAXOP   100     // max size of operand or operator
#define NUMBER  '0'     // signal that a number was found
#define COMMAND 'c'     // signal that a command was found
#define VARIABLE 'd'    // signal that a variable was found

int getop(char []);

void execute_cmd(char s[]);

void push(double f);
double pop();
double get_top();
void duplicate();
void swap();
void clear();

double var['z'-'a'+1];
double var_last;
bool var_assign = false;

void ungets(char s[]);

// reverse Polish calculator
int main(int argc, char *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    const int MAX_LINE = 1000;
    char line[MAX_LINE];
    line[0] = '\0';

    if (argc > 1) {
        for (int i = 1; i <= argc -1 ; i++) {
            strcat(line, argv[i]);
            strcat(line, " ");
        }
        strcat(line, "\n");
        printf("expr %s\n", line);
        ungets(line);
    }
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case VARIABLE:
            if (var_assign)
                var[s[0]+'a'] = pop();
            else
                push(var[s[0]+'a']);
            break;
        case '=':   // assign value from top of stack to variable
            var_assign = true;
            break;
        case '$':   // use value of variable as NUMBER
            var_assign = false;
            break;
        case '?':   // var holding most recently printed value
            push(var_last);
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
            var_last = pop();
            printf("\t%.8g\n", var_last);
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

#include <math.h>
// execute_cmd: executes command specified in string s
void execute_cmd(char s[]) {
    if (strcmp(s, "top") == 0) {        // print top element
        var_last = get_top();
        printf("\t%.8g\n", var_last);
    }
    else if (strcmp(s, "dup") == 0)     // duplicate top element
        duplicate();
    else if (strcmp(s, "swap") == 0)    // swap top two elements
        swap();
    else if (strcmp(s, "clear") == 0)   // clear stack
        clear();
    // math functions
    else if (strcmp(s, "sin") == 0)
        push(sin(pop()));
    else if (strcmp(s, "exp") == 0)
        push(exp(pop()));
    else if (strcmp(s, "pow") == 0) {
        double d = pop();
        push(pow(pop(), d));
    }
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
void ungets(char s[]);

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
    // command or variable
    if (isalpha(c)) {   // collect command string
        s[i] = tolower(s[i]);
        while (isalpha(s[++i] = c = tolower(getch())))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        if (i == 1)
            return VARIABLE;
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

void ungets(char s[])   // push entire string onto the input
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    while (--i >= 0)
        ungetch(s[i]);
}
