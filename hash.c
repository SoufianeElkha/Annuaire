#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "commandes.h"
#include "hash.h"


static entry_t *new_entry(char *key, char *value) {
    struct entry_t* entry = malloc(sizeof(struct entry_t));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

static void free_entry(entry_t *entry) {
    free(entry->key);
    free(entry->value);
    free(entry);
}

static char* free_entry_without_value(entry_t *entry) {
    char *value = entry->value;
    free(entry->key);
    free(entry);
    return value;
}

static char *copy_string(const char *const string) {
    char *string_copy = malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(string_copy, string);
    return string_copy;
}

//Fonctions de hachage
static unsigned hash(char *key, int length) {
    unsigned hashed = 0;
    for (int i = 0; key[i] != '\0'; i++)
        hashed = (43 * hashed + key[i]) % length;

    return hashed;
}

// création d'un pointeur vers une hm
hm_t *hm_create(unsigned int length) {
    struct hm_t *dictionary = malloc(sizeof(hm_t));
    dictionary->length = length;
    dictionary->entries = malloc(sizeof(struct entry_t*) * length);
    for (unsigned i = 0; i < length; i++) {
        dictionary->entries[i] = NULL;
    }
    return dictionary;
}

// destruction de la hm et libération de la mémoire
void hm_destroy(hm_t **hm) {
    if (hm == NULL) {
        return;
    }
    for (int i = 0; i < (*hm)->length; i++) {
        struct entry_t* current = (*hm)->entries[i];
        while (current != NULL) {
            struct entry_t* to_remove = current;
            current = current->next;
            free_entry(to_remove);
        }
    }
    free((*hm)->entries);
    free(*hm);
    *hm = NULL;
}

// insère la paire key-value dans la hm. si key est déjà présente
// écraser value dans la hm. La clé et la valeur sont stockées
// dans de nouveau espaces mémoires alloués par la fonction
hm_t *hm_set(hm_t *hm, char *key,char *value) {
    char *value_copy = copy_string(value);
    int hashed_key = hash(key, hm->length);
    //printf("%d\n", hashed_key);
    //printf("%s\n", value_copy);

    if (hm->entries[hashed_key] == NULL) {
        hm->entries[hashed_key] = new_entry(copy_string(key), value_copy);
    } else {
        struct entry_t* current = hm->entries[hashed_key];
        do {
            // If key already exists, then override value and exit
            if (strcmp(current->key, key) == 0) {
                free(current->value);
                current->value = value_copy;
                return hm;
            }
            if (current->next != NULL) {
                current = current->next;
            }
        } while (current->next != NULL);
        current->next = new_entry(copy_string(key), value_copy);
    }
    return hm;
}

// retourne la valeur associé à la clé, key
// retourne le pointeur dans la structure hm_t
char *hm_get(hm_t *hm,char *key) {
    for (int i = 0; i < hm->length; i++) {
        entry_t *current = hm->entries[i];
        while (current != NULL) {
            if (strcmp(key, current->key) == 0) {
                return current->value;
            }
            current = current->next;
        }
    }
    return NULL;
}

// retire une clé de la hm
char *hm_rm(hm_t *hm,char *key) {
    int error=0;
    for (int i = 0; i < hm->length; i++) {
        if (hm->entries[i] != NULL) {
            entry_t *previous = hm->entries[i];
            if (strcmp(previous->key, key) == 0) {
                error=1;
                hm->entries[i] = previous->next;
                return free_entry_without_value(previous);
            }
            entry_t *current = hm->entries[i]->next;
            while (current != NULL) {
                error=1;
                if (strcmp(current->key, key) == 0) {
                    previous->next = current->next;
                    return free_entry_without_value(current);
                }
                current = current->next;
            }
        }
    }
    if(error==0)
        printf("Error:\nLe nom n'existe pas dans la liste");
    if(error==1)
        printf("Nom supprime");

    return NULL;
}

//convertir hm to string
char *hm_to_str(hm_t *hm) {
    unsigned nb_key_value_chars = 0;
    unsigned nb_entries = 0;
    for (int i = 0; i < hm->length; i++) {
        entry_t *current = hm->entries[i];
        while (current != NULL) {
            nb_key_value_chars += strlen(current->key);
            nb_key_value_chars += strlen(current->value);
            nb_entries++;
            current = current->next;
        }
    }
    unsigned nb_brackets = 2;
    unsigned nb_commas = nb_entries - 1;
    unsigned nb_separators = nb_entries * 4;
    unsigned nb_key_value_separators = nb_entries;
    unsigned nb_chars = nb_brackets + nb_key_value_chars + nb_key_value_separators + nb_separators + nb_commas + 1;
    char *output = malloc(sizeof(char) * nb_chars);
    int i = 0;
    output[i++] = '{';
    for (int j = 0; j < hm->length; j++) {
        entry_t *current = hm->entries[j];
        // Foreach entry
        while (current != NULL) {
            output[i++] = '"';
            for (int c = 0; current->key[c] != '\0'; c++) {
                output[i++] = current->key[c];
            }
            output[i++] = '"';
            output[i++] = ':';
            output[i++] = '"';
            for (int c = 0; current->value[c] != '\0'; c++) {
                output[i++] = current->value[c];
            }
            output[i++] = '"';
            output[i++] = ',';
            current = current->next;
        }
    }
    output[nb_chars - 2] = '}';
    output[nb_chars - 1] = '\0';
    return output;
}

// affiche le contenu de la hm
void hm_print(hm_t *hm) {
    entry_t *current;
    int error=0;
    for (int i = 0; i < hm->length; i++) {
        current = hm->entries[i];
        while (current != NULL) {
            error=1;
            printf("%s:%s\n", current->key, current->value);
            current = current->next;
        }
    }
    printf("\n");
    if (error==0)
        printf("Annuaire Vide!\n");
}

//Save le contenu de la hm
void hm_save(hm_t *hm) {
    entry_t *current;
    int error=0;
    char name_file[] = "data.txt";
    FILE *f;
    f=fopen(name_file, "w");
    if(f==NULL) 
        printf("\nErreur d’ouverture de fichier\n");

    for (int i = 0; i < hm->length; i++) {
        current = hm->entries[i];
        while (current != NULL) {
            error=1;
            fprintf(f,"%s:%s\n", current->key, current->value);
            current = current->next;
        }
    }
    fclose(f);
    printf("\n");
    if (error==0)
        printf("Annuaire Vide!\n");
}

// save le contenu de la pass
void hm_save_pass(hm_t *hm) {
    entry_t *current;
    char name_file[] = "passwd.txt";
    FILE *fid;
    fid=fopen(name_file, "w");
    if(fid==NULL)
        printf("\nErreur d’ouverture de fichier\n");
        
    for (int i = 0; i < hm->length; i++) {
        current = hm->entries[i];
        while (current != NULL) {
            fprintf(fid,"%s:%s\n", current->key, current->value);
            current = current->next;
        }
    }
    fclose(fid);
}

//Importer dans la table de hachage
void hm_import(hm_t *hm, char *name_file){

    char *import_database;
    char table[TMP_MAX];
    char *data_C;
    char *numero_C;
    char *file = name_file;
    FILE *fid;
    fid=fopen(file, "r");
    if(fid){
        while(1) {
            import_database=fgets(table,999, fid);
            if( import_database==NULL )
                break;
            data_C = strtok(table,":");
            numero_C = strtok(NULL,"\n");
            hm_set(hm,data_C,numero_C);
        }
    }else
        printf("\nErreur d’ouverture de fichier\n");

    fclose(fid);
    fflush(stdin);
}

//Suppression de caractère \n en plus
char texte_sans_enter(char *data){

    //Suppression de caractère \n en plus
    int size = strlen(data);
    for( int x=0; x < size; x++){
        if( data[x]=='\n' ){
            data[x]='\0';
            break;
        }
    }
    return *data;
}