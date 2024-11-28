# MARC_The_Rover_MNM

## Description
Ce programme simule les mouvements d'un rover sur une carte. Le rover doit atteindre une base en évitant les obstacles et en respectant les limites de la carte. Le programme permet de visualiser la carte, de lancer des séquences de mouvements aléatoires, et de tester des séquences de présentation.

## Fonctionnalités
1. Afficher la carte.
2. Lancer et afficher la sélection de mouvements aléatoires.
3. Afficher l'arbre complet des mouvements.
4. Lancer et visualiser la séquence de déplacement.
5. Séquences de présentation orale.

## Utilisation
### Menu Principal
Le programme affiche un menu principal avec les options suivantes :
- `1`: Afficher la carte.
- `2`: Lancer et afficher la sélection de mouvements aléatoires.
- `3`: Afficher l'arbre complet des mouvements.
- `4`: Lancer et visualiser la séquence de déplacement.
- `91`: Séquence de présentation orale no1.
- `92`: Séquence de présentation orale no2.
- `93`: Séquence de présentation orale no3.
- `0`: Sortie du programme.

### Afficher la carte
Sélectionnez l'option `1` pour afficher la carte actuelle.

### Lancer et afficher la sélection de mouvements aléatoires
Sélectionnez l'option `2` pour lancer une séquence de mouvements aléatoires et afficher les mouvements choisis ainsi que la position actuelle du rover après chaque mouvement.

### Afficher l'arbre complet des mouvements
Sélectionnez l'option `3` pour afficher l'arbre complet des mouvements. Notez que la taille de l'arbre peut être conséquente.

### Lancer et visualiser la séquence de déplacement
Sélectionnez l'option `4` pour lancer et visualiser la séquence de déplacement du rover.

### Séquences de présentation orale
Sélectionnez les options `91`, `92`, ou `93` pour tester des séquences spécifiques utilisées pour des présentations orales.

## Structure du Code
### Fichiers Principaux
- `main.c`: Contient la fonction principale et le menu.
- `moves.c`: Contient les fonctions de gestion des mouvements du rover.
- `map.c`: Contient les fonctions de gestion de la carte.
- `tree_node.c`: Contient les fonctions de gestion des nœuds et de l'arbre.

### Fonctions Clés
- `chooseMovements`: Sélectionne et applique des mouvements aléatoires pour le rover.
- `displayMap`: Affiche la carte actuelle.
- `displayMapWithRover`: Affiche la carte avec la position actuelle du rover.
- `createMapFromFile`: Crée une carte à partir d'un fichier.
- `createTreeFromMap`: Crée un arbre de mouvements à partir de la carte.

## Compilation et Exécution
Pour compiler et exécuter le programme, utilisez les commandes suivantes :

```sh
gcc -o rover main.c moves.c map.c tree_node.c
./rover