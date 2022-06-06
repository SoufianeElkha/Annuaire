#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commandes.h"
#include "hash.h"


//Print le nom
void visit(char* address){
    printf("\n%s>", address);
}

//contre les deux string
int str_cmp(char *buffer, char *input, char *input1){
    if (strcmp(buffer,input)==0 || strcmp(buffer, input1)==0)
        return 0;
    return 1;
}

//Sauvegarde létat de l'annuaire dans une fichier texte
void cmd_save(hm_t *hm, char *commande){
    if(str_cmp(commande,save,save1) == 0){
        hm_save(hm);
        printf("Répertoire enregistré sur le disque");
    }
}

//Supprime l'utilisateur courant
void cmd_userdel(hm_t *hm, char *commande, char *username){
    char oui_non;
    if(str_cmp(commande,userdel,userdel1) == 0){

        printf("Éliminer utilisateur '%s' ?[y/n] : ",username);
        scanf("%c", &oui_non);
		// Se decido di eliminare l'utilizzatore
        if(oui_non == 'y' || oui_non == 'Y'){
            if(hm_get(hm,username)!=NULL){

                hm_rm(hm,username);
                hm_save_pass(hm);
				printf("\nUtilisateur '%s' éliminé", username);
                printf("\nSORTIE\n");
                exit(0);
            }else
                printf("\nCommande annulée, utilisateur non supprimé");
        }
    }
}

//Effacer une entrée de l'annuaire
void cmd_del(hm_t *hm, char *commande, char *data){
    if(str_cmp(commande,del,del1) == 0){

        //Suppression de caractère \n en plus
        texte_sans_enter(data);
				
        //quando si scrive il nome mettere anche ":"
        if(data != NULL){
            if(hm_get(hm,data)!=NULL){
					
                hm_rm(hm,data);
			    printf("Elément supprime"); 
            }else
                printf("Erreur:\nNom introuvable, ajoutez ':' après le nom. Ou le nom n'existe pas dans la liste");
        }
        if(data == NULL)
                printf("Erreur:\nLe nom n'a pas été saisi");
    }
}

//Ajouter un administrateur au système
void cmd_useradd(hm_t *hm,char *commande, char *data){ //numero
    if(str_cmp(commande,useradd,useradd1) == 0){

        if(data !=NULL){
            if(hm_get(hm,data)==NULL){
                int hashed = 0;

                char* numero = malloc(60*sizeof(char));
                char* numero1 = malloc(50*sizeof(char));
                printf("Choisir un mot de passe pour l’utilisateur : ");
                fgets(numero1,50,stdin);
                numero = strtok(numero1,"\n");
                //hash de mot de pass
                static char result[50];
                for (int i = 0; numero[i] != '\0'; i++)
                    hashed = (43 * hashed + numero[i]) % 5060;
                
                sprintf(result, "%d", hashed);

                //Suppression de caractère \n en plus
                texte_sans_enter(data);

                hm_set(hm,data,result);
                printf("Utilisateur: '%s',ajouté dans le répertoire",data);
                hm_save_pass(hm);
            }else
                printf("\nUtilisateur existant");   
        }else			
            printf("Erreur:\nLe nom ou le mot de passe n'a pas été saisi");
    }
}

//Afficher tout l'annuaire
void cmd_show(hm_t *hm,char *commande, char *data){

    if(str_cmp(commande,show,show1) == 0 && data == NULL){
        printf("\n         Print Annuaire:");
        printf("\n---------------------------------\n");
        hm_print(hm);
        printf("---------------------------------");
    }
}

//Consulter le numéro d'une personne
void cmd_show_name(hm_t *hm,char *commande, char *data){
    if(str_cmp(commande,show,show1) == 0 && data != NULL){

        //Suppression de caractère \n en plus
        texte_sans_enter(data);
        //Quand vous écrivez le nom, mettez aussi ':'
        printf("\nLe Numero de '%s' est: '%s'",data,hm_get(hm,data));
    }
}

//Ajouter pu éditer une entrée de l'annuaire
void cmd_add(hm_t *hm, char *commande, char *data, char *numero){

    char oui_non;
    if(str_cmp(commande,add,add1) == 0){
				
		//Je vérifie que toutes les données sont tapées 
        if(data !=NULL && numero != NULL){

		    //Vérification que le nom existe déjà dans l’Annuaire
            if(hm_get(hm, data) != NULL){
				printf("\n'%s' existe déjà dans le répertoire avec le numéro de téléphone '%s'", data, hm_get(hm,data));
                printf("\nSouhaitez-vous poursuivre ? [y/n] : ");
                scanf("%c", &oui_non);

				// Si je décide de remplacer la donnée 
                if(oui_non == 'y' || oui_non == 'Y'){
                    hm_set(hm,data,numero);
                    printf("Nom: '%s', numéro de téléphone: '%s' ajouté dans le répertoire", data,numero);
                }
                if(oui_non == 'n' || oui_non == 'N'){
                    printf("Nom non ajouté dans le répertoire");
                }
            }
            //Vérification que le nom n’existe pas déjà dans l’Annuaire
            if(hm_get(hm,data) ==NULL){
                hm_set(hm,data,numero);
                printf("Nom: '%s', numéro de téléphone: '%s' ajouté dans le répertoire", data,numero);
            }
        }else
            printf("Erreur:\nLe nom ou le numero n'a pas été saisi");
	}
}

//Sauvegarde létat de l'annuaire dans une fichier texte
void quit_save(hm_t *hm){
    char oui_non;
        printf("\nSouhaitez-vous enregistrer le fichier ? [y/n] : ");
        scanf("%c", &oui_non);
		//Si je décide de remplacer la donnée 
        if(oui_non == 'y' || oui_non == 'Y'){
            hm_save(hm);
            printf("Répertoire enregistré sur le disque\nSORTIE\n");
            exit(0);
        }
        if(oui_non == 'n' || oui_non == 'N'){
            printf("Répertoire NON enregistré sur le disque\nSORTIE\n");
            exit(0);
        }
}

//Change le mot de pass de l'utilisateur courant
void cmd_passwd(hm_t *hm, char *commande, char *username){

    if(str_cmp(commande,passwd,passwd1) == 0){
				
				int hashed = 0;
                char* numero = malloc(60*sizeof(char));
                char* numero1 = malloc(50*sizeof(char));
                printf("Choisir le nouveau mot de passe: ");
                fgets(numero1,50,stdin);
                numero = strtok(numero1,"\n");
                //hash de mot de pass
                static char result[50];
                for (int i = 0; numero[i] != '\0'; i++)
                    hashed = (43 * hashed + numero[i]) % 5060;
    
                sprintf(result, "%d", hashed); //Convert int to char

                hm_rm(hm,username); //Supprime le username
                hm_set(hm,username,result); 
                printf("Mot de passe de l’utilisateur'%s', modifié",username);
                hm_save_pass(hm);
            }
	}

//Commande inconnue
void commande_inconnue(char *commande){
    int len = strlen(commande);
    if (commande[len+1] == '\0'){
        if(str_cmp(commande,guest,guest1)       !=0 && 
            str_cmp(commande,show,show1)        !=0 && 
            str_cmp(commande,add,add1)          !=0 && 
            str_cmp(commande,save,save1)        !=0 && 
            str_cmp(commande,useradd,useradd1)  !=0 && 
            str_cmp(commande,userdel,userdel1)  !=0 && 
            str_cmp(commande,quit,quit1)        !=0 && 
            str_cmp(commande,del,del1)          !=0 && 
            str_cmp(commande,passwd,passwd1)    !=0   )
            {
                printf("Commande inconnue");
            }
        
    }
}




