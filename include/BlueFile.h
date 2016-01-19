#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define TAILLE_BLOC 1024
#define TAILLE_BLOC_OCTET TAILLE_BLOC*8
#define DOSSIER_EFFECTIF "datas"

class BlueFile
{
public:
	//Prépare pour la lecture
	BlueFile(string nom_fichier, bool cryptage, bool decryptage);

	//Détruit les données
	~BlueFile();

	//Lecture en binaire d'un fichier
	void lireBinaire();

	//Crypte l'ensemble des bits
	void crypter();

	//Décrypte l'ensemble des bits
	void decrypter();

	//Opère l'opération souhaitée
	void operer();

	//Réécris le fichier en binaire
	void ecrireBinaire();

	//Détecte si le fichier a fini d'être crypté
	int procedureFinie();

	//Affiche les bits
	void afficherBits();


private:

	//Détermine la taille du fichier
	void determineTaille();

	//Données
	string nom_fichier;
	vector<char> bits;
	int taille;

	//Fichier
	ifstream* fichier_lecture;
	ofstream* fichier_ecriture;

	//Opération
	bool cryptage;
	bool decryptage;

	//Analyse
	int passage;

};


//Whiax