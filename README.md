README

Le valgrind rc permet de supprimer les leaks de read_line, attention grep leak aussi, il ne faudra pas se laisser avoir
pour utiliser c'est juste : valgrind ./minishell dans le repo avec le .valgrindrc

Acess pour verifier la prescence du binaire

/!\ str_tok (man) utiliser à la place du split permet de separer un prenant en compte les quotes

Pour remplir les nodes, je dois savoir quelle est la commande et si elle est accessible.
Delimiter avec les characteres donnes par le sujet ?

• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).

Si "" : prendre en compte les variables d env (donc traduire directement dans la commande)
Si '' : ecrire directement le nom de la variable (pas sa valeur)

Rentrer dans une instance du split qui ignore les espaces entre les quotes donc quand le flag est à 1 on ignore les quotes

0 = pas de quote
1 = single
2 = single fermee

#define NOQ 0
#define SQUOTE_OPEN 1
#define SQUOTE_CLOSE 2


flag = 0; //on remet le flag a 0 au debut de la boucle seulement si la quote est fermee
if line[i] == quote
    flag = 1
if !quote
    words++ / strdup
if line[i] == quote
    flag = 2

if flag == 1
    return
else handle quotes(flag de la quote, ) ; //return l'argument traduit ou non

À la limite directement dans le split attribuer la commande, comme ça je peux mettre un flag dans la structure qui
traduit ou non
sinon à linterieur de la fonction traduire avant de remplir la node. (cette solution ne fonctionne que si c'est valable
de traduire à ce moment-là, le flag dans la struct permettrait de choisir quand on le traduit)
