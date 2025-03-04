README

Le valgrind rc permet de supprimer les leaks de read_line, attention grep leak aussi, il ne faudra pas se laisser avoir
pour utiliser c'est juste : valgrind ./minishell dans le repo avec le .valgrindrc

Acess pour verifier la prescence du binaire

/!\ str_tok (man) utiliser à la place du split permet de separer un prenant en compte les quotes

Pour remplir les nodes, je dois savoir quelle est la commande et si elle est accessible.
Delimiter avec les characteres donnes par le sujet ?

• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).

/!\ j ai gerer la semicolon dans le lexing, donc faire attention si ca leak ou quoi je le virerai, pas oblige de l implementer