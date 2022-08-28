//Encrypt.cpp
//========================================================================================
#include <string>
#include <iostream>
#include <vector>
#include "fileInOut.h"
using namespace std;
string Atbash_Encrypt(string text) {
	int num = 0;
	string lowercase_latin = { "abcdefghijklmnopqrstuvwxyz" };
	string uppercase_latin = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	for (int count = 0; count < text.length(); count++) {
		for (int i = 0; i < lowercase_latin.length(); i++) {
			if (text[count] == lowercase_latin[i]) {
				if (i != lowercase_latin.length()) {
					num = lowercase_latin.length() - i - 1;
				}
				text[count] = lowercase_latin[num];
				break;
			}
			if (text[count] == uppercase_latin[i]) {
				if (i != uppercase_latin.length()) {
					num = uppercase_latin.length() - i - 1;
				}
				text[count] = uppercase_latin[num];
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
	cout << "������������� ���������: " << text << endl;
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
void Visiner_in(int orig_encrypt_decrypt)//��� �������� 
{
	setlocale(LC_ALL, "");
	string str, code;
	string crypt;
	str = file_Read(orig_encrypt_decrypt - 1, 0,false);
	cout << "������� ���� ����������:\n: ";
	cin >> code;
	file_Write(code, orig_encrypt_decrypt,true);
	crypt = Visiner_Encrypt(str, code);
	cout << "������������� ���: " << crypt << endl;
	file_Write(crypt, orig_encrypt_decrypt,false);
}

string Gronsfeld_Encrypt(string stringInp, int key) {
	int keyLen = 0;
	for (int temp = key; temp > 0; keyLen++) {
		temp /= 10;
	}

	/*for (int i = 0, t1, t2; i < stringInp.length(); i++) {
		t1 = pow(10, i % keyLen);
		if (stringInp[i] == 32) continue;
		stringInp[i] += ((key / t1) % 10);
	}*/

	for (long long int i = 0, t1, t2, latin_symb_count = 0; i < stringInp.size(); i++) {
		if (!((stringInp[i] >= 'A' && stringInp[i] <= 'Z') || (stringInp[i] >= 'a' && stringInp[i] <= 'z'))) continue;

		t2 = keyLen - 1 - latin_symb_count;
		if (t2 < 0)
			t2 = (t2 % keyLen + (keyLen)) % keyLen;

		t1 = pow(10, t2);

		if (stringInp[i] >= 'A' && stringInp[i] <= 'Z') {
			stringInp[i] += ((key / t1) % 10);
			if (stringInp[i] > 'Z') stringInp[i] = (stringInp[i] - 'Z') % 26 + 'A' - 1;
		}
		if (stringInp[i] >= 'a' && stringInp[i] <= 'z') {
			stringInp[i] += ((key / t1) % 10);
			if (stringInp[i] > 'z') stringInp[i] = (stringInp[i] - 'z') % 26 + 'a' - 1;
		}

		latin_symb_count++;
	}

	return stringInp;
}

void Gronsfeld_in(int orig_encrypt_decrypt)
{
	setlocale(LC_ALL, "");
	string stringInp, encryptMessage;
	int key_1;
	cout << "������� ���������� ������� � �����:" << endl;
	cin >> key_1;
	file_Write_(key_1, orig_encrypt_decrypt, true);
	stringInp = file_Read(orig_encrypt_decrypt - 1, 0,false);
	cout << "��� ���� ������������� �����" << endl;
	encryptMessage = Gronsfeld_Encrypt(stringInp, key_1);
	cout << encryptMessage << endl;
	file_Write(encryptMessage, orig_encrypt_decrypt,false);
}

string Key_Encrypt(string message, int key) {

	vector <vector<char>> alphabet = {
		{'A','B','C','D','E','F','G','H','I','J'},
		{'K','L','M','N','O','P','Q','R','S','T'},
		{'U','V','W','X','Y','Z','A','B','C','D'},
		{'E','F','G','H','I','J','K','L','M','N'},
		{'O','P','Q','R','S','T','U','V','W','X'},
		{'Y','Z','A','B','C','D','E','F','G','H'},
		{'I','J','K','L','M','N','O','P','Q','R'},
		{'S','T','U','V','W','X','Y','Z','A','B'},
		{'C','D','E','F','G','H','I','J','K','L'},
		{'M','N','O','P','Q','R','S','T','U','V'}
	};
	int keyLen = 0;

	for (long long int temp = key; temp > 0; keyLen++) {
		temp /= 10;
	}


	for (int i = 0, t1, t2; i < message.size(); i++) {
		t2 = keyLen - 1 - i;
		if (t2 < 0)
			t2 = (t2 % keyLen + (keyLen)) % keyLen;

		t1 = pow(10, t2);

		int keyPart = ((key / t1) % 10);

		int messagePart = int(message[i] - '0');

		message[i] = alphabet[keyPart][messagePart];
	}

	return message;
}