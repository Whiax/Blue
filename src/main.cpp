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
	rep = opendir("./");
	struct dirent *lecture;
	while((lecture = readdir(rep)))
	{
		v = lecture->d_name;

		//Applique les conditions de sélections de fichiers (on ne prend que ceux qui ont une extension)
		if(v != "." && v != ".." && v.find('.') != string::npos)
			if(v.find(".txt") != string::npos) //TEST on ne prend que les txt durant les tests
				retour.push_back(lecture->d_name);

	}


	//Retour
	return retour;
}




//fonction principale
void main()
{
	listeFichier();

	getchar();
}

