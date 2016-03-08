#include "Header.h"


//Classe de gestion du fichier chiffré principal
class BlueBigFile
{
public:
	//Constructeurs
	BlueBigFile(vector<string>& liste_fichiers, vector<char>& cle_cryptage);
	BlueBigFile(vector<char>& cle_decryptage);

	//Génération du gros fichier
	void generer();

	//Déchiffrement du gros fichier en retournant les fichiers créés
	vector<string> degenerer();

private:
	//Chiffrement
	vector<string>* liste_fichiers;
	vector<char>& cle_cryptage;

	//Dechiffrement
	vector<char>& cle_decryptage;


};