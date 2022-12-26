#ifndef TETRIS1D_HPP
#define TETRIS1D_HPP

#include <iostream>
#include "AbstractTetris.cpp"

namespace Tetris1D
{
    class Tetris1D : public AbstractTetris::AbstractTetris
    {
        private:
        unsigned int row;
        unsigned int col;
        const unsigned int creationAreaHeight = 4;

        public:
        char *gameArea;
        std::pair<int,int> lMove;

        unsigned int getRowSize();
		unsigned int getColSize();
        int getCreationAreaHeight();

        virtual void draw();
        virtual void readFromFile();
        virtual void writeToFile();
        virtual bool animate(Tetromino::Tetromino &tetro);
        virtual bool move(Tetromino::Tetromino &tetro, Tetromino::route direction);
        virtual Tetris1D& operator+=(Tetromino::Tetromino& tetro);
        virtual std::pair<int,int> lastMove();


        void printArea() const;
        bool fitRow(Tetromino::Tetromino &tetro);
        void clearIndexes(vector<vector<int>> indexes);

        Tetris1D(unsigned int areaRow=4, unsigned int areaCol=4);
		~Tetris1D();
    };
}


#endif