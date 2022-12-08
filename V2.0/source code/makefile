all: clear clean compile run

clear:
	@clear
	
clean:
	@rm -f *.o
	@rm -f driver1
	@rm -f driver2

compile: driver2.cpp Tetromino.cpp Tetris.cpp
	@g++ -std=c++11 driver1.cpp Tetromino.cpp Tetris.cpp -o driver1
	@g++ -std=c++11 driver2.cpp Tetromino.cpp Tetris.cpp -o driver2	

run:
	./driver1
	./driver2	



