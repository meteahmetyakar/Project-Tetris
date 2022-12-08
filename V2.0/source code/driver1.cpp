#include "Tetris.h"
#include "Tetromino.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

	
int main()
{
	cout << "checking isValidInput function, its parameter is X and it will return false | " << Tetromino::isValidInput('X') << endl;
	cout << "checking isValidInput function, its parameter is Q and it will return true | " << Tetromino::isValidInput('Q') << endl;
	char *strNum = new char[4];
	strNum[0] = '0';
	strNum[1] = '1';
	strNum[2] = '2';
	strNum[3] = '3';

	int num = Tetromino::to_integer(strNum,4);
	cout << "checking to_integer function, parameter is 0123, it will return 123 as integer type | values is " << num << " | type is " << typeid(num).name() << endl; 
	
	Tetromino::Tetromino tetro(Tetromino::shapes('O'));
	Tetromino::Tetromino tetro2(Tetromino::shapes('Z'));
	cout << "getReturnOriginCounter of shape O is " << tetro.getReturnOriginCounter() << endl;
	cout << "getReturnOriginCounter of shape Z is " << tetro2.getReturnOriginCounter() << endl;
	cout <<endl<<endl;
	cout << "letter of variable tetro  is " << tetro.getLetter() << endl;
	cout << "letter of variable tetro2 is " << tetro2.getLetter() << endl;
	cout << endl<<endl;
	cout << "letterCount is same every letters and it is " << tetro.getLetterCount();
	cout << endl;
	cout << endl;

	cout << "SHAPE OF VARIABLE TETRO" << endl;
	char** shape = tetro.getShape();
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
			cout << shape[i][j];
		cout << endl;
	}

	cout << endl;
	cout << "SHAPE OF VARIABLE TETRO2" << endl;
	shape = tetro2.getShape();
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
			cout << shape[i][j];
		cout << endl;
	}

	cout << endl;
	cout << endl;
	cout << "LETTER COORDINATES OF VARIABLE TETRO IN TETRO MATRIX" << endl;
	int** coordinates = tetro.getLetterCoordinates();
	for(int i=0; i<4; i++)
		cout << "{" << coordinates[i][0]<<","<<coordinates[i][1]<<"}"<<endl;

	cout << endl;
	cout << endl;
	cout << "LETTER COORDINATES OF VARIABLE TETRO2 IN TETRO MATRIX" << endl;
	coordinates = tetro2.getLetterCoordinates();
	for(int i=0; i<4; i++)
		cout << "{" << coordinates[i][0]<<","<<coordinates[i][1]<<"}"<<endl;


	cout << endl << endl;
	cout << "position of variable tetro is " << tetro.getTetroPosition() << endl << endl;
	tetro2.rotate(Tetromino::route::toRight);
	cout << "variable tetro2 is rotated to right" << endl;
	tetro2.printTetro();
	cout << "new position of variable tetro is " << tetro2.getTetroPosition() << endl;
	
	cout << endl << endl;

	int row = 10; //will added creationAreaHeight (4) so row will be 14
	int col = 10;

	Tetris::Tetris board(row,col);
	cout << endl << "*** EMPTY BOARD *** " << endl;
	board.printArea();
	cout << endl << endl;
	char key;
	cout << "board row size --> " << board.getRowSize() << endl << "board col size --> " << board.getColSize() << endl << "board creation area is " << board.getCreationAreaHeight() << endl;

	cout << "added variable tetro to top of board";
	board += tetro;
	cout << endl << endl << endl;
	cout << "*** ENTER A KEY FOR DRAW FUNCTION***" << endl;
	cin >> key;
	board.draw();
	cout << "*** ENTER A KEY FOR CLEARINDEXES FUNCTION IT WILL DELETE TETRO FROM BOARD***" << endl;
	cin >> key;
	board.clearIndexes(tetro.letterCoordinatesOnBoard, tetro.getLetterCount());
	board.draw();
	
	cout << "*** ENTER A KEY FOR ANIMATE FUNCTION***" << endl;
	cin >> key;
	board.animate(tetro);
	board.animate(tetro2);

	cout << "*** ENTER A KEY FOR CONTINUE TO DRIVER2 ***" << endl;
	cin >> key;
	std::system("clear");








	
	return 0;
}
