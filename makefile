CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) 

#******* TravelingSalesPerson Driver************************
TravelingSalesPerson : TravelingSalesPerson.o Path.o GraphPlaceholder.o Graph.o
	$(CC) $(LFLAGS)  TravelingSalesPerson.o -o TravelingSalesPerson

TravelingSalesPerson.o : TravelingSalesPerson.cpp Path.cpp GraphPlaceholder.cpp Graph.cpp  
	$(CC) $(CFLAGS)  TravelingSalesPerson.cpp
# **********************************************************
# *******Testing Graph************************
##links o files
# GraphTest : GraphTest.o  Graph.o Path.o
# 	$(CC) $(LFLAGS)  GraphTest.o  -o GraphTest
##Creates Driver o file
# GraphTest.o : GraphTest.cpp Graph.cpp Path.cpp
# 	$(CC) $(CFLAGS)  GraphTest.cpp
# *******************************************
# *******Testing Path************************
# PathTest : PathTest.o  Path.o
# 	$(CC) $(LFLAGS)  PathTest.o  -o PathTest

# PathTest.o : PathTest.cpp Path.cpp
# 	$(CC) $(CFLAGS)  PathTest.cpp
# *******************************************

GraphPlaceholder.o : GraphPlaceholder.cpp Path.cpp
	$(CC) $(CFLAGS)  GraphPlaceholder.cpp

Graph.o : Graph.cpp Path.cpp
	$(CC) $(CFLAGS)  Graph.cpp
	
Path.o : Path.cpp
	$(CC) $(CFLAGS)  Path.cpp

clean:
	\rm *.o TravelingSalesPerson
