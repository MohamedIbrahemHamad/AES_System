#include <iostream>
#include "Decryption_Rounds.h"
#include "Encryption_Rounds.h"
#include "AES.h"
#include "Key_Generation.h"
#include "string"
using namespace std;


int main()
{

    bool running = true;
    while (running) {
       cout<<"Welcome to the Advanced Encryption Standard System !\n\n";
       cout << "1. Encryptin" << "\t\t" << "   2.Decryptin\n";
       cout<<"\t\t3. Exit\n";
       cout << "**************************************************************************************************\n" ;
        cout<<"Enter your choice: \n";
        cout << "__________________________________________________________________________________________________\n" ;
        int choice; cin >> choice ;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer

        switch (choice) {

        case 1:
        {
            string plain_text;
            cout << "Please enter plain text of only 16 characters : \n";
            cout << "__________________________________________________________________________________________________\n";

            getline(cin, plain_text);
          
            if (plain_text.size() != 16) {
                cout << "Error: Plain text must be exactly 16 characters.\n";
                continue;
            }
           
            cout << "\n";
            cout << "Please enter Master key must be exactly 16 characters :\n";
            cout << "__________________________________________________________________________________________________\n";
            string Mkey ;
            getline(cin, Mkey);

            if (Mkey.size() != 16) {
                cout << "Error: Master key must be exactly 16 characters.\n";
                continue;
            }

            unsigned char key[16];
            for (int i = 0; i < 16; i++)
            {
                key[i] = (int)Mkey[i];
            }

            AES EN(plain_text, 2);
            EN.set_MasterKey(key);
            cout << "__________________________________________________________________________________________________\n";
            EN.Encryption();
            cout << "__________________________________________________________________________________________________\n";
        }

        break;

        case 2: {

            string Cipher_text;
            cout << "Please enter Cipher text of only 16 characters : \n";
            cout << "__________________________________________________________________________________________________\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            getline(cin, Cipher_text);

            if (Cipher_text.size() != 16) {
                cout << "Error: Plain text must be exactly 16 characters.\n";
                continue;
            }

            cout << "\n";
            cout << "Please enter Master key must be exactly 16 characters :\n";
            cout << "__________________________________________________________________________________________________\n";
            string Mkey;
            getline(cin, Mkey);

            if (Mkey.size() != 16) {
                cout << "Error: Master key must be exactly 16 characters.\n";
                continue;
            }

            unsigned char key[16];

            for (int i = 0; i < 16; i++)
            {
                key[i] = (int)Mkey[i];
            }

            AES EN(Cipher_text);
            EN.set_MasterKey(key);
            cout << "__________________________________________________________________________________________________\n";
            EN.Decryption();
            cout << "__________________________________________________________________________________________________\n";

        }
              break;



        case 3: {
            cout << "thanks for using and goodbye\n";
            running = false;

        }
              break;


        default:
        {
            cout << "Invalid choice. Please enter a number between 1 and 3\n";
            cout << "__________________________________________________________________________________________________\n";
        }

      

        }//switch


    }//while


	return 0;
   
}
