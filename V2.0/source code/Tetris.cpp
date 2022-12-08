#include <iostream>
#include "Tetris.h"
#include "Tetromino.h"
#include <chrono>
#include <thread>

using namespace std;

namespace Tetris
{
	/* GETTERS */
	unsigned int Tetris::getRowSize(){return row;}
	unsigned int Tetris::getColSize(){return col;}
	int Tetris::getCreationAreaHeight(){return creationAreaHeight;}
	
	/* END OF GETTERS*/
	
	
	// it clear given indexes in gameArea, it using when collision while drawing letter to map
	void Tetris::clearIndexes(int *indexes[2], int indexSize)
	{
		for(int i = 0; i<indexSize; i++)
			gameArea[indexes[i][0]][indexes[i][1]] = ' ' ;
	}
	
	// a operatator overloaded function which add a tetromino to gameBoard
	void Tetris::operator+=(Tetromino::Tetromino &tetro)
	{
		int **tetroLetterIndexes = tetro.getLetterCoordinates(); //takes coordinates of letters from matrix of tetro
		
		//indexes of places to start drawing
		int startXIndex = 	this->col/2;
		int startYIndex = getCreationAreaHeight()-1;
		
		//reference points
		int referenceY = tetroLetterIndexes[0][0];
		int referenceX = tetroLetterIndexes[0][1];
		
		//drawing tetro to board by tetroLetterIndexes

		for(int i = 0; i<tetro.getLetterCount(); i++)
		{
			this->gameArea[startYIndex+(tetroLetterIndexes[i][0]-referenceY)][startXIndex+(tetroLetterIndexes[i][1]-referenceX)] = tetro.getLetter();
			tetro.letterCoordinatesOnBoard[i][0] = startYIndex+(tetroLetterIndexes[i][0]-referenceY);
			tetro.letterCoordinatesOnBoard[i][1] = startXIndex+(tetroLetterIndexes[i][1]-referenceX);
		}
		
	}
	
	bool Tetris::move(Tetromino::Tetromino &tetro, Tetromino::route direction)
	{
		int xStep = 0, yStep = 0;

		switch(direction)
		{
			case Tetromino::route::toRight:
				xStep = 1;
				break;
			case Tetromino::route::toLeft:
				xStep = -1;
				break;
			case Tetromino::route::toDown:
				yStep = 1;
				break;
			case Tetromino::route::toUp:
				yStep = -1;
				break;
		}
		
		
		int **coordinates = new int*[4];
		for(int i=0; i<4; i++)
		{
			coordinates[i] = new int[2];
			coordinates[i][0] = tetro.letterCoordinatesOnBoard[i][0];
			coordinates[i][1] = tetro.letterCoordinatesOnBoard[i][1];
		}
		
		char **tempBoard;
		tempBoard = new char*[this->row];
		for(int i=0; i<row; i++)
			tempBoard[i] = new char[col];

		for(int i=0; i<row; i++)
			for(int j=0; j<col; j++)
				tempBoard[i][j] = gameArea[i][j];


		this->clearIndexes(tetro.letterCoordinatesOnBoard, tetro.getLetterCount());
		
		for(int i =0; i<tetro.getLetterCount(); i++)
		{
			int yOfelement = tetro.letterCoordinatesOnBoard[i][0], xOfelement = tetro.letterCoordinatesOnBoard[i][1];
			//checking collision
			if(xOfelement+xStep < 0 || xOfelement+xStep >= this->getColSize() || yOfelement+yStep < 0 || yOfelement+yStep >= this->getRowSize() || this->gameArea[yOfelement+yStep][xOfelement+xStep] != ' ')
			{
				for(int i=0; i<row; i++)
					for(int j=0; j<col; j++)
						gameArea[i][j] = tempBoard[i][j];

				return false;
			}
			
		}
		
		
		for(int i =0; i<tetro.getLetterCount(); i++)
		{
			int yOfelement = tetro.letterCoordinatesOnBoard[i][0], xOfelement = tetro.letterCoordinatesOnBoard[i][1];
			
			this->gameArea[yOfelement+yStep][xOfelement+xStep] = tetro.getLetter();
			tetro.letterCoordinatesOnBoard[i][0] = yOfelement+yStep;
			tetro.letterCoordinatesOnBoard[i][1] = xOfelement+xStep;
						
		}

		this->draw();

		
		return true;
		
	}
	
	bool Tetris::fit(Tetromino::Tetromino &tetro)
	{
		//here tetro trying to itself in its position
		if(!tetro.isRotated)
		{
			Tetromino::Tetromino temp;
			temp.setShape((Tetromino::shapes)tetro.getLetter());
			
			this->clearIndexes(tetro.letterCoordinatesOnBoard, tetro.getLetterCount());
			*this += temp;
			this->draw();
			for(int i=0; i<tetro.getTetroPosition(); i++)
			{
				temp.rotate(tetro.direction);
				this->clearIndexes(temp.letterCoordinatesOnBoard, temp.getLetterCount());
				*this += temp;
				this->draw();
			}
			
			tetro.isRotated = true;
		}
		
		//navigating
		if(tetro.getTargetX() < tetro.letterCoordinatesOnBoard[0][1])
		{
			tetro.targetRoute = Tetromino::route::toLeft;
			tetro.oppositeOfTargetRoute = Tetromino::route::toRight;
		}
		else
		{
			tetro.targetRoute = Tetromino::route::toRight;
			tetro.oppositeOfTargetRoute = Tetromino::route::toLeft;
		}

		while(!tetro.isXFitted() && move(tetro, tetro.targetRoute));
	
		return tetro.isXFitted();
	
	}	
	
	void Tetris::draw()
	{
		std::system("clear");
		cout << endl << endl;
		this->printArea();
		std::this_thread::sleep_for(std::chrono::milliseconds(75));
	}
	
	// a function which print game area 
	void Tetris::printArea() const
	{
		int startloc = this->creationAreaHeight, rowSize = this->row;
		for(int i=0; i<startloc; i++)
		{
			cout << "|";
			for(int k = 0; k<col; k++)
				cout << gameArea[i][k];

			cout << "|"<<endl;
		}
		
		for(int j=0; j<this->col; j++)
			cout << "-";
		cout << "-- <-- when a block come here then game over" << endl;

		for(int i=startloc; i<rowSize; i++)
		{
			cout << "|";
			for(int k = 0; k<col; k++)
				cout << gameArea[i][k];

			cout << "|"<<endl;
		}
	}

	bool Tetris::animate(Tetromino::Tetromino &tetro)
	{

		{
			Tetromino::Tetromino temp;
			temp.setShape((Tetromino::shapes)tetro.getLetter());
			*this += temp;
			draw();
			this->clearIndexes(temp.letterCoordinatesOnBoard, tetro.getLetterCount());
		}


		char input[10];
		char inputs[2];
		int idx = 0;
		int targetRow, targetCol;
		bool isValid;
		int len;

		cout << "Enter target row" << endl;
		do
		{
			isValid = true;
			len = 0;
			cin >> input; //input taking by string and then checking it, if there is any character without digit it take a new input
			for (int i=0;  input[i] != '\0'; i++)
			{
				len++;
				if (input[i] < 48 || input[i] > 57)
				{
					isValid = false;
					break;
				}
			}
			
			if(!isValid)
				cout << "Please enter a valid input" << endl;
				
		}while(!isValid);
		targetRow = Tetromino::to_integer(input, len); //given input turn to int
		targetRow += 4; //first 4 row is passing because it is spawn area. It is not included in the game board

		cout << "Enter target col" << endl;
		do
		{
			isValid = true;
			len = 0;
			cin >> input; //input taking by string and then checking it, if there is any character without digit it take a new input
			for (int i=0;  input[i] != '\0'; i++)
			{
				len++;
				if (input[i] < 48 || input[i] > 57)
				{
					isValid = false;
					break;
				}
			}
			
			if(!isValid)
				cout << "Please enter a valid input" << endl;
				
		}while(!isValid);				
		targetCol = Tetromino::to_integer(input, len); 

		char direction;
		char directionInput[2];
		do
		{
			isValid = true;
			idx = 0;
			cout << "Enter direction (R(Right), L(Left))" << endl;
			cin >> directionInput;
			direction = directionInput[0];

			while(directionInput[idx] != '\0') idx++;

			if(idx != 1 || !(direction == 'R' || direction == 'L'))
			{
				cout << "Please enter a valid input" << endl;
				isValid = false;
			}

		}while(isValid == false);

		tetro.direction = (Tetromino::route)direction;
		
		int rotateCount;
		cout << "Enter rotate count" << endl;
		do
		{
			isValid = true;
			len = 0;
			cin >> input; //input taking by string and then checking it, if there is any character without digit it take a new input
			for (int i=0;  input[i] != '\0'; i++)
			{
				len++;
				if (input[i] < 48 || input[i] > 57)
				{
					isValid = false;
					break;
				}
			}
			
			if(!isValid)
				cout << "Please enter a valid input" << endl;
				
		}while(!isValid);				
		rotateCount = Tetromino::to_integer(input, len); 

		rotateCount %= tetro.getReturnOriginCounter()+1;

		for(int i=0; i<rotateCount; i++)
			tetro.rotate(tetro.direction);

		tetro.setTargetCoordinates(targetCol, targetRow);


		{
			*this += tetro;
			this->clearIndexes(tetro.letterCoordinatesOnBoard, tetro.getLetterCount());
			Tetromino::Tetromino temp;
			temp.setShape((Tetromino::shapes)tetro.getLetter());
			*this += temp;
		}

		this->fit(tetro);
		
		int oldXLoc = -1, oldYLoc = -1;
		while(!tetro.isYFitted() && !(tetro.letterCoordinatesOnBoard[0][1] == oldXLoc && tetro.letterCoordinatesOnBoard[0][0] == oldYLoc))
		{
			cout << "." << endl;
			oldXLoc = tetro.letterCoordinatesOnBoard[0][1];
			oldYLoc = tetro.letterCoordinatesOnBoard[0][0];
			while(this->move(tetro, Tetromino::route::toDown));

			if(!tetro.isYFitted())
			{

				//this->move(tetro, route::toRight);
				if(this->move(tetro, Tetromino::route::toDown))
					this->fit(tetro);

			}


			
		}
		this->fit(tetro);
		
		if(tetro.letterCoordinatesOnBoard[3][0] <= this->creationAreaHeight - 1)
		{
			cout << endl << "Map filled, process terminated." << endl;
			return false;
		}

		return true;
	}
	
	
	//constructor for define the map.
	Tetris::Tetris(unsigned int areaRow, unsigned int areaCol) : row{areaRow}, col{areaCol} 
	{
		row += creationAreaHeight;

		gameArea = new char*[row];
		for(int i=0; i<row; i++)
		{
			gameArea[i] = new char[col];
			for(int j = 0; j<col; j++)
				gameArea[i][j] = ' ';
		}
	}

	Tetris::~Tetris()
	{
		for(int i=0; i<row; i++)
			delete[] gameArea[i];
		delete[] gameArea;
	}
}
	