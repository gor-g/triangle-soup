# TP Visualisation et compression "out-of-core" de soupes de triangles

Ce dépôt contient le code source du TP1 du cours Introduction à l'informatique graphique. Le TP consiste à implémenter un algorithme de compression de soupes de triangles, basé sur un découpage régulier de l'espace en cellules. Le TP utilise la bibliothèque libQGLViewer pour la visualisation des modèles 3D.

L'implémentation de fonctions de lecture et d'écriture de fichiers `.tri` ainsi que de la classe Vecteur est demandée par le sujet du TP.

# Build et Utilisation

Il y a 4 exécutables :

- viewer : le visualiseur qui affiche les triangles avec un matériel métallique colorié par les valeurs du vecteur normal de chaque face ;
- zipper1 : le compresseur rudimentaire ;
- zipper2 : le compresseur avec lissage ;
- zipper3 : le compresseur avec lissage qui évite la génération de trianges doublons (hors sujet).

Pour construire les 4 exécutables, exécutez `build.sh`
Pour tester, exécutez `run.sh`

Les hyperparamètres utilisés définis dans `make.pro` sont utilisés dans `main.cpp` et `TriangleSoupZipper.cpp`

Pour construire manuellement les exécutables :

`qmake "VERSION=0" && make` pour pour `viewer`
`qmake "VERSION=[n]" && make` pour pour `zipper[n]`

# Résultat

La soupe de triangle initial :

![soupe de triangle initial](https://github.com/mySpecialUsername/triangle-soup/blob/main/images/initial.png)

Résultat de compression rudimentaire :

![compression rudimentaire](https://github.com/mySpecialUsername/triangle-soup/blob/main/images/zip_rough.png)

Résultat de compression lisse :

![compression lisse](https://github.com/mySpecialUsername/triangle-soup/blob/main/images/zip_smooth.png)

Le résultat de la compression lisse sans doublons est visuellement identique au résultat de la compression lisse.
