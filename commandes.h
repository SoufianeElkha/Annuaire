#ifndef _COMMANDES_H
#define _COMMANDES_H

//Définition des comandes

#define guest "guest"
#define show "show"
#define add "add"
#define save "save"
#define useradd "useradd"
#define userdel "userdel"
#define quit "quit"
#define del "del"
#define passwd "passwd"

#define guest1 "guest\n"
#define show1 "show\n"
#define add1 "add\n"
#define save1 "save\n"
#define useradd1 "useradd\n"
#define userdel1 "userdel\n"
#define quit1 "quit\n"
#define del1 "del\n"
#define passwd1 "passwd\n"

//comparaison de la chaîne avec deux entrées
int str_cmp(char *buffer, char *input, char *input1);

//Print utilisateur
void visit(char* address);

#endif
