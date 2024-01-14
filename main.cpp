#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <csetjmp>
#include <stdlib.h>
#include <fstream>
#include "Stats.h"
#include "Attempt.h"
#include "Attempts.h"
#include "Keyboard.h"
Stats s;
Attempts at;


using namespace std;

int howmanyarray(char x, char array[5]){
    int counter = 0;
    for(int i = 0; i < 5; i++){
        if(array[i] == x){
            counter++;
        }
    }
    return counter;
}

int howmanyletter(char x, string word){
    int counter = 0;
    for(int i = 0; i < 5; i++){
        if(word[i] == x){
            counter++;
        }
    }
    return counter;
}

bool compareallowed(string wordx){
    ifstream allowed("allowed.txt");
    ifstream words("words.txt");
    string compare;
    while(words >> compare){
        if(wordx == compare){
            return true;
        }
    }
    while(allowed >> compare){
           if(wordx == compare){
              return true;
         }
    }
    return false;
 }

 bool comparedupes(string word, string dupes[6]){
    for(int i = 0; i < 6; i++){
        if(word == dupes[i] && dupes[i] != " "){
            return true;
        }
    }
    return false;
 }

void wordle(string word, char wordleboard[6][5], int gyg[6][5]){
    // 2 = green, 1 = yellow, 0 = gray
    bool win = false;
    bool loss = false;
    int attempt = 0;
    string dupes[6] = {" "," "," "," "," "," "};
    Keyboard k;

    while(win == false && loss == false){
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 5; j++){
                
                if(gyg[i][j] == 2){
                    cout << "\033[92;1m" << "[" << wordleboard[i][j] << "]";
                } else if(gyg[i][j] == 1){
                    cout << "\033[93;1m" << "[" << wordleboard[i][j] << "]";
                } else if(gyg[i][j] == 0){
                    cout << "\033[90;1m" << "[" << wordleboard[i][j] << "]";
                }
            }
            cout << endl;
        }
        cout << "\033[97m" << endl;
        k.print();
        cout << endl;



        string input;
        cout << "Enter Word: ";
        cin >> input;

        while(compareallowed(input) == false || comparedupes(input,dupes) == true){
            cout << "Invalid Word" << endl;
            cout << "Enter Word: ";
            cin >> input;
        }

        dupes[attempt] = input;

        if(at.size() == 0){
            at.pushback(input, false);
        } else {
            bool wordfound = false;
            for(int i = 0; i < at.size(); i++){
                if(at.checkWord(i) == input){
                    at.updateA(i);
                    wordfound = true;
                }
            }
            if(wordfound == false){ at.pushback(input,false); }
        }

        for(int i = 0; i < 5; i++){
            wordleboard[attempt][i] = input[i];
        }
        char carray[5];
        for(int i = 0; i < 5; i++){
            carray[i] = ' ';
        }
        for(int i = 0; i < 5; i++){
            carray[i] = input[i];
            for(int j = 0; j < 5; j++){
                if(input[i] == word[j]){
                    if(i == j){
                        gyg[attempt][i] = 2;
                        k.greenLetter(input[i]);
                        if(howmanyletter(input[i], input) > 1 && howmanyletter(input[i], word) == 1){
                            for(int k = 0; k < 5; k++){
                                if(input[k] == input[i] && k != i){
                                    gyg[attempt][k] = 0;
                                }
                            }
                        }
                    } else {
                        if(gyg[attempt][i] < 2){
                            if(howmanyletter(input[i], word) >= howmanyarray(input[i], carray)){
                                gyg[attempt][i] = 1;
                                k.yellowLetter(input[i]);
                            } else {
                                gyg[attempt][i] = 0;
                            }
                        }
                    }
                } else {
                    if(gyg[attempt][i] < 1){
                        gyg[attempt][i] = 0;
                        k.grayLetter(input[i]);
                    }
                }

            }
        }

        int wincondition = 0;
        for(int i = 0; i < 5; i++){
            if(gyg[attempt][i] == 2){
                wincondition++;
            }
        }
        attempt++;
        if(wincondition == 5) {
            s.addTimesWon(attempt);

            bool wordfound = false;
            for(int i = 0; i < at.size(); i++){
                if(at.checkWord(i) == input){
                    at.updateW(i);
                    wordfound = true;
                }
            }
            if(wordfound == false){ at.pushback(input,true); }

            cout << "won" << endl;
            win = true;
        }
        if(attempt == 6){
            loss = true;
        }
    }
}



void mainmenu(int num){
    if (int(num) == 1){
        s.addTimesPlayed();
        char wordleboard[6][5];
        int gyg[6][5];
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 5; j++){
                wordleboard[i][j] = ' ';
                gyg[i][j] = 0;
            }
        }

        srand(time(0));
        int random = (rand() % 2315);
        ifstream words("words.txt");
        string wordtofind;
        string wordx;
        int i = 0;
        while(words >> wordx){
            if(i == random){
                wordtofind = wordx;
            }
            i++;
        }

        wordle(wordtofind,wordleboard,gyg);

        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 5; j++){
                
                if(gyg[i][j] == 2){
                    cout << "\033[92;1m" << "[" << wordleboard[i][j] << "]";
                } else if(gyg[i][j] == 1){
                    cout << "\033[93;1m" << "[" << wordleboard[i][j] << "]";
                } else if(gyg[i][j] == 0){
                    cout << "\033[90;1m" << "[" << wordleboard[i][j] << "]";
                }
            }
            cout << endl;
        }
        cout << "\033[0m" << endl;

        cout << "The word was " << wordtofind << "! Press Enter for Main Menu!" << endl;
        cin.ignore();
        cin.ignore();
    }
    
    if (int(num) == 2){
        cout << "=============================================" << endl;
        cout << "                 HOW TO PLAY                 " << endl;
        cout << "=============================================" << endl;
        
        cout << "Guess the Word in 6 tries or less." << endl;
        cout << " " << endl;

        
        cout << "HOW TO PLAY:" << endl;
        cout << "- Each guess must be a valid 5 letter word." << endl;
        cout << "- The color of the tiles will change to show you how close your guess was to the word." << endl;
        cout << "" << endl;
        cout << "Press Enter for Main Menu" << endl;
        cin.ignore();
        cin.ignore();

    }
    if (int (num) == 3){
        cout << "==========================" << endl;
        cout << "    STATISTICS SUMMARY    " << endl;
        cout << "==========================" << endl;
        cout << "Times Played: " << s.TimesPlayed() << endl;
        cout << "Average Attempts: " << s.AvgAttempts() << endl;
        cout << "Win Percentage: " << s.WinPercentage() << "%" << endl;
        cout << "Current Streak: " << s.CurrentStreak() << endl;
        cout << "Longest Streak: " << s.LongestStreak() << endl;
        cout << "--------------------------" << endl;
        cout << "WORD     ATTEMPTS      WIN" << endl;
        cout << "--------------------------" << endl;
        for(int i = 0; i < at.size(); i++){
            at.print(i);
        }

        cout << "" << endl;
        cout << "Press Enter for Main Menu" << endl;
        cin.ignore();
        cin.ignore();

    }

    if(int(num)==4){
        cout << "Are you sure you want to Reset Stats? (Y/N)" << endl;
        char reset;
        cin >> reset;
        if(reset == 'Y'){
            s.Reset();
            at.reset();
            cout << "Statistics have been Reset!" << endl;
        }
        cout << "Press Enter for Main Menu!" << endl;
        cin.ignore();
        cin.ignore();
    }

}

int main(int argc, char* argv[]) {
    int num = 0;
        while(num != 5){
        cout << "=========================" << endl;
        cout << "    Welcome to Wordle    " << endl;
        cout << "=========================" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "1. Play Wordle" << endl;
        cout << "2. How to Play" << endl;
        cout << "3. Statistics Summary" << endl;
        cout << "4. Reset Statistics" << endl;
        cout << "5. Exit" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "Select an option:" << endl;



        cin >> num;
        mainmenu(num);
    }
   

   return 0;
}
   
    