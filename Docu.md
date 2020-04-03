# Documentation : "to do list" en C++

## Description

Le programme codé est une "to do list" qui permet de consigner différentes tâches à effectuer et d'assurer leur gestion.

## Guide d'emploi

### Démarrer avec la "to do list"

Tout simplement déposer le fichier .cpp dans un dossier vide.

### Attributs d'une tâche

Un tâche consignée dans la to-do list possède diférents attributs.
Sauf mention contraire indiquée en parenthèse, ces attributs sont modifiables.

```
TACHE    
|- ID                   # Identifiant unique de la tâche (non modifiable)
|- Titre                # Titre de la tâche
|- Description          # Description de la tâche
|- Dâte création        # Date de création de la tâche
|- Dâte de clôture      # Date à laquelle la tâche est terminée
|- Statut               # Active / Inactive / Complétée
|- % de réalisation     # Caractérise précisément l'avancement
|- Priorité             # Basse / Moyenne / Haute
|- Commentaire          # Commentaires
|- Sous-tâches          # IDs des sous-tâches ratâchées à la tâche
```

### Intéractions avec le programme

L'intéraction avec le programme se fait en mode "Command Line Interface".
Différentes fonctions peuvent être utilisées.

### Compilation

On considèrera que la compilation suivante a été effectuée :

```sh
g++ todolist.cpp -o todo
```

### Ajout d'une tâche

Il est possible d'ajouter une tâche à la to-do list. 
Cela est possible via la commande "add" dont la syntaxe est la suivante

```sh
./todo add --attribut_1 "attribut_1" ... --attributN "attribut_N"
```
où "--atribut_k" est un attribut de la tâche parmi :

```yml
Titre:        --title
Statut:       --status
Description:  --description
Priorite:     --priority
Commentaires: --commentaries
```
Les attributs peuvent être ajoutés dans un ordre quelconque !
De plus il n'est pas nécessaire de préciser tous les attributs ! Dans le cas où des attributs sont manquants ils seront complétés par leur valeur par défaut. Ainsi les commandes suivantes renvoient la même chose :

```sh
./todo add --title "acheter patates" --status "active" --priority "vitale" --description "tedlt" --commentaire "cool!"
```
```sh
./todo add --priority "vitale" --commentaire "cool!" --description "tedlt" --title "acheter patates" --status "active" 
```
Renvoient :
```sh
Vous avez créé :
1/acheter patates/tedlt/29032020/00000000/active/0/vitale/cool!/.
```
On remarque que la date du jour a été automatiquement ajoutée "29032020".
Ainsi que le pourcentage d'accomplissement de 0 & la date de cloture réglée sur "00000000" et "." qui correspond aux sous-tâches.

De même,
```sh
./todo add --priority "chill" --title "braquer banque" --status "inactif" 
```
Renvoie :
```sh
Vous avez créé :
1/braquer banque/./29032020/00000000/inactif/0/chill/./.
```
Les valeurs manquantes sont indiquées par un "."

### Afficher tâches
##### - Toutes :
On utilise simplement la commande : 
```sh
./toto list all
```
Qui renvoie par exemple : 
```sh
1/achat patate/féculent/29032020/00000000/active/0/high/ça va!/.
2/achat carotte/légume/29032020/00000000/active/0/low/oh/.
3/faire le marché/tedlt/03042020/00000000/active/0/high/ça va!/2&3
```
#### - Avec un filtre :

Il est possible de n'afficher les tâches qui remplissent une condition d'égalité sur un de leurs attributs. Par exemple celles telle que  priorité = élevée.

Pour cela on utilise :

```sh
./toto list --priority high
```

Autre exemple : 

```sh
./toto list --status "mis de côté"
```
## Editer une tâche 
La fonction edit permet d'éditer un attribut d'une tâche.

La syntaxe est : 
```sh
./todo "id de la tâche à modifier" --attribut_a_modifier "nouvelle valeur"
```
Par exemple pour les tâches : 

```sh
1/achat patate/féculent/29032020/00000000/active/0/high/ça va!/.
2/achat carotte/légume/29032020/00000000/active/0/low/oh/.
3/faire le marché/tedlt/03042020/00000000/active/0/high/ça va!/2&3
```
Alors si on éxécute :

```sh
./todo 2 --priority URGENTE
```
On obtient : 
```sh
1/achat patate/féculent/29032020/00000000/active/0/high/ça va!/.
2/achat carotte/légume/29032020/00000000/active/0/URGENTE/oh/.
3/faire le marché/tedlt/03042020/00000000/active/0/high/ça va!/2&3
```

## Avertissement de seg fault 
A mon regret, parfois l'ajout de la première tâche cause une segfault. 
Je conseille d'ajouter un premier caractère manuellement au fichier texte puis de sauter une ligne.