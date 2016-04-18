#pragma once

#include "Header.h"



class BlueFile
{
public:
	//Prépare pour la lecture
	BlueFile(string nom_fichier, bool chiffrement, bool dechiffrement, vector<char>& cle_chiffrement, vector<char>& cle_dechiffrement);

	//Détruit les données
	~BlueFile();

	//Lecture en binaire d'un fichier
	void lireBinaire();

	//chiffre l'ensemble des bits
	void chiffrer();

	//Déchiffre l'ensemble des bits
	void dechiffrer();

	//Opère l'opération souhaitée
	void operer();

	//Réécris le fichier en binaire
	void ecrireBinaire();

	//Détecte si le fichier a fini d'être chiffré
	int procedureFinie();

	//Affiche les bits
	void afficherBits();

	//Supprime le fichier d'origine
	void suppression();

	//Renvoit le nom du fichier créé
	string getNewName();


private:

	//Détermine la taille du fichier
	void determineTaille();

	//Choisis le nom des fichiers
	void creerNomsFichiers();

	//Données
	string nom_fichier;
	vector<char> bits;
	int taille;

	//Fichier
	ifstream* fichier_lecture;
	ofstream* fichier_ecriture;
	string nom_lecture;
	string nom_ecriture;

	//Opération
	bool chiffrement;
	bool dechiffrement;
	vector<char>& cle_chiffrement;
	vector<char>& cle_dechiffrement;

	//Analyse
	int passage;

};


//Whiax