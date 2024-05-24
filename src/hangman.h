#ifndef HANGMAN_H
#define HANGMAN_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class Hangman {
private:
  char letter;
  int guessCount = 0;

  std::vector<char> guessedLetters;
  std::string password, playersName;
  std::string guessLetter;

  std::string passwordHider(std::string pass);
  std::string printGuessedLetters(std::vector<char> letters);

  void setPassword();
  void win();
  void lose();

public:
  Hangman();
  void game();
};

#endif