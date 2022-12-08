#include <iostream>
#include "Tetromino.h"
#include <chrono>
#include <thread>

using namespace std;

namespace Tetromino
{
	bool isValidInput(char c) //it check input is valid
	{
		return (c == 'I' || c == 'O' || c == 'T' || c == 'J' || c == 'L' || c == 'S' || c == 'Z' || c == 'Q' || c == 'R');
	}

	//it convert to integer from char array (It is guaranteed that the given array consists of numbers.)
	int to_integer(char *input, int len)
	{
		int diveder = 1;
		int result = 0;

		while(--len > 0) diveder *= 10;

		int i = 0;
		while(diveder > 0)
		{
			result += (input[i++]-48)*diveder;
			diveder /= 10;
		}

		return result;

	}


	/* GETTERS */
	unsigned int Tetromino::getReturnOriginCounter() { return returnOriginCounter;}
	char Tetromino::getLetter() { return letter; }
	char **Tetromino::getShape() { return tetro;}
	int Tetromino::getLetterCount() {return letterCount;}
	int **Tetromino::getLetterCoordinates() {return letterCoordinates;}	
	int Tetromino::getTargetY(){return targetY;}
	int Tetromino::getTargetX(){return targetX;}
	int Tetromino::getTetroPosition(){return tetroPosition;}
	
	/* END OF GETTERS*/
	
	//the shape of the tetrominos is determined according to the letter entered.
	void Tetromino::setShape(shapes type)
	{
		switch(type)
		{
			case shapes::I:
				tetro[0][0] = tetro[1][0] = tetro[2][0] = tetro[3][0] = 'I';
				returnOriginCounter = 1;
				letter = 'I';
				break;
				
			case shapes::O:
				tetro[0][0] = tetro[0][1] = tetro[1][0] = tetro[1][1] = 'O';
				returnOriginCounter = 0;
				letter = 'O';
				break;
				
			case shapes::T:			
				tetro[0][0] = tetro[0][1] = tetro[0][2] = tetro[1][1] = 'T';
				returnOriginCounter = 3;
				letter = 'T';
				break;
						
			case shapes::J:				
				tetro[0][1] = tetro[1][1] = tetro[2][0] = tetro[2][1] = 'J';
				returnOriginCounter = 3;
				letter = 'J';				
				break;
			case shapes::L:	
				tetro[0][0] = tetro[1][0] = tetro[2][0] = tetro[2][1] = 'L';
				returnOriginCounter = 3;
				letter = 'L';
				break;
						
			case shapes::S:				
				tetro[0][1] = tetro[0][2] = tetro[1][0] = tetro[1][1] = 'S';
				returnOriginCounter = 1;
				letter = 'S';
				break;
						
			case shapes::Z:				
				tetro[0][0] = tetro[0][1] = tetro[1][1] = tetro[1][2] = 'Z';
				returnOriginCounter = 1;
				letter = 'Z';
				break;
		}
		setLetterCoordinates();
	}
	
	//a function that print tetro
	void Tetromino::printTetro() const
	{
		for(int i = 0; i<rowSize; i++)
		{
			for(int j = 0; j<colSize; j++)
				cout << tetro[i][j];

			cout << endl;
		}

	}
	
	//it determining letter coordinates in tetro matrix, when using rotate function letters coordinates always change and with this function we take its coordinates. 
	//After that we draw to gameboard with taking reference these coordinates.
	//it start to reading from toLeft bottom side 
	void Tetromino::setLetterCoordinates()
	{
		
		int idx = 0;
		int _rowSize = rowSize, _colSize = colSize;
		
		for(int row = _rowSize-1; row>=0; row--)
		{
			for(int col = 0; col<_colSize; col++)
			{
				if(tetro[row][col] != ' ')
				{
					letterCoordinates[idx][0] = row;
					letterCoordinates[idx][1] = col;
					idx++;
				}
			}
		}
	}
	
	bool Tetromino::isXFitted() { return (this->getTargetX() == this->letterCoordinatesOnBoard[0][1]); }
	bool Tetromino::isYFitted() { return (this->getTargetY() == this->letterCoordinatesOnBoard[0][0]); }
	
	//it rotate the tetro matrix so rotate the shape of letter
	void Tetromino::rotate(route direction)
	{
		int len = 4;
		this->tetroPosition += 1; 
		this->tetroPosition %= this->getReturnOriginCounter()+1;
		
		if(direction==route::toRight)
        {
			for (int x = 0; x < (len + 1) / 2; x ++) 
			{
				for (int y = 0; y < len / 2; y++) 
				{
					int value = tetro[len - 1 - y][x];
					tetro[len - 1 - y][x] = tetro[len - 1 - x][len - y - 1];
					tetro[len - 1 - x][len - y - 1] = tetro[y][len - 1 -x];
					tetro[y][len - 1 - x] = tetro[x][y];
					tetro[x][y] = value;
				}
			}
		}
		else if(direction==route::toLeft)
        {
			for (int x = 0; x < (len + 1) / 2; x ++) 
			{
				for (int y = 0; y < len / 2; y++) 
				{
					int value = tetro[x][len - 1 - y];
					tetro[x][len - 1 - y] = tetro[len - y - 1][len - 1 - x];
					tetro[len - y - 1][len - 1 - x] = tetro[len - 1 -x][y];
					tetro[len - 1 - x][y] = tetro[y][x];
					tetro[y][x] = value;
				}
			}
		}
		setLetterCoordinates(); //setting coordinates of letters in matrix
	}
	
	//constructors
	Tetromino::Tetromino(shapes type)
	{
		/* INITILAZING DYNAMIC ARRAYS*/

		letterCoordinatesOnBoard = new int*[4];
		for(int i=0; i<4; i++)
			letterCoordinatesOnBoard[i] = new int[2];

		letterCoordinates= new int*[4];
		for(int i=0; i<4; i++)
			letterCoordinates[i] = new int[2];


		rowSize = _rowSize;
		colSize = _colSize;
		letter = (char)type;
		
		tetro = new char*[rowSize];
		for(int i=0; i<rowSize; i++)
			tetro[i] = new char[colSize];

		for(int i=0; i<rowSize; i++)
			for(int j=0; j<colSize; j++)
				tetro[i][j] = ' ';

		// setting tetro type	
		setShape(type);
	}
	
	Tetromino::Tetromino()
	{
		rowSize = _rowSize;
		colSize = _colSize;

		/* INITILAZING DYNAMIC ARRAYS*/
		letterCoordinatesOnBoard = new int*[4];
		for(int i=0; i<letterCount; i++)
			letterCoordinatesOnBoard[i] = new int[2];

		letterCoordinates= new int*[4];
		for(int i=0; i<letterCount; i++)
			letterCoordinates[i] = new int[2];

		
		tetro = new char*[rowSize];
		for(int i=0; i<rowSize; i++)
			tetro[i] = new char[colSize];

		for(int i=0; i<rowSize; i++)
			for(int j=0; j<colSize; j++)
				tetro[i][j] = ' ';

	}

	Tetromino::~Tetromino()
	{
		/* DELETING DYNAMIC ARRAYS*/

		for(int i=0; i<rowSize; i++)
			delete[] tetro[i];
		delete[] tetro;

		for(int i=0; i<letterCount; i++)
			delete[] letterCoordinates[i];
		delete[] letterCoordinates;

		for(int i=0; i<letterCount; i++)
			delete[] letterCoordinatesOnBoard[i];
		delete[] letterCoordinatesOnBoard;
	}
	

}

	