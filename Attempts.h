#ifndef ATTEMPTS
#define ATTEMPTS
#include <iostream>
#include <string>
#include <vector>
#include "Attempt.h"

class Attempts{
public:
    std::vector<Attempt> a;

    Attempts(){}

    void pushback(std::string s,bool w){
        Attempt temp(s,w);
        a.push_back(temp);
    }

    std::string checkWord(int i){
        return a[i].getAttemptWord();
    }

    int size(){
        return a.size();
    }

    void updateA(int i){
        a[i].updateAttempt();
    }

    void updateW(int i){
        a[i].updateWin();
    }

    void reset(){
        while(a.size() != 0){
            a.pop_back();
        }
    }

    void print(int i){
        a[i].print();
    }
};

#endif