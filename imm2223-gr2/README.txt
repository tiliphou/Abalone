+----------------------------------------+
| 		   Compilation		     |
+----------------------------------------+

Au niveau de imm2023-gr2
    Compilation, produit l'exécutable ./imm2223-gr2
	$ make 
    Tests : Compile et execute les tests sous ./test
	$ make tests
    Docs : Production des docs sous ./doc
	$ make docs


+---------------------------------------+
|		  Utilisation     	    |
+---------------------------------------+

$ ./abalone [option] [argument]


Les options suivantes sont disponibles:

	-l  Lance Abalone en local, permet de jouer contre une IA en choisissant 
	    parmis les arguments suivant: noir ou blanc.
	    (ex: ./abalone -l noir)

	-s  Lance Abalone en serveur, permet de preparer le serveur à accepter la 
	    connexion d'un  client pour jouer IA contre IA. Spécifier le port à utiliser en 
	    argument. 
	    (ex : ./abalone -s 6969)

	-c  Lance Abalone en client, permet de se connecter à un serveur dont l'IP est 
	    passé en argument et sur un port donné également.
 	    (ex : ./abalone -c 127.0.0.1:6969)

	 
