#include <iostream>
#include <chrono>
#include <thread>

#ifndef TETROMINO_H
#define TETROMINO_H

using namespace	std;

namespace Tetromino
{
	bool isValidInput(char c);
    int to_integer(char *input, int len);

	enum class shapes{ I = 'I', O = 'O', T = 'T', J = 'J', L = 'L', S = 'S', Z = 'Z'};
	enum class route {toRight = 'R', toLeft = 'L', toDown = 'D', toUp = 'U'};

	class Tetromino {
	private:
		char letter;
		int targetY;
		int targetX;
		unsigned int returnOriginCounter; // counter to check if the letter has returned to its origin state
		unsigned int tetroPosition = 0;
		unsigned int rowSize, colSize;
		const unsigned int letterCount = 4; //a area of letter shape in matrix without spaces. All tetrominos using 4 block for drawing. That's why it define constant variable and initiliaze with 4
		const unsigned int _colSize = 4, _rowSize = 4;
		char **tetro;
		int **letterCoordinates;

		
	public:
		route direction;
		int **letterCoordinatesOnBoard;
		bool isRotated = false;
		route targetRoute;
		route oppositeOfTargetRoute;
		int letterCoordinatesSize = 0;

		/* GETTERS */
		unsigned int getReturnOriginCounter();
		char getLetter();
		char **getShape();
		int getLetterCount();
		int **getLetterCoordinates();
		int getTetroPosition();
		int getTargetY();
		int getTargetX();
		
		/* END OF GETTERS*/
		
		bool isXFitted();
		bool isYFitted();
		//void setFitCoordinates(Tetris &board);
		void setTargetCoordinates(int _targetX, int _targetY) 
		{	
			targetY = _targetY;
			targetX = _targetX; 
		}

		//the shape of the tetrominos is determined according to the letter entered.
		void setShape(shapes type);
		
		//a function that print tetro
		void printTetro() const;
		
		//it determining letter coordinates in tetro matrix
		void setLetterCoordinates();
		
		//it rotate the tetro matrix so rotate the shape of letter
		void rotate(route direction);
		

		
		//constructor
		Tetromino(shapes type);
		Tetromino();
		~Tetromino();
	};

}


#endif

