#include <iostream>
#include <fstream>
#include <deque>
#include "TetrisAdapter.hpp"

namespace TetrisAdapter
{
	template<class T>
    void TetrisAdapter<T>::draw()
    {
        std::system("clear");
		this->printArea();
		std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }

	// a function which print game area 
	template<class T>
	void TetrisAdapter<T>::printArea() const
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


	template<class T> unsigned int TetrisAdapter<T>::getRowSize(){return row;}
	template<class T> unsigned int TetrisAdapter<T>::getColSize(){return col;}
    template<class T> int TetrisAdapter<T>::getCreationAreaHeight(){return creationAreaHeight;}

	template<class T>
    void TetrisAdapter<T>::readFromFile()
	{
		ifstream myfile("TetrisAdapter.txt");
		string line;
		T board;
		if(myfile.is_open())
		{
			getline(myfile, line);
			this->row = stoi(line);
			getline(myfile, line);
			this->col = stoi(line);

			board.resize(row);
			for(int i=0; i<row; i++)
			{
				board[i].resize(col);
				for(int j=0; j<col; j++)
					board[i][j] = ' ';
			}
			
			for(int i=0; i<row; i++)
			{
				for(int j=0; j<col; j++)
					myfile.get(board[i][j]);

				myfile.get();
			}	
			gameArea = board;
		}
		else throw 0;
	}


	template<class T>
    void TetrisAdapter<T>::writeToFile()
	{
		std::ofstream myfile("TetrisAdapter.txt");
		if(myfile.is_open())
		{
			myfile << row << "\n";
			myfile << col << "\n";
			for(int i=0; i<row; i++)
			{
				for(int j=0; j<col; j++)
				{
					myfile << gameArea[i][j];
				}
				myfile << "\n";
			}
		}
		else cout << "Unable to open file";
		myfile.close();
	}

	template<class T>
    bool TetrisAdapter<T>::animate(Tetromino::Tetromino &tetro)
    {
        {
			Tetromino::Tetromino temp((Tetromino::shapes)tetro.getLetter());
			*this += temp;
			draw();
			this->clearIndexes(temp.letterCoordinatesOnBoard);
		}


		char input[10];
		char inputs[2];
		int idx = 0;
		int targetRow, targetCol;
		bool isValid;
		int len;

		cout << "enter row" << endl;
        cin >> targetRow;
        targetRow += 4;

        cout << "enter col" << endl;
        cin >> targetCol;


		char direction;
		char directionInput[2];
		do
		{
			isValid = true;
			idx = 0;
			cout << "Enter direction (R(Right), L(Left))" << endl;
			cin >> directionInput;
			direction = directionInput[0];

			while(directionInput[idx] != '\0') idx++;

			if(idx != 1 || !(direction == 'R' || direction == 'L'))
			{
				cout << "Please enter a valid input" << endl;
				isValid = false;
			}

		}while(isValid == false);

		tetro.direction = (Tetromino::route)direction;
		
		int rotateCount;
		cout << "Enter rotate count" << endl;
		cin >> rotateCount;
		rotateCount %= tetro.getReturnOriginCounter()+1;
		for(int i=0; i<rotateCount; i++)
			tetro.rotate(tetro.direction);

		tetro.setTargetCoordinates(targetCol, targetRow);


		{
            *this += tetro;
			this->clearIndexes(tetro.letterCoordinatesOnBoard);
			Tetromino::Tetromino temp((Tetromino::shapes)tetro.getLetter());
			*this += temp;
		}
        //this->draw();

		this->fitRow(tetro);
		
		int oldXLoc = -1, oldYLoc = -1;
		while(!tetro.isYFitted() && !(tetro.letterCoordinatesOnBoard[0][1] == oldXLoc && tetro.letterCoordinatesOnBoard[0][0] == oldYLoc))
		{
			cout << "." << endl;
			oldXLoc = tetro.letterCoordinatesOnBoard[0][1];
			oldYLoc = tetro.letterCoordinatesOnBoard[0][0];
			while(this->move(tetro, Tetromino::route::toDown));

			if(!tetro.isYFitted())
			{

				//this->move(tetro, route::toRight);
				if(this->move(tetro, Tetromino::route::toDown))
					this->fitRow(tetro);

			}
			
		}
		this->fitRow(tetro);
		
		if(tetro.letterCoordinatesOnBoard[3][0] <= this->creationAreaHeight - 1)
		{
			TetrisAdapter<T>::AbstractTetris::lastMovement = make_pair(-1,-1);
			throw -1;
		}

		return true;
	}

	template<class T>
    bool TetrisAdapter<T>::move(Tetromino::Tetromino &tetro, Tetromino::route direction)
    { 
        int xStep = 0, yStep = 0;
        TetrisAdapter<T>::AbstractTetris::lastMovement = std::make_pair(-1, -1);

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
		
		T tempBoard;
		tempBoard = this->gameArea;

		this->clearIndexes(coordinates);
		
		for(auto element : coordinates)
		{
			int yOfelement = element[0], xOfelement = element[1];
			//checking collision
			if(xOfelement+xStep < 0 || xOfelement+xStep >= this->getColSize() || yOfelement+yStep < 0 || yOfelement+yStep >= this->getRowSize() || this->gameArea[yOfelement+yStep][xOfelement+xStep] != ' ')
			{
				this->gameArea = tempBoard;
                TetrisAdapter<T>::AbstractTetris::lastMovement = std::make_pair(tetro.letterCoordinatesOnBoard[0][0], tetro.letterCoordinatesOnBoard[0][1]);
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

		TetrisAdapter::AbstractTetris::moves++;
        TetrisAdapter<T>::AbstractTetris::lastMovement = std::make_pair(tetro.letterCoordinatesOnBoard[0][0], tetro.letterCoordinatesOnBoard[0][1]);
		return true;
        
    }

    template<class T> bool TetrisAdapter<T>::fitRow(Tetromino::Tetromino &tetro)
    {
        //here tetro trying to itself in its position
		if(!tetro.isRotated)
		{
			Tetromino::Tetromino temp = tetro;
            temp.setShape((Tetromino::shapes)tetro.getLetter());
			this->clearIndexes(tetro.letterCoordinatesOnBoard);
			*this += temp;
            int a;
			this->draw();
			for(int i=0; i<tetro.getTetroPosition(); i++)
			{
				this->clearIndexes(temp.letterCoordinatesOnBoard);
				temp.rotate(tetro.direction);
				*this += temp;
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

	template<class T>
    TetrisAdapter<T>& TetrisAdapter<T>::operator+=(Tetromino::Tetromino& tetro)
    {
        vector<vector<int>> tetroLetterIndexes = tetro.getLetterCoordinates(); //takes coordinates of letters from matrix of tetro
		
		//indexes of places to start drawing
		int startXIndex = this->col/2;
		int startYIndex = getCreationAreaHeight()-1;
		//reference points
		int referenceY = tetroLetterIndexes[0][0];
		int referenceX = tetroLetterIndexes[0][1];
		//drawing tetro to board by tetroLetterIndexes

		for(int i = 0; i<tetro.getLetterCount(); i++)
		{
			gameArea[startYIndex+(tetroLetterIndexes[i][0]-referenceY)][startXIndex+(tetroLetterIndexes[i][1]-referenceX)] = tetro.getLetter();
            
		
			tetro.letterCoordinatesOnBoard[i][0] = startYIndex+(tetroLetterIndexes[i][0]-referenceY);
			tetro.letterCoordinatesOnBoard[i][1] = startXIndex+(tetroLetterIndexes[i][1]-referenceX);

		}
        return *this;
    }

    
	template<class T>
    void TetrisAdapter<T>::clearIndexes(vector<vector<int>> indexes)
	{
		for(auto element : indexes)
			gameArea[element[0]][element[1]] = ' ' ;
	}


    //constructor for define the map.
	template<class T>
	TetrisAdapter<T>::TetrisAdapter(unsigned int areaRow, unsigned int areaCol) : row{areaRow}, col{areaCol} 
	{
		row += creationAreaHeight;

		gameArea.resize(row);
		for(int i=0; i<row; i++)
		{
			gameArea[i].resize(col);
			for(int j=0; j<col; j++)
				gameArea[i][j] = ' ';
		}
	}

	template<class T>
	TetrisAdapter<T>::~TetrisAdapter()
	{


	}

}