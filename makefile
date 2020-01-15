output : main.o display.o shader.o mesh.o stb_image.o texture.o
	g++ -o main main.o display.o shader.o mesh.o stb_image.o texture.o -lSDL2 -lGL -lGLEW 
 
main.o : main.cc
	g++ -c main.cc

display.o : display.cc display.h
	g++ -c display.cc

shader.o : shader.cc shader.h
	g++ -c shader.cc

mesh.o : mesh.cc mesh.h
	g++ -c mesh.cc

stb_image.o : stb_image.c stb_image.h
	g++ -c stb_image.c

texture.o : texture.cc texture.h
	g++ -c texture.cc

clean : 
	rm main.o
	rm display.o
	rm shader.o
	rm mesh.o
	rm texture.o
	rm main