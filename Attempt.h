#ifndef ATTEMPT
#define ATTEMPT
#include <iostream>
#include <string>

class Attempt{
public:
    std::string word;
    int attempts;
    bool win;

    Attempt(std::string s, bool w){
        word = s;
        attempts = 1;
        win = w;
    }

    std::string getAttemptWord(){
        return word;
    }

    void updateAttempt(){
        attempts++;
    }

    void updateWin(){
        win = true;
    }

    void print(){
        std::cout << word << "\t" << "\t" << attempts << "\t";
        if(win == true) { std::cout << "TRUE" << std::endl; } else { std::cout << "FALSE" << std::endl; }
    }
};

#endif