#include <iostream>
#include <vector>
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

	/* GETTERS */
	unsigned int Tetromino::getReturnOriginCounter() { return returnOriginCounter;}
	char Tetromino::getLetter() { return letter; }
	vector<vector<char>> Tetromino::getShape() { return tetro;}
	int Tetromino::getLetterCount() {return letterCount;}
	vector<vector<int>> Tetromino::getLetterCoordinates() {return letterCoordinates;}	
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
				tetro = {
							{'I',' ',' ',' '},
							{'I',' ',' ',' '},
							{'I',' ',' ',' '},
							{'I',' ',' ',' '}
						};
				returnOriginCounter = 1;
				letter = 'I';
				break;
				
			case shapes::O:
				tetro = {
							{'O','O',' ',' '},
							{'O','O',' ',' '},
							{' ',' ',' ',' '},
							{' ',' ',' ',' '}
						};
				returnOriginCounter = 0;
				letter = 'O';
				break;
				
			case shapes::T:			
				tetro = {
							{'T','T','T',' '},
							{' ','T',' ',' '},
							{' ',' ',' ',' '},
							{' ',' ',' ',' '}
						};
				returnOriginCounter = 3;
				letter = 'T';
				break;
						
			case shapes::J:				
				tetro = {
							{' ','J',' ',' '},
							{' ','J',' ',' '},
							{'J','J',' ',' '},
							{' ',' ',' ',' '}
						};
				returnOriginCounter = 3;
				letter = 'J';				
				break;
						
			case shapes::L:				
				tetro = {
							{'L',' ',' ',' '},
							{'L',' ',' ',' '},
							{'L','L',' ',' '},
							{' ',' ',' ',' '}
						};
				returnOriginCounter = 3;
				letter = 'L';
				break;
						
			case shapes::S:				
				tetro = {
							{' ','S','S',' '},
							{'S','S',' ',' '},
							{' ',' ',' ',' '},
							{' ',' ',' ',' '}
						};
				returnOriginCounter = 1;
				letter = 'S';
				break;
						
			case shapes::Z:				
				tetro = {
							{'Z','Z',' ',' '},
							{' ','Z','Z',' '},
							{' ',' ',' ',' '},
							{' ',' ',' ',' '}
						};
				returnOriginCounter = 1;
				letter = 'Z';
				break;
		}
		
		setLetterCoordinates();
	}
	
	//a function that print tetro
	void Tetromino::printTetro() const
	{
		for(auto row : tetro)
		{
			for(auto el : row)
				cout << el;

			cout << endl;
		}

	}
	
	void Tetromino::setFitCoordinates(vector<vector<char>> &board)
	{
		
		int rowBorder = board.size(), colBorder = board[0].size(); //borders of map
		int drawn = 0; //counter of drawn letters
		
		int x, y=rowBorder-1; //x and y axis of board
		
		int referenceY, referenceX, yOfLetter, xOfLetter; //yOfLetter is y index to start drawing and xOfLetter for x
		int locY, locX;
		
		//tetroLetterIndexes is indexes of letters in tetro matrix. According to the relations of the indexes here, the drawing will be made on the gameboard. 
		//For example letter indexes be {{3,3},{3,4},{3,5},{4,4}} in tetro matrix when drawing the gameboard we take the first index as a reference
		//and the locations where the letters will be drawn will be {{currentX+0,currentY+0},{currentX+0,currentY+1},{currentX+0,currentY+2},{currentX+1,currentY+1}}
		//if it couldn't draw, it rotate and try again
		vector<vector<int>> tetroLetterIndexes; 
	
		while(y>=4)
		{
			x = 0;
			while(x<colBorder)
			{
				if(board[y][x] == ' ')
				{
					for(unsigned int i=0; i<=this->getReturnOriginCounter(); i++) //try until originCounter if it couldn't draw this mean it cannot draw letter this position and then it pass the next x index;
					{					
						tetroLetterIndexes = this->getLetterCoordinates();	

						referenceY = tetroLetterIndexes[0][0];
						referenceX = tetroLetterIndexes[0][1];
						
						for(unsigned int i=0; i<tetroLetterIndexes.size(); i++)
						{
							yOfLetter = tetroLetterIndexes[i][0];
							xOfLetter = tetroLetterIndexes[i][1];
							
							//calculate the locations x and y for drawing the letter
							locY = y+yOfLetter-referenceY;
							locX = x+xOfLetter-referenceX;
							
							//if there is any mistake like collision or overflow in map it enter this if block
							if(locY < 4 || locY >= rowBorder || locX < 0 || locX >= colBorder || board[locY][locX] != ' ')
							{
								this->rotate(route::toLeft); //rotating the tetro for try again
								drawn = 0; //drawn counter set 0 because it try a new tetro which rotate 
								break;
							}
							
							drawn++;
						}
						//if the letter was drawn successfully
						if(drawn == this->getLetterCount()) break;
					}
				}
				
					if(drawn == this->getLetterCount()) break;
				
				x++; //passing next x 
			}
			
			if(drawn == this->getLetterCount()) break;
			
			y--;
		}
		
		this->targetX = x;
		this->targetY = y;
		
	}
	
	
	//it determining letter coordinates in tetro matrix, when using rotate function letters coordinates always change and with this function we take its coordinates. 
	//After that we draw to gameboard with taking reference these coordinates.
	//it start to reading from toLeft bottom side 
	void Tetromino::setLetterCoordinates()
	{
		letterCoordinates.clear();
		
		int _rowSize = rowSize, _colSize = colSize;
		
		for(int row = _rowSize-1; row>=0; row--)
			for(int col = 0; col<_colSize; col++)
				if(tetro[row][col] != ' ')
					letterCoordinates.push_back({row,col});
					
	}
	
	bool Tetromino::isXFitted() { return (this->getTargetX() == this->letterCoordinatesOnBoard[0][1]); }
	bool Tetromino::isYFitted() { return (this->getTargetY() == this->letterCoordinatesOnBoard[0][0]); }
	
	//it rotate the tetro matrix so rotate the shape of letter
	void Tetromino::rotate(route direction)
	{
		int len = tetro.size();
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
	
	//constructor
	Tetromino::Tetromino(shapes type)
	{
		rowSize = _rowSize;
		colSize = _colSize;
		letter = (char)type;
		setShape(type);
	}
	
	Tetromino::Tetromino()
	{
		rowSize = _rowSize;
		colSize = _colSize;
		
		tetro = {
							{' ',' ',' ',' '},
							{' ',' ',' ',' '},
							{' ',' ',' ',' '},
							{' ',' ',' ',' '}
				};
	}



}

	
	