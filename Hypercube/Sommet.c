#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Sommet.h"

int power(int base,int exponent){
    int res = 1;
    for(int i = 0; i < exponent;i++){
        res*= base;
    }
    return res;
}

Sommet returnBlankSommet(){
    Sommet s;
    s.etiquette = NULL;
    s.processus = NULL;
    return s;
}


void initPremierSommet(Sommet* s,int numberOfBits){
    /*
    s->processus = fork();
    if(s->processus < 0){
        fprintf(stderr,"Erreur init fork\n");
    }
    */
    
    s->etiquette = (char*) malloc(numberOfBits*sizeof(char));
    for(int i = 0; i < numberOfBits;i++){
        s->etiquette[i] = '0';
    }
}

void initSommetSuivant(Sommet* s, Sommet s2){
    initPremierSommet(s,strlen(s2.etiquette));
    int val = 0;
    //Conversion binaire en entier
    for(int i = 0,j = strlen(s2.etiquette)-1; i < strlen(s2.etiquette);i++,j--){
        val += power(2,i)* (s2.etiquette[j] - '0');
    }
    val++;
    //Conversion entier en binaire
    int x;
    for(int i = strlen(s->etiquette)-1;i >= 0; i--){
        x = power(2,i);
        if(x <= val ){
            val -= x;
            s->etiquette[i] = '1';
        }
    }
    
    //Inversion de la chaine de caractere binaire
    char temp;
    for(int i = 0, j = strlen(s->etiquette) - 1; i <= j;i++,j--){
        temp = s->etiquette[i];
        s->etiquette[i] = s->etiquette[j];
        s->etiquette[j] = temp;
    }
    
}

int estVoisin(Sommet s1, Sommet s2){
    int nbDifferences = 0;
    if(strcmp(s1.etiquette,s2.etiquette) == 0){
        return 0;
    }
    //printf("dans estVoisin : %s | %s\n",s1.etiquette,s2.etiquette);
    for(int i = 0; i < strlen(s1.etiquette);i++){
        if(s1.etiquette[i] != s2.etiquette[i]){
            nbDifferences++;    
        }
    }
    return nbDifferences <= 1;

}

int* voisinAdj (Sommet s1, Sommet *s, int sizeSommet,int *sizeTab) {
    *sizeTab = 0;
    for(int i = 0; i < sizeSommet; i++) {
        if(estVoisin(s1,s[i])) {
            (*sizeTab)++;
        }
    }

    int *tab = (int*) malloc(*sizeTab * sizeof(int));
    if(tab == NULL) {
        printf("Erreur lors de l'allocation memoire.\n");
        return NULL;
    }

    int j = 0;
    for(int i = 0; i < sizeSommet; i++) {
        if(estVoisin(s1,s[i])) {
            tab[j] = i;
            j++;
        }
    }

    return tab;
}