//Encrypt.h
//========================================================================================
#include<string>
std::string Atbash_Encrypt(std::string text);
void Atbash_in(int orig_encrypt_decrypt);
std::string Visiner_Encrypt(std::string message, std::string key);
void Visiner_in(int orig_encrypt_decrypt);
std::string Gronsfeld_Encrypt(std::string stringInp, int key);
void Gronsfeld_in(int orig_encrypt_decrypt);
