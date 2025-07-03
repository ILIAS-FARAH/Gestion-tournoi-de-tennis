#include <iostream>
#include <string>
#include<vector>
#include <cstdlib>
#include <ctime>
using namespace std;


//-----------------------------------------------------------------------------CLASS JOUEUR-----------------------------------------------------------------------------------------------

class Joueur{
private:
static int compteur;
int id;
string nom;
int score;
public:
    Joueur(string name):id(++compteur),nom(name),score(rand()%101 + 0){} // Generates a score between 0 and 100

    string getNom(){
    return nom;}
    int getId(){
    return id;}
    int getScore(){
    return score;}
};
int Joueur::compteur=0;
//-------------------------------------------------------------------------------CLASS TERRAIN-----------------------------------------------------------------------------------------------

class Terrain{
private:
string nom;
int capacite;
public:
    Terrain(string name,int capacite):nom(name),capacite(capacite){}
    string getNom(){
    return nom;}
    int getCapacite(){
    return capacite;}


};
//---------------------------------------------------------------------------------CLASS PARTIE-----------------------------------------------------------------------------------------------

class Partie{
public:
    static int comp;
    int idpartie;
    Joueur j1;
    Joueur j2;
    string phase;
    string nomterrain;
    Partie(Joueur joueur1,Joueur joueur2,string phase,string nomterrain):idpartie(++comp),j1(joueur1),j2(joueur2),phase(phase),nomterrain(nomterrain){}

     Joueur getvainqueure(){
     if(j1.getScore()>j2.getScore()){
        return j1;
     }
    else{
        return j2;
    }
     }
};
int Partie::comp=0;

//---------------------------------------------------------------------------------CLASS TICKET-----------------------------------------------------------------------------------------------
class Ticket{
 private:
     static int counter;
     int ticketid;
     int partieid;
     string nomsupp;
     float prix;
     public:
    Ticket(int pid,string name,float prix):ticketid(++counter),partieid(pid),nomsupp(name),prix(prix){}
    int getTicketId(){
    return ticketid;}
    int getPartieId(){
    return partieid;}
    string getNomSupp(){
    return nomsupp;}
    float getPrix(){
    return prix;}
};
int Ticket::counter=0;
//---------------------------------------------------------------------------------CLASS GESTIONTICKETS-----------------------------------------------------------------------------------------------
class gestiontickets {
private:
    vector<Ticket> tickets;               
    vector<Terrain> terrains;          
    vector<int> reservedTickets;      

public:
    
    gestiontickets(const vector<Terrain>& t) {
        terrains = t;  
        reservedTickets.resize(terrains.size(), 0);  
    //La redimension de reservedTickets à la même taille que terrains permet probablement de créer un tableau qui associe chaque terrain à un nombre de billets réservés.
    //En initialisant tous les éléments à 0, cela signifie que aucun billet n'est réservé pour aucun terrain au départ. Cela suggère que la classe gestiontickets gère la 
    //réservation de billets pour des terrains, et que reservedTickets est utilisé pour stocker l'état de réservation pour chaque terrain.
    }

    
    float getticketprice(const string& phase) {
        if (phase == "Eliminatoires") return 25;
        if (phase == "Huitiemes") return 50;
        if (phase == "quartdefinal") return 75;
        if (phase == "demifinal") return 100;
        if (phase == "TroisiemePlace") return 125;
        if (phase == "Finals") return 150;
        return 30.0;  
        //return un prix en fonction de la phase
    }


    int reserverticket(string terrainName, int partieid,  string supporterName, string phase) {
        for (size_t i = 0; i < terrains.size(); ++i) {
            if (terrains[i].getNom() == terrainName) { //parcourire terrains pour trouve le nom du terrain
                if (reservedTickets[i] >= terrains[i].getCapacite()) { //Si le terrain est trouvé et a des billets disponibles
                    //   (c'est-à-dire que reservedTickets[i] est inférieur à la capacité du terrain
                    cout << "No more tickets available for terrain: " << terrainName << endl;
                    return 1; 
                }

                
                float ticketPrice = getticketprice(phase);//Calcule le prix du billet en fonction de la phase.
                Ticket t(partieid, supporterName, ticketPrice);//Crée un nouvel objet Ticket avec l'ID de la partie (partieid), 
                //le nom du supporteur (supporterName) et le prix du billet.
                tickets.push_back(t);//Ajoute le billet au vecteur tickets.
                reservedTickets[i]++;//Incrémente le compteur reservedTickets pour le terrain.
                cout << "Ticket reserved successfully for terrain: " << terrainName << endl;
                return 0; 
            }
        }

        cout << "Terrain not found: " << terrainName << endl;
        return 1; 
    }

   
    void affichagetickets()  {
        for (auto& y : tickets) {
            cout << "Ticket ID: " << y.getTicketId()
                 << ", Partie ID: " << y.getTicketId()
                 << ", Supporter Name: " << y.getNomSupp()
                 << ", Price: " << y.getPrix() << endl;
        }
    }

   
    void affichagecapacites()  {
        for (size_t i = 0; i < terrains.size(); ++i) {
            cout << "Terrain: " << terrains[i].getNom()
                 << ", Capacity: " << terrains[i].getCapacite()
                 << ", Reserved Tickets: " << reservedTickets[i] << endl;
  }
}
};
//---------------------------------------------------------------------------------CLASS GESTIONJOUEUR-----------------------------------------------------------------------------------------------
class gestionjoueur{
public :
    vector <Joueur> joueurs;

    void ajoutjoueur(string name){
      Joueur j(name);
      joueurs.push_back(j);
    }
    void suppjoueur(string nom){
        auto it=joueurs.begin();
        for(auto &e:joueurs){
            if(e.getNom()==nom){
                break;
            }
            it++;
        }
        joueurs.erase(it);
    }
    void recherchejoueur(string nom){
           for(auto &e:joueurs){
            if(e.getNom()==nom){
               cout <<"le joueur existe cest :"<<endl;
               cout << "ID: " <<e.getId()<<" SON NOM: "<<e.getNom() <<" SON SCORE: "<<e.getScore()<<endl;
               cout <<"---------------------------------------"<<endl;
               break;
            }

        }
        return;
        cout<<"joueur n'existe pas. '"<<endl;
    }
    void affichage(){
    for(auto &t:joueurs){
       cout << "ID: "<<t.getId()<<" NOM DU JOUEUR: "<<t.getNom() <<" SON SCORE: "<<t.getScore()<<endl;

    }

    }

};
//---------------------------------------------------------------------------------CLASS GESTIONTERRAIN-----------------------------------------------------------------------------------------------
class gestionterrain{
    public:
 vector <Terrain> terrains;
  void ajoutterrain(string name, int capacite, gestiontickets& gestionTickets) {
        Terrain t(name, capacite);
        terrains.push_back(t);
//Elle crée un nouvel objet Terrain t avec le nom et la capacité donnés, l'ajoute au vecteur terrains, puis crée un nouvel objet gestiontickets avec le vecteur terrains mis à jour
// et l'assigne à la référence gestionTickets.      
        gestionTickets = gestiontickets(terrains); 
    }
void suppterrain(string name){
    auto it=terrains.begin();
        for(auto &e:terrains){
            if(e.getNom()==name){
                break;
            }
            it++;
        }
        terrains.erase(it);
    }
    void affichage(){
    for(auto &t:terrains){
       cout <<"NOM DU TERRAIN: "<<t.getNom() <<" CAPACITE: "<<t.getCapacite()<<endl;

    }
    }
};
//---------------------------------------------------------------------------------CLASS GESTIONPARTIES--------------------------------------------------------------------------------
class gestionparties{
public:
    vector <Partie> parties;

    void creerpartie(Joueur j1,Joueur j2,string phase,string nomterrain){
    Partie p(j1,j2,phase,nomterrain);
    parties.push_back(p);
    }


void afficherPartiesParPhase(string phase) {
    cout << "Phase: " << phase << endl;
    for (auto &i : parties) {
        if (i.phase == phase) {
            cout << "partie: " << i.idpartie << "(" << i.phase << ") "
                 << i.j1.getNom() << " vs " << i.j2.getNom() << " dans le terrain: "<<i.nomterrain<<endl;
        }
    }

}

void affichervainqeure(){
for(auto &i:parties){
    cout <<"partie: "<<i.idpartie <<" vainqueure est: "<< i.getvainqueure().getNom()<<endl;
}
}
void afficherchampion() {
    if (parties.empty()) { 
        cout << "Aucune partie n'a été jouée, pas de champion." << endl;
        return;
    }

 
    Joueur champion = parties.back().getvainqueure(); 
    cout << "Le champion est : " << champion.getNom()
         << " avec un score de " << champion.getScore() << endl;
         //elle récupère le vainqueur de la dernière partie (parties.back().getvainqueure()) et affiche son nom et son score.







}

};
//-------------------------------------------------------------------------------------ATTRIBUTION ALEATOIRE-------------------------------------------------------------------------------------
vector<Joueur> attribueraleatoire(vector <Joueur> joueurs,vector <Terrain> terrains,gestionparties &g,string phase){
//Cette fonction simule une compétition aléatoire entre des joueurs (Joueur) sur différents terrains (Terrain). Elle prend en entrée une liste de joueurs, une liste de terrains,
//un objet gestionparties (qui gère les parties/matches), et une chaîne de caractères représentant une phase.
gestionparties t;
vector <Joueur> jg;
vector <Joueur> joueurrestant=joueurs;
vector <Terrain> terrrestant=terrains;
//Elle crée des copies des listes d'entrée (joueurrestant et terrrestant) pour éviter de modifier les originaux.
while (joueurrestant.size() >=2){
    //À l'intérieur de la boucle, elle sélectionne de manière aléatoire deux joueurs (j1 et j2) dans joueurrestant et les supprime de la liste.
    int index=rand()%joueurrestant.size();
    Joueur j1=joueurrestant[index];
    joueurrestant.erase(joueurrestant.begin()+index);

int index2=rand()%joueurrestant.size();
    Joueur j2=joueurrestant[index2];
    joueurrestant.erase(joueurrestant.begin()+index2);

int ind=rand()%terrains.size();
 Terrain t1=terrrestant[ind];
 //Elle sélectionne de manière aléatoire un terrain (t1) dans terrrestant.

   g.creerpartie(j1,j2,phase,t1.getNom());
   //Elle crée une nouvelle partie/match entre j1 et j2 sur le terrain t1 en utilisant la méthode creerpartie de l'objet gestionparties.
    jg.push_back(g.parties.back().getvainqueure());
    //Elle ajoute le vainqueur du match (déterminé par getvainqueure) à une nouvelle liste (jg).

}


return jg;




};






//--------------------------------------------------------------------------------------------------MENU PRINCIPAL--------------------------------------------------------------------------------
int main()
{
    srand(static_cast<unsigned>(time(0))); // Initialize random seed
    gestionjoueur gestionJoueurs;
    gestionterrain gestionTerrains;
    gestionparties gestionParties;
    gestiontickets gestionTickets(gestionTerrains.terrains);


    int choix;
    do {
        cout << "\n*********** Menu Principal ***********\n";
        cout << "1. Ajouter un joueur\n";
        cout << "2. Supprimer un joueur\n";
        cout << "3. Rechercher un joueur\n";
        cout << "4. Afficher tous les joueurs\n";
        cout << "5. Ajouter un terrain\n";
        cout << "6. Supprimer un terrain\n";
        cout << "7. Afficher tous les terrains\n";
        cout << "8. Créer un tournoi\n";
        cout << "9. Afficher les parties par phase\n";
        cout << "10. Afficher les vainqueurs des parties\n";
        cout << "11. Afficher le champion\n";
        cout << "12. Réserver un ticket\n";
        cout << "13. Afficher tous les tickets réservés\n";
        cout << "0. Quitter\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1: {
                string nom;
                cout << "Entrez le nom du joueur : ";
                cin >> nom;
                gestionJoueurs.ajoutjoueur(nom);
                cout << "Joueur ajouté avec succès.\n";
                break;
            }
            case 2: {
                string nom;
                cout << "Entrez le nom du joueur à supprimer : ";
                cin >> nom;
                gestionJoueurs.suppjoueur(nom);
                cout << "Joueur supprimé avec succès.\n";
                break;
            }
            case 3: {
                string nom;
                cout << "Entrez le nom du joueur à rechercher : ";
                cin >> nom;
                gestionJoueurs.recherchejoueur(nom);
                break;
            }
            case 4:
                cout << "Liste des joueurs :\n";
                gestionJoueurs.affichage();
                break;

            case 5: {
                string nom;
                int capacite;
                cout << "Entrez le nom du terrain : ";
                cin >> nom;
                cout << "Entrez la capacité du terrain : ";
                cin >> capacite;
                gestionTerrains.ajoutterrain(nom, capacite,gestionTickets);
                cout << "Terrain ajouté avec succès.\n";
                break;
            }
            case 6: {
                string nom;
                cout << "Entrez le nom du terrain à supprimer : ";
                cin >> nom;
                gestionTerrains.suppterrain(nom);
                cout << "Terrain supprimé avec succès.\n";
                break;
            }
            case 7:
                cout << "Liste des terrains :\n";
                gestionTerrains.affichage();
                break;

            case 8: {
            
            gestionJoueurs.joueurs = attribueraleatoire(gestionJoueurs.joueurs, gestionTerrains.terrains, gestionParties, "Eliminatoires");
            gestionParties.afficherPartiesParPhase("Eliminatoires");

            gestionJoueurs.joueurs = attribueraleatoire(gestionJoueurs.joueurs, gestionTerrains.terrains, gestionParties, "Huitiemes");
            gestionParties.afficherPartiesParPhase("Huitiemes");

            gestionJoueurs.joueurs = attribueraleatoire(gestionJoueurs.joueurs, gestionTerrains.terrains, gestionParties, "quartdefinal");
            gestionParties.afficherPartiesParPhase("quartdefinal");

            gestionJoueurs.joueurs = attribueraleatoire(gestionJoueurs.joueurs, gestionTerrains.terrains, gestionParties, "demifinal");
            gestionParties.afficherPartiesParPhase("demifinal");

            gestionJoueurs.joueurs = attribueraleatoire(gestionJoueurs.joueurs, gestionTerrains.terrains, gestionParties, "TroisiemePlace");
            gestionParties.afficherPartiesParPhase("TroisiemePlace");

            gestionJoueurs.joueurs = attribueraleatoire(gestionJoueurs.joueurs, gestionTerrains.terrains, gestionParties, "Finals");
            gestionParties.afficherPartiesParPhase("Finals");
            break;
        }
        case 9: {
            string phase;
            cout << "Entrez la phase à afficher : ";
            cin >> phase;
            cin.ignore();  
            gestionParties.afficherPartiesParPhase(phase);
            break;
        }
            case 10:
                cout << "Liste des vainqueurs de chaque partie :\n";
                gestionParties.affichervainqeure();
                break;

            case 11:
                gestionParties.afficherchampion();
                break;

            case 12: {

                int partieId;
                string nomSupporter;
                string phase;
                string terrainname;
                cout << "Entrez l id de la partie : ";
                cin >> partieId;
                cout << "Entrez Votre Nom : ";
                cin >> nomSupporter;
                cout << "Entrez la phase de la partie (Eliminatoires,Huitiemes, quartdefinal, demifinal,TroisiemePlace,Finals) : ";
                cin >> phase;
                cout <<"donner le nom du terrain : ";
                cin>> terrainname;

                if(gestionTickets.reserverticket(terrainname,partieId, nomSupporter,phase)==1){
                  cout<<"could not reserve tickets"<<endl;
                }
                else{
                cout <<"ticket reserved succefully"<<endl;
                }
                break;
            }
            case 13:
                cout << "Liste des tickets réservés :\n";
                gestionTickets.affichagetickets();
                break;

            case 0:
                cout << "BYE <3\n";
                break;

            default:
                cout << "Choix invalide. Veuillez réessayer.\n";
        }
    } while (choix != 0);




return 0;
}