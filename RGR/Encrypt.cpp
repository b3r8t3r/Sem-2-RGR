//Encrypt.cpp
//========================================================================================
#include<string>
#include<iostream>
#include "fileInOut.h"
using namespace std;
string Atbash_Encrypt(string text) {
	int num;
	string alfavit = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	for (int count = 0; count < text.length(); count++) {
		for (int i = 0; i < alfavit.length(); i++) {
			if (text[count] == alfavit[i]) {
				if (i != alfavit.length()) {
					num = alfavit.length() - i - 1;
				}
				text[count] = alfavit[num];
				break;
			}
		}
	}
	
	return text;
}
void Atbash_in(int orig_encrypt_decrypt) {
	string text;
	text = file_Read(orig_encrypt_decrypt - 1, 0,false);
	text = Atbash_Encrypt(text);
	cout << "Зашифрованное сообщение: " << text << endl;
	file_Write(text, orig_encrypt_decrypt,false);
}
string Visiner_Encrypt(string message, string key) {
	int keyLen = key.size();

	for (int i = 0, j = 0; i < message.size(); i++)
	{
		if (message[i] > 64 && message[i] < 91)
		{
			message[i] += key[j % keyLen] - 'a';
			j++;
			if (message[i] > 90)
				message[i] -= 26;
		}
		else if (message[i] > 96 && message[i] < 123)
		{
			message[i] -= 32;
			message[i] += key[j % keyLen] - 'a';
			j++;
			if (message[i] > 90)
			{
				message[i] -= 26;
			}
			message[i] += 32;
		}
	}
	return message;
}
void Visiner_in(int orig_encrypt_decrypt)//для Вижинера 
{
	setlocale(LC_ALL, "");
	string str, code;
	string crypt;
	str = file_Read(orig_encrypt_decrypt - 1, 0,false);
	cout << "Введите ключ шифрования:\n: ";
	cin >> code;
	file_Write(code, orig_encrypt_decrypt,true);
	crypt = Visiner_Encrypt(str, code);
	cout << "Зашифрованный код: " << crypt << endl;
	file_Write(crypt, orig_encrypt_decrypt,false);
}

string Gronsfeld_Encrypt(string stringInp, int key) {
	int keyLen = 0;
	for (int temp = key; temp > 0; keyLen++) {
		temp /= 10;
	}

	for (int i = 0, t1, t2; i < stringInp.length(); i++) {
		t1 = pow(10, i % keyLen);
		stringInp[i] += ((key / t1) % 10);
	}

	return stringInp;
}

void Gronsfeld_in(int orig_encrypt_decrypt)
{
	setlocale(LC_ALL, "");
	string stringInp, encryptMessage;
	int key_1;
	cout << "Введите количество сдвигов в слове:" << endl;
	cin >> key_1;
	file_Write_(key_1, orig_encrypt_decrypt, true);
	stringInp = file_Read(orig_encrypt_decrypt - 1, 0,false);
	cout << "Это ваше зашифрованное слово" << endl;
	encryptMessage = Gronsfeld_Encrypt(stringInp, key_1);
	cout << encryptMessage << endl;
	file_Write(encryptMessage, orig_encrypt_decrypt,false);
}
