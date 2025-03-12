#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>

#define MAX_FILENAME 256
#define MAX_TIME 64

// Fonction pour extraire l'heure d'un fichier
time_t extract_time_from_file(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if(fd == -1) {
        perror("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    char buffer[1024]; // Tampon pour lire le fichier
    ssize_t bytes_read = read(fd,buffer,sizeof(buffer) - 1); //Lis le contenu du fichier
    if(bytes_read <= 0) {
        perror("Erreur lors de la lecture du fichier\n");
        close(fd);
        exit(1);
    }

    buffer[bytes_read] = "\0"; //S'assure que le tampon est bien terminé par un 0
    close(fd);

    //Cherche la chaine "Date systeme : " dans le fichier
    char *time_str = strstr(buffer,"Date systeme : ");
    if(!time_str) {
        exit(1);
    }

    //Extrait l'heure en temps que time_t
    time_t file_time = atol(time_str);
    return file_time;
}

//Fonction pour compter les occurences d'une heure donnée dans un répertoire
void count_processes_by_time(const char* directory) {
    DIR* dir;
    struct dirent *entry;
    struct tm *time_info;
    char time_string[MAX_TIME];
    time_t file_time;
    char filepath[MAX_FILENAME];

    //Table de hashage simple pour compter le nombre de processus par heure
    unsigned int time_counts[24] = {0}; // Pour stocker les comptes par heure

    //Ouvrir le répertoire
    dir = opendir(directory);
    if(dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        exit(1);
    }

    //Parcourir les fichiers du répertoire
    while((entry = readdir(dir)) != NULL) {
        //Ignorer les répertoires . etc ..
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name,"..") == 0) {
            continue;
        }

        //Construire le chemin complet du fichier
        snprintf(filepath,sizeof(filepath), "%s%s",directory, entry->d_name);

        //Extraire l'heure système du fichier
        file_time = extract_time_from_file(filepath);
        if(file_time == -1) {
            continue;
        }

        //Incrémenter le compteur pour l'heure spécifique
        time_counts[time_info->tm_hour]++;
    }
    closedir(dir);

    //Afficher les résultats : nombre de processus par heure 
    printf("Nombre de processus par heure système : \n");
    for(int i = 0; i < 24; i++) {
        if(time_counts[i] > 0) {
            printf("Heure %02d:00 : %u processus\n",i,time_counts[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage : %s <repertoire>\n", argv[0]);
        exit(1);
    }

    //Compter les processus par heure dans le répertoire donné
    count_processes_by_time(argv[1]);
    exit(0);
}