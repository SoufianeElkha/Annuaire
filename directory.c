/*
    SoufianeElkha

*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif 


#include "commandes.h"
#include "hash.h"

#define DICTIONARY_SIZE 1000
#define SIZE 50

char *mot_de_passe;
char *commande;
char *data;
char *numero;

int main(){

    hm_t *dictionary = hm_create(DICTIONARY_SIZE);
    hm_t *user = hm_create(DICTIONARY_SIZE);
    hm_import(dictionary, "data.txt");
    hm_import(user, "passwd.txt");

    char* buffer = malloc(100*sizeof(char));
    char* admin_or_guest = malloc(SIZE*sizeof(char));
    char* password = malloc(SIZE*sizeof(char));
    printf("> username: ");

    fgets(admin_or_guest,SIZE,stdin);
    char *username = strtok(admin_or_guest,"\n");

//Mode visiteur pour Guest comme nom d’utilisateur
    if (str_cmp(username, guest, guest1) ==0){
        printf("Vous êtes connecté en mode visiteur");
        visit(username);
        fgets(buffer,SIZE,stdin);


        //jusqu’à ce que j’exécute le commandement Quit
        while(str_cmp(buffer, quit, quit1)!= 0){

            //division du texte buffer
            commande = strtok(buffer," ");
            data = strtok(NULL,":");
            numero = strtok(NULL,"\n");
            commande_inconnue(commande);
            cmd_show_name(dictionary,commande,data);    //Consulter le numéro d'une personne
            cmd_show(dictionary,commande,data);         //Afficher tout l'annuaire

            visit(username);
			fgets(buffer,50,stdin);
        }//END WHILE

		fflush(stdin);
    }
	
//Mode visiteur pour Administrateur comme nom d’utilisateur

    if (hm_get(user,username) != NULL){

        //Caché le mot de pass
        struct termios original,noecho;
        //obtenir la configuration actuelle du terminal
        tcgetattr(STDIN_FILENO,&original);
        //dupliquer
        noecho = original;
        //désactiver le duplex intégral
        noecho.c_lflag = noecho.c_lflag ^ ECHO;
        //régler le terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &noecho);
        //demande et saisie du mot de passe
        printf("> password: ");
        fgets(password,SIZE,stdin);
        mot_de_passe = strtok(password,"\n");

        //restaurer les paramètres du terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &original);


        //hachage du mot de passe
        int hashed = 0;
        static char result[SIZE];
        for (int i = 0; mot_de_passe[i] != '\0'; i++) 
            hashed = (43 * hashed + mot_de_passe[i]) % 5060;
        sprintf(result, "%d", hashed); //convertir entier en char
        
        if (strcmp(hm_get(user,username),result)==0) {
            printf("\nVous êtes connecté en mode Administrateur\n");
        }else{
            printf("Erreur : mot de passe incorrect!\nSORTIE\n\n");
            exit(0);
        }
        visit(username);
		fgets(buffer,50,stdin);

		//jusqu’à ce que j’exécute le commandement Quit
        while(str_cmp(buffer, quit, quit1)!= 0)
        {
            //division du texte buffer
            commande = strtok(buffer," ");
            data = strtok(NULL,":");
            numero = strtok(NULL,"\n");

            commande_inconnue(commande);
            cmd_passwd(user,commande,username);         //Change le mot de pass de l'utilisateur courant
            cmd_add(dictionary,commande,data,numero);   //Ajouter pu éditer une entrée de l'annuaire
            cmd_show_name(dictionary,commande,data);    //Consulter le numéro d'une personne
            cmd_show(dictionary,commande,data);         //Afficher tout l'annuaire
            cmd_useradd(user,commande,data);            //Ajouter un administrateur au système
            cmd_del(dictionary,commande,data);          //Effacer une entrée de l'annuaire
            cmd_userdel(user,commande,username);        //Supprime l'utilisateur courant
            cmd_save(dictionary,commande);              //Sauvegarde létat de l'annuaire dans une fichier texte

            visit(username);
            fgets(buffer,50,stdin);
            
        }//END ADMINISTRATOR

    quit_save(dictionary);
	
    }//END WHILE

//free malloc
free(buffer);
free(admin_or_guest);
free(password);
//free table de hash pour dictionary et user
hm_destroy(&dictionary);
hm_destroy(&user);
fflush(stdin);
printf("\nEXIT\n");
    
exit(0);
}
