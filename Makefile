graphtest: graphtest.o graphops.o hashops.o
	gcc -Wall -o graphtest graphops.o hashops.o graphtest.o
hashtest: hashtest.o hashops.o
	gcc -Wall -o hashtest hashops.o hashtest.o
hashops.o: hashops.c
	gcc -Wall -c -o hashops.o hashops.c
graphops.o: graphops.c
	gcc -Wall -c -o graphops.o graphops.c
hashtest.o: hashtest.c
	gcc -Wall -c -o hashtest.o hashtest.c
graphtest.o: graphtest.c
	gcc -Wall -c -o graphtest.o graphtest.c
