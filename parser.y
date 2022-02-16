%{
  #include <stdio.h>
  #include <ctype.h>
  #include <unistd.h>

  #include "asa.h"
  #include "ts.h"

  extern int yylex();

%}

%union{
  int nb;
  struct asa * noeud;
  char id[64];
 };

%define parse.error verbose

%token NL VAR TQ FTQ FAIRE SI ALORS SINON FSI INFEGAL SUPEGAL DIFF AFFICHER NON INCR DECR NOM
%token ALGO ENTREE DEBUT FIN '(' ')'
%token <nb> NB
%token <id> ID 



%type <noeud> EXP EXPARI EXPBOOL INSTS INST LVAL LISTE

%left '+' '-' OU ADDFAST
%left '*' '/' ET
%right '%' AFFECT NON

%start PROG

%%

PROG : ALGO ID NL ENTREE LISTE NL DEBUT NL INSTS FIN  { codegen($9);printf("STOP\n"); }
| ALGO ID NL DEBUT NL INSTS FIN NL			{ codegen($6);printf("STOP\n"); }
| ALGO ID NL ENTREE LISTE NL DEBUT NL INSTS FIN NL    { codegen($9);printf("STOP\n"); }
;
LISTE : EXP { $$ = $1; }
| EXP LISTE 
;
INSTS: INST                { $$ = $1; }
| INST INSTS               { $$ = creer_noeudInst($1, $2); }


INST: 
| EXP NL                   { $$ = $1; }
| VAR LVAL NL              { $$ = creer_noeudDecla($2); } 
| VAR LVAL AFFECT EXP NL   { $$ = creer_noeudInst(creer_noeudDecla($2), creer_noeudAff($2, $4));} 
| LVAL AFFECT EXP NL       { $$ = creer_noeudAff($1, $3); } 
| VAR LVAL LVAL NL         { $$ = creer_noeudInst(creer_noeudDecla($2), creer_noeudDecla($3)); }
| TQ EXPBOOL FAIRE NL
  INSTS
FTQ NL                   { $$ = creer_noeudTantQue($2, $5); }
| SI EXPBOOL ALORS NL
  INSTS
SINON NL
  INSTS
FSI NL    { $$ = creer_noeudSi($2, $5, $8); }
| AFFICHER EXPARI NL       { $$ = creer_noeudAfficher($2); }
| AFFICHER EXPBOOL NL      { $$ = creer_noeudAfficher($2); }
;

LVAL: ID                { $$ = creer_feuilleId($1); }
| LVAL ID               { $$ = $1; }    
;

EXP: EXPARI                { $$ = creer_noeudExp($1); }
| EXPBOOL                  { $$ = creer_noeudExp($1); }
;

EXPARI : NB                { $$ = creer_feuilleNb($1); }
| ID                       { $$ = creer_feuilleId($1); }
| EXPARI '+' EXPARI        { $$ = creer_noeudOp('+', $1, $3); }
| EXPARI '-' EXPARI        { $$ = creer_noeudOp('-', $1, $3); }
| EXPARI '*' EXPARI        { $$ = creer_noeudOp('*', $1, $3); }
| EXPARI '/' EXPARI        { $$ = creer_noeudOp('/', $1, $3); }
| EXPARI '%' EXPARI        { $$ = creer_noeudOp('%', $1, $3); }
| EXPARI INCR              { $$ = creer_noeudIncr($1); }
| EXPARI DECR              { $$ = creer_noeudDecr($1); }
| '(' EXPARI ')'           { $$ = $2; }
;

EXPBOOL: EXPARI '<' EXPARI { $$ = creer_noeudOp('<', $1, $3); }
| EXPARI '>' EXPARI        { $$ = creer_noeudOp('>', $1, $3); }
| EXPARI '=' EXPARI        { $$ = creer_noeudOp('=', $1, $3); }
| EXPARI INFEGAL EXPARI    { $$ = creer_noeudOp('I', $1, $3); }
| EXPARI SUPEGAL EXPARI    { $$ = creer_noeudOp('S', $1, $3); }
| EXPARI DIFF EXPARI       { $$ = creer_noeudOp('D', $1, $3); }
| EXPBOOL ET EXPBOOL       { $$ = creer_noeudOp('&', $1, $3); }
| EXPBOOL OU EXPBOOL       { $$ = creer_noeudOp('|', $1, $3); }
| NON EXPBOOL              { $$ = creer_noeudNon($2); }
| '(' EXPBOOL ')'          { $$ = $2; }
;

%%

int main( int argc, char * argv[] ) {

  extern FILE *yyin, *yyout;
  if (argc == 1){
    fprintf(stderr, "aucun fichier fournie\n");
    return 1;
  }

  if (argc == 3){
    yyout = fopen(argv[2], "w");
  }
  else
    yyout = fopen("algo.ram", "w");

  yyin = fopen(argv[1], "r");
  dup2(fileno(yyout), 1);
  yyparse();
  fclose(yyout);
  fclose(yyin);

  return 0;
}
