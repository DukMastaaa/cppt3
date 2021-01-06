main: makeobj/main.o makeobj/model.o makeobj/view.o makeobj/colours.o
	g++ makeobj/main.o makeobj/colours.o makeobj/model.o makeobj/view.o -lncurses -o main

makeobj/main.o: main.cpp
	g++ -c main.cpp
	mv main.o makeobj

makeobj/colours.o: colours.cpp colours.h
	g++ -c colours.cpp
	mv colours.o makeobj

makeobj/model.o: model.cpp model.h
	g++ -c model.cpp
	mv model.o makeobj

makeobj/view.o: view.cpp view.h model.cpp model.h colours.cpp colours.h
	g++ -c view.cpp model.cpp colours.cpp
	mv view.o makeobj

clean:
	rm makeobj/*.o