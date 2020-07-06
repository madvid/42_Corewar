# Projet Corewar:
auteurs: armajchr, mdavid, yaye, weilin

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

