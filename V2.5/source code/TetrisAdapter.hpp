#ifndef TETRISADAPTER_HPP
#define TETRISADAPTER_HPP

#include <iostream>
#include <deque>
#include "AbstractTetris.cpp"

namespace TetrisAdapter
{
    template <class T>
    class TetrisAdapter : public AbstractTetris::AbstractTetris
    {
        private:
        unsigned int row;
        unsigned int col;
        const unsigned int creationAreaHeight = 4;

        public:
        T gameArea;

        unsigned int getRowSize();
		unsigned int getColSize();
        int getCreationAreaHeight();

        virtual void draw();
        virtual void readFromFile();
        virtual void writeToFile();
        virtual bool animate(Tetromino::Tetromino &tetro);
        virtual bool move(Tetromino::Tetromino &tetro, Tetromino::route direction);
        virtual TetrisAdapter<T>& operator+=(Tetromino::Tetromino& tetro);
    


        void printArea() const;
        bool fitRow(Tetromino::Tetromino &tetro);
        void clearIndexes(vector<vector<int>> indexes);

        TetrisAdapter(unsigned int areaRow=4, unsigned int areaCol=4);
		~TetrisAdapter();


    };
        template class TetrisAdapter<vector<vector<char>>>;
        template class TetrisAdapter<deque<deque<char>>>;
        template class TetrisAdapter<deque<vector<char>>>;
        template class TetrisAdapter<vector<deque<char>>>;
}


#endif