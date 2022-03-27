/*____________definition de la classe game___________*/

#include <iostream> // Inclusion du bibliothèque standard d'entrée et de sortie
#include <string>   // Inclusion du bibliothèque des chaînes de caractère
#include "Game.h"   // Inclusion des prototypes de la classe Game
#include <string.h> // Inclusion du bibliothèque string

using namespace std; // Utiliser le nom standard du fonction

/* Constructeur de la class */
Game::Game()
{
    gridInit();       // initialiser le jeux
    turn = 1;         // initialiser le tour avec le joueur 1
    gameOver = false; // le jeux est en cours d'éxécution
}

/* Ititialiser la grille du jeu */
void Game::gridInit()
{ // Réinitialiser les valeurs du grille
    char c = '1';
    for (int i = 0; i < 3; i++)         // itérer les lignes
    {
        for (int j = 0; j < 3; j++)     // itérer les colonnes
        {
            grid[i][j] = c;
            c++;                        // Incrémenter le caractère
        }
    }
}

/* // Afficher la grille */
void Game::displayGrid()
{ 
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "\t";
        for (int j = 0; j < 3; j++)
        {
            cout << grid[i][j];                 // Afficher le contenu de la grille
            if (j < 2)
                cout << "   |   ";              // Ajouter de l'espace entre chaque numéros de position
        }
        if (i < 2)
            cout << "\n\t-----------------";    // Afficher un séparateur
        cout << endl;
    }
}

/* Remplir la case choisie par le joueur avec son symbol*/
bool Game::gridFill(char n, char playerChar)
{ // Remplir avec le caractère du joueur l'élément en position  n
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((grid[i][j] == n) && !((grid[i][j] == 'X') || (grid[i][j] == 'O'))) // verifier si la position choisi est libre et corresponde aux choix du joueur
            { 
                grid[i][j] = playerChar;        
                return true;
            }
        }
    }
    return false;
}

/* Jouer un tour */
void Game::playTurn()
{
    char choice = '1';
    bool reserve(false);
    
    if (turn == 1)      // Afficher les menus en fonction du joueur qui joue
    {
        cout << endl
             << "---------------------------------------------------------------" << endl;
        cout << "\tAu tour de " << playerOne << " de jouer, ton symbole est le X (Croix)" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "La Grille :" << endl;
        displayGrid();
        cout << endl
             << "Entrer votre choix : ";

        while (!reserve)                        // Redemmander le choix jusqu'à ce qu'une réponse valide
        {
            choice = manageInput();             // Valider les informations saisies
            
            reserve = gridFill(choice, 'X');    // remplir la girlle avec le symbol de l'utilisateur
            if (!reserve)
                cout << "Case déjà reserver ! veuillez ressayer = ";
        }
        cout << endl
             << "RESULTAT :" << endl;
        displayGrid();
        turn = 2;
        reserve = false;
        cout << endl
             << endl;
    }
    else if (turn == 2)
    {
        cout << endl
             << "---------------------------------------------------------------" << endl;
        cout << "\tAu tour de " << playerTwo << " de jouer, ton symbole est le O (Cercle)" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "La Grille :" << endl;
        displayGrid();
        cout << endl
             << "Entrer votre choix : ";

        while (!reserve)
        {
            choice = manageInput();                 // Valider les informations saisies
            reserve = gridFill(choice, 'O');        // remplir la girlle avec le symbol de l'utilisateur
            if (!reserve)
                cout << "Case déjà reserver ! veuillez ressayer = ";
        }
        cout << endl
             << "RESULTAT :" << endl;
        displayGrid();
        turn = 1;
        reserve = false;
        cout << endl
             << endl;
    }
    else
        cout << "\nErreur dans la gestion des tours \n";
}

/* Vérifier si la grille est pleinne */
bool Game::checkFull()
{
    int fill = 0;                        // compter les espaces occupés
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == 'X' || grid[i][j] == 'O')
            {
                fill++;
            }
        }
    }
    if (fill == 9)                       // les 9 cases de la grille sont remplies
    {
        gameOver = true;                 
        return true;
    }
    else
        return false;                    // la grille est remplies
}

/* Vérifier si 3 symboles de joueur sont alignés */
bool Game::check(char playerChar)
{
    // verifier les ligne
    for (int i = 0; i < 3; i++)
    {
        int match = 0;
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == playerChar)
                match++;
        }
        if (match == 3)         // vérifier le nombre de symbole sur la même ligne
            return true;
    }
    // Verifier les colonnes
    for (int i = 0; i < 3; i++)
    {
        int match = 0;
        for (int j = 0; j < 3; j++)
        {
            if (grid[j][i] == playerChar)
                match++;
        }
        if (match == 3)         // vérifier le nombre de symbole sur la même colonne
            return true;
    }

    // verifier les diagonales
    int match = 0;

    for (int i = 0; i < 3; i++)
    {
        if (grid[i][i] == playerChar)
        {
            match++;
        }
    }

    if (match == 3)
        return true;            // vérifier le nombre de symbole sur la la giagonal

    match = 0;
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][i] == playerChar)
        {
            match++;
        }
    }
    if (match == 3)
        return true;

    return false;
}

/* Vérifier si un des joueurs a gagné */
bool Game::chekWin()
{
    if (check('X') || check('O'))   /* Vérifier si un des joueurs a gagné */
        return true;
    else
        return false;
}

/* Lancer le jeu */
void Game::playGame()
{
    readme();               // afficher le readme
    cout << "Veuiller entrer le nom du joueur 1 : ";
    cin >> playerOne;       // récupérer le nom du joueur 1
    cout << "Veuiller entrer le nom du joueur 2 : ";
    cin >> playerTwo;       // récupérer le nom du joueur 2

    while (!gameOver)       // commuter les tours tant que le jeux est en cours
    {

        if (chekWin())      // annoncer le gagnant si un des joueur gagne
        {
            if (turn == 1)  //    
            { 
                char choice = 'N';
                cout << "\nBravo!!" << playerTwo << " Vous avez gagné " << endl;    // annoncer le résultat
                cout << "\nVoulez-vous recommencer à jouer (Y/N) ?" << endl;        // demander si les joueurs veulent encore jouer
                cin >> choice;
                if (choice == 'Y'||choice == 'y')
                {
                    replayGame();   // relancer le jeux
                }
                else
                {
                    endGame();      // terminer le jeu
                }
            }
            else
            {
                char choice = 'N';
                cout << "\nBravo!! " << playerOne << "  Vous avez gagné. " << endl;
                cout << "\nVoulez-vous recommencer à jouer (Y/N) ?" << endl;
                cin >> choice;
                if (choice == 'Y')
                {
                    replayGame();   // rejouer le jeu
                }
                else
                {
                    endGame();      // terminer le jeu
                }

            }
            break;
        }

        else if (checkFull())       // la grille est remplies
        {
            char ans = 'N';         
            cout << "Toutes les cases sont remplies, recommencer (Y/N)?" << endl;
            cin >> ans;
            if (ans == 'N')
                endGame();          // terminer le jeu

            else if(ans=='Y'||ans=='y')
                replayGame();       // rejouer le jeu

            else
                cout << "Error : manage input grid full err" << endl;
        }

        else
            playTurn();     // continuer le jeux tour par tour
    }
}

/* Rejuer le jeu */
void Game::replayGame()
{
    gameOver = false;       // le status du jeux est toujours en cours
    turn = 1;               // reinitialiser le tour avec le joueur 1
    gridInit();             // reinitialiser la grille
}

/* Gérer les données d'entrées de l'utilisateur*/
bool Game::isValidChoice(string c)
{
    for(int i=0;i<9;i++)
    {
        if(c == validChoice[i])     // vérifier si le donnée d'entrée fait partie de la liste des données d'entrée valide
            return true;
    }
    return false;
}

/* Controller les choix d'entrées de l'utilisateur */
char Game::manageInput()
{
    string input;                   // stocker les informations saisie par l'utilisateur
    cin >> input;                   // récupérer les valeurs
    while(!isValidChoice(input)){   // demander de nouvel choix tant que les données ne sont pas valide
        cout << "\nVeuiller choisir un nombre entre 1 et 9, Reéssayer ! = ";
        cin >> input;
    }
    return input[0];                // renvoyer le charactère
}

/* Stoper le jeu */
void Game::endGame()
{
    cout << "\nLe jeux est terminé" << endl;    // alerter les joueurs de l'arrêt du jeu
    gameOver = true;                            // game over
}

/* Afficher  */
void Game::drawRow()                            // afficher une ligne
{
   for(int i(0); i<40;i++) { 
        cout << "___";
    }
    cout << endl;
    cout<< endl;
}

/* Afficher un "lisez-moi" au début du jeux */
void Game::readme()
{
    cout << endl;
    drawRow();
    cout << "\t\t\t\t __________Bienvenue dans le jeu TIC TAC TOE !!________" << endl << endl ;
    cout << "\tOBJECTIF DU JEU :" << endl;
    cout << "\t\tPour gagner le jeu, vous devez aligner 3 symboles qui vous appartiennent sur une même ligne,"<<endl;
    cout << "\t\tcolonne ou sur une diagonale, \"Faites le avant votre adversaire !\""<< endl;
    cout << "\tRÈGLE DU JEU :" << endl;
    cout << "\t\tDeux joueurs s'affronteront, à tour de rôle chaque joueur aura l'occasion de placer son symbole"<<endl;
    cout << "\t\tAttention ! les choix valides sont les positions indiquées par un nombre compris entre [1] et [9]"<< endl;
    
    drawRow();
}

/* Destruction */

Game::~Game(){
}