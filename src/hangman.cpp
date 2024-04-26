#include "hangman.h"

Hangman::Hangman() {
  std::cout << "Welcome in Hangman game !" << '\n';
  std::cout << "Enter your name: ";
  std::cin >> playersName;
  Hangman::setPassword();
}

void Hangman::game() {
  system("clear");
  if (guessCount == 11) {
    Hangman::lose();
  }
  std::cout << "Player: " << playersName << '\n' << '\n';
  std::cout << Hangman::passwordHider(password) << '\n';
  std::cout << Hangman::printGuessedLetters(guessedLetters) << '\n';
  std::cout << "Remaining trials: " << 11 - guessCount << '\n';
  std::cout << "Guess letter or word: ";
  std::cin >> guessLetter;

  if (guessLetter.size() == 1) {
    letter = guessLetter.at(0);
    if (std::count(guessedLetters.begin(),guessedLetters.end(),letter)) {
        std::cout << "You already guessed this letter. Please guess a diferns one !" << '\n';
        std::chrono::seconds timespan(2);
        std::this_thread::sleep_for(timespan);
    } else {
        int tmp = 0;
        guessedLetters.push_back(letter);
        guessCount++;
        for (int i=0; i<password.size(); i++) {
          if (std::count(guessedLetters.begin(), guessedLetters.end(), password.at(i))) {
            tmp++;
          }
        }
        if (tmp == password.size()) {
          Hangman::win();
        }
    }
  } else {
    if (guessLetter == password) {
      Hangman::win();
    } else {
      guessCount++;
    }
  }
}

std::string Hangman::passwordHider(std::string pass) {
  std::string hidden_password;
  for (int i=0; i<pass.length(); i++) {
    if (std::count(guessedLetters.begin(),guessedLetters.end(),pass.at(i))) {
      if (i == 0) {
        hidden_password.push_back(toupper(pass.at(i)));
      } else {
        hidden_password.push_back(pass.at(i));
      }
    } else {
      hidden_password.push_back('_');
    }
  }
  return hidden_password;
}

std::string Hangman::printGuessedLetters(std::vector<char> letters) {
  std::string answer = "Guessed letters: ";
  for (int i=0; i<letters.size(); i++) {
    answer.push_back(letters.at(i));
    if (i+1 != letters.size()) {
      answer.push_back(',');
      answer.push_back(' ');
    }
  }
  answer.push_back('\n');
  return answer;
}

void Hangman::setPassword() {
  std::ifstream File("words.txt");
  std::vector<std::string> words;
  if (File.is_open()) {
    std::string read_tmp, tmp;
    while (getline(File, read_tmp)) {
      for (int i=0; i<read_tmp.size(); i++) {
        tmp.push_back(tolower(read_tmp.at(i)));
      }
      words.push_back(tmp);
      tmp = "";
    }
  }
  srand(time(NULL));
  password = words.at(rand() % words.size());
}

void Hangman::win() {
  system("clear");
  std::cout << "You won the game !" << '\n';
  std::cout << "The password was: " << password;
  exit(0);
}

void Hangman::lose() {
  system("clear");
  password[0] = toupper(password[0]);
  std::cout << "You lost the game :(" << '\n';
  std::cout << "The password was: " << password << '\n';
  exit(0);
}
