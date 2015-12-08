#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class BlueFile
{
public:
	//Lis le fichier et génère le tableau de bits
	BlueFile(string nom_fichier);

	//Crypte l'ensemble des bits
	void crypter();

	//Réécris le fichier en binaire
	void ecrireBinaire();

private:
	//Lecture en binaire d'un fichier
	void lireBinaire();


	string nom_fichier;
	vector<char> bits;
	int taille;

};