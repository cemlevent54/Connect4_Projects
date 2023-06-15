#include<iostream>
#include<stdlib.h>
using namespace std;
#include<cstring>
#include<fstream>
#include<string>
#include<sstream>



int i, j;
char player1 = 'X';
char player2 = 'O';
char** board;

void showmenu();
void printboard(char** board, int r, int c);
void clearboard(char** board, int r, int c);
void playgame(char** board, char player1, char player2, int movesplayed, int r, int c, int slot);
int makemove(char** board, int movesplayed, char player1, char player2, int r, int c, int slot);
int checkforwinner(char** board, char player1, char player2, int r, int c, int slot);
bool checkmatch(char** board, string pat, int r, int c);
bool matchforrows(char** board, string pat, int x, int y, int r, int c, int level);
bool matchforcolumns(char** board, string pat, int x, int y, int r, int c, int level);
bool matchforbottomrightdiagonals(char** board, string pat, int x, int y, int r, int c, int level);
bool matchforbottomleftdiagonals(char** board, string pat, int x, int y, int r, int c, int level);
bool matchfortopleftdiagonals(char** board, string pat, int x, int y, int r, int c, int level);
bool matchfortoprightdiagonals(char** board, string pat, int x, int y, int r, int c, int level);

void saveGameBoard(char** board, char player1, char player2, int r, int c, int movesplayed, int slot, const char* filename);
void saveRowandColumns(int r, int c);
void saveMovesPlayedandSlot(int movesplayed, int slot);



int main() {
    int endofprogram = 0;

    while (endofprogram == 0) {
        int movesplayed = 0;

        showmenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int r, c;
            int slot;
            cout << "enter row number(min 4): ";
            cin >> r;
            cout << "enter column number(min 4): ";
            cin >> c;

            if ((r < 4) || (c < 4)) {
                cout << "row and column numbers must be 4. try again!";
                continue;
            }

            cout << "How many horizontal, vertical or diagonal slots are next to each other and the game will be over ?: ";
            cin >> slot;

            if ((slot > r) && (slot > c)) {
                cout << "slot number is bigger than row and column number, try again!";
                continue;
            }

            board = new char* [r];
            for (int i = 0; i < r; i++) {
                board[i] = new char[c];
            }

            clearboard(board, r, c);
            printboard(board, r, c);
            playgame(board, player1, player2, movesplayed, r, c, slot);
            break;
        }
        case 2: {

            int r, c;
            ifstream file1("rowandcolumn.txt");

            if (!file1.is_open()) cout << "error opening file" << endl;
            else {
                file1 >> r >> c;
                file1.close();
            }

            int movesplayed, slot;
            ifstream file2("movesplayedandslot.txt");

            if (!file2.is_open()) cout << "error opening file" << endl;
            else {
                file2 >> movesplayed >> slot;
                file2.close();
            }

            char** loadBoard = new char*[r];
            for (int i = 0; i < r; i++) {
                loadBoard[i] = new char[c];
            }
            clearboard(loadBoard, r, c);

            ifstream file3("savedgame1.txt");
            string line;

            if (!file3.is_open()) cout << "error opening file" << endl;

            else {

                while (getline(file3, line)) {
                    istringstream iss(line);

                    int num1, num2;
                    char ch;

                    while (iss >> num1 >> num2 >> ch) {
                        if (ch == player1) loadBoard[num1][num2] = player1;
                        else if (ch == player2) loadBoard[num1][num2] = player2;

                    }
                }
                file3.close();
            }


            int is_winner = checkforwinner(loadBoard, player1, player2, r, c, slot);
            if (is_winner == 1 || is_winner == 2) {
                printboard(loadBoard, r, c);
                if (is_winner == 1) {
                    cout << player1 << " wins!" << endl;
                    cout << "Please start new game!" << endl;
                }
                else if (is_winner == 2) {
                    cout << player2 << " wins!" << endl;
                    cout << "Please start new game!" << endl;
                }

                break;
            }

            else if (movesplayed == (r * c)) {
                printboard(loadBoard, r, c);
                cout << "Tie ! " << endl;
                cout << "Please start new game!" << endl;
                break;
            }

            else {
                printboard(loadBoard, r, c);
                playgame(loadBoard, player1, player2, movesplayed, r, c, slot);
            }


            break;

        }



        case 3: {
            endofprogram = 1;
            cout << "goodbye !" << endl;
            break;
        }
        default: {
            cout << "wrong choice! try again!";
            break;
        }
        }
    }

}

void showmenu() {     // giris ekranındaki menuyu gosterir
    cout << "*****Welcome to MxN Connect X game!****";
    cout << "\n1.New Game" << endl;
    cout << "2.Saved Game" << endl;
    cout << "3.Exit Game" << endl;
    cout << "choose: ";
}

void printboard(char** board, int r, int c) {   // olusturulan tahtayı ekrana yazar

    string line = "|---";
    string last = "";

    for (int k = 0; k < c; k++) {
        last += line;
    }

    system("CLS");

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            cout << "| " << *(board[i] + j) << " ";
        }
        cout << "|" << endl;
        cout << last << "|" << endl;
    }
}

void clearboard(char** board, int r, int c) { //olusturulan tahtayı temizler
    int i, j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) *(board[i] + j) = ' ';
    }
}

void playgame(char** board, char player1, char player2, int movesplayed, int r, int c, int slot) { //oyunun oynanma mantığı ile ilgili
    while (1) {
        printboard(board, r, c);

        if (makemove(board, movesplayed, player1, player2, r, c, slot) == 1) break;

        movesplayed++;

        int result = checkforwinner(board, player1, player2, r, c, slot);

        if (result != 0) {
            printboard(board, r, c);

            if (result == 1) {
                saveGameBoard(board, player1, player2, r, c, movesplayed, slot, "savedgame1.txt");
                cout << "\nX wins\n\n";
            }
            else if (result == 2) {
                saveGameBoard(board, player1, player2, r, c, movesplayed, slot, "savedgame1.txt");
                cout << "\nO wins\n\n";
            }
            break;
        }
        if (movesplayed == (r * c)) {
            saveGameBoard(board, player1, player2, r, c, movesplayed, slot, "savedgame1.txt");
            printboard(board, r, c);
            cout << "\nTie!\n\n";
            break;
        }
    }
}

int makemove(char** board, int movesplayed, char player1, char player2, int r, int c, int slot) { // oyunun oynanma mantığı ile ilgili
    char sign = player1;

    if (movesplayed % 2 == 1) {
        sign = player2;
    }

    int column;
    while (1) {
        cout << "press 0 for exitting or saving the game";
        cout << "\nplayer " << sign << "'s turn: ";
        cin >> column;


        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "invalid input\n\n";
        }

        else if (column == 0) {
            while (1) {
                int choice;

                cout << "1.Save Game" << endl;
                cout << "2.Exit without Saving" << endl;
                cout << "Choice: " << endl;
                cin >> choice;

                if (choice == 1) {
                    saveGameBoard(board, player1, player2, r, c, movesplayed, slot, "savedgame1.txt");
                    return 1;
                }

                else if (choice == 2) {
                    cout << "\nplayer " << sign << " quitted the game!" << endl;
                    return 1;
                }
            }
        }

        else if (column > 0) break;
        else cout << "move not allowed!";


    }

    if (column != 0) {
        for (i = r - 1; i >= 0; i--) {
            if (board[i][column - 1] == ' ') {
                board[i][column - 1] = sign;
                cout << "\n\n";
                break;
            }
        }
    }
    else return 1;

    return 0;
}


int checkforwinner(char** board, char player1, char player2, int r, int c, int slot) { //kazananı kontrol etmek için yazılan bir fonksiyon
    string str1 = "";
    string str2 = "";

    for (i = 0; i < slot; i++) {
        str1 += "X";
        str2 += "O";
    }

    if (checkmatch(board, str1, r, c)) return 1;
    else if (checkmatch(board, str2, r, c)) return 2;

    return 0;
}

bool matchforrows(char** board, string pat, int x, int y, int r, int c, int level) { // satırda match arayan fonksiyon
    int l = pat.length();

    if (level == l) return true;
    if (x < 0 || y < 0 || x >= r || y >= c) return false;


    if (*((*(board + x)) + y) == pat[level]) {
        char temp = *((*(board + x)) + y);
        *((*(board + x)) + y) = '#';

        bool res = matchforrows(board, pat, x + 1, y, r, c, level + 1);

        *((*(board + x)) + y) = temp;
        return res;
    }
    else return false;
}

bool matchforcolumns(char** board, string pat, int x, int y, int r, int c, int level) { // sütunda match arayan fonksiyon
    int l = pat.length();

    if (level == l) return true;
    if (x < 0 || y < 0 || x >= r || y >= c) return false;


    if (*((*(board + x)) + y) == pat[level]) {
        char temp = *((*(board + x)) + y);
        *((*(board + x)) + y) = '#';

        bool res = matchforcolumns(board, pat, x, y + 1, r, c, level + 1);

        *((*(board + x)) + y) = temp;
        return res;
    }

    else return false;
}

bool matchforbottomrightdiagonals(char** board, string pat, int x, int y, int r, int c, int level) { // sağ alt çapraz match arayan fonksiyon
    int l = pat.length();

    if (level == l) return true;
    if (x < 0 || y < 0 || x >= r || y >= c) return false;

    if (*((*(board + x)) + y) == pat[level]) {
        char temp = *((*(board + x)) + y);
        *((*(board + x)) + y) = '#';

        bool res = matchforbottomrightdiagonals(board, pat, x + 1, y + 1, r, c, level + 1);

        *((*(board + x)) + y) = temp;
        return res;
    }

    else return false;
}

bool matchforbottomleftdiagonals(char** board, string pat, int x, int y, int r, int c, int level) { // sol alt çapraz match arayan fonksiyon
    int l = pat.length();

    if (level == l) return true;
    if (x < 0 || y < 0 || x >= r || y >= c) return false;

    if (*((*(board + x)) + y) == pat[level]) {
        char temp = *((*(board + x)) + y);
        *((*(board + x)) + y) = '#';

        bool res = matchforbottomleftdiagonals(board, pat, x + 1, y - 1, r, c, level + 1);

        *((*(board + x)) + y) = temp;
        return res;
    }

    else return false;
}

bool matchfortoprightdiagonals(char** board, string pat, int x, int y, int r, int c, int level) { // sağ üst çapraz match arayan fonksiyon
    int l = pat.length();

    if (level == l) return true;
    if (x < 0 || y < 0 || x >= r || y >= c) return false;

    if (*((*(board + x)) + y) == pat[level]) {
        char temp = *((*(board + x)) + y);
        *((*(board + x)) + y) = '#';

        bool res = matchfortoprightdiagonals(board, pat, x - 1, y + 1, r, c, level + 1);

        *((*(board + x)) + y) = temp;
        return res;
    }

    else return false;

}

bool matchfortopleftdiagonals(char** board, string pat, int x, int y, int r, int c, int level) { // sol üst çapraz match arayan fonksiyon
    int l = pat.length();

    if (level == l) return true;
    if (x < 0 || y < 0 || x >= r || y >= c) return false;

    if (*((*(board + x)) + y) == pat[level]) {
        char temp = *((*(board + x)) + y);
        *((*(board + x)) + y) = '#';

        bool res = matchfortopleftdiagonals(board, pat, x - 1, y - 1, r, c, level + 1);

        *((*(board + x)) + y) = temp;
        return res;

    }

    else return false;
}

bool checkmatch(char** board, string pat, int r, int c) {// match fonksiyonlarını kendi içinde birleştiren fonksiyon

    int l = pat.length();

    if (l > (r * c)) return false;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (board[i][j] == pat[0]) {
                if (matchforrows(board, pat, i, j, r, c, 0)) return true;
                else if (matchforcolumns(board, pat, i, j, r, c, 0)) return true;
                else if (matchforbottomrightdiagonals(board, pat, i, j, r, c, 0)) return true;
                else if (matchforbottomleftdiagonals(board, pat, i, j, r, c, 0)) return true;
                else if (matchfortoprightdiagonals(board, pat, i, j, r, c, 0)) return true;
                else if (matchfortoprightdiagonals(board, pat, i, j, r, c, 0)) return true;
            }
        }
    }

    return false;
}



void saveGameBoard(char** board, char player1, char player2, int r, int c, int movesplayed, int slot, const char* filename) { // oyun tahtasındaki bilgileri kaydeden bir fonksiyon
    ofstream file(filename);

    if (!file.is_open()) cout << "Error opening file";

    else {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (board[i][j] == player1) {
                    file << i << " " << j << " " << player1 << endl;
                }
                else if (board[i][j] == player2) {
                    file << i << " " << j << " " << player2 << endl;
                }
            }
        }

        file.close();
    }



    saveRowandColumns(r, c);
    saveMovesPlayedandSlot(movesplayed, slot);

}



void saveRowandColumns(int r, int c) { //oyun tahtasının satır sütun değerlerini kaydeden fonksiyon(savegameboard içinde kullanılıyor)

    ofstream file("rowandcolumn.txt");
    if (!file.is_open()) cout << "Error opening file" << endl;

    else {
        file << r << " " << c;
        file.close();
    }
}


void saveMovesPlayedandSlot(int movesplayed, int slot) { //oyun tahtasının movesplayed ve slot değerlerini kaydeden fonksiyon(savegameboard içinde kullanılıyor)
    ofstream file("movesplayedandslot.txt");

    if (!file.is_open()) cout << "Error opening file" << endl;

    else {
        file << movesplayed << " " << slot;
        file.close();
    }
}

