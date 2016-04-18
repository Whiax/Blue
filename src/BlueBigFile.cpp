#include "../include/BlueBigFile.h"

//Constructeur
BlueBigFile::BlueBigFile(vector<string>& liste_fichiers, vector<char>& cle_chiffrement) 
	: cle_chiffrement(cle_chiffrement), liste_fichiers(&liste_fichiers), cle_dechiffrement(cle_chiffrement)
{ }


BlueBigFile::BlueBigFile(vector<char>& cle_dechiffrement) 
	: cle_dechiffrement(cle_dechiffrement), cle_chiffrement(cle_dechiffrement)
{ }

//Génération du gros fichier
void BlueBigFile::generer()
{
	//0: Initialisation
	string donnee; char c='_';
	ifstream fichier;
	vector<int> tailles;
	vector<string>& fichiers = *liste_fichiers;
	
	//1: Ouverture/Création du fichier
	ofstream fichier_principal("" DOSSIER_EFFECTIF "/" "archive.blueroom", ios::binary);

	//2: Enregistrer le nombre de fichier
	donnee = to_string(fichiers.size());
	fichier_principal << donnee << " ";
	
	//3: Enregistrer la taille du nom de chaque fichier sur un octet
	for(size_t i = 0; i < fichiers.size(); i++)
		fichier_principal << (unsigned char)(fichiers[i].length()) << " ";
	
	//4: Enregistrer le nom de chaque fichier (tu ne devrais pas passer le DOSSIER )
	for(size_t i = 0; i < fichiers.size(); i++)
		fichier_principal << fichiers[i] << " ";

	//5: Enregistrer la taille de chaque fichier (ouverture, lecture, enregistrement)
	for(size_t i = 0; i < fichiers.size(); i++)
	{
		fichier.open("" DOSSIER_EFFECTIF "/" + fichiers[i], ifstream::ate | ifstream::binary);
		int taille =  fichier.tellg();
		tailles.push_back(taille);
		fichier_principal << taille << " ";
		fichier.close();
	}


	
	//6: Enregistrer chaque fichier
	for(size_t i = 0; i < fichiers.size(); i++)
	{
		fichier.open("" DOSSIER_EFFECTIF "/" + fichiers[i], ios::binary);
		for(size_t j = 0; j < tailles[i]; j++)
		{
			fichier >> noskipws >> c;
			if(!fichier.eof())
			{ 
				fichier_principal << c;
			}
		}
		fichier_principal << " ";
		fichier.close();
	}

	//7: Fermer le fichier principal
	fichier_principal.close();

	//8: Supprimer les bluecrypt
	for(size_t i = 0; i < liste_fichiers->size(); i++)
	{
		if(remove(("" DOSSIER_EFFECTIF "/" + (*liste_fichiers)[i]).c_str()) != 0)
			cout << "Impossibilite de supprimer le fichier d'origine" << endl;
		else
			cout << "Fichier d'origine supprime" << endl;
	}
}

//Déchiffrement du gros fichier en retournant les fichiers créés
vector<string> BlueBigFile::degenerer()
{
	//0: Initialisation
	int nb_fichiers;
	vector<unsigned char> tailles_nom;
	vector<string> noms_bluecrypt;
	string buffer_nom;
	string buffer_fichier;
	vector<int> tailles;
	int taille;
	ofstream fichier;

	// 1: Ouverture du fichier
	ifstream fichier_principal("" DOSSIER_EFFECTIF "/" "archive.blueroom", ios::binary);

	//2: Lire le nombre de fichier
	fichier_principal >> nb_fichiers;
	for(size_t i = 0; i < nb_fichiers; i++)
		tailles_nom.push_back(0);
	for(size_t i = 0; i < nb_fichiers; i++)
		noms_bluecrypt.push_back("");
	for(size_t i = 0; i < nb_fichiers; i++)
		tailles.push_back(0);

	//3: Lire la taille du nom de chaque fichier sur un octet
	for(size_t i = 0; i < nb_fichiers; i++)
		fichier_principal >> tailles_nom[i];

	//4: Lire le nom de chaque fichier
	for(size_t i = 0; i < nb_fichiers; i++)
	{
		fichier_principal.seekg((long)fichier_principal.tellg() + 1);
		for(size_t j = 0; j < tailles_nom[i]; j++)
		{
			buffer_nom.push_back(' ');
			fichier_principal.read(&(buffer_nom[j]), 1);
		}

		cout << buffer_nom << " - " << endl;
		noms_bluecrypt[i] = buffer_nom;
		buffer_nom.clear();
	}

	//5: Lire la taille de chaque fichier
	for(size_t i = 0; i < nb_fichiers; i++)
		fichier_principal >> tailles[i];

	//6: Recharger chaque fichier
	for(size_t i = 0; i < nb_fichiers; i++)
	{
		fichier_principal.seekg((long)fichier_principal.tellg() + 1);
		fichier.open("" DOSSIER_EFFECTIF "/" + noms_bluecrypt[i], ios::binary);
		int taille_totale_a_prendre = tailles[i];
		while(taille_totale_a_prendre != 0)
		{
			int taille_locale = TAILLE_BLOC_OCTET;
			if(taille_locale > taille_totale_a_prendre)
				taille_locale = taille_totale_a_prendre;
			char* buffer = new char[taille_locale];
			fichier_principal.read(buffer, taille_locale);
			fichier.write(buffer,taille_locale);
			delete[] buffer;
			taille_totale_a_prendre -= taille_locale;
		}

		fichier.close();
	}

	//7: Fermer le fichier principal
	fichier_principal.close();

	//8: Supprimer le fichier principal
	if(remove("" DOSSIER_EFFECTIF "/" "archive.blueroom") != 0)
		cout << "Impossibilite de supprimer le fichier d'origine" << endl;
	else
		cout << "Fichier d'origine supprime" << endl;

	return noms_bluecrypt;
}