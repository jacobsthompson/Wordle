#ifndef STATS
#define STATS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Stats{
public:
    int timesplayed ;
    int gotitin;
    int timeswon;
    int streak;
    int longeststreak;
    std::vector<std::string> wordsused;
    std::vector<int> timeswordsused;
    std::vector<bool> wonwithwordsused;

    Stats(){
        timesplayed = 0;
        gotitin = 0;
        timeswon = 0;
        streak = 0;
        longeststreak = 0;
    }

    void addTimesPlayed(){ timesplayed++; }
    void addTimesWon(int x){ 
        std::cout << "I've been called" << std::endl;
        timeswon++;
        streak++; 
        gotitin += x;
        if(streak > longeststreak){
            longeststreak = streak; 
        }
        std::cout << timeswon << ":" << streak <<":" << gotitin << ":" << longeststreak << std::endl;
    }

    int TimesPlayed(){ return timesplayed; }
    int AvgAttempts(){ return gotitin/timesplayed; }
    int WinPercentage(){
        return (timeswon*100)/timesplayed;
    }
    int CurrentStreak(){ return streak; }
    int LongestStreak(){ return longeststreak; }

    void Reset(){
        timesplayed = 0;
        gotitin = 0;
        timeswon = 0;
        streak = 0;
        longeststreak = 0;
    }
};

#endif