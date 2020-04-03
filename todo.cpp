#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
using namespace std;

string give_date() // Permet de renvoyer la date du jour au format DDMMYYYY
{
    time_t temps;
    struct tm datetime;
    char  format[32];
    time(&temps);
    datetime = *localtime(&temps);
    strftime(format, 32, "%d%m%Y", &datetime);
    return format;
};

void list_all_tasks()
{
    string const nomFichier("events.txt");
    ifstream flux_lecture(nomFichier.c_str()); //ouverture du fichier .txt en mode lecture
    string ligne; 
    while(getline(flux_lecture, ligne)) //parcours tant qu'on est pas à la fin
        {
            std::cout << ligne << std::endl; //affichage classique
        }
};

void list_tasks(char* argv[])
{                        
    int search; //ici je crée une sorte de dictionnaire, à chaque attribut est associé un nombre de séparateur '/' à passer, noté dans search
    if(!strcmp(argv[2],"--creationdate"))
    {
        search = 3;
    }
    if(!strcmp(argv[2],"--closuredate"))
    {
        search = 4;
    }
    if(!strcmp(argv[2],"--status"))
    {
        search = 5;
    }
    if(!strcmp(argv[2],"--percent"))
    {
        search = 6;
    }
    if(!strcmp(argv[2],"--priority"))
    {
        search = 7;
    }
    string const nomFichier("events.txt");
    ifstream flux_lecture(nomFichier.c_str()); //ouverture du fichier en lecture
    string ligne;
    while(getline(flux_lecture, ligne))
        {
            int nbseparateurs = 0; //nombre de séparateurs parcourus pour le moment
            int lec = 0;    // numéro du caractère en lecture
            string buffer = ""; //stockage temporaire de la phrase lue
            while(lec<=ligne.size())
            {
                buffer += ligne[lec];
                if(ligne[lec]=='/') // si on croise un séparateur
                {
                    ++nbseparateurs; //on incrémente le nb de séparateurs
                    buffer = ""; //on supprime le stockage
                }
                ++lec; //on avance dans le texte 
            if (nbseparateurs == search && !strcmp(buffer.c_str(),argv[3])) //verifie qu'on a bien le bon nombre de séparateurs pour pointer le bon attribut et que le stockage temporaire correspond au bon attribut
            {
                std::cout << ligne << std::endl; //on affiche la bonne ligne
                ++lec;
            }
            }
        }
};

void add_task(char* argv[], int argc, std::ofstream& flux)
{
    if (flux)
    {
        flux.seekp(0, ios::end);  //On va à la fin du fichier
        int taille;
        taille = flux.tellp();
        int id = 1;
        if(taille != 0) //s'il est déjà initialisé on passe en lecture et on compte le nombres de ligne pour déterminer le prochain id
        {
            string const nomFichier("events.txt");
            ifstream flux_lecture(nomFichier.c_str());
            string ligne; 
            while(getline(flux_lecture, ligne))
                {
                    ++id;
                }
        }
        else // sinon id =1 et on rajoute un peu de graphisme rudimentaire
        {
            flux << "id/titre/description/datecreation/datedelete/status/percent/priority/commentaries" << endl;
        }
            const char* attribut[9]; //tableau de char qui sera concaténé pour obtenir la tâche en entier, permet de pas se préoccuper de l'ordre et de la présence de tous les attributs
            //attribut[0] = std::to_string(id);
            attribut[1] = ".";
            attribut[2] = ".";
            //attribut[3] = give_date();
            attribut[4] = "00000000";
            attribut[5] = "active";
            attribut[6] = "0";
            attribut[7] = ".";
            attribut[8] = ".";
            attribut[9] = ".";

            for (int iter=2; iter<argc; iter=iter+2) // on avance de 2 en 2 car on a la syntaxe "--attribut_k attribut_k"
            {
                if(!strcmp(argv[iter],"--title"))
                {
                    attribut[1] = argv[iter+1]; // le iter+1 permet d'accéder à la valeur de l'attribut --title
                }
                if(!strcmp(argv[iter],"--description"))
                {
                    attribut[2] = argv[iter+1];
                }
                if(!strcmp(argv[iter],"--priority"))
                {
                    attribut[7] = argv[iter+1];
                }
                if(!strcmp(argv[iter],"--commentaries"))
                {
                    attribut[8] = argv[iter+1];
                } 
            }
            std::string nb = std::to_string(id);  
            for(int iter=0; iter<=9; iter=iter+1) //ici on concatène le tableau de char attribut en mettant des séparateurs
            {
                nb += attribut[iter];
                if(iter!=9)
                {
                    nb += "/";
                }
                if(iter==2)
                {
                    nb += give_date();
                    nb += "/";
                    iter = 3;
                }
            }
            flux << nb << endl;
            cout << "Vous avez créé la tâche :" << endl;
            cout << nb << endl;
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
};

void edit_tasks(char* argv[], std::ofstream& flux)
{
    int Line_to_Erase = atoi(argv[2]); //l'id nous donne la ligne a remplacer "à effacer puis réécrire"
    int search;
    if(!strcmp(argv[3],"--title")) //dictionnaire précédemment rencontré, plus large car on peut modifier plsu d'attributs que ceux sur lesquels on trie
    {
        search = 1;
    }
    if(!strcmp(argv[3],"--description"))
    {
        search = 2;
    }
    if(!strcmp(argv[3],"--status"))
    {
        search = 5;
    }
    if(!strcmp(argv[3],"--percent"))
    {
        search = 6;
    }
    if(!strcmp(argv[3],"--priority"))
    {
        search = 7;
    }
    if(!strcmp(argv[3],"--commentaries"))
    {
        search = 8;
    }
    if(!strcmp(argv[3],"--subtasks"))
    {
        search = 9;
    }
    std::string Buffer = ""; //Variable contenant le texte à réécrire dans le fichier
    std::ifstream ReadFile("events.txt");
    if (ReadFile) //Si le fichier est trouvé (évite les erreurs inutiles)
    {
        std::string line;
        int Line = 0;
        while (std::getline(ReadFile, line)) //on parcourt le fichier par ligne
        {
            Line++;
            if(Line != Line_to_Erase) //Si la ligne atteinte est différente de la ligne à modifier
            {
                Buffer += line + "\n"; //On ajoute le contenu de la ligne dans le contenu à réécrire
            }
            if(Line == Line_to_Erase) //sinon on traite la ligne à modifier
            {
                std::string newline = "";
                int curseur = 0; //numéro de caractère lu
                int nbslashes = 0; //nombres de séparateurs rencontrés
                while(curseur<=line.size()) // bloc qui permet de trouver l'attribut à modifier
                {
                    if(nbslashes == search)
                    {
                        newline += argv[4];
                        if(search<9)
                        {
                        newline += "/";
                        }
                        while(nbslashes == search)
                        {
                            ++curseur;
                            if(line[curseur]=='/') //on incrémente le compteur de séparateurs à la rencontre d'un slash
                            {
                                ++nbslashes;
                            }
                        }
                    }
                    else
                    {
                        newline += line[curseur]; //on ajoute à la ligne nouvelle, hors zone de modification, ses caractères habituels
                    }
                    if(line[curseur]=='/')
                    {
                        ++nbslashes; //on incrémente le compteur de séparateurs à la rencontre d'un slash
                    }
                    ++curseur;
                }
                Buffer += newline + "\n"; // on ajotue la ligne et on saute une ligne
            }
        }

    ReadFile.close(); //On ferme le fichier en lecture
    std::ofstream WriteFile("events.txt"); //On ouvre ce même fichier en écriture
    WriteFile << Buffer; //On écrit le texte dedans
    WriteFile.close();  //Et on ferme définitivement
    }
};

int main(int argc, char* argv[]) // permet l'interaction in-line
{
    string const nomFichier("events.txt");
    ofstream monFlux(nomFichier.c_str(), ios::app);
    if (!strcmp(argv[1], "add")) //par disjonction sur le mot tapé après le nom du programme
    {
        add_task(argv, argc, monFlux);
    }
    if (!strcmp(argv[1], "list"))
    {
        if(!strcmp(argv[2], "all"))
        {
            list_all_tasks();
        }
        else
        {
            list_tasks(argv);
        }
    }
    if (!strcmp(argv[1], "edit"))
    {
        edit_tasks(argv, monFlux); 
    }
}