#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

using namespace std;

//Fais la liste des fichiers courants
vector<string> listeFichier()
{
	//Init
	vector<string> retour;
	string nom_fichier;

	//Prend les fichiers un à un
	DIR *rep;
	rep = opendir("./datas/");
	struct dirent *lecture;
	while((lecture = readdir(rep)))
	{
		nom_fichier = lecture->d_name;

		//Applique les conditions de sélections de fichiers (on ne prend que ceux qui ont une extension)
		if(nom_fichier != "." && nom_fichier != ".." && nom_fichier.find('.') != string::npos)
			if(nom_fichier.find(".txt") != string::npos) //TEST on ne prend que les txt durant les tests
				retour.push_back(nom_fichier);

	}

	//Affichage basique des fichiers sélectionnés
	for(size_t i = 0; i < retour.size(); i++)
		cout << retour[i] << endl;

	//Retour
	return retour;
}

//Lecture en binaire d'un fichier
vector<bool> lireBinaire(string nom_fichier)
{
	
}

//Crypte l'ensemble des bits
void crypter(vector<bool>& bin)
{

}

//Réécris le fichier en binaire
void ecrireBinaire(string nom_fichier)
{

}


//Fonction principale
void main()
{
	//Récupère les fichiers à crypter
	vector<string> fichiers = listeFichier();

	//Crypte la liste de fichier
	for(size_t i = 0; i < fichiers.size(); i++)
	{
		string nom_fichier = fichiers[i];
		vector<bool> bin = lireBinaire(nom_fichier);
		crypter(bin);
		ecrireBinaire(nom_fichier);
	}
	
	getchar();
}

