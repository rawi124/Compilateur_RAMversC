#ifndef ASA_H
#define ASA_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ts.h"

typedef enum {typeNb,
  typeOp,
  typeId,
  typeAffect,
  typeDecla,
  typeInst,
  typeTantQue,
  typeSi,
  typeExp,
  typeAffichage,
  typeNon,
  typeIncr,
  typeDecr,
} typeNoeud;

typedef struct {
  int val;
} feuilleNb;

typedef struct {
  char nom[64];
  char boo ;
} feuilleId;

typedef struct {
  char nom[64];
} feuilleEntre;

typedef struct{
  struct asa * noeud[1];
  int size;
} feuilleDecla;

typedef struct{
  struct asa* noeud[1];
}noeudDecla;



typedef struct{
  struct asa * noeud[2];
} noeudAff;

typedef struct {
  int ope;
  struct asa * noeud[2];
} noeudOp;

typedef struct {
  struct asa* noeud[2];
} noeudInst;

typedef struct{
  struct asa* noeud[2];
} noeudTantQue;

typedef struct{
  struct asa* noeud[3];
} noeudSi;

typedef struct{
  struct asa* noeud[1];
} noeudExp;

typedef struct{
  struct asa* noeud[1];
} noeudAffichage;

typedef struct{
  struct asa* noeud[1];
} noeudNon;

typedef struct{
  struct asa* noeud[1];
} noeudIncr;

typedef struct{
  struct asa* noeud[1];
} noeudDecr;

typedef struct{
  struct asa * noeud[2];
} noeudAddFast;

typedef struct asa{
  typeNoeud type;
  int ninst;

  union {
    feuilleNb nb;
    noeudOp op;

    noeudInst inst;

    feuilleId id;
    feuilleEntre entre ;

    noeudAff affect;

    noeudDecla decla;


    noeudTantQue tantque;

    noeudSi si;

    noeudExp exp;

    noeudAffichage affichage;


    noeudNon non;

    noeudIncr incr;

    noeudDecr decr;
  };
} asa;

// fonction d'erreur utilisée également par Bison
void yyerror(const char * s);

/*
  Les fonctions creer_<type> construise un noeud de l'arbre
  abstrait du type correspondant et renvoie un pointeur celui-ci
 */
asa * creer_feuilleNb( int value );
asa * creer_feuilleId(char* nom);
asa * creer_noeudOp( int ope, asa * p1, asa * p2 );
asa * creer_noeudInst(asa * p1, asa * p2);
asa * creer_noeudDecla(asa * p1);
asa * creer_noeudAff(asa * p1, asa * p2);
asa * creer_noeudTantQue(asa* p1, asa* p2);
asa * creer_noeudSi(asa* p1, asa* p2, asa* p3);
asa * creer_noeudExp(asa* p1);
asa * creer_noeudAfficher(asa * p1);
asa * creer_noeudNon(asa * p1);
asa * creer_noeudIncr(asa * p1);
asa * creer_noeudDecr(asa * p1);

void free_asa(asa *p);

// produit du code pour la machine RAM à partir de l'arbre abstrait
// ET de la table de symbole
void codegen(asa *p);

extern ts * tsymb;

#endif
