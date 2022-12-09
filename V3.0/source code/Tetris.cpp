#include <iostream>
#include <vector>
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
	void Tetris::clearIndexes(vector<vector<int>> indexes)
	{
		for(auto element : indexes)
			gameArea[element[0]][element[1]] = ' ' ;
	}
	
	// a function which add a tetromino to gameBoard
	void Tetris::add(Tetromino::Tetromino &tetro)
	{
		vector<vector<int>> tetroLetterIndexes = tetro.getLetterCoordinates(); //takes coordinates of letters from matrix of tetro
		
		//indexes of places to start drawing
		int startXIndex = 	this->gameArea[0].size()/2;
		int startYIndex = getCreationAreaHeight()-1;
		
		//reference points
		int referenceY = tetroLetterIndexes[0][0];
		int referenceX = tetroLetterIndexes[0][1];
		
		//drawing tetro to board by tetroLetterIndexes
		for(auto el : tetroLetterIndexes)
		{
			this->gameArea[startYIndex+(el[0]-referenceY)][startXIndex+(el[1]-referenceX)] = tetro.getLetter();
			tetro.letterCoordinatesOnBoard.push_back({startYIndex+(el[0]-referenceY),startXIndex+(el[1]-referenceX)});
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
		
		vector<vector<int>> coordinates = tetro.letterCoordinatesOnBoard;
		
		vector<vector<char>> tempBoard;
		tempBoard = this->gameArea;

		this->clearIndexes(coordinates);
		
		for(auto element : coordinates)
		{
			int yOfelement = element[0], xOfelement = element[1];
			//checking collision
			if(xOfelement+xStep < 0 || xOfelement+xStep >= this->getColSize() || yOfelement+yStep < 0 || yOfelement+yStep >= this->getRowSize() || this->gameArea[yOfelement+yStep][xOfelement+xStep] != ' ')
			{
				this->gameArea = tempBoard;
				return false;
			}
			
		}
		
		tetro.letterCoordinatesOnBoard.clear();
		for(auto element : coordinates)
		{
			int yOfelement = element[0], xOfelement = element[1];
			
			this->gameArea[yOfelement+yStep][xOfelement+xStep] = tetro.getLetter();
			tetro.letterCoordinatesOnBoard.push_back({yOfelement+yStep,xOfelement+xStep});
						
		}

		this->draw();

		
		return true;
		
	}
	
	bool Tetris::fit(Tetromino::Tetromino &tetro)
	{
		//here tetro trying to itself in its position
		if(!tetro.isRotated)
		{
			Tetromino::Tetromino temp = tetro;
			temp.setShape((Tetromino::shapes)tetro.getLetter());
			this->clearIndexes(tetro.letterCoordinatesOnBoard);
			this->add(temp);
			this->draw();
			for(int i=0; i<tetro.getTetroPosition(); i++)
			{
				temp.rotate(Tetromino::route::toLeft);
				this->clearIndexes(temp.letterCoordinatesOnBoard);
				this->add(temp);
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
			for(auto el : gameArea[i])
				cout << el;

			cout << "|"<<endl;
		}
		
		for(int j=0; j<this->col; j++)
			cout << "-";
		cout << "-- <-- when a block come here then game over" << endl;

		for(int i=startloc; i<rowSize; i++)
		{
			cout << "|";
			for(auto el : gameArea[i])
				cout << el;

			cout << "|"<<endl;
		}
	}

	bool Tetris::animate(Tetromino::Tetromino &tetro)
	{
		{
			this->add(tetro);
			this->clearIndexes(tetro.letterCoordinatesOnBoard);
			Tetromino::Tetromino temp = tetro;
			temp.setShape((Tetromino::shapes)tetro.getLetter());
			this->add(temp);
		}

		this->fit(tetro);
		
		int oldXLoc = -1, oldYLoc = -1;
		while(!tetro.isYFitted() && !(tetro.letterCoordinatesOnBoard[0][1] == oldXLoc && tetro.letterCoordinatesOnBoard[0][0] == oldYLoc))
		{
			oldXLoc = tetro.letterCoordinatesOnBoard[0][1];
			oldYLoc = tetro.letterCoordinatesOnBoard[0][0];
			while(this->move(tetro, Tetromino::route::toDown));

			if(!tetro.isYFitted())
			{

				this->move(tetro, Tetromino::route::toRight);
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
		gameArea.resize(row, vector<char>(col,' '));
	}
}