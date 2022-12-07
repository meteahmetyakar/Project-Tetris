#include <iostream>
#include <vector>

#ifndef UTILS_H
#define UTILS_H

using namespace	std;

enum class shapes{ I = 'I', O = 'O', T = 'T', J = 'J', L = 'L', S = 'S', Z = 'Z'};
enum class route {rSide, lSide};

class GameBoard {
private:
	unsigned int row;
	unsigned int col;
	unsigned int _lenght;
	
public:
	vector<vector<char>> gameArea;
	
	/* GETTERS */
	unsigned int getRowSize();
	unsigned int getColSize();
	
	/* END OF GETTERS*/
	
	
	// it clear given indexes in gameArea, it using when collision while drawing letter to map
	void clearIndexes(vector<vector<int>> indexes);
	
	// a function which print game area 
	void printArea() const;
	
	//constructor for define the map.
	GameBoard(unsigned int areaRow=1, unsigned int areaCol=1, unsigned int lenght=4);
	
};

#endif

class Tetromino {
private:
	char letter;
	unsigned int returnOriginCounter; // counter to check if the letter has returned to its origin state
	unsigned int rowSize, colSize;
	const unsigned int letterCount = 4; //a area of letter shape in matrix without spaces. All tetrominos using 4 block for drawing. That's why it define constant variable and initiliaze with 4
	const unsigned int _colSize = 4, _rowSize = 4;
	vector<vector<char>> tetro;
	vector<vector<int>> letterCoordinates;
	
	
public:
	/* GETTERS */
	unsigned int getReturnOriginCounter();
	char getLetter();
	vector<vector<char>> getShape();
	int getLetterCount();
	vector<vector<int>> getLetterCoordinates();
	
	
	/* END OF GETTERS*/
	
	//the shape of the tetrominos is determined according to the letter entered.
	void setShape(shapes type);
	
	//a function that print tetro
	void printTetro() const;
	
	//it determining letter coordinates in tetro matrix
	void setLetterCoordinates();
	
	//it rotate the tetro matrix so rotate the shape of letter
	void rotate(route direction);
	
	//try to fit the tetro to the gameboard
	bool canFit(GameBoard &board);
	
	//constructor
	Tetromino(shapes type);
	Tetromino();
	//destructor
};
