/*____________fichier Game.h__________*/
/*_______declaration de la classe Game______*/
#include <string>

using namespace std;

class Game{
 private:
   string playerOne;
   string playerTwo;
   int turn;
   char grid[3][3];
   bool gameOver;
   string validChoice[9]={"1","2","3","4","5","6","7","8","9"};

 public:
    Game(); //constructeur
    void gridInit();    // initialisation du grid
    bool gridFill(char n,char playerChar); // fill nth element
    void initGame();
    void displayGrid();           //re-affiche le tableau du jeux
    
    bool isValidChoice(string c);
    char manageInput();           // gérer les choix entéer par l'utilisateur            
    void playTurn();
    
    bool checkFull();
    bool chekWin();               // verifier si un jueur à gagner
    bool check(char playerChar);  // symbole que le player utilise
    

    void playGame();
    void replayGame();
    void endGame();
    void final();       //savoir si vous avez gagner ou non
    void drawRow(); 
    void readme();
};