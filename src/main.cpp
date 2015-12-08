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
	string v;

	//Prend les fichiers un à un
	DIR *rep;
	rep = opendir("./datas/");
	struct dirent *lecture;
	while((lecture = readdir(rep)))
	{
		v = lecture->d_name;

		//Applique les conditions de sélections de fichiers (on ne prend que ceux qui ont une extension)
		if(v != "." && v != ".." && v.find('.') != string::npos)
			if(v.find(".txt") != string::npos) //TEST on ne prend que les txt durant les tests
				retour.push_back(lecture->d_name);

	}

	//Affichage basique des fichiers sélectionnés
	for(size_t i = 0; i < retour.size(); i++)
		cout << retour[i] << endl;

	//Retour
	return retour;
}

//Lecture en binaire d'un fichier
vector<bool> lireBinaire(string file_name)
{
	
}

//Crypte l'ensemble des bits
void crypter(vector<bool>& bin)
{

}

//Réécris le fichier en binaire
void ecrireBinaire(string file_name)
{

}


//Fonction principale
void main()
{
	//Récupère les fichiers à crypter
	vector<string> files = listeFichier();

	//Crypte la liste de fichier
	for(size_t i = 0; i < files.size(); i++)
	{
		string file_name = files[i];
		vector<bool> bin = lireBinaire(file_name);
		crypter(bin);
		ecrireBinaire(file_name);
	}
	
	getchar();
}

