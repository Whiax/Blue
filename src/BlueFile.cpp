#include "../include/BlueFile.h"

//Lis le fichier et g�n�re le tableau de bits
BlueFile::BlueFile(string nom_fichier) : nom_fichier(nom_fichier)
{
	lireBinaire();
}

//Lecture en binaire d'un fichier
void BlueFile::lireBinaire()
{
	ifstream fichier("datas/"+nom_fichier, ios::binary);

	//lecture caract�re par caract�re
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

//R��cris le fichier en binaire
void BlueFile::ecrireBinaire()
{
}