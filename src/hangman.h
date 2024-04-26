#ifndef HANGMAN_H
#define HANGMAN_H

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <vector>

class hangman {
  public:
    hangman();
    void game();
  private:
    char leter;
    int guess_count = 0;
    
    std::vector<char> guessed_letters;
    std::string password, players_name;
    std::string guess_letter;

    std::string password_hider(std::string pass);
    std::string print_guessed_letters(std::vector<char> leters);
    
    void setPassword();
    void Win();
    void Loose();
};

#endif