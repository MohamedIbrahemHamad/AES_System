using namespace std;
#include "Encryption_Rounds.h"
#include <queue>

void Encryption_Rounds::Set_State(char unsigned s[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = s[i][j];
        }

    }
}

void Encryption_Rounds::Shift_Rows()
{
    queue <char> arr;

    for (int i = 1; i < 4; i++) {
        arr.push(state[i][0]); arr.push(state[i][1]);
        arr.push(state[i][2]); arr.push(state[i][3]);

        for (int j = 0; j < i; j++) {
            char c = arr.front();
            arr.pop();
            arr.push(c);
        }

        for (int k = 0; k < 4; k++) {
            state[i][k] = arr.front();
            arr.pop();
        }
    }
}

void Encryption_Rounds::AddRoundKey(unsigned char Round_key[4][4])
{

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] ^= Round_key[i][j];
        }
    }

}

void Encryption_Rounds::Substitution_Bytes()
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int temp = (int)state[i][j];

            int Hex_digits[2]; // Array to store each hexadecimal digit

            // Extract and store each hexadecimal digit
            for (int i = 0; i < 2; ++i) {
                Hex_digits[i] = temp & 0xF; // Extract the rightmost nibble
                temp >>= 4; // Move to the next nibble
            }

            int x = Hex_digits[1]; // leftmost hex digit stored in index 1 (initialize x by it);
            int y = Hex_digits[0]; // rightmost hex digit stored in index 0 (initialize y by it);

            state[i][j] = s_box[x][y]; // sub in?INVS_Box

        }

    }
}

void Encryption_Rounds::mixColumns()
{
    unsigned char result[4][4];

    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            result[r][c] =
                multiply(0x02, state[(r + 0) % 4][c]) ^
                multiply(0x03, state[(r + 1) % 4][c]) ^
                multiply(0x01, state[(r + 2) % 4][c]) ^
                multiply(0x01, state[(r + 3) % 4][c]);
        }
    }

    // Copy the result back to the state
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = result[i][j];
        }
    }
}

unsigned char Encryption_Rounds::multiply(unsigned char a, unsigned char b)
{
    unsigned char result = 0;
    unsigned char high_bit;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= a;
        }
        high_bit = a & 0x80;
        a <<= 1;
        if (high_bit) {
            a ^= 0x1B; // This is the irreducible polynomial in AES
        }
        b >>= 1;
    }
    return result;
}


void Encryption_Rounds::Initial_Round(unsigned char Round_key[4][4])
{
    AddRoundKey(Round_key);

}


    void Encryption_Rounds::Main_Round(unsigned char Round_key[4][4])
    {
        Substitution_Bytes();
        Shift_Rows();
        mixColumns();
        AddRoundKey(Round_key);

    }

    void Encryption_Rounds::Final_Round(unsigned char Round_key[4][4])
    {

        Substitution_Bytes();
        Shift_Rows();
        AddRoundKey(Round_key);

    }





