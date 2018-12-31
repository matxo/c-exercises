/*
Exercise 4-10. An alternate organization uses getline to read an entire input
line; this makes getch and ungetch unnecessary. Revise the calculator to use
this approach.

matxo
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>     // for atof()
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
void execute_cmd(char s[])
{
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
#define BUFFER_LINE 1000
char line[BUFFER_LINE];
int i, get_line(char s[], int lim);

// getop: get next character or numeric operand
int getop(char s[])
{
    int j = 0;
    while (true) {
        if (line[i] == '\0') {
             if (get_line(line, BUFFER_LINE) <= 0)
                return EOF;
            i = 0;
        } else {
            // skip blanks
            while (isblank(line[i]))
                i++;
            // number
            if ((line[i] == '+' || line[i] == '-') &&
                (isdigit(line[i+1]) || line[i+1] == '.'))
            {
                s[j++] = line[i++];
            }
            while (isdigit(line[i]))        // collect integer part
                s[j++] = line[i++];
            if (line[i] == '.') {
                s[j++] = line[i++];
                while (isdigit(line[i]))    // collect fraction part
                    s[j++] = line[i++];
            }
            if (j != 0) {
                s[j] = '\0';
                return NUMBER;
            }
            // command or variable
            while (isalpha(line[i]))
                s[j++] = line[i++];
            if (j != 0) {
                s[j] = '\0';
                if (j == 1)
                    return VARIABLE;
                return COMMAND;
            }
            // operator
            return line[i++];
        }
    }
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
