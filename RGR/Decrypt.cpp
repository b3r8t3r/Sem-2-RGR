//Decrypt.cpp
//========================================================================================
#include<string>
#include<iostream>
#include "fileInOut.h"
using namespace std;

string Atbash_Decrypt(string text) {
	string alfavit = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int num;
	for (int count = 0; count < text.length(); count++) {
		for (int i = 0; i < alfavit.length(); i++) {
			if (text[count] == alfavit[i]) {
				num = alfavit.length() - i - 1;
				text[count] = alfavit[num];
				break;
			}
		}
	}
	
	return text;
}

void Atbash_out(int orig_encrypt_decrypt, bool after_encrypt) {
	string text;
	if (after_encrypt) {
		text = file_Read(orig_encrypt_decrypt - 1, 0, false);
	}
	else {
		text = file_Read(orig_encrypt_decrypt - 2, 0, false);
	}
	text = Atbash_Decrypt(text);
	cout << "Расшифрованное сообщение: " << text << endl;
	file_Write(text, orig_encrypt_decrypt, false);
}

string Visiner_Decrypt(string message, string key) {
	int keyLen = key.size();
	for (int i = 0, j = 0; i < message.size(); i++)
	{
		if (message[i] > 64 && message[i] < 91)
		{
			message[i] -= key[j % keyLen] - 'a';
			j++;
			if (message[i] < 65)
				message[i] += 26;
		}
		else if (message[i] > 96 && message[i] < 123)
		{
			message[i] -= 32;
			message[i] -= key[j % keyLen] - 'a';
			j++;
			if (message[i] < 65)
				message[i] += 26;

			message[i] += 32;
		}
	}
	return message;
}

void Visiner_out(int orig_encrypt_decrypt, bool after_encrypt)
{
	setlocale(LC_ALL, "");
	string str, code;
	string decrypt;
	if (after_encrypt) {
		str = file_Read(orig_encrypt_decrypt - 1, 1, false);
		code = file_Read(orig_encrypt_decrypt - 1, 0, true);
	}
	else {
		str = file_Read(orig_encrypt_decrypt - 2, 0,false);
		cout << "Введите ключ шифрования:\n: ";
		cin >> code;
	}
	decrypt = Visiner_Decrypt(str, code);
	cout << "Расшифрованный код: " << decrypt << endl;
	file_Write(decrypt, orig_encrypt_decrypt,false);
}

string Gronsfeld_Decrypt(string stringInp, int key) {

	int keyLen = 0;
	for (int temp = key; temp > 0; keyLen++) {
		temp /= 10;
	}

	for (int i = 0, t1, t2; i < stringInp.length(); i++) {
		t1 = pow(10, i % keyLen);
		stringInp[i] -= ((key / t1) % 10);
	}

	return stringInp;
}

void Gronsfeld_out(int orig_encrypt_decrypt, bool after_encrypt)//для Цезаря
{
	setlocale(LC_ALL, "");
	string stringInp, decryptMessage;
	int key_1;
	if (after_encrypt) {
		key_1 = file_Read_(orig_encrypt_decrypt - 1, 0,true);
		cout << "Количество сдвигов в слове: " << key_1 << endl;
		stringInp = file_Read(orig_encrypt_decrypt - 1, 1,false);
	}
	else {
		cout << "Введите количество сдвигов в слове:\n: ";
		cin >> key_1;
		stringInp = file_Read(orig_encrypt_decrypt - 2, 0,false);
	}
	cout << "Это ваше расшифрованное слово:" << endl;
	decryptMessage = Gronsfeld_Decrypt(stringInp, key_1);
	cout << decryptMessage << endl;
	file_Write(decryptMessage, orig_encrypt_decrypt,false);
}