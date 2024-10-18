# 🐚 Minishell - 42 Project

Bienvenue sur le repository de **Minishell**, un projet développé dans le cadre de la formation 42. Le but de ce projet est de recréer un shell basique, capable d'exécuter des commandes système tout en respectant le comportement attendu d'un véritable terminal Unix.

## À propos

**Minishell** est un projet de simulation de shell UNIX, qui permet d'approfondir les concepts de gestion des processus, de création d'environnements interactifs et de manipulation des signaux. Ce projet vous aidera à mieux comprendre le fonctionnement interne d'un shell, tout en vous initiant aux appels système Unix, à la gestion de la mémoire, et à la programmation en C.

Le programme est capable d'exécuter plusieurs types de commandes et de gérer les redirections, les pipes, les signaux et les variables d'environnement. C'est une version simplifiée mais fidèle d'un shell Unix.

## Fonctionnalités

Voici une liste des fonctionnalités principales de **Minishell** :

- Exécution des commandes Unix comme `ls`, `echo`, `cat`, `grep`, etc.
- Gestion des redirections (`>`, `>>`, `<`).
- Support des pipes (`|`).
- Gestion des variables d'environnement (`$ENV_VAR`).
- Signaux : `Ctrl+C`, `Ctrl+D`, et `Ctrl+\`.
- Commandes intégrées (builtins) :
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Gestion des erreurs avec des messages explicites.
- Support partiel des guillemets simples (`'`) et doubles (`"`).
  
## Installation

### Prérequis

- Un environnement Unix (Linux ou macOS).
- Un compilateur C (`gcc` ou équivalent).
- `make` pour la compilation.

### Étapes

1. Clonez ce repository :
   ```bash
   git clone https://github.com/votre-utilisateur/minishell.git
   cd minishell
   
2. Compilez avec make :
  ```bash
  make
  ```

3. Lancez le minishell :
  ```bash
   `./minishell
   ```

## Utilisation 

Une fois que vous avez lancé Minishell, vous pouvez entrer des commandes comme vous le feriez dans un shell classique. Par exemple :
```bash 
minishell> echo "Hello, World!"
Hello, World!
minishell> ls -l
total 8
-rwxr-xr-x  1 user  group  4096 Oct 18 10:00 minishell
minishell> export MY_VAR=42
minishell> echo $MY_VAR
42
minishell> exit
```

### Commandes intégrées
Voici quelques-unes des commandes internes que Minishell supporte : 
-  cd [directory] : Change le répertoire de travail.
-  pwd : Affiche le répertoire de travail courant.
-  export VAR=value : Exporte une nouvelle variable d'environnement.
-  unset VAR : Supprime une variable d'environnement.
- env : Affiche toutes les variables d'environnement.
- exit [status] : Ferme le shell avec un code de sortie optionnel.

### Redirections et pipes 

Redirigez la sortie d'une commande vers un fichier avec > ou >> (ajout).
Redirigez l'entrée d'une commande avec <.
Utilisez des pipes (|) pour enchaîner plusieurs commandes.

Exemple : 
```bash
minishell> cat file.txt | grep 42 | wc -l
```

## Contributeurs 

- Edouard Baillot
- Adrien Hors

Nous avons travaillé ensemble pour implémenter les différentes fonctionnalités du projet en respectant les contraintes du sujet.
