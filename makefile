Affichage: Affichage.o libisentlib.a
	gcc -Wall Affichage.o -o Affichage libisentlib.a -lm -lglut -lGL -lX11
	
Testf: Testf.o libisentlib.a
	gcc -Wall Testf.o -o Testf libisentlib.a -lm -lglut -lGL -lX11

Affiche: Affiche.o libisentlib.a
	gcc -Wall Affiche.o -o Affiche libisentlib.a -lm -lglut -lGL -lX11
		
Timer: Timer.o libisentlib.a
	gcc -Wall Timer.o -o Timer libisentlib.a -lm -lglut -lGL -lX11
	
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exemple.o -o exemple libisentlib.a -lm -framework OpenGL -framework GLUT


Affichage.o: Affichage.c GfxLib.h BmpLib.h ESLib.h
	gcc -Wall -c Affichage.c

Testf.o: Testf.c GfxLib.h BmpLib.h mvmt.h savetest.h
	gcc -Wall -c Testf.c
	
Affiche.o: Affiche.c GfxLib.h BmpLib.h mvmt.h savetest.h
	gcc -Wall -c -g Affiche.c

Timer.o: Timer.c GfxLib.h BmpLib.h ESLib.h
	gcc -Wall -c Timer.c
		
libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o Mvmt.o savetest.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o Mvmt.o savetest.o
	ranlib libisentlib.a

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c
	

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c GfxLib.c -Wno-deprecated-declarations

Mvmt.o: Mvmt.c mvmt.h
	gcc -Wall -O2 -c Mvmt.c
	
savetest.o: savetest.c savetest.h
	gcc -Wall -O2 -c savetest.c
	
OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c

SocketLib.o: SocketLib.c SocketLib.h
	gcc -Wall -O2 -c SocketLib.c

ThreadLib.o: ThreadLib.c ThreadLib.h
	gcc -Wall -O2 -c ThreadLib.c

TortueLib.o: TortueLib.c TortueLib.h GfxLib.h
	gcc -Wall -O2 -c TortueLib.c

VectorLib.o: VectorLib.c VectorLib.h
	gcc -Wall -O2 -c VectorLib.c -msse3

WavLib.o: WavLib.c WavLib.h OutilsLib.h
	gcc -Wall -O2 -c WavLib.c -Wno-unused-result
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c WavLib.c

zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile makefile2

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f exemple Affichage Testf Timer Switch Affiche libisentlib.a

