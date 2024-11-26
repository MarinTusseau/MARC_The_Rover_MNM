# MARC_The_Rover_MNM
# Malo GAVARD Noé MILLEREUX Marin TUSSEAU

## BUGS NOTABLES  

- **Segmentation Faults (SegFaults)** : Dans certaines situations, il peut y avoir une erreur liée à un accès mémoire incorrect. Ces erreurs sont souvent dues à une mauvaise allocation ou gestion dynamique des données (notamment dans les arbres ou les files d'attente).  
- **Gestion de la mémoire** : Si la mémoire n’est pas correctement libérée (notamment lors de la suppression de l'arbre), cela peut entraîner une fuite de mémoire.  
- **Arbre de recherche** : Les chemins minimaux ne sont parfois pas corrects si les paramètres d'entrée ou les coûts ne sont pas bien définis.  

## Précautions à prendre avant d'utiliser le programme  

1. Assurez-vous que toutes les structures de données (map, tree, stack, queue) sont correctement initialisées.  
2. Vérifiez les fichiers d’entrée (ex. `map`) pour qu’ils soient cohérents (pas de dépassement de limites dans les coordonnées).  

---

## Fonctions Principales  

### Structures Générales  

- **Création des Files**  
  - **Fonction** : `createQueue(int size)`  
  - **Utilisation** : Initialise une file de taille donnée.  

  - **Fonction** : `enqueue(t_queue *p_queue, t_position pos)`  
  - **Utilisation** : Ajoute un élément à la fin de la file.  

  - **Fonction** : `dequeue(t_queue *p_queue)`  
  - **Utilisation** : Retire et retourne le premier élément de la file.  

- **Création des Piles**  
  - **Fonction** : `createStack(int size)`  
  - **Utilisation** : Initialise une pile de taille donnée.  

  - **Fonction** : `push(t_stack *p_stack, int value)`  
  - **Utilisation** : Ajoute une valeur au sommet de la pile.  

  - **Fonction** : `pop(t_stack *p_stack)`  
  - **Utilisation** : Retire et retourne la valeur au sommet de la pile.  

### Gestion des Mouvements  

- **Conversion en texte**  
  - **Fonction** : `getMoveAsString(t_move move)`  
  - **Utilisation** : Retourne la chaîne correspondant à un mouvement donné.  

- **Déplacement du robot**  
  - **Fonction** : `move(t_localisation loc, t_move move)`  
  - **Utilisation** : Calcule la nouvelle localisation après un déplacement.  

  - **Fonction** : `updateLocalisation(t_localisation *p_loc, t_move m)`  
  - **Utilisation** : Met à jour la localisation actuelle du robot après un déplacement.  

- **Choix aléatoire des mouvements**  
  - **Fonction** : `chooseMovements(Dispo *dispo, t_move choice[], int nbChoice, unsigned int seed, t_map map, t_localisation loc)`  
  - **Utilisation** : Génère une séquence de mouvements aléatoires tout en mettant à jour les disponibilités.  

### Manipulation des Arbres  

- **Création d'un noeud/arbre**  
  - **Fonction** : `createNode(int value)`  
  - **Utilisation** : Crée un nœud avec une valeur et initialise ses paramètres.  

  - **Fonction** : `createTree(p_node root)`  
  - **Utilisation** : Crée un arbre à partir d’un nœud racine.  

- **Ajout d'un fils à un nœud**  
  - **Fonction** : `addChild(p_node parent, p_node child)`  
  - **Utilisation** : Ajoute un enfant au nœud parent.  

- **Parcours d’un arbre**  
  - **Fonction** : `displayTree(p_node node, int level)`  
  - **Utilisation** : Affiche l’arbre récursivement, avec des indentations par niveau.  

- **Recherche du chemin minimal**  
  - **Fonction** : `findMinPath(p_node node, int currentSum)`  
  - **Utilisation** : Calcule la somme minimale pour atteindre un nœud de base dans l’arbre.  

- **Construction de l’arbre à partir d’une carte**  
  - **Fonction** : `buildTreeFromMap(p_node currentNode, t_map map, t_localisation *loc, t_move *remainingMoves, int nb_moves)`  
  - **Utilisation** : Construit un arbre représentant les chemins possibles en fonction des mouvements restants et de la carte.  

  - **Fonction** : `createTreeFromMap(p_node currentNode, t_map map, t_localisation *loc, t_move *remainingMoves, int nb_moves)`  
  - **Utilisation** : Initialise et génère un arbre complet basé sur une carte donnée.  

- **Libération de mémoire d’un arbre**  
  - **Fonction** : `freeTree(p_node node)`  
  - **Utilisation** : Libère la mémoire associée à un arbre et ses enfants.  

---

## Fonctionnalités Clés  

- Génération d’un arbre pour modéliser les mouvements possibles sur une carte avec des coûts.  
- Parcours de cet arbre pour trouver les chemins les moins coûteux.  
- Simulation des déplacements d’un robot dans un environnement en deux dimensions.  
- Gestion efficace des structures de données (pile, file, arbre) pour optimiser les calculs.  

---

## Notes  

- Le programme est conçu pour être modulaire et peut facilement s’adapter à d’autres types de cartes ou mouvements.  
- Attention aux dépassements de limites et à la gestion dynamique des structures pour éviter les bugs critiques.  


