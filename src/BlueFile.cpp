#include "../include/BlueFile.h"

//Lis le fichier et génère le tableau de bits
BlueFile::BlueFile(string nom_fichier) : nom_fichier(nom_fichier)
{
	lireBinaire();
}

//Lecture en binaire d'un fichier
void BlueFile::lireBinaire()
{
	ifstream fichier("datas/"+nom_fichier, ios::binary);

	//lecture caractère par caractère
	char c;
	while(fichier >> noskipws >> c)
		//lecture bit par bit
		for(int i = 7; i >= 0; i--) 
			bits.push_back(((c >> i) & 1));

	//Affichage des bits
	for(size_t i = 0; i < bits.size(); i++)
	{
		if(i % 8 == 0)
			cout << endl;
		char c = (bits[i] ? '1' : '0');
		cout << c;

	}
}


//Crypte l'ensemble des bits
void BlueFile::crypter()
{
}

//Réécris le fichier en binaire
void BlueFile::ecrireBinaire()
{
	ofstream fichier("datas/" + nom_fichier);
	
	//regroupement des bits en caractère
}