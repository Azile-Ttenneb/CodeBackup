OBJ=main.o inifileoperator.o
target:inifile
inifile:$(OBJ)
	g++ main.o inifileoperator.o -oinifile
main.o:
	g++ -g -c main.cpp
inifileoperator.o:
	g++ -g -c inifileoperator.cpp
clean:
	rm $(OBJ)
