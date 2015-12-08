#include "../include/BlueFile.h"

//Lis le fichier et génère le tableau de bits
BlueFile::BlueFile(string nom_fichier) : nom_fichier(nom_fichier)
{
	lireBinaire();
}

//Lecture en binaire d'un fichier
void BlueFile::lireBinaire()
{
	ifstream fichier(nom_fichier, ios::binary);

}