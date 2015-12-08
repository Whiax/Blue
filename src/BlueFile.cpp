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
	while(fichier >> c)
	{
		//lecture bit par bit
	}
}


//Crypte l'ensemble des bits
void BlueFile::crypter()
{
}

//Réécris le fichier en binaire
void BlueFile::ecrireBinaire()
{
}