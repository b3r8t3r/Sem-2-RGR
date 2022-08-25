// Source.cpp
//========================================================================================
#include <iostream>
#include <map>

#include "Decrypt.h"
#include "Encrypt.h"
#include "fileInOut.h"
using namespace std;

enum Ciphers { Gronsfeld = 1, Visiner, Atbash };

void switch_encrypt(int number_of_code, int orig_encrypt_decrypt) {
  cout << "Введите номер шифровки:" << endl;
  cout << "<1> Гронсфельд" << endl << "<2> Вижинер" << endl << "<3> Атбаш\n: ";
  cin >> number_of_code;
  cout << endl;
  switch (Ciphers(number_of_code)) {
    case Ciphers::Gronsfeld:
      Gronsfeld_in(orig_encrypt_decrypt);
      break;
    case Ciphers::Visiner:
      Visiner_in(orig_encrypt_decrypt);
      break;
    case Ciphers::Atbash:
      Atbash_in(orig_encrypt_decrypt);
      break;
    default:
      cout << "Ошибка! Было введено неверное значение! Попробуйте еще раз."
           << endl
           << endl;
      switch_encrypt(number_of_code, orig_encrypt_decrypt);
  }
}

void switch_decrypt(int number_of_code, int orig_encrypt_decrypt,
                    bool after_encrypt) {
  cout << "Введите номер дешифровки:" << endl;
  cout << "<1> Гронсфельд" << endl << "<2> Вижинер" << endl << "<3> Атбаш\n: ";
  cin >> number_of_code;
  cout << endl;
  switch (Ciphers(number_of_code)) {
    case Ciphers::Gronsfeld:
      Gronsfeld_out(orig_encrypt_decrypt, after_encrypt);
      break;
    case Ciphers::Visiner:
      Visiner_out(orig_encrypt_decrypt, after_encrypt);
      break;
    case Ciphers::Atbash:
      Atbash_out(orig_encrypt_decrypt, after_encrypt);
      break;
    default:
      cout << "Ошибка! Было введено неверное значение! Попробуйте еще раз."
           << endl
           << endl;
      switch_decrypt(number_of_code, orig_encrypt_decrypt, after_encrypt);
      break;
  }
}

void password_check() {
  int password = 0;
  cout << "Введите пароль:" << endl;

  while (cin >> password) {  //проверка пароля
    if (password != 7301) {
      cout << "Пароль неверный, попробуйте ещё раз!" << endl << endl;
    } else {
      cout << "Пароль верный" << endl << endl;
      break;
    }
  }
  cin.ignore(32767, '\n');
}

int switch_aftermath(int aftermath, int number_of_code,
                     int orig_encrypt_decrypt) {
  if (aftermath != 2) {
    cout << "Желаете провести расшифровку?" << endl
         << "<1> Да" << endl
         << "<2> Нет\n: ";
    cin >> aftermath;
    cout << endl;
  }
  orig_encrypt_decrypt = 2;
  bool after_encrypt;
  switch (aftermath) {
    case 1:
      password_check();
      after_encrypt = true;
      switch_decrypt(number_of_code, orig_encrypt_decrypt, after_encrypt);
      break;
    case 2:
      cout << "Перед повторным запусом программы не забудьте сохранить "
              "полученные результаты."
           << endl;
      return 0;
      break;
    default:
      cout << "Ошибка! Было введено неверное значение! Попробуйте еще раз."
           << endl;
      switch_aftermath(aftermath, number_of_code, orig_encrypt_decrypt);
      break;
  }
}

void switch_program_mode(int encrypt_or_decrypt, int number_of_code,
                         int orig_encrypt_decrypt) {
  cout << "Вы хотите зашифровать сообщение или расшифровать?" << endl
       << "<1> Зашифровать" << endl
       << "<2> Расшифровать\n: ";
  cin >> encrypt_or_decrypt;
  cout << endl;
  bool after_encrypt;  //На случаи, когда пользователь выбирает расшифровку
                       //текста сразу, минуя шифровку
  switch (encrypt_or_decrypt) {
    case 1:
      orig_encrypt_decrypt = 1;
      switch_encrypt(number_of_code, orig_encrypt_decrypt);
      switch_aftermath(0, number_of_code, orig_encrypt_decrypt);
      break;
    case 2:
      password_check();
      orig_encrypt_decrypt = 2;
      after_encrypt = false;
      switch_decrypt(number_of_code, orig_encrypt_decrypt, after_encrypt);
      switch_aftermath(2, number_of_code, orig_encrypt_decrypt);
      break;
    default:
      cout << "Ошибка! Было введено неверное значение! Попробуйте еще раз."
           << endl;
      switch_program_mode(encrypt_or_decrypt, number_of_code,
                          orig_encrypt_decrypt);
      break;
  }
}

int main() {
  file_New();

  password_check();

  string text;
  cout << "Введите шифруемое/расшифруемое сообщение: \n: ";
  getline(cin, text);
  file_Write(text, 0, false);
  int encrypt_or_decrypt = 0, number_of_code = 0, orig_encrypt_decrypt = 0,
      aftermath = 0;

  cout << endl;

  switch_program_mode(encrypt_or_decrypt, number_of_code, orig_encrypt_decrypt);

  return 0;
}