#include <iostream>
#include "TetrisAdapter.hpp"
#include "TetrisAdapter.cpp"
#include "TetrisVector.hpp"
#include "Tetris1D.hpp"
#include "Tetromino.hpp"
#include "AbstractTetris.cpp"
#include <deque>

int main()
{
    AbstractTetris::AbstractTetris *board;

    bool isValid;
    char type;
    string inputs;
    do
    {
        cout << "Choose your board type" << endl;
        cout << "1-) Vector" << endl;
        cout << "2-) 1D Array" << endl;
        cout << "3-) Adapter" << endl;
        isValid = true;
        cin >> inputs;
        type = inputs[0];

        Tetromino::Tetromino tetro;
        if(inputs.size() != 1 || (type < 49 || type > 51))
        {
            cout << "Please enter a valid input" << endl;
            isValid = false;
        }
        else
        {

            int row, col;
            cout << "Enter row size?" << endl;
            do
            {
                isValid = true;
                cin >> inputs; //input taking by string and then checking it, if there is any character without digit it take a new input
                for (auto el : inputs)
                {
                    if (isdigit(el) == false)
                    {
                        isValid = false;
                        break;
                    }
                }
                
                if(!isValid)
                    cout << "Please enter a valid input" << endl;
                    
            }while(!isValid);
            
            row = stoi(inputs); //given input turn to int

            cout << "Enter col size?" << endl;
            do
            {
                isValid = true;
                cin >> inputs; //input taking by string and then checking it, if there is any character without digit it take a new input
                for (auto el : inputs)
                {
                    if (isdigit(el) == false)
                    {
                        isValid = false;
                        break;
                    }
                }
                
                if(!isValid)
                    cout << "Please enter a valid input" << endl;
                    
            }while(!isValid);

            col = stoi(inputs); //given input turn to int

            if(type == '1')
                board = new TetrisVector::TetrisVector(row,col);
            else if(type == '2')
                board = new Tetris1D::Tetris1D(row,col);
            else if(type == '3')
            {
                do
                {
                    cout << "Choose your T type" << endl;
                    cout << "1-) vector<vector<char>>" << endl;
                    cout << "2-) vector<deque<char>>" << endl;
                    cout << "3-) deque<vector<char>>" << endl;
                    cout << "4-) deque<deque<char>>" << endl;
                    isValid = true;
                    inputs.clear();
                    cin >> inputs;
                    type = inputs[0];

                    if(inputs.size() != 1 || (type < 49 || type > 52))
                    {
                        cout << "Please enter a valid input" << endl;
                        isValid = false;
                    }
                    else
                    {
                        if(type == '1')
                            board = new TetrisAdapter::TetrisAdapter<vector<vector<char>>>(row,col);
                        else if(type == '2')
                            board = new TetrisAdapter::TetrisAdapter<vector<deque<char>>>(row,col);
                        else if(type == '3')
                            board = new TetrisAdapter::TetrisAdapter<deque<vector<char>>>(row,col);
                        else if(type == '4')
                            board = new TetrisAdapter::TetrisAdapter<deque<deque<char>>>(row,col);
                    }

                }while(isValid == false);
            }
        }
    }while(isValid == false);

    string tmp;
    cout << endl << endl;
    cout << "-- void draw() function will work and it draw an empty board -- " << endl;
    board->draw();
    cout << "press any key ";
    cin >> tmp;

    std::system("clear");

    cout << "-- void readFromFile() function will work if you want an it fill the board (press Y for fill or press another key)-- "<<endl;
    cin >> tmp;
    if(tmp == "Y")
    {
        try
        {
            board->readFromFile();
            board->draw();
        }
        catch(int &ex)
        {
            cout << " no txt file to open " << endl;
        }
    }
    
    cout << "press any key ";
    cin >> tmp;
	bool isOver = true;
    bool isQuit = false;
    while(!isQuit)
    {
        do
        {
            cout << "Which would you like to add? (I, O, T, J, L, S, Z, Q = Quit)" << endl;
            isValid = true;
            cin >> inputs;
            type = inputs[0];
            if(inputs.size() != 1 || !Tetromino::isValidInput(type))
            {
                cout << "Please enter a valid input" << endl;
                isValid = false;
            }
            else if(type == 'Q')
            {
                isQuit = true;
                break;
            }
            else
            {
                Tetromino::Tetromino tetro((Tetromino::shapes)type);
                *board += tetro;
                try
                {
                    board->animate(tetro);
                    board->lastMove(); //if there is a problem on lastMove, program will throw exception
                }
                catch(int &ex)
                {
                    cout << "There is no move on last movement program will terminate" << endl;
                    isOver = false;
                }
            }


        }while(isValid == false);
        
        if(!isOver) break;
    }

    cout << "press any key ";
    cin >> tmp;

    board->writeToFile();
    cout << "game saved " << endl;
    cout << "press any key ";
    cin >> tmp;

    std::system("clear");
    cout << "an empty board is created to use functions which use functions" << endl;
    cout << "board row = 10" << endl;
    cout << "board col = 10" << endl;
    cout << "Tetromino type = J" << endl;

    TetrisVector::TetrisVector board2(10,10);
    Tetromino::Tetromino tetro3((Tetromino::shapes)'J');

    cout << endl << endl;
    cout << "Tetromino J will add to middle of top" << endl;
    cout << "press any key " ;
    cin >> tmp;
    board2 += tetro3;
    board2.draw();

    cout << endl << endl;
    cout << "Tetromino J will move to down 5 times" << endl;
    cout << "press any key " ;
    cin >> tmp;
    for(int i=0; i<5; i++)
    {
        board2.move(tetro3, Tetromino::route::toDown);
        board2.draw();

    }

    cout << endl << endl;
    cout << "Tetromino J will fit in row (target col = 3)" << endl;
    cout << "press any key " ;
    cin >> tmp;
    tetro3.setTargetCoordinates(3,0);
    tetro3.isRotated = true;
    board2.fitRow(tetro3);
    //board2 += tetro3;

    cout << endl << endl;
    cout << "Tetromino J will delete from board" << endl;
    cout << "press any key " ;
    cin >> tmp;
    board2.clearIndexes(tetro3.letterCoordinatesOnBoard);
    board2.draw();
    cout << "press any key " ;
    cin >> tmp;
    std::system("clear");
    
    cout << endl << endl;
    cout << "Tetromino J will rotate to left " << endl;
    cout << "press any key " ;
    cin >> tmp;
    tetro3.rotate(Tetromino::route::toLeft);
    tetro3.printTetro();

    cout << endl << endl;
    cout << "Tetromino J will rotate to left " << endl;
    cout << "press any key " ;
    cin >> tmp;
    tetro3.rotate(Tetromino::route::toLeft);
    tetro3.printTetro();

    cout << endl << endl;
    cout << "Tetromino J will rotate to right " << endl;
    cout << "press any key " ;
    cin >> tmp;
    tetro3.rotate(Tetromino::route::toRight);
    tetro3.printTetro();

    cout << "the number of moves you make while trying your chosen board --> " << board->numberOfMoves() << endl;
    cout << "number of moves on second board --> " << board2.numberOfMoves() << endl;




}