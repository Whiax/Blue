#include "../include/BlueFile.h"

//Pr�pare pour la lecture
BlueFile::BlueFile(string nom_fichier, bool cryptage, bool decryptage) : nom_fichier(nom_fichier), cryptage(cryptage), decryptage(decryptage)
{
	//cryptage 
	bits.reserve(TAILLE_BLOC_OCTET);

	determineTaille();

	fichier_lecture = NULL;
	fichier_ecriture = NULL;

	cout << "__________/_\\__________" << endl;
	if(decryptage) cout << "DE";
	cout << "CRYPTAGE DE " << nom_fichier << endl;
	cout << "TAILLE: " << taille << endl << endl;

	//analyse
	passage = 0;
}

//D�truit les donn�es
BlueFile::~BlueFile()
{
	fichier_lecture->close();
	fichier_ecriture->close();
	delete fichier_lecture;
	delete fichier_ecriture;
}

//D�termine la taille du fichier
void BlueFile::determineTaille()
{
	ifstream in("" DOSSIER_EFFECTIF "/" + nom_fichier, ifstream::ate | ifstream::binary);
	taille = in.tellg();
}

//Lecture en binaire d'un fichier
void BlueFile::lireBinaire()
{
	if(fichier_lecture == NULL)
		fichier_lecture = new ifstream("" DOSSIER_EFFECTIF "/" + nom_fichier, ios::binary);

	//lecture caract�re par caract�re
	char c = '_';
	while(bits.size() < TAILLE_BLOC_OCTET && (int)fichier_lecture->tellg() != taille)
	{
		*fichier_lecture >> noskipws >> c;
		//lecture bit par bit
		for(int i = 7; i >= 0; i--)
			bits.push_back(((c >> i) & 1));

	}


	passage++;
}

//D�tecte si le fichier a fini d'�tre crypt�
int BlueFile::procedureFinie()
{
	int position = (int)fichier_lecture->tellg();
	bool end = position == taille;

	//message de fin / progression
	if(end)
		cout << "CRYPTAGE/DECRYPTAGE FINI" << endl << "__________\\_/__________" << endl << endl;
	else
		cout << passage << " : Progression : " << (float)position / (float)taille * 100.f << "%" << endl;

	if(end)
		return 1;
	else if(position == -1)
		return -1;
	else return 0;
}

//Crypte l'ensemble des bits courants
void BlueFile::crypter()
{
	//cryptage basique: inverser les bits deux � deux
	for(size_t i = 0; i < bits.size() -1; i+=2)
	{
		char c1 = bits[i];
		bits[i] = bits[i + 1];
		bits[i + 1] = c1;
	}
}

//D�crypte l'ensemble des bits courants
void BlueFile::decrypter()
{
	//d�cryptage basique: inverser les bits deux � deux
	for(size_t i = 0; i < bits.size() - 1; i+=2)
	{
		char c1 = bits[i];
		bits[i] = bits[i + 1];
		bits[i + 1] = c1;
	}
}

//Op�re l'op�ration souhait�e
void BlueFile::operer()
{
	if(cryptage)
		crypter();
	if(decryptage)
		decrypter();
}

//R��cris l'ensemble des bits courants dans le fichier en binaire 
void BlueFile::ecrireBinaire()
{
	if(!fichier_ecriture)
	{
		string nom = "" DOSSIER_EFFECTIF "/" + nom_fichier;
		if(cryptage)
			nom += ".bluecrypt";
		if(decryptage)
			nom = nom.substr(0, nom.size() - (sizeof(".bluecrypt")-1));
		fichier_ecriture = new ofstream(nom, ios::binary);
	}
	
	//lecture des bits
	for(size_t i = 0; i < bits.size(); i+=8)
	{
		//regroupement en caract�re
		char c = 0;
		for(int j = 0; j < 8; j++)
			c ^= (-(int)bits[i + j] ^ c) & (1 << (7 - j));

		//si non saut de ligne sp�cial
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

//Whiax