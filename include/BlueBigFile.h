#include "Header.h"


//Classe de gestion du fichier chiffr� principal
class BlueBigFile
{
public:
	//Constructeurs
	BlueBigFile(vector<string>& liste_fichiers, vector<char>& cle_cryptage);
	BlueBigFile(vector<char>& cle_decryptage);

	//G�n�ration du gros fichier
	void generer();

	//D�chiffrement du gros fichier en retournant les fichiers cr��s
	vector<string> degenerer();

private:
	//Chiffrement
	vector<string>* liste_fichiers;
	vector<char>& cle_cryptage;

	//Dechiffrement
	vector<char>& cle_decryptage;


};