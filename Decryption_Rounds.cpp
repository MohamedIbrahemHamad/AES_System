#include "Decryption_Rounds.h"
using namespace std;
#include <iostream>
#include <algorithm>

void Decryption_Rounds::Set_State(char unsigned State[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CipherState[i][j] = State[i][j];
		}

	}
}

void Decryption_Rounds::INVSub_Byte()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{ 
			int temp = (int)CipherState[i][j];

			int Hex_digits[2]; // Array to store each hexadecimal digit


			// Extract and store each hexadecimal digit
			for (int i = 0; i < 2; ++i) {
				Hex_digits[i] = temp & 0xF; // Extract the rightmost nibble
				temp >>= 4; // Move to the next nibble
			}

			int x = Hex_digits[1]; // leftmost hex digit stored in index 1 (initialize x by it);
			int y = Hex_digits[0]; // rightmost hex digit stored in index 0 (initialize y by it);

			CipherState[i][j] = INVS_BOX[x][y]; // sub in INVS_Box

		}

	}


}

void Decryption_Rounds::INVShiftRow()
{
	//  row 0 doesnot changed 

	//  in row 1 : Shift rightmost byte to left once
	unsigned char temp = CipherState[1][3];

	for (int i = 3; i > 0; i--)
	{
		CipherState[1][i] = CipherState[1][i - 1];
	}

	CipherState[1][0] = temp;

	//  in row 2 : Shift rightmost byte to left twice
	swap (CipherState[2][2], CipherState[2][0]);
	swap(CipherState[2][3], CipherState[2][1]);

	//  in row 3 : Shift rightmost byte to left third times
	temp = CipherState[3][0];

	for (int i = 0; i < 3; i++)
	{
		CipherState[3][i] = CipherState[3][i + 1];
	}
	CipherState[3][3] = temp;

}

void Decryption_Rounds::INVMixColumn()
{

	unsigned char result[4][4];

	for (int c = 0; c < 4; c++) {
		for (int r = 0; r < 4; r++) {
			result[r][c] =
				Poly_multiply(0x0E, CipherState[(r + 0) % 4][c]) ^
				Poly_multiply(0x0B, CipherState[(r + 1) % 4][c]) ^
				Poly_multiply(0x0D, CipherState[(r + 2) % 4][c]) ^
				Poly_multiply(0x09, CipherState[(r + 3) % 4][c]);
		}
	}

	// Copy the result back to the state
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			CipherState[i][j] = result[i][j];
		}
	}


}

unsigned char Decryption_Rounds::Poly_multiply(unsigned char a, unsigned char b)
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

void Decryption_Rounds::Add_RoundKey(unsigned char Round_key[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			CipherState[i][j] ^= Round_key[i][j];
		}
	}
}





void Decryption_Rounds::Initial_Round(unsigned char Round_key[4][4])
{
	Add_RoundKey(Round_key);
}

void Decryption_Rounds::Main_Round(unsigned char Round_key[4][4])
{
	
	
	INVShiftRow();
	INVSub_Byte();
	Add_RoundKey(Round_key);
	INVMixColumn();
	
}

void Decryption_Rounds::Final_Round(unsigned char Round_key[4][4])
{
	
	INVShiftRow();
	INVSub_Byte();
	Add_RoundKey(Round_key);
}






