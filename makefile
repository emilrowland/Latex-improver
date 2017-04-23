OBJS = main.o latexImprover.o KMP.o

LatexImprover: $(OBJS)
	g++ -o LatexImprover $(OBJS)

main.o: main.cpp include/latexImprover.h
	g++ -c main.cpp
	
latexImprover.o: src/latexImprover.cpp include/latexImprover.h include/KMP.h
	g++ -c src/latexImprover.cpp

KMP.o: src/KMP.cpp include/KMP.h
	g++ -c src/KMP.cpp