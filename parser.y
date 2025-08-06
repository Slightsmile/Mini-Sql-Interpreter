%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_utils.h"

void yyerror(const char *s);
int yylex(void);
%}

%union {
    char *sval;
    int  ival;
}

%token SELECT FROM WHERE
%token GT LT EQ
%token COMMA SEMICOLON
%token <sval> IDENTIFIER STRING
%token <ival> NUMBER

%type <sval> query column_list where_clause condition

%%

query:
    SELECT column_list FROM IDENTIFIER where_clause SEMICOLON {
        execute_query($2, $4, $5);
    }
;

column_list:
    IDENTIFIER {
        $$ = strdup($1);
    }
    | column_list COMMA IDENTIFIER {
        char *tmp = malloc(strlen($1)+strlen($3)+2);
        sprintf(tmp, "%s,%s", $1, $3);
        $$ = tmp;
    }
;

where_clause:
    /* empty */ { $$ = NULL; }
    | WHERE condition { $$ = $2; }
;

condition:
    IDENTIFIER GT NUMBER {
        char *tmp = malloc(strlen($1)+20);
        sprintf(tmp, "%s>%d", $1, $3);
        $$ = tmp;
    }
    | IDENTIFIER LT NUMBER {
        char *tmp = malloc(strlen($1)+20);
        sprintf(tmp, "%s<%d", $1, $3);
        $$ = tmp;
    }
    | IDENTIFIER EQ NUMBER {
        char *tmp = malloc(strlen($1)+20);
        sprintf(tmp, "%s=%d", $1, $3);
        $$ = tmp;
    }
    | IDENTIFIER EQ STRING {
        char *tmp = malloc(strlen($1)+strlen($3)+5);
        sprintf(tmp, "%s=%s", $1, $3);
        $$ = tmp;
    }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
