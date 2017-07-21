all: play

play: playGame.o initGame.o Board.o Player.o Card.o botPlayer.o draw.o
	g++ -g playGame.o initGame.o Board.o Player.o Card.o botPlayer.o draw.o -o play

botPlayer.o: botPlayer.cpp botPlayer.hpp playGame.hpp initGame.hpp Board.hpp Player.hpp Card.hpp
	g++ -c botPlayer.cpp

draw.o: draw.cpp draw.hpp playGame.hpp initGame.hpp Board.hpp Player.hpp Card.hpp
	g++ -c draw.cpp

playGame.o: playGame.cpp playGame.hpp initGame.hpp Board.hpp Player.hpp Card.hpp
	g++ -c playGame.cpp

initGame.o: initGame.cpp initGame.hpp Board.hpp Player.hpp Card.hpp
	g++ -c initGame.cpp

Board.o: Board.cpp Board.hpp Player.hpp Card.hpp
	g++ -c Board.cpp

Player.o: Player.cpp Player.hpp Card.hpp
	g++ -c Player.cpp

Card.o: Card.cpp Card.hpp
	g++ -c Card.cpp

clean:
	rm -f *.o
