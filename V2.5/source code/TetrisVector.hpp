#ifndef TETRISVECTOR_HPP
#define TETRISVECTOR_HPP

#include <iostream>
#include "AbstractTetris.cpp"

namespace TetrisVector
{
    class TetrisVector : public AbstractTetris::AbstractTetris
    {
        private:
        unsigned int row;
        unsigned int col;
        const unsigned int creationAreaHeight = 4;

        public:
        vector<vector<char>> gameArea;
        std::pair<int,int> lMove;

        unsigned int getRowSize();
		unsigned int getColSize();
        int getCreationAreaHeight();

        virtual void draw();
        virtual void readFromFile();
        virtual void writeToFile();
        virtual bool animate(Tetromino::Tetromino &tetro);
        virtual bool move(Tetromino::Tetromino &tetro, Tetromino::route direction);
        virtual TetrisVector& operator+=(Tetromino::Tetromino& tetro);
        virtual std::pair<int,int> lastMove();


        void printArea() const;
        bool fitRow(Tetromino::Tetromino &tetro);
        void clearIndexes(vector<vector<int>> indexes);

        TetrisVector(unsigned int areaRow=4, unsigned int areaCol=4);
		~TetrisVector();


    };
}


#endif