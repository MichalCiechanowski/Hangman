#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

class hangman {
  public:
    hangman() {
      std::cout << "Welcome in Hangman game !" << std::endl;
      std::cout << "Enter your name: ";
      std::cin >> players_name;
      hangman::setPassword();
    }

    void game() {
      system("clear");
      if (guess_count == 11) {
        hangman::Loose();
      }
      std::cout << "Player: " << players_name << std::endl << std::endl;
      std::cout << hangman::password_hider(password) << std::endl;
      std::cout << hangman::print_guessed_letters(guessed_letters) << std::endl;
      std::cout << "Remaining trials: " << 11 - guess_count << std::endl;
      std::cout << "Guess letter or word: ";
      std::cin >> guess_letter;

      if (guess_letter.size() == 1) {
        leter = guess_letter.at(0);
        if (std::count(guessed_letters.begin(),guessed_letters.end(),leter)) {
            std::cout << "You already guessed this letter. Please guess a diferns one !" << std::endl;
            std::chrono::seconds timespan(2);
            std::this_thread::sleep_for(timespan);
        }
        else {
            int tmp = 0;
            guessed_letters.push_back(leter);
            guess_count++;
            for (int i=0; i<password.size(); i++) {
              if (std::count(guessed_letters.begin(), guessed_letters.end(), password.at(i))) {
                tmp++;
              }
            }
            if (tmp == password.size()) {
              hangman::Win();
            }
        }
      }
      else {
        if (guess_letter == password) {
          hangman::Win();
        }
        else {
          guess_count++;
        }
      }
    }
  private:
    std::vector<char> guessed_letters;
    std::string password, players_name;
    std::string guess_letter;
    char leter;
    int guess_count = 0;
        std::string password_hider(std::string pass) {
      std::string hidden_password;
      for (int i=0; i<pass.length(); i++) {
        if (std::count(guessed_letters.begin(),guessed_letters.end(),pass.at(i))) {
          if (i == 0) {
            hidden_password.push_back(toupper(pass.at(i)));
          }
          else {
            hidden_password.push_back(pass.at(i));
          }
        }
        else {
          hidden_password.push_back('_');
        }
      }
      return hidden_password;
    }

    std::string print_guessed_letters(std::vector<char> leters) {
      std::string answer = "Guessed letters: ";
      for (int i=0; i<leters.size(); i++) {
        answer.push_back(leters.at(i));
        if (i+1 != leters.size()) {
          answer.push_back(',');
          answer.push_back(' ');
        }
      }
      answer.push_back('\n');
      return answer;
    }

    void setPassword() {
      std::ifstream File("../words.txt");
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

    void Win() {
      system("clear");
      std::cout << "You won the game !" << std::endl;
      std::cout << "The password was: " << password;
      exit(0);
    }

    void Loose() {
      system("clear");
      std::cout << "You lost the game :(" << std::endl;
      std::cout << "The password was: " << password;
      exit(0);
    }
};

int main(){
  hangman game;
  for (;;) {
    game.game();
  }
  return 0;
}
