#include "Tetris.h"
#include "Tetromino.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

	
int main()
{
	char input[10];
	bool isValid;
	int rowSize, colSize;
	int len;
	cout << "Enter row size?" << endl;
	do
	{
		isValid = true;
		len = 0;
		cin >> input; //input taking by string and then checking it, if there is any character without digit it take a new input
		for (int i=0;  input[i] != '\0'; i++)
		{
			len++;
			if (input[i] < 48 || input[i] > 57)
			{
				isValid = false;
				break;
			}
		}
		
		if(!isValid)
			cout << "Please enter a valid input" << endl;
			
	}while(!isValid);
	
	rowSize = Tetromino::to_integer(input, len); //given input turn to int

	cout << "Enter col size?" << endl;
	do
	{
		isValid = true;
		len = 0;
		cin >> input; //input taking by string and then checking it, if there is any character without digit it take a new input
		for (int i=0;  input[i] != '\0'; i++)
		{
			len++;
			if (input[i] < 48 || input[i] > 57)
			{
				isValid = false;
				break;
			}
		}
		
		if(!isValid)
			cout << "Please enter a valid input" << endl;
			
	}while(!isValid);

	colSize = Tetromino::to_integer(input, len); //given input turn to int
	
	//making a gameboard with given ROW and Column
	Tetris::Tetris board(rowSize,colSize);



	char type;
	
	srand(time(0));

	bool isQuit = false;
	bool isOver = false;
	while(!isQuit)
	{
		do
		{
			char inputs[2];
			int idx = 0;
			int targetRow, targetCol;
			cout << "Which would you like to add? (I, O, T, J, L, S, Z, R(Random), Q(Quit))" << endl;
			isValid = true;
			cin >> inputs;
			type = inputs[0];

			while(inputs[idx] != '\0') idx++;

			Tetromino::Tetromino tetro;
			if(idx != 1 || !Tetromino::isValidInput(type))
			{
				cout << "Please enter a valid input" << endl;
				isValid = false;
			}
			else if(type == 'Q')
				isQuit = true;
			else
			{
				if(type == 'R')
				{
					int element = rand() % 7;
					switch(element)
					{
						case 0:
							tetro.setShape((Tetromino::shapes)'I');
							break;
						case 1:
							tetro.setShape((Tetromino::shapes)'O');
							break;
						case 2:
							tetro.setShape((Tetromino::shapes)'T');
							break;
						case 3:
							tetro.setShape((Tetromino::shapes)'J');
							break;
						case 4:
							tetro.setShape((Tetromino::shapes)'L');
							break;
						case 5:
							tetro.setShape((Tetromino::shapes)'S');
							break;
						case 6:
							tetro.setShape((Tetromino::shapes)'Z');
							break;
					}
				}
				else
					tetro.setShape((Tetromino::shapes)type);


				isOver = board.animate(tetro);
			}

		}while(isValid == false);

		if(!isOver)
			break;
	}
	
	return 0;
}
