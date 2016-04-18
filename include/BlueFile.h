#pragma once

#include "Header.h"



class BlueFile
{
public:
	//Pr�pare pour la lecture
	BlueFile(string nom_fichier, bool chiffrement, bool dechiffrement, vector<char>& cle_chiffrement, vector<char>& cle_dechiffrement);

	//D�truit les donn�es
	~BlueFile();

	//Lecture en binaire d'un fichier
	void lireBinaire();

	//chiffre l'ensemble des bits
	void chiffrer();

	//D�chiffre l'ensemble des bits
	void dechiffrer();

	//Op�re l'op�ration souhait�e
	void operer();

	//R��cris le fichier en binaire
	void ecrireBinaire();

	//D�tecte si le fichier a fini d'�tre chiffr�
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
	bool chiffrement;
	bool dechiffrement;
	vector<char>& cle_chiffrement;
	vector<char>& cle_dechiffrement;

	//Analyse
	int passage;

};


//Whiax