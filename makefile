lab3: main.o hashTable.o
	g++ main.o hashTable.o -o lab3

main.o: main.cpp hashTable.h
	g++ -c main.cpp

hashTable.o: hashTable.cpp hashTable.h
	g++ -c hashTable.cpp

clean:
	rm -f lab3 *.o
