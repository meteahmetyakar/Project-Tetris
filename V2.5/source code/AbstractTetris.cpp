#ifndef ABSTRACTTETRIS_HPP
#define ABSTRACTTETRIS_HPP

#include <iostream>
#include "Tetromino.hpp"

namespace AbstractTetris
{
    class AbstractTetris
    {
        private:
        unsigned int row;
        unsigned int col;
        const unsigned int creationAreaHeight = 4;

        public:
        pair<int,int> lastMovement;


        unsigned int getRowSize() {return row;}
		unsigned int getColSize() {return col;}
        int getCreationAreaHeight() {return creationAreaHeight;}

        virtual void clearIndexes(vector<vector<int>> indexes){} //it clear board with given indexes
        virtual bool fitRow(Tetromino::Tetromino &tetro) {return false;} //it fit the tetromino on row
        virtual void draw() {} //draw board
        virtual void readFromFile() {} //save game
        virtual void writeToFile() {}        //load game
        virtual bool animate(Tetromino::Tetromino &tetro) {return false;} //animation tetromino on board
        virtual bool move(Tetromino::Tetromino &tetro, Tetromino::route direction) {return false;} //move tetro on board
        virtual AbstractTetris& operator+=(Tetromino::Tetromino& tetro) {return *this;} //append a tetro to board
        virtual std::pair<int,int> lastMove() 
        {
            if(lastMovement.first == -1 || lastMovement.second == -1)
                throw -1;
            else return lastMovement;
        }
        int numberOfMoves() { return moves;}

        int moves = 0;

    };
}

#endif