#include <iostream>
#include <chrono>
#include <thread>
#include "Tetromino.h"

#ifndef TETRIS_H
#define TETRIS_H

using namespace	std;



//enum class route {toRight = 'R', toLeft = 'L', toUp = 'U', toDown = 'D'};

namespace Tetris
{
	class Tetris {
	private:
		unsigned int row;
		unsigned int col;
		const unsigned int creationAreaHeight = 4;
		
	public:
		char **gameArea;
		
		/* GETTERS */
		unsigned int getRowSize();
		unsigned int getColSize();
		int getCreationAreaHeight();
		
		/* END OF GETTERS*/
		
		
		//void add(Tetromino &tetro);
		void operator+=(Tetromino::Tetromino &tetro);
		
		bool fit(Tetromino::Tetromino &tetro); //This is fitting tetro in row, it is not canFit
		
		bool move(Tetromino::Tetromino &tetro, Tetromino::route direction);
		
		void draw();

		//animation of board
		bool animate(Tetromino::Tetromino &tetro);
		
		// it clear given indexes in gameArea, it using when collision while drawing letter to map
		void clearIndexes(int *indexes[2], int indexSize);
		
		// a function which print game area 
		void printArea() const;
		
		//constructor for define the map.
		Tetris(unsigned int areaRow=4, unsigned int areaCol=4);
		~Tetris();
		
	};

}

#endif

