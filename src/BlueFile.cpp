#include "../include/BlueFile.h"

//Prépare pour la lecture
BlueFile::BlueFile(string nom_fichier) : nom_fichier(nom_fichier)
{
	bits.reserve(BLOCK_SIZE);
	determineTaille();
	cout << taille;
	fichier_lecture = NULL;
}

//Détruit les données
BlueFile::~BlueFile()
{
	fichier_lecture->close();
	delete fichier_lecture;
}

//Détermine la taille du fichier
void BlueFile::determineTaille()
{
	ifstream in("datas/" + nom_fichier, ifstream::ate | ifstream::binary);
	taille = in.tellg();
}

//Lecture en binaire d'un fichier
void BlueFile::lireBinaire()
{
	if(fichier_lecture == NULL)
		fichier_lecture = new ifstream("datas/" + nom_fichier, ios::binary);

	//lecture caractère par caractère
	char c = '_';
	while(bits.size() < BLOCK_SIZE && (int)fichier_lecture->tellg() != taille)
	{
		*fichier_lecture >> noskipws >> c;
		//lecture bit par bit
		for(int i = 7; i >= 0; i--)
			bits.push_back(((c >> i) & 1));

	}


	//Affichage des bits
	/*for(size_t i = 0; i < bits.size(); i++)
	{
		if(i % 8 == 0)
			cout << endl;
		char bit = (bits[i] ? '1' : '0');
		cout << bit;
	}
	cout << endl;*/
}

//Détecte si le fichier a fini d'être crypté
bool BlueFile::procedureFinie()
{
	return (int)fichier_lecture->tellg() == taille;
}

//Crypte l'ensemble des bits courants
void BlueFile::crypter()
{

}

//Décrypte l'ensemble des bits courants
void BlueFile::decrypter()
{

}

//Réécris l'ensemble des bits courants dans le fichier en binaire 
void BlueFile::ecrireBinaire()
{
	ofstream fichier("datas/" + nom_fichier, ios_base::app);
	
	//lecture des bits
	for(size_t i = 0; i < bits.size(); i+=8)
	{
		//regroupement en caractère
		char c = 0;
		for(int j = 0; j < 8; j++)
		{
			int bit_value = bits[i + j];
			c ^= (-bit_value ^ c) & (1 << (7-j));
		}

		//voir si nécessaire sous LINUX
		//si non saut de ligne spécial
		if(c != 13)
		{
			fichier << c;

			//Affichage
			//cout << "\t = >\t" << (int)c << "\t" << c << endl;
		}
	}
	bits.clear();
}