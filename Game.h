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

 public:
    Game(); //constructeur
    void gridInit();    // initialisation du grid
    bool gridFill(char n,char playerChar); // fill nth element
    void initGame();
    void displayGrid(); //re-affiche le tableau du jeux
    void playTurn();
    bool checkFull();
    bool chekWin();     // comment gagner
    bool check(char playerChar); //symbole que le player utilise

    void playGame();
    void replayGame();
    void endGame();
    void final();       //savoir si vous avez gagner ou non
    void drawRow(); 
    void readme();
};