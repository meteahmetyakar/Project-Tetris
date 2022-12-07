#include "utils.h"
using namespace std;

	
int main()
{
	string input;
	bool isValid;
	
	cout << "How many tetrominos?" << endl;
	do
	{
		isValid = true;
		cin >> input; //input taking by string and then checking it, if there is any character without digit it take a new input
		for (auto el : input)
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

	int tetroCount = stoi(input); //given input turn to int
	
	//making a gameboard with given tetroCount, it takes the required length as 4 per tetro and sets the row and column multiplied by 4. 
	//if want enter another required lenght per tetro, it can setting as GameBoard board(tetroCount,tetroCount,lenght);
	GameBoard board(1,tetroCount);
	vector<Tetromino> tetroPieces;
	
	//						 A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
	const int letters[26] = {0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,1}; //here I used a hashtable for check valid letter input
	char type;
	
	cout << "What are the types?" << endl;
	for(int i=0; i<tetroCount; i++)
	{
		do
		{
			isValid = true;
			cin >> input;
			type = input[0];
			if(input.size() != 1 || type < 65 || type > 90 || letters[type-'A'] == 0)
			{
				cout << "Please enter a valid input" << endl;
				isValid = false;
			}
			else
				tetroPieces.push_back((shapes)type);

		}while(isValid == false);
	}
	
	for(auto tetro : tetroPieces)
	    tetro.canFit(board);
	
	cout << "Horizontally best-fit tetrominos" << endl;
	board.printArea();

	return 0;
}











