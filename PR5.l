%{
#include <stdio.h>
%}

KEYWORD    "int"|"float"|"char"|"return"|"if"|"else"|"while"|"for"|"void"
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
CONSTANT   [0-9]+(\.[0-9]+)?
STRING     \"([^\"\\]|\\.)*\"
PUNCTUATION [();,{}]
OPERATORS  [+\-*/=<>!]=?|&&|\|\|
COMMENT    \/\*([^*]|\*+[^\/])*\*+\/|\/\/.*

%%

{KEYWORD}      { printf("Keyword: %s\n", yytext); }
{IDENTIFIER}   { printf("Identifier: %s\n", yytext); }
{CONSTANT}     { printf("Constant: %s\n", yytext); }
{STRING}       { printf("String: %s\n", yytext); }
{PUNCTUATION}  { printf("Punctuation: %s\n", yytext); }
{OPERATORS}    { printf("Operator: %s\n", yytext); }
{COMMENT}      { printf("Comment detected\n"); }
[ \t\n]        { /* Ignore whitespace */ }
.              { printf("Lexical error: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

/*
steps to run this code
step 1) Install and setup win_flex_bison
step 2) win_flex -o lex.yy.c file_name.l
step 3) gcc lex.yy.c -o file_name.exe
step 4) Get-Content input.c | ./file_name.exe
*/
