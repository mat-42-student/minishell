# Minishell

  

Gros problèmes.

  

## Parsing

### Syntaxe

1. vérifier que les doubles et simples quotes sont bien fermés _OK_

2. Verifier les caracteres interdits (\, ;, etc.) _OK_

### Interpréter les caractères spéciaux


1. Supprimer ce qui suit apres une dièse /!\ uniquement quand # est le premier caractere d'un mot _OK_

```
les jeunes sont accros aux réseaux et n'ont aucun recul sur les informations
qu'ils voient #pauvrefrance #decadence
```

va donner
```
les jeunes sont accros au réseaux et n'ont aucun recul sur les informations
qu'ils voient
```

### Remplissage de t_cmd
1. Split | _OK_

Attention ce premier split ne supprime pas les quotes. Il split t_line.line sur le caractere |, compte le nb de commandes, malloc t_cmd et remplit t_cmd[i].line avec le retour de split

Desormais on ne devrait plus avoir qu'a travailler sur t_cmd[i].line

2. Gerer les redirections ( < << >> >) _OK_

chaque fois qu'on tombe sur une redirection > ou >>, on gere les dollars concernés, on crée le fichier cible, on modifie le fdout et on detruit ou ignore la redirection dans t_cmd.line

3. Split sur espace _OK_

Sauf entre les quotes, et les quotes doivent rester dans les bouts de string finaux (ca doit pas split quand " ou ' sinon 'e''c''h''o' ne marche pas). Remplir les champs de t_cmd avec le char** qui sort de split

echo" pouet" -> command not found: echo pouet

4. Interpréter les dollars (+trim les quotes)

```
var1=oignon
var2=fi
var3=Var
var4=coll
salade tomate $var1 'j'ai la $var2 icelle' "j'habite dans le $var3" il est un peu $var4ant
```

va donner
```
salade tomate oignon 'j'ai la $var2 icelle' "j'habite dans le Var" il est un peu
```

  
les dollar point d'interrogation.

```mermaid
graph LR
A($?) ---> B(statut de sortie du dernier pipeline)
```
  
## Execution

1. fork + execve ou builtins

##

valeur utiles pour implementer des securite

```
#define MAXPATHLEN      PATH_MAX
#define MAX_CANON                1024   /* max bytes in term canon input line */
#define MAX_INPUT                1024   /* max bytes in terminal input */
#define NAME_MAX                  255   /* max bytes in a file name */
#define PATH_MAX                 1024   /* max bytes in pathname */
#define PIPE_BUF                  512   /* max bytes for atomic pipe writes */
#define LINE_MAX                 2048   /* max bytes in an input line */

```