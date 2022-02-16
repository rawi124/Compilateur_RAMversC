#include "asa.h"

static int pile = 1;
static int ligneno = 0;


asa * creer_feuilleNb(int val)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeNb;
  p->nb.val = val;
  return p;
}

asa * creer_feuilleId(char* nom){
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeId;
  strcpy(p->id.nom, nom);

  return p;
}

asa * creer_feuilleID(char* nom)
{
  ts_ajouter_id(nom, 2);
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeId;
  strcpy(p->id.nom, nom);

  return p;
}


asa * creer_noeudOp( int ope, asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeOp;
  p->op.ope = ope;
  p->op.noeud[0]=p1;
  p->op.noeud[1]=p2;
  p->ninst = p1->ninst+p2->ninst+3;

  return p;
}

asa * creer_noeudInst(asa * p1, asa * p2)
{
  asa * p;
  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeInst;
  p->inst.noeud[0]=p1;
  p->inst.noeud[1]=p2;
  p->ninst = p1->ninst+p2->ninst+2;

  return p;
}


asa * creer_noeudDecla(asa* p1){

  ts_ajouter_id(p1->id.nom, 1);
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeDecla;
  p->decla.noeud[0]=p1;
  p->ninst = 0;

  return p;
}

asa * creer_noeudAff(asa * p1, asa * p2){
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeAffect;
  p->affect.noeud[0]=p1;
  p->affect.noeud[1]=p2;
  p->ninst = p->affect.noeud[1]->ninst + 1;

  return p;
}

asa * creer_noeudTantQue(asa * p1, asa * p2){
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeTantQue;
  p->tantque.noeud[0]=p1;
  p->tantque.noeud[1]=p2;
  p->ninst = p->tantque.noeud[0]->ninst+ p->tantque.noeud[1]->ninst+3;

  return p;
}

asa* creer_noeudSi(asa* p1, asa* p2, asa* p3){
  asa* p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeSi;
  p->si.noeud[0] = p1;
  p->si.noeud[1] = p2;
  p->si.noeud[2] = p3;

  p->ninst = p1->ninst + p2->ninst + p3->ninst + 5;
  return p;
}

asa* creer_noeudExp(asa* p1){
  asa* p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeExp;
  p->exp.noeud[0] = p1;
  p->ninst = p1->ninst+1;

  return p;
}

asa * creer_noeudAfficher(asa * p1){
  asa* p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeAffichage;
  p->affichage.noeud[0] = p1;
  p->ninst = p1->ninst;

  return p;

}


asa * creer_noeudNon(asa * p1){
  asa* p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeNon;
  p->non.noeud[0] = p1;
  p->ninst = p1->ninst + 3;

  return p;
}

asa * creer_noeudIncr(asa * p1){
  asa* p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeIncr;
  p->incr.noeud[0] = p1;
  p->ninst = p1->ninst;

  return p;
}

asa * creer_noeudDecr(asa * p1){
  asa* p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeDecr;
  p->incr.noeud[0] = p1;
  p->ninst = p1->ninst;

  return p;
}


void free_asa(asa *p)
{
  if (!p) return;
  switch (p->type) {
    case typeOp:
      free_asa(p->op.noeud[0]);
      free_asa(p->op.noeud[1]);
      break;
    case typeInst:
      free_asa(p->inst.noeud[0]);
      free_asa(p->inst.noeud[1]);
      break;
    case typeAffect:
      free_asa(p->affect.noeud[0]);
      free_asa(p->affect.noeud[1]);
      break;
    case typeTantQue:
      free_asa(p->tantque.noeud[0]);
      free_asa(p->tantque.noeud[1]);
      break;
    case typeSi:
      free_asa(p->si.noeud[0]);
      free_asa(p->si.noeud[1]);
      free_asa(p->si.noeud[2]);
      break;
    case typeDecla:
      free_asa(p->decla.noeud[0]);
      break;
    case typeExp:
      free_asa(p->exp.noeud[0]);
      break;
    case typeAffichage:
      free_asa(p->affichage.noeud[0]);
      break;
    case typeNon:
      free_asa(p->non.noeud[0]);
      break;
    case typeIncr:
      free_asa(p->incr.noeud[0]);
      break;
    case typeDecr:
      free_asa(p->decr.noeud[0]);
      break;
    default: break;
  }
  free(p);
}


void codegen(asa *p)
{
  int ret;
  ts* pts;
  if (!p) return;
  switch(p->type) {

    case typeNb:
      printf("LOAD #%d\n", p->nb.val);
      ligneno++;
      break;

    case typeId:
      if ((pts = ts_retrouver_id(p->id.nom)) == 0){
          ts_ajouter_id(p->id.nom, 2);
          printf("READ\n");
          printf("STORE %d\n",pile);
          printf("LOAD %d\n",pile);
          pile++;
      ligneno++;
      }
      else
      {
      	printf("LOAD %d\n", pts->adr);
      ligneno++;}
      break;

    case typeDecla:
      break;

    case typeExp:
      codegen(p->exp.noeud[0]);
      break;

    case typeTantQue:
      ret = ligneno;
      codegen(p->tantque.noeud[0]);
      printf("JUMZ %d\n", ligneno + p->tantque.noeud[1]->ninst + 2);
      ligneno++;
      codegen(p->tantque.noeud[1]);
      printf("JUMP %d\n", ret);
      ligneno++;
      break;

    case typeSi:
      codegen(p->si.noeud[0]);
      printf("JUMZ %d\n", ligneno + p->si.noeud[1]->ninst + 2);
      ligneno++;
      codegen(p->si.noeud[1]);
      printf("JUMP %d\n", ligneno + p->si.noeud[2]->ninst + 1);
      ligneno++;
      codegen(p->si.noeud[2]);
      break;

    case typeAffect:
      codegen(p->affect.noeud[1]);
      if ((pts = ts_retrouver_id(p->affect.noeud[0]->id.nom)) == 0){
        fprintf(stderr, "Variable %s introuvable.\n", p->affect.noeud[0]->id.nom);
        exit(1);
      }
      printf("STORE %d\n", pts->adr);
      ligneno++;
      break;

    case typeInst:
      codegen(p->inst.noeud[0]);
      codegen(p->inst.noeud[1]);
      break;

    case typeAffichage:
      codegen(p->inst.noeud[0]);
      printf("WRITE\n");
      ligneno++;
      break;


    case typeNon:
      codegen(p->inst.noeud[0]);
      printf("JUMZ %d\nLOAD #0\n", ligneno + 3);
      printf("JUMP %d\nLOAD #1\n", ligneno + 4);
      ligneno += 4;
      break;

    case typeIncr:
      codegen(p->inst.noeud[0]);
      pts = ts_retrouver_id(p->incr.noeud[0]->id.nom);
      if (pts){
        printf("ADD #1\n");
        printf("STORE %d\n", pts->adr);
        ligneno += 4;
      }else{
        yyerror("ERREUR: Variabel inconnu\n");
      }
      break;

    case typeDecr:
      codegen(p->inst.noeud[0]);
      pts = ts_retrouver_id(p->decr.noeud[0]->id.nom);
      if (pts){
        printf("SUB #1\n");
        printf("STORE %d\n", pts->adr);
        ligneno += 4;
      }else{
        yyerror("ERREUR: Variabel inconnu\n");
      }
      break;

    case typeOp:
      codegen(p->op.noeud[1]);
      printf("STORE %d\n", pile++);
      ligneno++;
      codegen(p->op.noeud[0]);

      switch(p->op.ope){
        case '+':
          printf("ADD %d\n", --pile); // On dépile puis on utilise la case mémoire
          ligneno++;
          break;
        case '-':
          printf("SUB %d\n", --pile);
          ligneno++;
          break;
        case '*':
          printf("MUL %d\n", --pile);
          ligneno++;
          break;
        case '/':
          printf("DIV %d\n", --pile);
          ligneno++;
          break;
        case '%':
          printf("MOD %d\n", --pile);
          ligneno++;
          break;
        case '<':
          printf("SUB %d\n", --pile);
          printf("JUML %d\nLOAD #0\n", ligneno + 4);
          printf("JUMP %d\nLOAD #1\n", ligneno + 5);
          ligneno += 5;
          break;
        case '>':
          printf("SUB %d\n", --pile);
          printf("JUMG %d\nLOAD #0\n", ligneno + 4);
          printf("JUMP %d\nLOAD #1\n", ligneno + 5);
          ligneno += 5;
          break;
        case '=':
          printf("SUB %d\n", --pile);
          printf("JUMZ %d\nLOAD #0\n", ligneno + 4);
          printf("JUMP %d\nLOAD #1\n", ligneno + 5);
          ligneno += 5;
          break;
        case 'I': // <=
          printf("SUB %d\n", --pile);
          printf("JUML %d\n", ligneno + 5);
          printf("JUMZ %d\nLOAD #1\n", ligneno + 6);
          printf("LOAD #0\n");
          ligneno += 5;
          break;
        case 'S': // >=
          printf("SUB %d\n", --pile);
          printf("JUMG %d\n", ligneno + 5);
          printf("JUMZ %d\nLOAD #1\n", ligneno + 6);
          printf("LOAD #0\n");
          ligneno += 5;
          break;
        case 'D': // !=
          printf("SUB %d\n", --pile);
          printf("JUMG %d\n", ligneno + 5);
          printf("JUML %d\nLOAD #1\n", ligneno + 6);
          printf("LOAD #0\n");
          ligneno += 5;
          break;
        case '&': // ET
          printf("JUMZ %d\n", ligneno + 2);
          printf("LOAD %d\n", --pile);
          ligneno += 2;
          break;
        case '|':
          printf("JUMG %d\n", ligneno + 2);
          printf("LOAD %d\n", --pile);
          ligneno += 2;
          break;
      }
      break;
  default:
    break;
  }

}



void yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  exit(0);
}
