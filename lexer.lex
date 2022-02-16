%{
#include <string.h>
#include "parser.h"
%}

%option nounput
%option noinput

CHIFFRE  (0|[0-9][0-9]*)
ID  [a-zA-Z][a-zA-Z0-9]*
COMMENTAIRE [#].*\n


%%
{COMMENTAIRE}
DEBUT         { return DEBUT; }
ALGO          { return ALGO; }
FIN           { return FIN; }
ENTREE        { return ENTREE; }
SI            { return SI; }
ALORS         { return ALORS; }
SINON         { return SINON; }
FSI           { return FSI; }
TQ            { return TQ; }
FAIRE         { return FAIRE; }
FTQ           { return FTQ; }
"<"           { return yytext[0]; }
">"           { return yytext[0]; }
"="           { return yytext[0]; }
"<="          { return INFEGAL; }
">="          { return SUPEGAL; }
"!="          { return DIFF; }
"++"          { return INCR; }
"--"          { return DECR; }
"ET"          { return ET; }
"OU"          { return OU; }
"NON"         { return NON; }
"AFFICHER"    { return AFFICHER; }
","           { return yytext[0]; }
VAR           { return VAR; }
[)(%*/+-]     { return yytext[0];}
"<-"          { return AFFECT; }
[\n]          { return NL; }
{ID}          { strcpy(yylval.id, yytext); return ID; }
{CHIFFRE}     { yylval.nb = atoi(yytext); return NB; }
"-"{CHIFFRE}  { yylval.nb = atoi(yytext); return NB; }
[ \t]         {}
.             { fprintf(stderr, "[err lexer] caractere inconnu %c\n",yytext[0]); return 1;}

%%
