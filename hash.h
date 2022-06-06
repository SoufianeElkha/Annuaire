#ifndef _HASH_H
#define _HASH_H

//Structure hashmap 
struct hm_t {
    struct entry_t **entries;
    int length;
};

//Structure entrée de la table
struct entry_t {
    char *key;
    char *value;
    struct entry_t *next;
};

typedef struct hm_t hm_t;
typedef struct entry_t entry_t;

// création d'un pointeur vers une hm
hm_t *hm_create(unsigned int length);

// insère la paire key-value dans la hm. si key est déjà présente
// écraser value dans la hm. La clé et la valeur sont stockées
// dans de nouveau espaces mémoires alloués par la fonction
hm_t *hm_set(hm_t *hm,char *key,char *value);

// retourne la valeur associé à la clé, key
// retourne le pointeur dans la structure hm_t
char *hm_get(hm_t *hm,char *key);

// retire une clé de la hm
char *hm_rm(hm_t *hm,char *key);

// destruction de la hm et libération de la mémoire
void hm_destroy(hm_t **hm);

// hm to string
char *hm_to_str(hm_t *hm);

// affiche le contenu de la hm
void hm_print(hm_t *hm);

//Sauvegarde l'état de l'annuaire dans une fichier texte
void hm_save(hm_t *hm);

//Sauvegarde le mot de pass dans une fichier texte
void hm_save_pass(hm_t *hm);

//Importer dans la table de hachage
void hm_import(hm_t *hm, char *name_file);

//Afficher tout l'annuaire
void cmd_show(hm_t *hm,char *commande, char *data);

//Consulter le numéro d'une personne
void cmd_show_name(hm_t *hm,char *commande, char *data);

//Sauvegarde létat de l'annuaire dans une fichier texte
void cmd_save(hm_t *hm, char *commande);

//Ajouter pu éditer une entrée de l'annuaire
void cmd_add(hm_t *hm, char *commande, char *data, char *numero);

//Effacer une entrée de l'annuaire
void cmd_userdel(hm_t *hm, char *commande, char *username);

//Effacer une entrée de l'annuaire
void cmd_del(hm_t *hm, char *commande, char *data);

//Ajouter un administrateur au système
void cmd_useradd(hm_t *hm,char *commande, char *data);

//Sauvegarde létat de l'annuaire dans une fichier texte
void quit_save(hm_t *hm);

//Change le mot de pass de l'utilisateur courant
void cmd_passwd(hm_t *hm, char *commande, char *username);

//Comamnde inconnue
void commande_inconnue(char *commande);

//Suppression de caractère \n en plus
char texte_sans_enter(char *data);



#endif
