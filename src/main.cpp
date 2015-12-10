#include <dirent.h>

#include "../include/BlueFile.h"


//Fais la liste des fichiers courants
vector<string> listeFichier()
{
	//Init
	vector<string> retour;
	string nom_fichier;

	//Prend les fichiers un à un
	DIR *rep;
	rep = opendir("./" DOSSIER_EFFECTIF  "/ ");
	struct dirent *lecture;
	while((lecture = readdir(rep)))
	{
		nom_fichier = lecture->d_name;

		//Applique les conditions de selections de fichiers (on ne prend que ceux qui ont une extension)
		if(nom_fichier != "." && nom_fichier != ".." && nom_fichier.find('.') != string::npos)
			//if(nom_fichier.find(".txt") != string::npos) //TEST on ne prend que les txt durant les tests
			if(nom_fichier != "Blue.exe") //Conditions de nom
				retour.push_back(nom_fichier);

	}

	//Affichage basique des fichiers selectionnes
	cout << "Fichiers:" << endl;
	for(size_t i = 0; i < retour.size(); i++)
		cout << "   * " << retour[i] << endl;
	cout << "_______" << endl << endl;

	//Retour
	return retour;
}

//Affiche les instructions du logiciel
void afficherInstructions()
{
	cout << "_________" << endl;
	cout << "INSTRUCTIONS" << endl;
	cout << "- L'ensemble des fichiers a la racine du fichier contenant le logiciel seront affectes" << endl;
	cout << "- Pour crypter les fichiers, mettez un fichier bluedoor.txt contenant la cle de codage" << endl;
	cout << "- Pour decrypter les fichiers, mettez un fichier bluekey.txt contenant la cle de decodage" << endl;
	cout << "- Les fichiers subiront quoiqu'il arrive les instructions de codage ou decodage" << endl;
	cout << "- Il est donc important de ne crypter que les fichiers non cryptes et de ne decrypter que les fichiers cryptes" << endl;
	cout << "FIN INSTRUCTIONS" << endl;
	cout << "_________" << endl;
	cout << endl << endl;

}

//Fonction principale
void main()
{
	//Recupère les fichiers à crypter/decrypter
	vector<string> fichiers = listeFichier();

	//Cherche à savoir s'il faut crypter ou decrypter
	vector<string>::iterator position_door = find(fichiers.begin(), fichiers.end(), "bluedoor.txt");
	vector<string>::iterator position_key = find(fichiers.begin(), fichiers.end(), "bluekey.txt");
	bool crypter = position_door != fichiers.end();
	bool decrypter = position_key != fichiers.end();
	
	//Supprime les fichiers door et key
	if(crypter)
		fichiers.erase(position_door);
	if(decrypter)
		fichiers.erase(position_key);

	//Si aucun des fichiers n'est present
	if(!crypter && !decrypter)
		afficherInstructions();
	

	//Crypte/Decrypte la liste de fichier
	else
		for(size_t i = 0; i < fichiers.size(); i++)
		{
			string nom_fichier = fichiers[i];
			BlueFile fichier(nom_fichier);
			do
			{
				fichier.lireBinaire();
				if(crypter)
					fichier.crypter();
				if(decrypter)
					fichier.decrypter();
				fichier.ecrireBinaire();
			} while(!fichier.procedureFinie());
		}
	
	getchar();
}

//Whiax