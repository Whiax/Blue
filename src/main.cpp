#include <dirent.h>

#include "../include/BlueFile.h"
#include "../include/BlueBigFile.h"


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
	cout << "- Pour chiffrer les fichiers, mettez un fichier bluedoor.txt contenant la cle de codage" << endl;
	cout << "- Pour dechiffrer les fichiers, mettez un fichier bluekey.txt contenant la cle de decodage" << endl;
	cout << "- Les fichiers subiront quoiqu'il arrive les instructions de codage ou decodage" << endl;
	cout << "- Il est donc important de ne chiffrer que les fichiers non chiffres et de ne dechiffrer que les fichiers chiffres" << endl;
	cout << "FIN INSTRUCTIONS" << endl;
	cout << "_________" << endl;
	cout << endl << endl;

}

//Renvoit les clés de chiffrement des fichiers door et key
vector<vector<char>> recupererCle(string nom_fichier_door, string nom_fichier_key)
{
	//Initialisation
	vector<vector<char>> cles_de_chiffrement;

	//Porte
	vector<char> serrure;
	if(nom_fichier_door != "")
	{
		cout << "./" DOSSIER_EFFECTIF  "/ " + nom_fichier_door << endl;
		ifstream fichier_door("./" DOSSIER_EFFECTIF  "/" +nom_fichier_door, ios::binary);
		char c = '_';
		while(!fichier_door.eof())
		{
			fichier_door >> noskipws >> c;
			//lecture bit par bit
			if(!fichier_door.eof())
				for(int i = 7; i >= 0; i--)
					serrure.push_back(((c >> i) & 1));

		}
		fichier_door.close();
	}
	cles_de_chiffrement.push_back(serrure);
	

	//Clé
	vector<char> cle;
	if(nom_fichier_key != "")
	{
		ifstream fichier_key("./" DOSSIER_EFFECTIF  "/" + nom_fichier_key, ios::binary);
		char c = '_';
		while(!fichier_key.eof())
		{
			fichier_key >> noskipws >> c;
			//lecture bit par bit
			if(!fichier_key.eof())
				for(int i = 7; i >= 0; i--)
					cle.push_back(((c >> i) & 1));

		}
		fichier_key.close();
	}
	cles_de_chiffrement.push_back(cle);
	


	//Retour
	return cles_de_chiffrement;
}

//Fonction principale
void main()
{
	

	//Recupère les fichiers à chiffrer/dechiffrer
	vector<string> fichiers = listeFichier();

	//Cherche à savoir s'il faut chiffrer ou dechiffrer
	vector<string>::iterator position_door = find(fichiers.begin(), fichiers.end(), "bluedoor.txt");
	vector<string>::iterator position_key = find(fichiers.begin(), fichiers.end(), "bluekey.txt");
	bool chiffrer = position_door != fichiers.end();
	bool dechiffrer = position_key != fichiers.end();

	//Récupère les clés de chiffrement
	vector<vector<char>> cles = recupererCle(chiffrer ? *position_door : "", dechiffrer ? *position_key : "");
	
	//Supprime les fichiers door et key de la liste des fichiers
	if(chiffrer)
		fichiers.erase(position_door);
	if(dechiffrer)
		fichiers.erase(position_key);

	//Si aucun des fichiers n'est present
	if(!chiffrer && !dechiffrer)
		afficherInstructions();


	

	//Sinon chiffre/Dechiffre la liste de fichier
	else
	{
		//Si on souhaite déchiffrer, on commence par dégrouper les .bluecrypt
		if(dechiffrer)
		{
			BlueBigFile big_file(cles[1]);
			vector<string> nouveaux_bluecrypt = big_file.degenerer();
			fichiers.insert(fichiers.end(), nouveaux_bluecrypt.begin(), nouveaux_bluecrypt.end());
		}

		//Si on souhaite déchiffrer des fichiers, on ne déchiffre que les .bluecrypt
		if(dechiffrer)
		{
			for(int i = fichiers.size() - 1; i >= 0; --i)
			{
				string nom_fichier = fichiers[i];
				if(nom_fichier.find(".bluecrypt") == string::npos)
					fichiers.erase(fichiers.begin() + i);
			}
		}
		
		//On parcourt et on opère sur la liste des fichiers
		vector<string> nouveaux_noms;
		for(size_t i = 0; i < fichiers.size(); i++)
		{
			string nom_fichier = fichiers[i];
			BlueFile fichier(nom_fichier, chiffrer, dechiffrer, cles[0], cles[1]);
			do
			{
				fichier.lireBinaire();
				fichier.operer();
				fichier.ecrireBinaire();
			} while(!fichier.procedureFinie());
			fichier.suppression();
			
			//Si on chiffre, on enregistre les nouveaux noms de fichiers
			if(chiffrer)
				nouveaux_noms.push_back(fichier.getNewName());

		}

		//Si on chiffre on met tout dans un seul fichier
		if(chiffrer)
		{
			BlueBigFile big_file(nouveaux_noms, cles[0]);
			big_file.generer();
		}
		
	}
		
	//Fin du programme
	cout << endl << "OPERATION TERMINEE" << endl << "Fermer le programme en appuyant sur entree...";
	getchar();
}

//Whiax