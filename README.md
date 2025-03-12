# Programmation Système

Ce projet contient plusieurs exercices et exemples de code démontrant divers mécanismes de programmation système en C. Les mécanismes abordés incluent la gestion des processus, la communication inter-processus (IPC) via les tubes (pipes), les sockets, les sémaphores, et la mémoire partagée.

## Structure du Projet

Le projet est organisé en plusieurs répertoires, chacun contenant des exercices et des exemples spécifiques :

- `Hypercube/`
- `Programmation_basique/`
- `Programmation_client_serveur/`
- `Programmation_fichier/`
- `Programmation_sémaphore/`
- `Programmation_tubes/`

## Mécanismes Système

### Gestion des Processus

Les fichiers suivants démontrent la création et la gestion des processus en utilisant `fork()`, `wait()`, et `exec()` :

- [Hypercube/Exercice1.c](Hypercube/Exercice1.c)
- [Hypercube/main.c](Hypercube/main.c)
- [Programmation_basique/Exercice1.c](Programmation_basique/Exercice1.c)
- [Programmation_basique/Ex2_1.c](Programmation_basique/Ex2_1.c)
- [Programmation_basique/Ex2_2.c](Programmation_basique/Ex2_2.c)

### Communication Inter-Processus (IPC)

#### Tubes (Pipes)

Les tubes sont utilisés pour la communication entre processus. Les exemples suivants montrent comment créer et utiliser des tubes :

- [Programmation_tubes/Exercice1.c](Programmation_tubes/Exercice1.c)
- [Programmation_tubes/Exercice2.c](Programmation_tubes/Exercice2.c)
- [Programmation_tubes/Exercice3.c](Programmation_tubes/Exercice3.c)

#### Sockets

Les sockets sont utilisées pour la communication réseau. Les exemples suivants montrent comment créer des clients et des serveurs utilisant des sockets TCP et UDP :

- [Programmation_client_serveur/client.c](Programmation_client_serveur/client.c)
- [Programmation_client_serveur/clientEx1.c](Programmation_client_serveur/clientEx1.c)
- [Programmation_client_serveur/clientEx2.c](Programmation_client_serveur/clientEx2.c)
- [Programmation_client_serveur/serveur.c](Programmation_client_serveur/serveur.c)
- [Programmation_client_serveur/serveurEx1.c](Programmation_client_serveur/serveurEx1.c)
- [Programmation_client_serveur/serveurEx2.c](Programmation_client_serveur/serveurEx2.c)

#### Sémaphores

Les sémaphores sont utilisés pour la synchronisation entre processus. Les exemples suivants montrent comment créer et utiliser des sémaphores :

- [Programmation_sémaphore/semaphore.c](Programmation_sémaphore/semaphore.c)
- [Programmation_sémaphore/processus1.c](Programmation_sémaphore/processus1.c)
- [Programmation_sémaphore/processus2.c](Programmation_sémaphore/processus2.c)
- [Programmation_sémaphore/Ex1_3.c](Programmation_sémaphore/Ex1_3.c)
- [Programmation_sémaphore/Ex1_3_1.c](Programmation_sémaphore/Ex1_3_1.c)
- [Programmation_sémaphore/Ex1_3_2.c](Programmation_sémaphore/Ex1_3_2.c)
- [Programmation_sémaphore/Ex2.c](Programmation_sémaphore/Ex2.c)
- [Programmation_sémaphore/Ex3_P.c](Programmation_sémaphore/Ex3_P.c)
- [Programmation_sémaphore/Ex3_Q.c](Programmation_sémaphore/Ex3_Q.c)

#### Mémoire Partagée

La mémoire partagée permet à plusieurs processus d'accéder à une même région de mémoire. Les exemples suivants montrent comment créer et utiliser la mémoire partagée :

- [Programmation_sémaphore/Exercice2.c](Programmation_sémaphore/Exercice2.c)
- [Programmation_sémaphore/Ex2.c](Programmation_sémaphore/Ex2.c)
- [Programmation_sémaphore/testEx2.c](Programmation_sémaphore/testEx2.c)

### Gestion des Fichiers

Les exemples suivants montrent comment manipuler des fichiers en C, y compris l'ouverture, la lecture, l'écriture et la fermeture de fichiers :

- [Programmation_fichier/Ex3_1.c](Programmation_fichier/Ex3_1.c)
- [Programmation_fichier/Ex3_2.c](Programmation_fichier/Ex3_2.c)
- [Programmation_fichier/Exercice4.c](Programmation_fichier/Exercice4.c)

## Compilation et Exécution

Pour compiler et exécuter les programmes, utilisez les commandes suivantes :

```sh
gcc -o <nom_executable> <nom_fichier.c>
./<nom_executable>
```

Par exemple, pour compiler et exécuter `Exercice1.c` dans le répertoire `Hypercube` :

```sh
gcc -o Exercice1 Hypercube/Exercice1.c
./Exercice1
```

## Conclusion

Ce projet couvre une variété de mécanismes de programmation système en C, offrant une base solide pour comprendre et utiliser ces techniques dans des applications réelles.
