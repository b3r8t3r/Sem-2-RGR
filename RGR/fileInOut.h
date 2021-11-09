//fileInOut.h
//========================================================================================
#include <string>
void file_New();
void file_Write(std::string str, int orig_encrypt_decrypt, bool is_encrypt);
void file_Write_(int str, int orig_encrypt_decrypt, bool is_encrypt);
std::string file_Read(int orig_encrypt_decrypt, int string_num, bool is_encrypt);
int file_Read_(int orig_encrypt_decrypt, int string_num, bool is_encrypt);
