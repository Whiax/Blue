#include "../include/BlueFile.h"

//Prépare pour la lecture
BlueFile::BlueFile(string nom_fichier) : nom_fichier(nom_fichier)
{
	bits.reserve(BLOCK_SIZE);

	determineTaille();

	fichier_lecture = NULL;
	fichier_ecriture = NULL;

	cout << "__________/_\\__________" << endl;
	cout << "CRYPTAGE/DECRYPTAGE DE " << nom_fichier << endl;
	cout << "TAILLE: " << taille << endl << endl;
}

//Détruit les données
BlueFile::~BlueFile()
{
	fichier_lecture->close();
	delete fichier_lecture;
	delete fichier_ecriture;
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


	
}

//Détecte si le fichier a fini d'être crypté
int BlueFile::procedureFinie()
{
	int position = (int)fichier_lecture->tellg();
	bool end = position == taille;

	//message de fin / progression
	if(end)
		cout << "CRYPTAGE/DECRYPTAGE FINI" << endl << "__________\\_/__________" << endl << endl;
	else
		cout << "Progression : " << (float)fichier_lecture->tellg() / (float) taille << "%" << endl;

	if(end)
		return 1;
	else if(position == -1)
		return -1;
	else return 0;
}

//Crypte l'ensemble des bits courants
void BlueFile::crypter()
{
	//cryptage basique: inverser les bits deux à deux
	for(size_t i = 0; i < bits.size() -1; i+=2)
	{
		char c1 = bits[i];
		bits[i] = bits[i + 1];
		bits[i + 1] = c1;
	}
}

//Décrypte l'ensemble des bits courants
void BlueFile::decrypter()
{
	//décryptage basique: inverser les bits deux à deux
	for(size_t i = 0; i < bits.size() - 1; i+=2)
	{
		char c1 = bits[i];
		bits[i] = bits[i + 1];
		bits[i + 1] = c1;
	}
}

//Réécris l'ensemble des bits courants dans le fichier en binaire 
void BlueFile::ecrireBinaire()
{
	if(!fichier_ecriture)
		fichier_ecriture = new ofstream("datas/" + nom_fichier,   ios::binary);
	
	//lecture des bits
	for(size_t i = 0; i < bits.size(); i+=8)
	{
		//regroupement en caractère
		char c = 0;
		for(int j = 0; j < 8; j++)
			c ^= (-(int)bits[i + j] ^ c) & (1 << (7 - j));

		//si non saut de ligne spécial
		*fichier_ecriture << c;
	}
	bits.clear();
}

//Affiche les bits
void BlueFile::afficherBits()
{
	cout << endl << "AFFICHAGE BITS:" << endl;
	for(size_t i = 0; i < bits.size(); i++)
	{
		if(i % 8 == 0)
			cout << endl;
		char bit = (bits[i] ? '1' : '0');
		cout << bit;
	}
	cout << endl << "______" << endl << endl;
	
}