P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -std=c++11 -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -std=c++11 -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -std=c++11 -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -std=c++11 -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -std=c++11 -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf TeamYP1
	mkdir TeamYP1
	cp Project1.cpp TeamYP1
	cp LexicalAnalyzer.h TeamYP1
	cp LexicalAnalyzer.cpp TeamYP1
	cp SyntacticalAnalyzer.h TeamYP1
	cp SyntacticalAnalyzer.cpp TeamYP1
	cp makefile TeamYP1
	cp README.txt TeamYP1
	tar cfvz yourlastnameP1.tgz TeamYP1
	cp TeamYP1.tgz ~tiawatts/cs460drop
