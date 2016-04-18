#include "Header.h"


//Classe de gestion du fichier chiffré principal
class BlueBigFile
{
public:
	//Constructeurs
	BlueBigFile(vector<string>& liste_fichiers, vector<char>& cle_chiffrement);
	BlueBigFile(vector<char>& cle_dechiffrement);

	//Génération du gros fichier
	void generer();

	//Déchiffrement du gros fichier en retournant les fichiers créés
	vector<string> degenerer();

private:
	//Chiffrement
	vector<string>* liste_fichiers;
	vector<char>& cle_chiffrement;

	//Dechiffrement
	vector<char>& cle_dechiffrement;


};