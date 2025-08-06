%{
#include "parser.tab.h"
#include <string.h>
%}

%option noyywrap

%%

[ \t\n]+                  ;
"SELECT"                  return SELECT;
"FROM"                    return FROM;
"WHERE"                   return WHERE;
">"                       return GT;
"<"                       return LT;
"="                       return EQ;
","                       return COMMA;
";"                       return SEMICOLON;

\"([^\"\n]*)\"            { yylval.sval = strndup(yytext+1, yyleng-2); return STRING; }
\'([^\'\n]*)\'            { yylval.sval = strndup(yytext+1, yyleng-2); return STRING; }

[0-9]+                    { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_.]*   { yylval.sval = strdup(yytext); return IDENTIFIER; }

.                         return yytext[0];

%%
