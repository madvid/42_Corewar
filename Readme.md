# Projet Corewar:
auteurs: armajchr, mdavid, yaye

## Présentation du projet:
[source: pdf du sujet 42]
* Le Corewar est un jeu très particulier.
Il consiste à rassembler autour d’une "machine virtuelle" des "joueurs", lesquels vont y charger des "champions" qui vont se battre à l’aide de "processus", dans le but, entre autres, de faire en sorte qu’on dise d’eux qu’ils sont "en vie".

* Les processus s’exécutent séquentiellement au sein de la même machine virtuelle, et du même espace mémoire. Ils peuvent donc, entre autre chose, s’écrire les uns sur les autres afin de se corrompre mutuellement, de forcer les autres à exécuter des instructions qui leur font du mal, de tenter de recréer à la volée l’équivalent logiciel d’un Côtes du Rhône 1982, etc ...

* Le jeu se termine quand plus aucun processus n’est en vie. À ce moment là, legagnant est le dernier joueur à avoir été rapporté comme étant "en vie".

## Description d'ensemble:
[source: pdf du sujet 42]
Le projet consiste à rendre trois parties distinctes :
* L’assembleur: C’est le programme qui va compiler vos champions et les traduire du langage dans lequel vous allez les écrire (l’assembleur) vers un "bytecode", à savoir un code machine qui sera directement interprété par la machine virtuelle.
* La machine virtuelle: C’est l’"arène" dans laquelle les champions vont s’exécuter. Elle offre de nombreuses fonctionnalités, toutes utiles au combat des champions. Il va de soi qu’elle permet d’exécuter plusieurs processus en simultané ; on vous demande une arène, pas un simulateur de one-man show.
* Le champion: C’est un cas un peu particulier. Plus tard, pour le championnat, vous allez devoir rendre un champion si puissant et effrayant qu’il ferait trembler de peur un bocalien. Cependant, comme cela constitue en soi un travail conséquent, et que pour l’instant on est juste intéressés par votre capacité à réaliser les autres programmes du Corewar, et que votre champion du moment ne sert qu’à nous prouver que vous savez écrire des bouts d’ASM de Corewar, le champion à rendre dans le cadre de ce projet précis n’a besoin d’effrayer qu’un hérisson neurasthénique.

## Objectif(s) du document:
Ce document sert `a rassembler l'ensemble des réflexions de ses auteurs concernant le projet. Vous pourrez y trouver des explications concernant certains concepts, des pistes de compréhension et de réflexions.

### Fichier op.h:
Quelques explications concernant les macros définies dans le fichier ```op.h```:

#### **Taille des différents arguments:**
```C
#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE
```
```IND_SIZE```, ```REG_SIZE``` et ```DIR_SIZE``` correspond à la taille en byte des différents type d'éléments présent dans le fichier en bytecode (*.cor ou dans la zone mémoire de la VM) qui sont:
* les arguments de type indirect (2 bytes),
* les arguments de type direct (4 bytes),
* les registres (4 bytes).

---
#### Note sur bit, byte et octet:
Il faut distinguer c'est 3 objets, un bit est la plus petite unité mémoire qui peut avoir comme valeur **0** ou **1**, un byte est un ensemble de byte comme un octet. La différence entre un byte et un octet est que l'octet est obligatoirement un ensemble de **8 bits** alors que la définition d'un byte ne donne pas le nombre de bit le constituant *(à vérifier)*.

---
#### Remarque:
Attention, en se référant aux différents cheat sheet, on peut être confus en voyant que pour les registres on parle de 4 bytes et 1 byte.
Cela vient du fait que dans le fichier bytecode et dans la zone mémoire de la VM, le byte correspondant/faisant référence au registre est son adresse, et non pas le registre lui même. N'ayant que 16 registres à disposition pour chaque champion, il devient donc logique d'être en mesure de distinguer leurs adresses avec un seul byte uniquement.

---

#### **Taille des différents arguments:**
```C
#define REG_CODE				1
#define DIR_CODE				2
#define IND_CODE				3
```
Sachant que les paramètres d'un *opcode* (code d'opération en français ?) ne sont pas tous encodés sur le même nombre de bytes, il nous faut savoir *comment lire les bytes*.
Pour cela, après le byte décrivant l'opération, il y a un byte qui décrit le type des arguments de l'*opcode*:

|  Valeur binaire | Valeur décimale | type de l'argument  | taille en byte associé |
|:---------------:|:---------------:|:-------------------:|:----------------------:|
| 01 | 1 |  registre  |  1                   |
| 10 | 2 |  direct    |  4/2 (int/addresse)  |
| 11 | 3 |  indirect  |  2                   |

```REG_CODE```, ```DIR_CODE```, ```IND_CODE``` correspondent aux valeurs décimal des couples de bits dans le byte d'encoding.
En lisant chaque couple de bits dans le byte nous connaissons alors le type du premier, second et troisième paramètre de l'opcode.
Comme il n'y a qu'au maximum 3 arguments, le dernier couple de bits est donc non utilisé (et doit être donc **00**).

#### **Nombre maximum d'argument et de joueurs:**
```C
#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
```
* Commençons par  ```MAX_PLAYERS``` qui est le plus simple à expliquer: il spécifie que le nombre maximum de champion pouvant être présent dans l'arène (mémoire visible lors de l'affichage du champ de bataille) est de 4.
* Concernant ```MAX_ARGS_NUMBER``` [? **No information for the moment** ?].

#### **Taille de l'arène, modulo de l'index et taille maximale d'un champion:**
```C
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
```
* L'arène est la zone mémoire dans laquelle les codes des champions sont écrits/exécutés.
La taille de l'arène est définie par ```MEM_SIZE``` et est de 4096 octets.
* ```IDX_MOD``` définie ... .
* ```CHAMP_MAX_SIZE``` définie la taille maximale en octets de chaque champion, si le code du champion dépasse cette taille, c'est une erreur.

#### ** Caractères de spécification du type en assembleur:**
Au sein des fichiers en assembleur, on utilise différents caractères pour spécifier, au compilateur que nous créons, le type de données qui vient à la partie du code faisant l'analyse lexicale.
En d'autre mots, au sein de la ligne parsée, le ou les types des éléments sont spécifiés par des caractères précis.
```C
#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','
```
* ```COMMENT_CHAR``` précise que l'élément qui suit est un commentaire,
* ```LABEL_CHAR```  précise que l'élément qui suit est un label,
* ```DIRECT_CHAR``` précise que l'élément qui suit est un paramètre de type direct,
* ```SEPARATOR_CHAR``` précise que l'élément qui suit est un paramètre de type direct,

```C
#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"
```
```C
#define REG_NUMBER				16
```
```C
#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10
```
```C
typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8
```
```C
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
```
```C
typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;
```


### Partie VM:

#### Description du format des fichiers des champions [fichier].cor:
Le contenue d'un fichier correspondant à un champion est en bycode.
Ce fichier doit contenir une entête constituée:
* d'un nombre magique '0x ea 83 f3'. Comme nous pouvons le voir ce nombre magique
est constitué de 4 valeurs hexadécimales, chacunes des valeurs hexadécimales représentent 1 byte/octet, le nombre magique occupe donc 4 octets et donc 32 bits. 
* Un ensemble de 128 octets réservé pour le nom du champion.
* Un *padding* de 4 octets, qui ont comme valeur NULL,
* 4 octets donnant la taille (```CHP_SIZE```) du bytecode du champion (que l'on trouve en dernier).
* Un champ d'octets correspondant au commentaire d'une taille de 2048 octets.
* Un *padding* de 4 octets, devant être NULL,
* Un champ de ```CHP_SIZE``` octets.
Nous ne devons trouver rien d'autre à priori, le fichier doit donc être terminé après le code du champion.

### Brouillons:

#### Note sur l'ordre des champions:
cmiran 28 juin 2019 à 18 h 49
cela se traduit par, le joueur ayant le token le plus élevé commence et ainsi de suite jusqu’au token le plus bas, ou simplement le dernier joueur déclaré commence ?
3 réponses

cmiran  il y a un an
si jamais quelqu’un se pose la meme question..après investigation, et finalement la réponse est toute c*nne, la vm fournie place les champions en mémoire en fonction de l’ordre de déclaration, puis exécute de bas en haut :aussiereversecongaparrot:.
./a.out a.cor -n 1 b.cor -n 2 c.cor -n 3 d.cor
b<-c<-d<-a

ndelhomm:génie_homme:  il y a un an
@cmiran donc si tu as : ./a.out a.cor b.cor -n 1 c.cor d.cor
l'ordre sera b, a, c, d ?

cmiran  il y a un an
c <- a <- b <- d

## Bibliographie:
 1. https://docs.google.com/document/d/1DT_47inyTLDEUMevdmsA4jqr3_FXGvgKhzpGv_rtuOo/edit# | Corewar_Cheat_Sheet.pdf (dans le répertoire documentation)

