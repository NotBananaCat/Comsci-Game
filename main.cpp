#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <tuple>
#include <unistd.h>
#include <vector>
using namespace std;

class Menu {
private:
  int choice; // which choice the person is hovering
  vector<string> menu;

public:
  Menu() {
    //vector<string> menu;
    menu.push_back("<Play Game>");
    menu.push_back("<Help Menu>");
    menu.push_back("<Quit Game>");
    this->choice = 0;
    //this->menu = menu;
  }

  int getChoice() { return this->choice; }

  void setChoice(string direction) {

    if (direction == "up" && this->choice > 0) {
      this->choice--;
    } else if (direction == "down" && this->choice < 2) {
      this->choice++;
    }
  }

  void loadMenu(string path) {
    fstream fp;
    fp.open("picture.txt", ios::in);
    if (fp.is_open()) {
      string ln;
      while (getline(fp, ln)) {
        cout << ln << '\n';
      }
    }
    fp.close();

    fstream f;
    f.open("LEVELS/" + path + ".txt", ios::in);
    int counter = 0;
    if (f.is_open()) {
      string line;
      while (getline(f, line)) {
        counter++;
        cout << line << "\n";
        // choice currently selected
        if (counter == 6) {
          if (this->choice == 0) {
            cout << "║                       ===> <Play Game> <===             "
                    "            ║\n";
            cout << "║                            <Help Menu>                  "
                    "            ║\n";
            cout << "║                            <Quit Game>                  "
                    "            ║\n";
          } else if (this->choice == 1) {
            cout << "║                            <Play Game>                  "
                    "            ║\n";
            cout << "║                       ===> <Help Menu> <===             "
                    "            ║\n";
            cout << "║                            <Quit Game>                  "
                    "            ║\n";
          } else {
            cout << "║                            <Play Game>                  "
                    "            ║\n";
            cout << "║                            <Help Menu>                  "
                    "            ║\n";
            cout << "║                       ===> <Quit Game> <===             "
                    "            ║\n";
          }
        }
      }
      f.close();
    }
  }
};

class Game {
private:
  char board[14][71];
  int level = 2;

public:
  char getBoardSpot(int x, int y){
    return this->board[x][y];
  }
 
  void nextLevel() { this->level += 1; }

  int movePlayer(char direction, int x, int y) {
    // later make it return 0 for wall, 1 for moved, 2 for died and
    // make it so setX,seY will return to default level constructors

    if (direction == 'w') {
      if (this->board[x - 1][y] == ' ') {
        this->board[x - 1][y] = 'M';
        this->board[x][y] = ' ';
        return 1;
      } else if (this->board[x - 1][y] == 'B') {
        if (this->board[x - 2][y] == ' ' || this->board[x - 2][y] == '|') {
          this->board[x - 2][y] = 'B';
          this->board[x - 1][y] = 'M';
          this->board[x][y] = ' ';
          return 1;
        }
      } else if (this->board[x - 1][y] == '^' || this->board[x - 1][y] == '|') {
        this->loadLevel(to_string(this->level));
        return 3;
      } else if (this->board[x - 1][y] == 'E') {
        return 2;
      }

    } else if (direction == 'a') {
      if (this->board[x][y - 1] == ' ') {
        this->board[x][y - 1] = 'M';
        this->board[x][y] = ' ';
        return 1;
      } else if (this->board[x][y - 1] == 'B') {
        if (this->board[x][y - 2] == ' ' || this->board[x][y - 2] == '|') {
          this->board[x][y - 2] = 'B';
          this->board[x][y - 1] = 'M';
          this->board[x][y] = ' ';
          return 1;
        }
      } else if (this->board[x][y - 1] == '^' || this->board[x][y - 1] == '|') {
        this->loadLevel(to_string(this->level));
        return 3;
      } else if (this->board[x][y - 1] == 'E') {
        return 2;
      }

    } else if (direction == 's') {
      if (this->board[x + 1][y] == ' ') {
        this->board[x + 1][y] = 'M';
        this->board[x][y] = ' ';
        return 1;
      } else if (this->board[x + 1][y] == 'B') {
        if (this->board[x + 2][y] == ' ' || this->board[x + 2][y] == '|') {
          this->board[x + 2][y] = 'B';
          this->board[x + 1][y] = 'M';
          this->board[x][y] = ' ';
          return 1;
        }
      } else if (this->board[x + 1][y] == '^' || this->board[x + 1][y] == '|') {
        this->loadLevel(to_string(this->level));
        return 3;

      } else if (this->board[x + 1][y] == 'E') {
        return 2;
      }
    } else if (direction == 'd') {
      if (this->board[x][y + 1] == ' ') {
        this->board[x][y + 1] = 'M';
        this->board[x][y] = ' ';
        return 1;
      } else if (this->board[x][y + 1] == 'B') {
        if (this->board[x][y + 2] == ' ' || this->board[x][y + 2] == '|') {
          this->board[x][y + 2] = 'B';
          this->board[x][y + 1] = 'M';
          this->board[x][y] = ' ';
          return 1;
        }
      } else if (this->board[x][y + 1] == '^' || this->board[x][y + 1] == '|') {
        this->loadLevel(to_string(this->level));
        return 3;
      } else if (this->board[x][y + 1] == 'E') {
        return 2;
      }
    }
    return 0;
  }

  int getLevel() { return this->level; }

  char seeCoord(int x, int y) { return this->board[x][y]; }

  void setCoord(char newthing, int x, int y) { this->board[x][y] = newthing; }

  void loadLevel(string path) {
    char board[14][71];
    ifstream f("LEVELS/" + path + ".txt");
    int x = 0;
    string input;
    while (getline(f, input)) {
      for (int y = 0; y < 71; y++) {
        if (input[y] == '.') {
          this->board[x][y] = ' ';
        } else {
          this->board[x][y] = input[y];
        }
      }
      x++;
    }
    f.close();
  }

  void printLevel() {
    string str = "";
    for (int i = 0; i < 14; i++) {
      for (int j = 0; j < 71; j++) {
        if (this->board[i][j] == ' ') {
          // colour
          str += " ";
        } else if (this->board[i][j] == '#') {
          str += "\033[90m";
          str += "█";
          str += "\033[0m";
          } else if (this->board[i][j] == 'G') {
          str += "\033[33m";
          str += "ö";
          str += "\033[0m";
        } else if (this->board[i][j] == '^') {
          // colour
          str += "▲";
        } else if (this->board[i][j] == 'B') {
          // colour
          str += "▨";
        } else if (this->board[i][j] == 'M') {
          str += "\033[31;1m";
          str += "M";
          str += "\033[0m";

        } else if (this->board[i][j] == 'E') {
          str += "\033[93;1m";
          str += "⚑";
          str += "\033[0m";
        } else {
          str += this->board[i][j];
        }
      }
      str += "\n";
    }
    cout << str;
  }

  //INTERACTIVE OBJECTS: 1 LAZER, 2 GOOMBA, 3 MOVING SPIKES
  bool lazerPath(char direction, int x, int y, int endx) {
    bool blocked = false;
    if(direction == 'U'){
      for(int xCoord = x - 1; xCoord > endx; xCoord--){
        if((board[xCoord][y] == ' ' || board[xCoord][y] == '|') && blocked == false){
          board[xCoord][y] = '|';
        }
        else if(board[xCoord][y] == 'M' == false){
          return false; //mario ded reset level 
        }
        else if(blocked == true && board[xCoord][y] == '|'){
          board[xCoord][y] = ' ';
        }
        else{
          blocked = true;
        }
      }
    }
    else{
      for(int xCoord = x + 1; xCoord < endx; xCoord++){
        if((board[xCoord][y] == ' ' || board[xCoord][y] == '|') && blocked == false){
          board[xCoord][y] = '|';
        }
        else if(board[xCoord][y] == 'M' && blocked == false){
          return false; //mario ded reset level 
        }
        else if(blocked == true && board[xCoord][y] == '|'){
          board[xCoord][y] = ' ';
        }
        else{
          blocked = true;
        }
      }
    }
    
    return true;
  }

  bool GoombaMove(int Px, int Py, vector<tuple<int, int>> &G_Parameters){

    for(int i = 0; i < G_Parameters.size(); i++) {
      int Gx = get<0>(G_Parameters[i]);
      int Gy = get<1>(G_Parameters[i]);
      
      if(Gy < Py){ //should you go right?
        if (board[Gx][Gy+1] == ' ' || board[Gx][Gy+1] == 'M'){ //try go right
          this->board[Gx][Gy+1] = 'G';
          this->board[Gx][Gy] = ' ';
          get<1>(G_Parameters[i]) = Gy+1;
        }  
        else if(Gx < Px){ //can't go right, should you go down?
          if(board[Gx+1][Gy] == ' ' || board[Gx+1][Gy] == 'M'){ //try go down
            this->board[Gx+1][Gy] = 'G';
            this->board[Gx][Gy] = ' ';
            get<0>(G_Parameters[i]) = Gx+1;
          }
        }
        else{ //can't go right, shouldn't go down, should go up
          if(board[Gx-1][Gy] == ' ' || board[Gx-1][Gx] == 'M'){ //try go up
            this->board[Gx-1][Gy] = 'G';
            this->board[Gx][Gy] = ' ';
            get<0>(G_Parameters[i]) = Gx-1;
          }
        }
      }
      else if(Gy == Py){
        if(Gx < Px){ //middle, should you go down?
          if(board[Gx+1][Gy] == ' ' || board[Gx+1][Gy] == 'M'){ //try go down
            this->board[Gx+1][Gy] = 'G';
            this->board[Gx][Gy] = ' ';
            get<0>(G_Parameters[i]) = Gx+1;
          }
        }
        else{ //middle, shouldn't go down, should go up
          if(board[Gx-1][Gy] == ' ' || board[Gx-1][Gx] == 'M'){ //try go up
            this->board[Gx-1][Gy] = 'G';
            this->board[Gx][Gy] = ' ';
            get<0>(G_Parameters[i]) = Gx-1;
          }
        }        
      }
      //shouldn't go right, should go left
      else if(board[Gx][Gy-1] == ' ' || board[Gx][Gy-1] == 'M'){ //CAN YOU GO LEFT?
        this->board[Gx][Gy-1] = 'G';
        this->board[Gx][Gy] = ' ';
        get<1>(G_Parameters[i]) = Gy-1;
      }
      else if(Gx < Px){ //can't go right, should you go down?
        if(board[Gx+1][Gy] == ' ' || board[Gx+1][Gy] == 'M'){ //try go down
          this->board[Gx+1][Gy] = 'G';
          this->board[Gx][Gy] = ' ';
          get<0>(G_Parameters[i]) = Gx+1;
        }
      }
      else{ //can't go right, shouldn't go down, should go up
        if(board[Gx-1][Gy] == ' ' || board[Gx-1][Gx] == 'M'){ //try go up
          this->board[Gx-1][Gy] = 'G';
          this->board[Gx][Gy] = ' ';
          get<0>(G_Parameters[i]) = Gx-1;
        }
      }

      if(Px == get<0>(G_Parameters[i]) && Py == get<1>(G_Parameters[i])) {
        return false;
      }
    }
  return true;
  }

  bool MovingSpike(vector<tuple<char,int, int, int, int>> &X_Parameters){
    for(int i = 0; i < X_Parameters.size();i++){
      int SpikeX = get<1>(X_Parameters[i]);
      int SpikeY = get<2>(X_Parameters[i]); // ඞ

      if(get<0>(X_Parameters[i]) == 'U'){ // if moving up move up
        if(get<3>(X_Parameters[i]) == get<1>(X_Parameters[i])){
          get<0>(X_Parameters[i]) = 'D';
        }
        else{
          //CHECK WHATS ABOVE B4 MOVE
          if(this->board[SpikeX-1][SpikeY] == ' ') { //if not ' ' could be a box :o
            this->board[SpikeX][SpikeY] = ' ';
            this->board[SpikeX-1][SpikeY] = 'X';
            get<1>(X_Parameters[i])--;
          }
          else if(this->board[SpikeX-1][SpikeY] == 'M'){
            return false; // i have magic trick :D
          }
        }
      }  
      else{
        if(get<4>(X_Parameters[i]) == get<1>(X_Parameters[i])){
          get<0>(X_Parameters[i]) = 'U';
        }
        else{
          //CHECK WHATS ABOVE B4 MOVE
          if(this->board[SpikeX+1][SpikeY] == ' ') { //if not ' ' could be a box :o
            this->board[SpikeX][SpikeY] = ' ';
            this->board[SpikeX+1][SpikeY] = 'X';
            get<1>(X_Parameters[i])++;
          }
          else if(this->board[SpikeX+1][SpikeY] == 'M'){
            return false; // i have magic trick :D
          }
        }
      } 
    }
    return true;
  }


};

class Entity { // object in the board

private:
  bool isDeadly;
  char symbol;
  int xCoord;
  int yCoord;

public:
  virtual void move() {}

  virtual bool getIsDeadly() { return this->isDeadly; }
};

class Player : public Entity {
private:
  int xCoord;
  int yCoord;

  int xCoordStart;
  int yCoordStart;

  bool isDeadly = false;
  char symbol = 'M';
  int lives;

public:
  Player(int levelnum) {
    if (levelnum == 0) {
      this->xCoord = 11;
      this->yCoord = 2;
      this->xCoordStart = 11;
      this->yCoordStart = 2;
    }
  }
  int getX() { return this->xCoord; }
  int getY() { return this->yCoord; }

  void SetCoordToInitial() {
    this->xCoord = this->xCoordStart;
    this->yCoord = this->yCoordStart;
  }

  void updateCoord(char direction) { 
    if(direction == 'w'){
      this->xCoord = this->xCoord - 1; 
    }
    else if(direction == 's'){
      this->xCoord = this->xCoord + 1;
    }
    else if(direction == 'a'){
      this->yCoord = this->yCoord - 1;
    }
    else{
      this->yCoord = this->yCoord + 1;
    }
  }

  bool getIsDeadly() { return false; }
};

class Goomba : public Entity {
private:
  int xCoord;
  int yCoord;
  bool isDeadly = true;
  char symbol = 'G';

public:
  void move() {}
  bool getIsDeadly() { return true; }
};

class Item {
private:
  string name;
  int ability;

public:
  // getters and setters

  // destry 1 block a1round you
  // summon 1 box
  //
};

class Itemset : public Player { // set has a aplayer
private:
  int capacity;
  queue<Item *> itemset;
  Player *player;

public:
  // if above capacity take the back off

  // use top item (maybe return 1 for boost 2 for projectile or something like
  // that) (will have to interact with player for fire shots or whatever) (like
  // give the player fire then if input r shot a fire from player positin on the
  // board )

  // print set (same time as board)

  // add item (to the back)

  // random item box maybe =D (could initialize a random item then add it to the
  // list (random int 1-4, if 1 mushroom if 2 bannana something like that))
};

/////////////////
// Level Objects//
/////////////////
void initializeLevel2(vector<tuple<char, int, int, int>> &L_Parameters, vector<tuple<char, int, int, int, int>> &X_Parameters, vector<tuple<int, int>> &G_Parameters) {
  L_Parameters.clear();
  X_Parameters.clear();
  G_Parameters.clear();

  G_Parameters.push_back(make_tuple(4,44));
}

void initializeLevel3(vector<tuple<char, int, int, int>> &L_Parameters, vector<tuple<char, int, int, int, int>> &X_Parameters, vector<tuple<int, int>> &G_Parameters) {
  L_Parameters.clear();
  X_Parameters.clear();
  G_Parameters.clear();
  
  L_Parameters.push_back(make_tuple('D', 1, 34, 13));
  L_Parameters.push_back(make_tuple('D', 1, 37, 13));
}

void initializeLevel4(vector<tuple<char, int, int, int>> &L_Parameters, vector<tuple<char, int, int, int, int>> &X_Parameters, vector<tuple<int, int>> &G_Parameters) {
  L_Parameters.clear();
  X_Parameters.clear();
  G_Parameters.clear();

  L_Parameters.push_back(make_tuple('D', 1, 60, 13));
  
   
}

void initializeLevel5(vector<tuple<char, int, int, int>> &L_Parameters, vector<tuple<char, int, int, int, int>> &X_Parameters, vector<tuple<int, int>> &G_Parameters) 
{
  L_Parameters.clear();
  X_Parameters.clear();
  G_Parameters.clear();

  X_Parameters.push_back(make_tuple('D', 2 , 13, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 17, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 21, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 25, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 29, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 33, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 37, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 41, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 45, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 49, 2 , 11));
  X_Parameters.push_back(make_tuple('D', 2 , 53, 2 , 11));
  
  X_Parameters.push_back(make_tuple('U', 11, 14 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 18 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 22 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 26 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 30 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 34 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 38 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 42 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 46 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 50 , 2, 11));
  X_Parameters.push_back(make_tuple('U', 11, 54 , 2, 11));
}

void initializeLevel6(vector<tuple<char, int, int, int>> &L_Parameters, vector<tuple<char, int, int, int, int>> &X_Parameters, vector<tuple<int, int>> &G_Parameters) {
  L_Parameters.clear();
  X_Parameters.clear();
  G_Parameters.clear();
  
}

///////////////////////////////////////////////////////////
//PICK LEVEL TO INITIALIZE                               //
///////////////////////////////////////////////////////////
void initializeLevel(int x, vector<tuple<char, int, int, int>> &L_Parameters, vector<tuple<char, int, int, int, int>> &X_Parameters, vector<tuple<int, int>> &G_Parameters){
  if(x == 2){
    initializeLevel2(L_Parameters , X_Parameters , G_Parameters);   
  }
  else if(x == 3){
    initializeLevel3(L_Parameters , X_Parameters , G_Parameters);
  }
  else if(x == 4){
    initializeLevel4(L_Parameters , X_Parameters , G_Parameters);
  }
  else if(x == 5){
    initializeLevel5(L_Parameters , X_Parameters , G_Parameters);
  }
  else if(x == 6){
    initializeLevel6(L_Parameters , X_Parameters , G_Parameters);
  }
}

///////////////////////////////////////////////////////////
// DO NOT MODIFY USED TO ALLOW FOR NON-PASUED USER INPUTS//
//    MODIFICATIONS TO KBHIT + GETCH() BUILT INS WORK    //
///////////////////////////////////////////////////////////
int kbhit() {
  static const int STDIN = 0;
  static int initialized = 0;

  if (!initialized) {
    struct termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = 1;
  }
  int bytesWaiting;
  ioctl(STDIN, FIONREAD, &bytesWaiting);
  return bytesWaiting;
}

int getch(void) {
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

//////////////////////////////////////////////////////////
int main() {
  Menu *startmenu = new Menu();
  // startmenu->OpenMenu();

  startmenu->loadMenu("1-startmenu");

  bool ChosingMenu = true;
  while (ChosingMenu) {
    while (!kbhit()) {
      fflush(stdout);
      usleep(50000); // microseconds
    }
    char input = getchar(); // keyboard has been pressed!

    if (input == 'w') {
      system("clear");
      startmenu->setChoice("up");
      startmenu->loadMenu("1-startmenu");
    } else if (input == 's') {
      system("clear");
      startmenu->setChoice("down");
      startmenu->loadMenu("1-startmenu");
    } else if (input == ' ') {
      if (startmenu->getChoice() == 0) {
        ChosingMenu = false;
        system("clear");
      }
      if (startmenu->getChoice() == 1) {
        system("clear");
        fstream file2;
        file2.open("instructions.txt", ios::in);
        int counter = 0;
        if (file2.is_open()) {
          string line2;
          while (getline(file2, line2)) {
            cout << line2 << "\n";
          }
        }
        file2.close();
        bool helpOpen = true;
        while (helpOpen) {
          char done = getchar();
          if (done == ' ') {
            helpOpen = false;
          }
        }
        system("clear");
        startmenu->loadMenu("1-startmenu");
      }
      if (startmenu->getChoice() == 2) {
        system("clear");
        fstream fp;
        fp.open("ohhhnoo.txt", ios::in);
        if (fp.is_open()) {
          string ln;
          while (getline(fp, ln)) {
            cout << ln << "\n";
          }
        }
        fp.close();
        cout << "GAME OVER";

        return 0;
      }
    }
  }

  Game *game = new Game();
  Player *player = new Player(0);
  bool run = true;

  // input and update board/others here

  // Keeps track of all objects in each level
  vector<tuple<char, int, int, int>> L_Parameters;
  vector<tuple<char, int, int, int, int>> X_Parameters;
  vector<tuple<int, int>> G_Parameters;
  
  game->loadLevel("2");
  game->printLevel();
  initializeLevel2(L_Parameters , X_Parameters , G_Parameters);

  int x = 0;
  bool updatedSomething;
  
  while (run) {
    while (!kbhit()) { // keyboard not pressed, update in game objects 
      updatedSomething = false;
      
      if (x % 5 == 0) { // 0.1 delay * every 10 = 1 sec interval
        if(game->GoombaMove(player->getX(), player->getY(), G_Parameters) == false) {
            player->SetCoordToInitial();
            game->loadLevel(to_string(game->getLevel()));
            initializeLevel(game->getLevel(), L_Parameters , X_Parameters , G_Parameters);
        }
        if(G_Parameters.size() != 0){ 
          updatedSomething = true;   
        }      
      }

      if (x % 5 == 0) {
        if(game->MovingSpike(X_Parameters) == false){
          player->SetCoordToInitial();
          game->loadLevel(to_string(game->getLevel()));
          initializeLevel(game->getLevel(), L_Parameters , X_Parameters , G_Parameters);    
        }
        if(X_Parameters.size() != 0){
          updatedSomething = true;
        }
      }

      if(updatedSomething == true){
        system("clear");
        game->printLevel(); 
      }
      x++;
      fflush(stdout);
      usleep(100000); // 0.1 sec delay
    }

    
    // KEYBOARD MOVEMENT/BUTTONS
    char input = getchar(); // keyboard has been pressed!
    usleep(100000);
    int movePlayerReturned = 0;

    if (input == 'r') {
      player->SetCoordToInitial();
      game->loadLevel(to_string(game->getLevel()));
    }
      
    /////////////////////////
    //TEMP SKIP LEVEL BUTTON
    else if (input == 'l') {
      player->SetCoordToInitial();
      game->nextLevel();
      game->loadLevel(to_string(game->getLevel()));

      //INITIALIZE OBJECTS IN LEVEL
      initializeLevel(game->getLevel(), L_Parameters , X_Parameters , G_Parameters);
    }
    ///////////////////////////


    //BOARD RESPONSE TO PLAYER MOVEMENT
    else {
      movePlayerReturned =
          game->movePlayer(input, player->getX(), player->getY());
      if (movePlayerReturned == 1) {
        player->updateCoord(input);
        
      } else if (movePlayerReturned == 3) {
        player->SetCoordToInitial();
        initializeLevel(game->getLevel(), L_Parameters , X_Parameters , G_Parameters); 
        
      } else if (movePlayerReturned == 2) {
        player->SetCoordToInitial();
        game->nextLevel();
        game->loadLevel(to_string(game->getLevel()));
        
        // load next level features
        initializeLevel(game->getLevel(), L_Parameters , X_Parameters , G_Parameters);
        // else if(game->getLevel() == 7){
        //   initializeLevel7(L_Parameters , X_Parameters , G_Parameters);
        // }
        
      }
    }

    // LAZERSSSSSSSSS
    for(int x = 0; x < L_Parameters.size(); x++){
      if(game->lazerPath(get<0>(L_Parameters[x]), get<1>(L_Parameters[x]), get<2>(L_Parameters[x]), get<3>(L_Parameters[x])) == false){//if die reset 
        player->SetCoordToInitial();
        game->loadLevel(to_string(game->getLevel()));
      }
      
    }
    system("clear");
    game->printLevel();
    
  } //while run
}


