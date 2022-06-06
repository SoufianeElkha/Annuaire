Pour compilation:

>make
>./directory

Mot de passe masqué:
Modalité Administrateur1

    username: admin

    password: pass

Modalité Guest

    username: guest

//////////////////////////////////////////////////////////////////////////////////////////

Énoncé

Le but de ce travail pratique est d’implémenter un système d’annuaire avec
contrôle d’accès. Lors du lancement du programme nommé directory, l’utilisateur verra s’afficher un invite de connexion qui lui demandera d’abord son nom
d’utilisateur, puis son mot de passe. Si l’utilisateur saisi un couple nom d’utilisateur, mot de passe valide, il sera alors considéré comme un “administrateur”,
tandis que si il choisit comme nom d’utilisateur “guest” et qu’il ne spécifie pas
de mot de passe , il sera considéré comme un invité.

Les administrateurs peuvent modifier les informations du système, tandis que les
invités ne peuvent que les consulter. Une fois connecté, tout utilisateur peut :

— Consulter les informations liées à un nom dans l’annuaire.

— Afficher l’intégralité de l’annuaire.

— Quitter le programme.




Et tout administrateur peut :




— Effacer une entrée de l’annuaire.

— Ajouter ou éditer une entrée de l’annuaire.

— Sauvegarder l’état de l’annuaire dans un fichier.

— Ajouter un utilisateur.

— Modifier le mot de passe de l’utilisateur courant.

— Supprimer l’utilisateur courant.


Ces fonctionnalités seront accessibles via des commandes sur l’invite :


— show [name], consulter le numéro d’une personne. Par exemple : show
    Pierre Kunzli (tout ce qui suit l’espace après la commande show est
    considéré comme étant le nom).
— show, afficher tout l’annuaire.

— del [name] effacer une entrée de l’annuaire. Par exemple : del Pierre
    Kunzli. Si l’entrée n’est pas trouvée, afficher un message d’erreur.

— add [name]:[number] ajouter ou éditer une entrée de l’annuaire. Par
    exemple : add Pier Ku:0210001122. Si l’entrée se trouve déjà
    dans l’annuaire, afficher un message demandant confirmation.

— save sauvegarde l’état de l’annuaire dans un fichier texte.

— quit quitter le programme. Si l’utilisateur courant est un administrateur,
    demander si il veut sauvegarder l’annuaire sur le disque.

— useradd [username] ajouter un administrateur au système. 

    Par exemple:

        useradd pk. Si l’utilisateur existe déjà, un message d’erreur est affiché.
        Sinon, le système demande un mot de passe pour l’utilisateur.

— passwd change le mot de passe de l’utilisateur courant. Le système demande un nouveau     mot de passe.

— userdel supprime l’utilisateur courant. Une demande de confirmation
    est effectuée avant d’exécuter la commande.

Exemple d’utilisation
$ ./directory

> username : pk

> password :

pk > show Pierre Kunzli

Name : Pierre Kunzli, Phone number : 0210001122

pk > add Paul Albuquerque:0123211212

Name : Paul Albuquerque, Phone number : 0123211212 added in directory

pk > add Pierre Kunzli:0210001121

Pierre Kunzli already exists in directory with phone number 0210001122.

Would you like to continue ? [y/n] y

Name : Pierre Kunzli, Phone number : 0210001121 added in directory

pk > save

Directory saved to disk

Unknown command

pk > useradd pa

Choose a password for user pa :

pk > kjhfdkjdsf

Unknown command

pk > quit

Would you like to save directory to disk ? [y/n] n

$


