#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100
#define BUFFSIZE 100

enum { NAME, PARENS, BRACKETS };
enum { FALSE, TRUE };

void dcl(void);
void dirdcl(void);
void paramdcl(void);
void specdcl(void);
int typespec(void);
int typequalifier(void);
void errmsg(char *);

int gettoken(void);
int tokentype;
int hasprevtoken = FALSE;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main(void) {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype == '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*';)
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            errmsg("missing )");
    } else if (tokentype == NAME) {
        if (name[0] == '\0')
            strcpy(name, token);
    } else
        hasprevtoken = TRUE;
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            strcat(out, " function expecting");
            paramdcl();
            strcat(out, " and returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

void paramdcl(void) {
    do
        specdcl();
    while (tokentype == ',');
    if (tokentype != ')')
        errmsg("missing ) in parameter declaration");
}

void specdcl(void) {
    char temp[MAXTOKEN];

    temp[0] = '\0';
    gettoken();
    do {
        if (tokentype != NAME) {
            hasprevtoken = TRUE;
            dcl();
        } else if (typespec() == TRUE || typequalifier() == TRUE) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else
            errmsg("unknown type in parameter list");
    } while (tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ",");
}

int typespec(void) {
    static char *types[] = {"char", "int", "long", "float", "double", "void"};
    int i;

    for (i = 0; i < sizeof(types) / sizeof(types[0]); i++)
        if (strcmp(types[i], token) == 0)
            return TRUE;
    return FALSE;
}

int typequalifier(void) {
    static char *qualifiers[] = {"const", "volatile"};
    int i;

    for (i = 0; i < sizeof(qualifiers) / sizeof(qualifiers[0]); i++)
        if (strcmp(qualifiers[i], token) == 0)
            return TRUE;
    return FALSE;
}

int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (hasprevtoken == TRUE) {
        hasprevtoken = FALSE;
        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

void errmsg(char *s) {
    printf("error: %s\n", s);
    hasprevtoken = TRUE;
}

int bufp = 0;
char buf[BUFFSIZE];

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
