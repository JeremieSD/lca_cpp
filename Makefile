lca.o: lca.o
	g++ -o lca.o lca.cpp -I$GOOGLETESTDIR/include -L$GOOGLETESTDIR/lib -lgtest -lpthread

clean: 
	rm *.o