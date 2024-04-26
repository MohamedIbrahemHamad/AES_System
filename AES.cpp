using namespace std;
#include "AES.h"
#include <iostream>
#include <string>



AES::AES(string p , int flag)
{
    plain_text = p;

    unsigned char hex_val [16];

    for (int i = 0; i < 16; i++)
    {
         
             hex_val[i] = (int)plain_text[i];

    }

    unsigned char temp[4][4];

    int c = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp[j][i] = hex_val[c];
            c++;

        }

    }

    Encrypt.Set_State(temp);
}

AES::AES(string C)
{ 
    Cipher_text = C; 
   
    unsigned char hex_val [16];

    for (int i = 0; i < 16; i++)
    {
        hex_val[i] = (int)Cipher_text[i] ;
    }

    unsigned char temp[4][4] ;

    int c = 0;
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0; j < 4; j++ )
        {
            temp[j][i] = hex_val[c];
            c++;

        }

    }

    Decrypt.Set_State(temp);
}


void AES::set_MasterKey(unsigned char Master [16] )
{
    for (int i = 0; i < 16; i++)
    {
            Master_Key[i] = Master[i] ;
        
    }
}


void AES::Encryption()
{
    cout << "Plain_text before starting : " << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << hex << uppercase <<int(Encrypt.state[i][j]) << " ";

        }
        cout << endl;
    }
    cout << endl;

    Key_Generation Key(Master_Key); 
    Key.loop();
   
    //Initial_Round
    Encrypt.Initial_Round(Key.Get_RoundKey(0));


    cout << "Plain_text After Round 0  : " << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << hex << uppercase << int(Encrypt.state[i][j]) << " ";

        }
        cout << endl;
    }

    cout << endl;


    //Main_Rounds
    for (int i = 1; i <= 9; i++)
    {
        Encrypt.Main_Round(Key.Get_RoundKey(i));

        cout << "Plain_text After Round " <<i<<" : " << endl;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << hex << uppercase << int(Encrypt.state[i][j]) << " ";

            }
            cout << endl;
        }

        cout << endl;
    }


    //Final_Round
    Encrypt.Final_Round(Key.Get_RoundKey(10));


    cout << "plain text After Final round (Cipher_text state) : " << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
           cout<<hex<< uppercase <<  int(Encrypt.state[i][j])<<" ";
           
        }
        cout << endl;
    }

}



void AES::Decryption()
{

    cout << "Cipher_text before starting : " << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << hex << uppercase << int(Decrypt.CipherState[i][j]) << " ";

        }
        cout << endl;
    }
    cout << endl;


    Key_Generation Key(Master_Key);
    Key.loop();


    //Initial_Round
    Decrypt.Initial_Round(Key.Get_RoundKey(10));


    cout << "Cipher_text After Round 0: " << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << hex << uppercase << int(Decrypt.CipherState[i][j]) << " ";

        }
        cout << endl;
    }
    cout << endl;


    // Main_Rounds 
    int r = 1;
    for (int i = 9; i >= 1; i--)
    {
         Decrypt.Main_Round(Key.Get_RoundKey(i));


         cout << "Plain_text After Round " << r << " : " << endl;
         for (int i = 0; i < 4; i++)
         {
             for (int j = 0; j < 4; j++)
             {
                 cout << hex << uppercase << int(Decrypt.CipherState[i][j]) << " ";

             }
             cout << endl;
         }

         cout << endl;
         r++;
    }



    // Final_Round 
     Decrypt.Final_Round(Key.Get_RoundKey(0));
   

     cout << "plain text After Final round (Plain_text state) : " << endl;
     for (int i = 0; i < 4; i++)
     {
         for (int j = 0; j < 4; j++)
         {
             cout << hex << uppercase << int(Decrypt.CipherState[i][j]) << " ";

         }
         cout << endl;
     }
}



