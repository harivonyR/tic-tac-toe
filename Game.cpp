/*____________definition de la classe game___________*/

#include <iostream> // Inclusion du bibliothèque standard d'entrée et de sortie
#include <string>   // Inclusion du bibliothèque des chaînes de caractère
#include "Game.h"   // Inclusion des prototypes de la classe Game
#include <string.h>

using namespace std; // Utiliser le nom standard du fonction

Game::Game()
{
    gridInit();       // initialiser le jeux
    turn = 1;         // initialiser le tour avec le joueur 1
    gameOver = false; // le jeux est en cours d'éxécution
}

void Game::gridInit()
{ // Réinitialiser les valeurs du grille
    char c = '1';
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            grid[i][j] = c;
            c++; // Incrémenter le caractère
        }
    }
}

void Game::displayGrid()
{ // Afficher la grille
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "\t";
        for (int j = 0; j < 3; j++)
        {
            cout << grid[i][j]; // Afficher le contenu de la grille
            if (j < 2)
                cout << "   |   "; // Ajouter de l'espace entre chaque numéros de position
        }
        if (i < 2)
            cout << "\n\t-----------------";
        cout << endl;
    }
}

bool Game::gridFill(char n, char playerChar)
{ // Remplir avec le caractère du joueur l'élément en position  n
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((grid[i][j] == n) && !((grid[i][j] == 'X') || (grid[i][j] == 'O')))
            { // verifier si la position choisi est déja rempli
                grid[i][j] = playerChar;
                return true;
            }
        }
    }
    return false;
}

void Game::playTurn()
{
    char choice = '1';
    bool reserve(false);
    if (turn == 1)
    {
        cout << endl
             << "--------------------------------------------" << endl;
        cout << "\tAu tour de " << playerOne << " de jouer (X)" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "La Grille :" << endl;
        displayGrid();
        cout << endl
             << "Entrer votre choix : ";

        while (!reserve)
        {
            cin >> choice;
            
            reserve = gridFill(choice, 'X');
            if (!reserve)
                cout << "ERREUR,case reserver ; veuillez reesayer= ";
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
             << "--------------------------------------------" << endl;
        cout << "\tAu tour de " << playerTwo << " de jouer (O)" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "La Grille :" << endl;
        displayGrid();
        cout << endl
             << "Entrer votre choix : ";

        while (!reserve)
        {
            cin >> choice;
            reserve = gridFill(choice, 'O');
            if (!reserve)
                cout << "ERREUR,case reserver ; veuillez ressayer= ";
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

bool Game::checkFull()
{
    int fill = 0; // count filled space
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
    if (fill == 9)
    {
        gameOver = true;
        return true;
    }
    else
        return false;
}

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
        if (match == 3)
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
        if (match == 3)
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
        return true;

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

bool Game::chekWin()
{
    if (check('X') || check('O'))
        return true;
    else
        return false;
}

void Game::playGame()
{
    readme();
    cout << "\nVeuiller entrer le nom du joueur 1 : ";
    cin >> playerOne;
    cout << "Veuiller entrer le nom du joueur 2 : ";
    cin >> playerTwo;

    while (!gameOver)
    {

        if (chekWin())
        {
            if (turn == 1)
            { 
                char choice = 'N';
                cout << "\nBravo!!" << playerTwo << " Vous avez gagné " << endl;
                cout << "\nVoulez-vous recommencer à jouer (Y/N) ?" << endl;
                cin >> choice;
                if (choice == 'Y'||choice == 'y')
                {
                    replayGame();
                }
                else
                {
                    endGame();
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
                    replayGame();
                }
                else
                {
                    endGame();
                }

            }
            break;
        }
        else if (checkFull())
        {
            char ans = 'N';
            cout << "Toutes les cases sont remplies, recommencer (Y/N)?" << endl;
            cin >> ans;
            if (ans == 'N')
                break;
        }

        else
            playTurn();
    }
}

void Game::replayGame()
{
    gameOver = false;
    turn = 1;   // reinitialiser le tour avec le joueur 1
    gridInit(); // reinitialiser la grille
}

void Game::endGame()
{
    cout << "\nLe jeux est terminé" << endl;
    gameOver = true;
}
void Game::drawRow()
{
   for(int i(0); i<40;i++) { 
        cout << "___";
    }
    cout << endl;
    cout<< endl;
}
void Game::readme()
{
    drawRow();
    cout << "\t\t\t\t __________Welcome to TIC TAC TOE game!!________" << endl;
    cout << "REGLE DU JEU:" << endl;
    cout << "Deux joueurs posent tour à tour un rond pour l'un et une croix pour l'autre. Le but du jeux est d'obtenir un alignement en ligne, \ncolonne ou diagonale de ses 3 signes.Contrairement à la marelle les signes une fois posés ne sont plus déplacés." << endl;
    drawRow();
}