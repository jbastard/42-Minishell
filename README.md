README

- Alors, CD est pas totalement au point :
cd - doit renvoyer au répertoire précédent (optionnel)
cd (VIDE) doit renvoyer au HOME sauf si celui-ci est unset
cd ~ doit renvoyer au HOME quoi qu'il arrive

- Les redirections :
Si plusieurs redirections sont présentes dans une commande et qu elles
doivent creer un fichier, tout les fichiers doivent etre créés

- La fonction exit ne fonctionne pas

- $? est une variable d environnement qui doit contenir le code de retour d erreur de la derniere commande
j ai gere ca dans mon parsing donc

echo $?
print juste le code d erreur