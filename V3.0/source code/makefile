all: clear clean compile run

clear:
	@clear
	
clean:
	@rm -f *.o
	@rm -f main

compile: main.cpp Tetromino.cpp Tetris.cpp
	@g++ -std=c++11 main.cpp Tetromino.cpp Tetris.cpp -o main

run:
	./main	



