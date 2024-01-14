#pragma once
#include <iostream>
#include <string>

class Keyboard{
public:
    char letters[26];
    int colors[26];

    Keyboard(){
        for(int i = 0; i < 26; i++){
            letters[i] = char(96+i);
            colors[i] = 0;
        }
    }

    void grayLetter(char c){
        colors[c-97] = 1;
    }

    void yellowLetter(char c){
        colors[c-97] = 2;
    }

    void greenLetter(char c){
        colors[c-97] = 3;
    }

    void print(){
        char qwerty[26] = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};

        for(int i = 0; i < 26; i++){
            if(i == 10){
                std::cout << std::endl;
                std::cout << " ";
            }
            if(i == 19){
                std::cout << std::endl;
                std::cout << "   ";
            }
            if(colors[qwerty[i]-97] == 1){
                std:: cout << "\033[90;1m";
            } else if (colors[qwerty[i]-97] == 2){
                std::cout << "\033[93;1m";
            } else if (colors[qwerty[i]-97] == 3){
                std::cout << "\033[92;1m";
            } else {
                std::cout << "\033[97m";
            }
            std::cout << '[' << qwerty[i] << ']';

        }
        std::cout << std::endl;
    }

};