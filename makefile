JackCompiler: *.cpp
	g++  -c -g -Wall  -o bin/codeGenerator.o sources/codeGenerator.cpp -std=c++17 -lstdc++fs
	g++  -c -g -Wall  -o bin/compilationEngine.o sources/compilationEngine.cpp -std=c++17 -lstdc++fs
	g++  -c -g -Wall  -o bin/syntaxAnalyzer.o sources/syntaxAnalyzer.cpp -std=c++17 -lstdc++fs
	g++  -c -g -Wall  -o bin/tokenizer.o sources/tokenizer.cpp -std=c++17 -lstdc++fs
	g++  -c -g -Wall  -o bin/parser.o sources/parser.cpp -std=c++17 -lstdc++fs
	g++  -c -g -Wall  -o bin/main.o main.cpp -std=c++17 -lstdc++fs
	g++  bin/main.o  bin/codeGenerator.o bin/parser.o bin/compilationEngine.o  bin/syntaxAnalyzer.o bin/tokenizer.o -o JackCompiler -std=c++17 -lstdc++fs
clean : 
	del /Q bin\*.o JackCompiler.exe
test :
	rm -f bin/*.o  JackCompiler.exe
