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
	//Pr�pare pour la lecture
	BlueFile(string nom_fichier);

	//D�truit les donn�es
	~BlueFile();

	//Lecture en binaire d'un fichier
	void lireBinaire();

	//Crypte l'ensemble des bits
	void crypter();

	//D�crypte l'ensemble des bits
	void decrypter();

	//R��cris le fichier en binaire
	void ecrireBinaire();

	//D�tecte si le fichier a fini d'�tre crypt�
	bool procedureFinie();
private:

	//D�termine la taille du fichier
	void determineTaille();

	//Donn�es
	string nom_fichier;
	vector<char> bits;
	int taille;

	//Fichier
	ifstream* fichier_lecture;

};