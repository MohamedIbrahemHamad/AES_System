#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "Decryption_Rounds.h"
#include "Encryption_Rounds.h"
#include "Key_Generation.h"
#include <string>
class AES
{
private:
	unsigned char Master_Key[16];

	Encryption_Rounds  Encrypt ;
    Decryption_Rounds Decrypt ;
	
	string plain_text  = "1111111111111111";
	string Cipher_text = "1111111111111111";

  public : 
	  
	  AES(string plain_text , int flag);
	  AES(string Cipher_text);

	  void set_MasterKey(unsigned char Master [16]);

	  void Encryption();
	  void Decryption();

};

