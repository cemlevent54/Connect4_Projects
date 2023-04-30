#include<iostream>
#include<stdlib.h>
using namespace std;
#include<cstring>

int r,c;
int slot;
int i,j;
char player1 = 'X';
char player2 = 'O';
char** board;

void showmenu();
void printboard(char** board,int r,int c);
void clearboard(char** board,int r,int c);
void playgame(char** board,char player1, char player2, int movesplayed,int r,int c,int slot);
int makemove(char** board,int movesplayed, char player1, char player2, int r);
int checkforwinner(char** board,char player1, char player2,int r,int c,int slot);
bool checkmatch(char** board, string pat, int r,int c);
bool matchforrows(char** board,string pat,int x,int y, int r,int c,int level);
bool matchforcolumns(char** board,string pat,int x,int y, int r,int c,int level);
bool matchforbottomrightdiagonals(char** board,string pat,int x,int y, int r,int c,int level);
bool matchforbottomleftdiagonals(char** board,string pat,int x,int y, int r,int c,int level);
bool matchfortopleftdiagonals(char** board,string pat,int x,int y, int r,int c,int level) ;
bool matchfortoprightdiagonals(char** board,string pat,int x,int y, int r,int c,int level);

int main() {
    int endofprogram = 0; 

    while(endofprogram == 0) {
        int movesplayed = 0;

        showmenu();
        int choice;
        cin >> choice;

      switch (choice){
        case 1:
            cout << "enter row number(min 4): ";
            cin >> r;
            cout << "enter column number(min 4): ";
            cin >> c;
            
			    if((r < 4) || (c < 4)) {
            cout << "row and column numbers must be 4. try again!";
            continue;
          }
            
          cout << "How many horizontal, vertical or diagonal slots are next to each other and the game will be over ?: ";
          cin >> slot;

          if((slot > r) && (slot > c)) {
              cout << "slot number is bigger than row and column number, try again!";
              continue;
          }

          board = new char*[r];
          for(int i = 0; i < c; i++) {
            board[i] = new char[c];
          }
  
          clearboard(board,r,c);
          printboard(board,r,c);
          playgame(board,player1,player2,movesplayed,r,c,slot);

          delete board;  
          break;

          
        
          case 2:
              endofprogram = 1;
              cout << "goodbye !" << endl;
              break;
        
          default:
              cout << "wrong choice! try again!";
              break;
      }
    }
    
}

void showmenu() {
    cout << "\n\n1.New Game" << endl;
    cout << "2.Exit" << endl;
    cout << "choose: ";
}

void printboard(char** board,int r,int c) {
    
    string line = "|---";
    string last = "";
    
    for(int k = 0; k < c; k++) {
            last += line;
    }
    
    system("CLS");

    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            cout << "| " << *(*(board+i)+j)<< " ";
        }
        cout << "|" << endl;
        cout << last << "|" <<endl;
    }
}

void clearboard(char** board,int r,int c) {
    int i,j;
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) *(*(board+i)+j) = ' ';
    }
}

void playgame(char** board,char player1, char player2, int movesplayed,int r,int c,int slot) {
    while(1) {
        printboard(board,r,c);

        if(makemove(board,movesplayed,player1,player2,r) == 1) break;
        
        movesplayed++;

        int result = checkforwinner(board,player1,player2,r,c,slot);

        if(result != 0) {
            printboard(board,r,c);

            if(result == 1) {
                cout << "\nX wins\n\n";
            }
            else if(result == 2) {
                cout << "\nO wins\n\n";
            }
            break;
        }
        if(movesplayed == (r*c)) {
            printboard(board,r,c);
            cout << "\nTie!\n\n";
            break;
        }
    }
}

int makemove(char** board,int movesplayed, char player1, char player2, int r) {
    char sign = player1;

    if(movesplayed % 2== 1) {
        sign = player2;
    }

    int column;
  
    while(1) {
        cout << "\nplayer " << sign << "'s turn(press only 0 to quit the game): ";
        cin >> column;

        if(column > 0) break;
      
        if(column == 0) {
          cout << "\nplayer " << sign << " quitted the game!" << endl;
          break;
        }  
        cout << "move not allowed!";
    }

    if(column!=0) {
        for(i = r-1; i >= 0; i--)  {
            if(*(*(board+i)+(column-1)) == ' ') {
                *(*(board+i)+(column-1)) = sign;
                cout << "\n\n";
                break;
            }
        }
    }
    else return 1;

    return 0;
}

int checkforwinner(char** board,char player1, char player2,int r,int c,int slot) {
  string str1 = "";
  string str2 = "";
  
  for(i = 0; i < slot; i++) {
    str1 += "X";
    str2 += "O";
  }

  if(checkmatch(board,str1,r,c)) return 1;
  else if(checkmatch(board,str2,r,c)) return 2;
  
  return 0;
}

bool matchforrows(char** board,string pat,int x,int y, int r,int c,int level) {
  int l = pat.length();
  const char* patptr = pat.c_str();

  if(level == l) return true;
  if(x < 0 || y < 0 || x >= r || y >=c) return false;
  
  if(*(*(board+x)+y) == *(patptr+level)) {
    char temp = *(*(board+x)+y);
    *(*(board+x)+y) = '#';
  
    bool res =  matchforrows(board, patptr, x + 1, y, r, c, level + 1);     
    
    *(*(board+x)+y) = temp;
    return res;
  }
  else return false;
}

bool matchforcolumns(char** board,string pat,int x,int y, int r,int c,int level) {
  int l = pat.length();
  const char* patptr = pat.c_str();

  if(level == l) return true;
  if(x < 0 || y < 0 || x >= r || y >=c) return false;
  

  if(*(*(board+x)+y) == *(patptr+level)) {
    char temp = *(*(board+x)+y);
    *(*(board+x)+y) = '#';
    
    bool res = matchforcolumns(board, patptr, x, y + 1, r, c, level + 1) ;      
    
    *(*(board+x)+y) = temp;
    return res;
  }
  else return false;
}

bool matchforbottomrightdiagonals(char** board,string pat,int x,int y, int r,int c,int level) {
  int l = pat.length();
  const char* patptr = pat.c_str();

  if(level == l) return true;
  if(x < 0 || y < 0 || x >= r || y >=c) return false;
  
  if(*(*(board+x)+y) == *(patptr+level)) {
    char temp = *(*(board+x)+y);
    *(*(board+x)+y) = '#';
    
    bool res =  matchforbottomrightdiagonals(board, patptr, x + 1, y+1, r,c, level+1) ; 
    
    *(*(board+x)+y) = temp;
    return res;
  }
  else return false;
}

bool matchforbottomleftdiagonals(char** board,string pat,int x,int y, int r,int c,int level) {
  int l = pat.length();
  const char* patptr = pat.c_str();

  if(level == l) return true;
  if(x < 0 || y < 0 || x >= r || y >=c) return false;

  if(*(*(board+x)+y) == *(patptr+level)) {
    char temp = *(*(board+x)+y);
    *(*(board+x)+y) = '#';
    
    bool res = matchforbottomleftdiagonals(board, patptr, x + 1,y-1, r,c, level + 1) ; 

    *(*(board+x)+y) = temp;
    return res;
  }
  else return false;
}

bool matchfortoprightdiagonals(char** board,string pat,int x,int y, int r,int c,int level) {
  int l = pat.length();
  const char* patptr = pat.c_str();

  if(level == l) return true;
  if(x < 0 || y < 0 || x >= r || y >=c) return false;

  if(*(*(board+x)+y) == *(patptr+level)) {
    char temp = *(*(board+x)+y);
    *(*(board+x)+y) = '#';
   
    bool res = matchfortoprightdiagonals(board, patptr, x-1,y+1, r,c, level + 1) ; 

    *(*(board+x)+y) = temp;
    return res;
  }
  else return false;
}

bool matchfortopleftdiagonals(char** board,string pat,int x,int y, int r,int c,int level) {
  int l = pat.length();
  const char* patptr = pat.c_str();

  if(level == l) return true;
  if(x < 0 || y < 0 || x >= r || y >=c) return false;

  if(*(*(board+x)+y) == *(patptr+level)) {
    char temp = *(*(board+x)+y);
    *(*(board+x)+y) = '#';
    
    bool res = matchfortopleftdiagonals(board, patptr, x-1,y-1, r,c, level + 1) ;
  
    *(*(board+x)+y) = temp;
    return res;
  }
  else return false;
}

bool checkmatch(char** board, string pat, int r,int c) {
  int l = pat.length();
  const char* patptr = pat.c_str();

  if(l > (r*c)) return false;

  for(i = 0; i < r; i++) {
    for(j = 0; j < c; j++) {
      if(*(*(board+i)+j) == *(patptr+0)) {
        if(matchforrows(board,patptr,i,j,r,c,0)) return true;
        else if(matchforcolumns(board,patptr,i,j,r,c,0)) return true;
        else if(matchforbottomrightdiagonals(board,patptr,i,j,r,c,0)) return true;
        else if(matchforbottomleftdiagonals(board,patptr,i,j,r,c,0)) return true;
        else if(matchfortoprightdiagonals(board,patptr,i,j,r,c,0)) return true;
        else if(matchfortoprightdiagonals(board,patptr,i,j,r,c,0)) return true;
      }
    }
  }
  return false;
}
