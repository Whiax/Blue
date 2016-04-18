#include "../include/BlueFile.h"

//Prépare pour la lecture
BlueFile::BlueFile(string nom_fichier, bool chiffrement, bool dechiffrement, vector<char>& cle_chiffrement, vector<char>& cle_dechiffrement)
	: nom_fichier(nom_fichier), chiffrement(chiffrement), dechiffrement(dechiffrement), cle_chiffrement(cle_chiffrement), cle_dechiffrement(cle_dechiffrement)
{
	//chiffrement 
	bits.reserve(TAILLE_BLOC_OCTET);

	determineTaille();

	fichier_lecture = NULL;
	fichier_ecriture = NULL;

	cout << "__________/_\\__________" << endl;
	if(dechiffrement) cout << "DE";
	cout << "CHIFFREMENT DE " << nom_fichier << endl;
	cout << "TAILLE: " << taille << endl << endl;

	//noms des fichiers sources et destination
	creerNomsFichiers();

	//analyse
	passage = 0;
}

//Détruit les données
BlueFile::~BlueFile()
{
	fichier_lecture->close();
	fichier_ecriture->close();
	delete fichier_lecture;
	delete fichier_ecriture;
}

//Détermine la taille du fichier
void BlueFile::determineTaille()
{
	ifstream in("" DOSSIER_EFFECTIF "/" + nom_fichier, ifstream::ate | ifstream::binary);
	taille = in.tellg();
}

//Lecture en binaire d'un fichier
void BlueFile::lireBinaire()
{
	if(fichier_lecture == NULL)
		fichier_lecture = new ifstream("" DOSSIER_EFFECTIF "/" +  nom_lecture, ios::binary);

	//lecture caractère par caractère
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

//Détecte si le fichier a fini d'être chiffré
int BlueFile::procedureFinie()
{
	int position = (int)fichier_lecture->tellg();
	bool end = position == taille;

	//message de fin / progression
	if(end)
		cout << "OPERATION FINIE" << endl << "__________\\_/__________" << endl << endl;
	else
		cout << passage << " : Progression : " << (float)position / (float)taille * 100.f << "%" << endl;

	if(end)
		return 1;
	else if(position == -1)
		return -1;
	else return 0;
}

//chiffre l'ensemble des bits courants
void BlueFile::chiffrer()
{
	//si on a pas de cles de chiffrement
	if(cle_chiffrement.size() == 0)
		//chiffrement basique: inverser les bits deux à deux
		for(size_t i = 0; i < bits.size() -1; i+=2)
		{
			char c1 = bits[i];
			bits[i] = bits[i + 1];
			bits[i + 1] = c1;
		}
	//sinon
	else //chiffrement basique d'inversion de valeur de bit
		for(size_t i = 0; i < bits.size(); ++i)
			bits[i] = cle_chiffrement[i % cle_chiffrement.size()] ? !bits[i] : bits[i];
}

//Déchiffre l'ensemble des bits courants
void BlueFile::dechiffrer()
{
	//si on a pas de cles de chiffrement
	if(cle_dechiffrement.size() == 0)
		//déchiffrement basique: inverser les bits deux à deux
		for(size_t i = 0; i < bits.size() - 1; i+=2)
		{
			char c1 = bits[i];
			bits[i] = bits[i + 1];
			bits[i + 1] = c1;
		}
	//sinon
	else //dechiffrement basique d'inversion de valeur de bit
		for(size_t i = 0; i < bits.size(); ++i)
			bits[i] = cle_dechiffrement[i % cle_dechiffrement.size()] ? !bits[i] : bits[i];
}

//Opère l'opération souhaitée
void BlueFile::operer()
{
	if(chiffrement)
		chiffrer();
	if(dechiffrement)
		dechiffrer();
}

//Réécris l'ensemble des bits courants dans le fichier en binaire 
void BlueFile::ecrireBinaire()
{
	if(!fichier_ecriture)
		fichier_ecriture = new ofstream("" DOSSIER_EFFECTIF "/" + nom_ecriture, ios::binary);
	
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

//Supprime le fichier d'origine
void BlueFile::suppression()
{
	fichier_lecture->close();
	
	if(remove(("" DOSSIER_EFFECTIF "/" +  nom_lecture).c_str()) != 0)
		cout << "Impossibilite de supprimer le fichier d'origine" << endl;
	else
		cout << "Fichier d'origine supprime" << endl;
}

//Choisis le nom des fichiers
void BlueFile::creerNomsFichiers()
{
	nom_lecture =  nom_fichier;
	nom_ecriture =  nom_fichier;
	if(chiffrement)
		nom_ecriture += ".bluecrypt";
	if(dechiffrement)
		nom_ecriture = nom_ecriture.substr(0, nom_ecriture.size() - (sizeof(".bluecrypt") - 1));
}

//Renvoit le nom du fichier créé
string BlueFile::getNewName()
{
	return nom_ecriture;
}

//Whiax