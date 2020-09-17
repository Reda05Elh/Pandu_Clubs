#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pandu_Clubs.h"

int main()
{
    srand(time(NULL));
    system("cls");
    printf("\tBienvenue dans le Pendu_Clubs !\n");
    printf("\n>> Tape Entrer pour lancer le jeu\n");
    getche();
    game();
    return 0;
}

void game(){

    system("cls");
    int i,coups = niveauDejeu();
    short nombreTotaldevies = coups;
    system("cls");
    char c, ClubSecret[20];
    modeDejeu(ClubSecret);

    system("cls");
    char *mot = NULL;
    int l = strlen(ClubSecret) + 1;
    mot = (char*) malloc( l * sizeof(char));
    memset(mot,0,l);
    for(i=0;i<l-1;i++){
        if (ClubSecret[i] == ' ') {
                mot[i]=' ';
                continue;}
        mot[i]='*';

    }

    do {
    system("cls");
    printf("Il vous reste %d coups a jouer\n",coups);
    printf("Quel est le Club secret ? %s\n",mot);
    printf("Proposez une lettre :");
    c = lireCaractere();

    for (i=0;i<l;i++){
        if (ClubSecret[i]==c){
            mot[i]=c;}}

    if (strchr(ClubSecret,c)== NULL) coups-=1;

    }while ((coups!=0) && (strchr(mot,'*') != NULL));

    system("cls");

    if (coups == 0){
        printf("\n>> Game Over\n");}
    else {
        printf("\n>> Bien joue vous l'avez trouve apres %d fautes \n",nombreTotaldevies-coups);}

    free(mot);
    while (getchar() != '\n') ;
    printf("\nREJOUEZ ? (y/n)");
    c = getche();
    switch(c){
    case 'y' : game();break;
    case 'n' : system("cls");printf("BYE !");break;
    default : main();
    }
}

void modeDejeu(char * ClubSecret){
    char c;
    int i;
    system("cls");
    printf(">> Choissisez le mode de jeu : \n");
    printf("1 - 1 Joueur\n");
    printf("2 - Multi Joueurs\n");
    printf("\nVotre choix");
    c = getche();
    system("cls");
    switch(c){
        case '1' : choix(ClubSecret);break;
        case '2' : printf("Le Club mystere : ");
                   fgets(ClubSecret,20,stdin);
                   ClubSecret[strcspn(ClubSecret, "\n")] = 0;
                   while (getchar() != '\n') ;


                   for(i=0;i<strlen(ClubSecret);i++){
                        ClubSecret[i] = toupper(ClubSecret[i]); // mettre le ClubSecret en majuscule
                   }

                   break;
        default  : modeDejeu(ClubSecret); break;

    }
}

int niveauDejeu(){
    char c;
    system("cls");
    printf(">> Choisissez un niveau \n\n");
    printf("1 : Niveau Facile (Nombre des vies = 20)\n");
    printf("2 : Niveau Moyen (Nombre des vies = 10)\n");
    printf("3 : Niveau difficile (Nombre des vies = 5)\n");
    printf("\nVotre choix :");
    c = getche();
    switch(c){
    case '1' : return 20;break;
    case '2' : return 10;break;
    case '3' : return 5;break;
    default : niveauDejeu();

    }
}

char lireCaractere()
{
    char caractere = 0;
    caractere = getchar();
    caractere = toupper(caractere);
    while (getchar() != '\n') ;
    return caractere;
}


void choix(char *ClubSecret){
    int x,i,n = 0 ;
    FILE* ptr = NULL;
    ptr = fopen("Clubs.txt","r");
    if (ptr != NULL){
        while(fgets(ClubSecret,20,ptr)!= NULL){
            ClubSecret[strcspn(ClubSecret, "\n")] = 0;
            n++; }

        if (n == 0){
            printf("\nVotre dictionnaire est vide!");
            exit(0);}

        rewind(ptr);
        x = rand()%n;
        for(i=0;i<x;i++){
        fgets(ClubSecret,20,ptr);
        ClubSecret[strcspn(ClubSecret, "\n")] = 0;
        }

        fclose(ptr);    }

    if (ptr == NULL){
        printf("\n Erreur : Dictionnaire introuvable \n");
        exit(0);
    }
}
