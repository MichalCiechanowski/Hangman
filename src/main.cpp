#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>

#include "hangman.h"

int main(){
  hangman game;
  for (;;) {
    game.game();
  }
  return 0;
}