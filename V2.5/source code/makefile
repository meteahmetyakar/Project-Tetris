all: clear clean compile run

clear:
	@clear
	
clean:
	@rm -f *.o
	@rm -f driver1

compile: driver1.cpp Tetromino.cpp AbstractTetris.cpp TetrisAdapter.cpp TetrisVector.cpp Tetris1D.cpp
	@g++ -std=c++11 driver1.cpp Tetromino.cpp AbstractTetris.cpp TetrisAdapter.cpp TetrisVector.cpp Tetris1D.cpp -o driver1

run:
	./driver1	
