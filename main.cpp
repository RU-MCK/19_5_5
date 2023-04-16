#include <iostream>
#include <fstream>
#include <limits>
bool checkError() {
  if (std::cin.fail() || std::cin.peek() != '\n') {
    std::cerr << "Enter Error!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  } else
    return true;
}
int sector(bool(&spin)[13], int numb) {
  static int temp = 0;
  ((temp + numb) <= 13) ? (temp = temp + numb) : temp = numb - (13 - temp);
  if (spin[temp]) {
    while (!spin[temp]) {
      ++temp;
    }
  }
  spin[temp] = true;
  return temp + 1;
}

std::string readText(std::string &path, std::string &wordKey, int spin) {
  std::string _spinStart = wordKey + std::to_string(spin);
  std::string _spinFinish = wordKey + std::to_string(spin + 1);
  std::ifstream text;
  text.open(path);
  if (!text.is_open()) {
    std::cout << "Error opening file!";
    exit(3);
  }
  std::string str;
  std::string _str;
  bool flag = false;
  while (!text.eof()) {
    text >> str;
    if (str == _spinStart) {
      flag = true;
    } else if (str == _spinFinish || text.eof()) {
      flag = false;
    }
    if (flag) {
      _str += str + " ";
    }
  }
  text.close();
  return _str;
}
int main() {
  int spin;
  bool numberSpin[13]{};
  std::string questionsPath = "C:\\Users\\User\\Desktop\\Questions.txt";
  std::string answersPath = "C:\\Users\\User\\Desktop\\Answers.txt";
  int expert = 0;
  int _public = 0;
  do {
    std::cout << "Spin " << std::endl;
    std::cin >> spin;
    if (checkError()) {
      if (spin > 13) {
        spin = 13;
      }
      std::cout << std::endl;
      spin = sector(numberSpin, spin);
      std::string questionKey = "Question#";
      std::cout << readText(questionsPath, questionKey, spin);
      std::cout << std::endl;
      std::cout << "Enter answer: " << std::endl;
      std::string answer;
      std::cin >> answer;
      std::string answerKey = "Answer#";
      if (answerKey + std::to_string(spin) + " " + answer + " " == readText(answersPath, answerKey, spin)) {
        ++expert;
        std::cout << "Expert < " << expert << " >" << std::endl
                  << "Public < " << _public << " >" << std::endl;
      } else {
        ++_public;
        std::cout << "Expert < " << expert << " >" << std::endl
                  << "Public < " << _public << " >" << std::endl;
      }
      if ((_public == 6 && expert < 6) || expert == 6 && _public < 6)
        break;
    }
  } while (_public != 7 || expert != 7);
  if (_public >= 6) {
    std::cout << "Won public!" << std::endl;
  } else {
    std::cout << "Won experts!" << std::endl;
  }
  return 0;
}
