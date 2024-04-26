#include "Key_Generation.h"


Key_Generation::Key_Generation(unsigned char Master[16])
{
    int c = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            All_RoundKeys[j][i] = Master[c];
            c++;
        }
    }
}

void Key_Generation::Rotate(unsigned char T[])
{
    unsigned char t = T[0];
    T[0] = T[1];
    T[1] = T[2];
    T[2] = T[3];
    T[3] = t;

}

void Key_Generation::Sub_Bytes(unsigned char T[])
{

    for (int i = 0; i < 4; i++)
    {
        int temp = (int)T[i];

        int Hex_digits[2]; // Array to store each hexadecimal digit

        // Extract and store each hexadecimal digit
        for (int i = 0; i < 2; ++i) {
            Hex_digits[i] = temp & 0xF; // Extract the rightmost nibble

            temp >>= 4; // Move to the next nibble
        }

        int x = Hex_digits[1]; // leftmost hex digit stored in index 1 (initialize x by it);
        int y = Hex_digits[0]; // rightmost hex digit stored in index 0 (initialize y by it);

        T[i] = S_BOX[x][y]; // sub in S_Box

    }
}

void Key_Generation::add_rcon(unsigned char T[], int r_number)
{
    unsigned char temp = (Rcon[r_number] >> 24) & 0xFF;

    T[0] ^= temp;
    T[1] ^= 0x00;
    T[2] ^= 0x00;
    T[3] ^= 0x00;

}

void Key_Generation::XOR_with_col(unsigned char T[], unsigned char w[])
{
    for (int i = 0; i < 4; i++) {
        T[i] ^= w[i];

    }
}

void Key_Generation::loop()
{
    unsigned char T[4];
    unsigned char w[4];
    int col = 0;
    for (int i = 4; i < 44; i++) {
        for (int j = 0; j < 4; j++) {
            T[j] = All_RoundKeys[j][i - 1];
        }
        if (i % 4 == 0) {
            Rotate(T);
            Sub_Bytes(T);
            add_rcon(T, (i / 4) - 1);
        }
        for (int j = 0; j < 4; j++) {
            w[j] = All_RoundKeys[j][col];
        }

        XOR_with_col(T, w);
        col++;
        for (int j = 0; j < 4; j++) {
            All_RoundKeys[j][i] = T[j];
        }
    }
}


unsigned char(*Key_Generation::Get_RoundKey(int round_num))[4]
    {
        static unsigned char temp[4][4];
        int R = round_num * 4 ; // R is first column i will accessed in All_RoundKeys[][] ;

        for (int i = 0; i < 4; i++)
        {

            for (int j = 0; j < 4; j++)
            {
                temp[j][i] = All_RoundKeys[j][R];

            }
            
            R++;
        }

        return temp;
    }







