##############################################################
#						      		#
#              TP 8 I53 FLEX ET BISON	 	      		#
#        	algo ==> machine RAM                 		#
#								# 
##############################################################


dans ce mini-projet on se propose de creer un "compilateur" qui traduit
un programme ecrit en langage algorithmique vers le langage RAM
Ce compilateur est nommé arc, pour Algo-Ram-Compiler.

pour pouvoir mettre en marche notre compilateur on a utilisé FLEX et BISON 

FICHIER LEXER.LEX
--------------------------------------------------------------------------------
ce fichier permet d'effectuer une analyse lexicale du flux entrant 
a travers l analyse des règles et des actions .
 l'analyseur va tenter de satisfaire la premeière règle, la deuxième .. etc
 -------------------------------------------------------------------------------
 
Le fichier PARSER.Y
--------------------------------------------------------------------------------
le role de ce fichier est de faire une analyse syntaxique 
pour chaque type une action est faite et des caracteristiques sont fixes
comme associativite a gauche ou a droite , comme par exemple 
l operateur + est associatif a gauche 
--------------------------------------------------------------------------------

les fichiers asa.h et asa.c
--------------------------------------------------------------------------------
leurs roles  est de definir les fonctions specifiques pour chaque type detectes 
par le fichier parser.y
deux types existent bien evidamment : les feuilles et les noeud 
les id par exemple sont des feuilles ( c est des terminaux , comme les nombres aussi)

************************************CORPS DU PROGRAMME*************************************
la silhouette de base qui est acceptée est :
	ALGO ID 
	ENTREE VARIABLE
	DEBUT
	INSTRUCTIONS
	FIN 
	
	
	ou sans les ENTREE
	mais un algo sans le mot ALGO ou DEBUT ou fin n est jamais accepté ,
	 
***********************************OPTIMISATIONS********************************************


des optimisations ont ete faites : 
exemple au lieu de faire VAR A
			  A <- 5
	on peut faire directement VAR A <- 5
	et ceci grace a :VAR LVAL AFFECT EXP NL   { $$ = creer_noeudInst(creer_noeudDecla($2), creer_noeudAff($2, $4));}
aussi on peut declarer plusieurs variables dans le meme VAR X Y par exemple au lieu de VAR X VAR Y 





********************************TEST DU PROGRAMME ********************************

des exemples de code en langage algo sont fournis dans le dossier sous les noms :
Tq.algo Si.algo TQ.algo ARITH1.algo  SI.algo ARITH2.algo 

pour les tester il suffit juste d ecrire sur la ligne de commande : 
		make -B
		./arc le_nom_du_fichier_a_testé 
l algorithme ecrit en langage machine ram sera dans le fichier algo.ram 
		
	si vous voulez testez vos propres fichiers modifiez le fichier test.algo
	( un fichier vide vous pouvez ecrire les dedans les codes a tester )
	
*****************************************EXEMPLE DE PROGRAMME**************************************
premier exemple basique :

ALGO M
DEBUT 
10+9
FIN

produit : 
LOAD #9
STORE 1
LOAD #10
ADD 1
STOP

autre exemple basique : 

ALGO Arith
DEBUT
AFFICHER (3+5*(2+3)%5)/3
FIN

ceci produit :
LOAD #3
STORE 1
LOAD #5
STORE 2
LOAD #3
STORE 3
LOAD #2
ADD 3
MOD 2
STORE 2
LOAD #5
MUL 2
STORE 2
LOAD #3
ADD 2
DIV 1
WRITE
STOP

executé avec la machine ram sur le site on a bien affiché 1 

deuxieme exemple : 
ALGO Arith
DEBUT
VAR A B
A <- 5
B <- 10
VAR C <- A + B
AFFICHER  A
AFFICHER B
AFFICHER C
FIN

produit le code ram suivant : 


LOAD #5
STORE 34
LOAD #10
STORE 33
LOAD 33
STORE 1
LOAD 34
ADD 1
STORE 35
LOAD 34
WRITE
LOAD 33
WRITE
LOAD 35
WRITE
STOP

ce programme testé sur la machine RAM sur le site de Mr zanooti affiche bien
sur la bande de sortie  : 5 10 15 


3 eme exemple avec TQ :

ALGO tq
DEBUT
VAR hello
hello <- 10
TQ (hello > 0) FAIRE
  hello <- hello - 1
  AFFICHER hello
FTQ
FIN

on attend de ce programme d afficher 9 8 7 ..... 0

LOAD #10
STORE 33
LOAD #0
STORE 1
LOAD 33
SUB 1
JUMG 9
LOAD #0
JUMP 10
LOAD #1
JUMZ 19
LOAD #1
STORE 1
LOAD 33
SUB 1
STORE 33
LOAD 33
WRITE
JUMP 2
STOP
 
la simulation sur le site produit bien ceci 9 8 ...... 0 


autre exemple avec Si : 
ALGO Max
DEBUT 
VAR x <- 5
VAR y <- 7
SI ( x > y) ALORS
	AFFICHER x
SINON
	AFFICHER y
FSI
FIN


code ram :
LOAD #5
STORE 33
LOAD #7
STORE 34
LOAD 34
STORE 1
LOAD 33
SUB 1
JUMG 11
LOAD #0
JUMP 12
LOAD #1
JUMZ 14
LOAD 33
WRITE
JUMP 16
LOAD 34
WRITE
STOP



maintenant un exemple avec des entrees qui sont lus a partir de la bande d entree :
ALGO Arith
ENTREE X Y
DEBUT
VAR A B
A <- X
B <- Y
AFFICHER  A
AFFICHER B
FIN


READ
STORE 1
LOAD 1
STORE 34
READ
STORE 2
LOAD 2
STORE 33
LOAD 34
WRITE
LOAD 33
WRITE
STOP

affiche sur la bande de sortie 5 et 7 qui sont les valeurs de a et b 




















 
