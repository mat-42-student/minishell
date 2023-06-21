TODO

* il faudrait afficher permission denied dans un repertoire sans droits

OK
* copier / coller dans le prompt fait un truc bizarre. Ca fait des artefacts juste apres le prompt, impossible de delete : c'etait RESET dans le prompt
* leaks sur les builtins
* export A=pouet fait un truc bizarre dans env (ligne export ?)
* export A=pouet 10 fois va faire 10 entrees dans export et env
* Gerer $A$B
* Gerer $A$B$C
* Gerer $$
* $? à gérer dans dollar_replace
* assigner correctement les valeurs d'err.
* quitter une commande avec ctrl-C doit renvoyer 1 dans $?
* Gestion d'erreurs (code d'erreur de la derniere commande stockée dans $?)
* Gerer mieux les | | | | |
* Gerer >| -> syntax error
* historique permanent dans fichier .ms_history
* exit n'exit plus ?
* signaux marchent bizarre / pas dans certains cas (heredoc, passwd, minishell dans minishell)
* segfault quand argument invalides.
* enlever les $EMPTY au debut de ms_lex avant de quotesplit
* cd, cd - (oldpasswd)
* env : pas de valeurs vides
* export declare -x, content des variables entre quotes
* permission denied a l'execution d'un fichier ./ ou / si chmod -x
* exit segfault
* (est-ce le cas pour toutes les builtins ?) echo $? renvoie 0 apres un fd incorrect (devrait renvoyer 1)
* unset detruit toutes les variables apres le arg
* export leaks
* signaux : sauter une ligne apres ctrl-C (apres passwd, as, ce genre de plans)
* appeler deux fois export segfault
* export A+=
* export doit dol_replace(comment ça px ile fait pas le sacripan)
* desactiver sigquit (reactivé pour certains tests)
* echo banane >   >out fonctionne et devrait pas !
* OLDPWD se recree tout seul apres unset quand on env ou export
* unset fonctionne aussi avec les variables vides
* $? ne doit pas perdre sa valeur quand on fait des entrees vides (appuyer plusieurs fois sur entree doit conserver la derniere valeur de retour et pas remettre a 0)
* echo $USER+4 devrait afficher mdjemaa+4 (dolreplace doit s'arreter des que on n'est plus dans un caractere autorise par le nom de variable (donc des que alpha ou  _, beacuse pas de chiffre en premier dans un nom de variable))
* export PATH=$PATH:$PWD -> $PWD ecrase tout
* execve lance un fichier qui est dans le repertoire courant sans qu'il commence par ./
* "cat <not_exist <<A <file" Pour moi notre gestion est ok. Trop relou de faire marcher exactement comme dans bash, et notre comportement final reste valable. C'est notamment chiant dans le cas ou "cmd <fileinok <<HEREDOC" ou "cmd <<HEREDOC <fileok" de garder le fil des fd et en fait ca a du putain de sens de faire dans le vrai ordre ou c'est ecrit.
