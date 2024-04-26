#include "hangman.h"

hangman::hangman() {
  std::cout << "Welcome in Hangman game !" << '\n';
  std::cout << "Enter your name: ";
  std::cin >> players_name;
  hangman::setPassword();
}

void hangman::game() {
  system("clear");
  if (guess_count == 11) {
    hangman::Loose();
  }
  std::cout << "Player: " << players_name << '\n' << '\n';
  std::cout << hangman::password_hider(password) << '\n';
  std::cout << hangman::print_guessed_letters(guessed_letters) << '\n';
  std::cout << "Remaining trials: " << 11 - guess_count << '\n';
  std::cout << "Guess letter or word: ";
  std::cin >> guess_letter;

  if (guess_letter.size() == 1) {
    leter = guess_letter.at(0);
    if (std::count(guessed_letters.begin(),guessed_letters.end(),leter)) {
        std::cout << "You already guessed this letter. Please guess a diferns one !" << '\n';
        std::chrono::seconds timespan(2);
        std::this_thread::sleep_for(timespan);
    } else {
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
  } else {
    if (guess_letter == password) {
      hangman::Win();
    } else {
      guess_count++;
    }
  }
}

std::string hangman::password_hider(std::string pass) {
  std::string hidden_password;
  for (int i=0; i<pass.length(); i++) {
    if (std::count(guessed_letters.begin(),guessed_letters.end(),pass.at(i))) {
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

std::string hangman::print_guessed_letters(std::vector<char> leters) {
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

void hangman::setPassword() {
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

void hangman::Win() {
  system("clear");
  std::cout << "You won the game !" << '\n';
  std::cout << "The password was: " << password;
  exit(0);
}

void hangman::Loose() {
  system("clear");
  password[0] = toupper(password[0]);
  std::cout << "You lost the game :(" << '\n';
  std::cout << "The password was: " << password << '\n';
  exit(0);
}
