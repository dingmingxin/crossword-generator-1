xws: xws_main.o xws.o Grid.o Dict.o
	g++ -o xws Grid.o Dict.o xws_main.o xws.o
	
xws_main.o: xws_main.cpp Grid.h Dict.h xws.h
	g++ -c xws_main.cpp
	
xws.o: xws.cpp xws.h Dict.h Grid.h
	g++ -c xws.cpp

Grid.o: Grid.cpp Grid.h
	g++ -c Grid.cpp

Dict.o: Dict.cpp Dict.h
	g++ -c Dict.cpp