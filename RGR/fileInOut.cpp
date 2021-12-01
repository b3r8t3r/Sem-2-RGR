//fileInOut.cpp
//========================================================================================
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Encrypt.h"
#include "Decrypt.h"

using namespace std;

const string fileOrig = "Original.txt";
const string fileEncrypt = "Encrypted.txt";
const string fileDecrypt = "Decrypted.txt";
const int Key = 15;
const string Vis_Key = "tem";




void file_New() {
	setlocale(LC_ALL, "ru");
	ofstream file_out;
	file_out.open(fileOrig);
	file_out.close();
	file_out.open(fileEncrypt);
	file_out.close();
	file_out.open(fileDecrypt);
	file_out.close();
}

//Блок записи в файл строковых переменных
void file_Write(string str,int orig_encrypt_decrypt, bool is_encrypt) {	
	setlocale(LC_ALL, "ru");
	
	ofstream file_out;
	
		if (orig_encrypt_decrypt == 0) {	//Выборка работы с конкретным файлом
			file_out.open(fileOrig, ofstream::app);
		} 
		else if (orig_encrypt_decrypt == 1) {
			file_out.open(fileEncrypt, ofstream::app);
		}
		else  {
			file_out.open(fileDecrypt, ofstream::app);
		}

	if (!file_out.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}
	else {
		if (is_encrypt) str = Visiner_Encrypt(str, Vis_Key);
		file_out << str << endl;
	}

	file_out.close();
}

//Блок записи в файл целочисленных переменных
void file_Write_(int str, int orig_encrypt_decrypt, bool is_encrypt) {
	setlocale(LC_ALL, "ru");

	ofstream file_out;

	if (orig_encrypt_decrypt == 0) {	//Выборка работы с конкретным файлом
		file_out.open(fileOrig, ofstream::app);
	}
	else if (orig_encrypt_decrypt == 1) {
		file_out.open(fileEncrypt, ofstream::app);
	}
	else {
		file_out.open(fileDecrypt, ofstream::app);
	}

	if (!file_out.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}
	else {
		string str_cr = to_string(str);
		if (is_encrypt) str_cr = Key_Encrypt(str_cr, Key);
		file_out << str_cr << endl;
	}

	file_out.close();
}

//Блок чтения с файла
string file_Read(int orig_encrypt_decrypt, int string_num, bool is_encrypt) {
	setlocale(LC_ALL, "ru");
	
	ifstream file_in;
		
	if (orig_encrypt_decrypt == 0) {	//Выборка работы с конкретным файлом
		file_in.open(fileOrig);
	}
	else if (orig_encrypt_decrypt == 1){
		file_in.open(fileEncrypt);
	}
	else {
		file_in.open(fileDecrypt);
	}
	
	

	if (!file_in.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}
	else {
		int index = 0;	//Индекс текущей строки в while
		string str;
		while (!file_in.eof()) {
			str = "";
			getline(file_in, str);	//Считывание строки целиком

			if (is_encrypt) str = Visiner_Decrypt(str, Vis_Key);
			if (index == string_num) {	//Считывание строки с определенным номером
				return str;
			}

			index++;
			
			if (index >= 100000) { 
				cout << "Ошибка! Значение index превысило возможный лимит." << endl;
				break;
			}
		
		}

	}

	file_in.close();
}

int file_Read_(int orig_encrypt_decrypt, int string_num, bool is_encrypt) {
	setlocale(LC_ALL, "ru");

	ifstream file_in;

	if (orig_encrypt_decrypt == 0) {	//Выборка работы с конкретным файлом
		file_in.open(fileOrig);
	}
	else if (orig_encrypt_decrypt == 1) {
		file_in.open(fileEncrypt);
	}
	else {
		file_in.open(fileDecrypt);
	}

	if (!file_in.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}
	else {
		int index = 0;	//Индекс текущей строки в while
		string str;
		while (!file_in.eof()) {
			str = "";
			getline(file_in, str);	//Считывание строки целиком
			if (is_encrypt) str = Key_Decrypt(str, Key);
			if (index == string_num) {	//Считывание строки с определенным номером
				return stoi(str);	//Преобразует string в integer
			}

			index++;

			if (index >= 100000) {
				cout << "Ошибка! Значение index превысило возможный лимит." << endl;
				break;
			}

		}

	}

	file_in.close();
}