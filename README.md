README

Alors, CD est pas totalement au point :
cd - doit renvoyer au répertoire précédent (optionnel)
cd (VIDE) doit renvoyer au HOME sauf si celui-ci est unset
cd ~ doit renvoyer au HOME quoi qu'il arrive

Les redirections :
Si plusieurs redirections sont présentes dans une commande et qu elles
doivent creer un fichier, tout les fichiers doivent etre créés

alors encore un probleme de gestion des variables d'environnement

echo ta $USER ta
minishell : ta jbastardta
expected : ta jbastard ta

echo ta$USER ta
minishell : tajbastardta
expected : tajbastard ta

echo test $USER test $USER test
minishell : test jbastardtest jbastardtest
expected : test jbastard test jbastard test

echo ta$USERta
minishell : ta$
expected : ta