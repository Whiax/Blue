#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define BLOCK_SIZE 1024

class BlueFile
{
public:
	//Prépare pour la lecture
	BlueFile(string nom_fichier);

	//Détruit les données
	~BlueFile();

	//Lecture en binaire d'un fichier
	void lireBinaire();

	//Crypte l'ensemble des bits
	void crypter();

	//Décrypte l'ensemble des bits
	void decrypter();

	//Réécris le fichier en binaire
	void ecrireBinaire();

	//Détecte si le fichier a fini d'être crypté
	bool procedureFinie();
private:

	//Détermine la taille du fichier
	void determineTaille();

	//Données
	string nom_fichier;
	vector<char> bits;
	int taille;

	//Fichier
	ifstream* fichier_lecture;

};