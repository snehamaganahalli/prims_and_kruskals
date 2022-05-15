all:
	g++ prims_kruskal.cpp -std=c++11 -o exe

clean:
	/bin/rm -rf exe
