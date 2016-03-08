#pragma once

#include "Header.h"



class BlueFile
{
public:
	//Pr�pare pour la lecture
	BlueFile(string nom_fichier, bool cryptage, bool decryptage, vector<char>& cle_cryptage, vector<char>& cle_decryptage);

	//D�truit les donn�es
	~BlueFile();

	//Lecture en binaire d'un fichier
	void lireBinaire();

	//Crypte l'ensemble des bits
	void crypter();

	//D�crypte l'ensemble des bits
	void decrypter();

	//Op�re l'op�ration souhait�e
	void operer();

	//R��cris le fichier en binaire
	void ecrireBinaire();

	//D�tecte si le fichier a fini d'�tre crypt�
	int procedureFinie();

	//Affiche les bits
	void afficherBits();

	//Supprime le fichier d'origine
	void suppression();

	//Renvoit le nom du fichier cr��
	string getNewName();


private:

	//D�termine la taille du fichier
	void determineTaille();

	//Choisis le nom des fichiers
	void creerNomsFichiers();

	//Donn�es
	string nom_fichier;
	vector<char> bits;
	int taille;

	//Fichier
	ifstream* fichier_lecture;
	ofstream* fichier_ecriture;
	string nom_lecture;
	string nom_ecriture;

	//Op�ration
	bool cryptage;
	bool decryptage;
	vector<char>& cle_cryptage;
	vector<char>& cle_decryptage;

	//Analyse
	int passage;

};


//Whiax