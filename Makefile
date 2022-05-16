all:
	g++ -ID:\VNU\Program\LTNC\libraries\src\include\SDL2 -LD:\VNU\Program\LTNC\libraries\src\lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer