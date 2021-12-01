//Decrypt.h
//========================================================================================
#include <string>
std::string Atbash_Decrypt(std::string text);
void Atbash_out(int orig_encrypt_decrypt, bool after_encrypt);
std::string Visiner_Decrypt(std::string message, std::string key);
void Visiner_out(int orig_encrypt_decrypt, bool after_encrypt);
std::string Gronsfeld_Decrypt(std::string stringInp, int key);
void Gronsfeld_out(int orig_encrypt_decrypt, bool after_encrypt);
std::string Key_Decrypt(std::string stringInp, int key);