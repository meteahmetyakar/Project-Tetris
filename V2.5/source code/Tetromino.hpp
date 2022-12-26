#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#ifndef TETROMINO_HPP
#define TETROMINO_HPP

using namespace	std;

namespace Tetromino
{
	enum class shapes{ I = 'I', O = 'O', T = 'T', J = 'J', L = 'L', S = 'S', Z = 'Z'};
	enum class route {toRight = 'R', toLeft = 'L', toUp, toDown};
	bool isValidInput(char c);
	
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
		vector<vector<char>> tetro;
		vector<vector<int>> letterCoordinates;
		
	public:
		vector<vector<int>> letterCoordinatesOnBoard;
		bool isRotated = false;
		route targetRoute;
		route oppositeOfTargetRoute;
		route direction;


		/* GETTERS */
		unsigned int getReturnOriginCounter();
		char getLetter() const;
		vector<vector<char>> getShape();
		int getLetterCount();
		vector<vector<int>> getLetterCoordinates();
		int getTetroPosition();
		int getTargetY();
		int getTargetX();
		
		/* END OF GETTERS*/
		
		bool isXFitted();
		bool isYFitted();
		void setFitCoordinates(vector<vector<char>> &board);
		void setTargetCoordinates(int _targetX, int _targetY);
		
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
	};
}

#endif
