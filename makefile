CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) 

#******* TravelingSalesPerson Driver************************
#links o files
TravelingSalesPerson : TravelingSalesPerson.o Path.o #Graph.cpp
	$(CC) $(LFLAGS)  TravelingSalesPerson.o -o TravelingSalesPerson

#Creates Driver o file
TravelingSalesPerson.o : TravelingSalesPerson.cpp Path.cpp #Graph.cpp  
	$(CC) $(CFLAGS)  TravelingSalesPerson.cpp
# **********************************************************
# *******Testing Graph************************
# GraphTest : GraphTest.o  Graph.o Path.o
# 	$(CC) $(LFLAGS)  GraphTest.o  -o GraphTest

# GraphTest.o : GraphTest.cpp Graph.cpp Path.cpp
# 	$(CC) $(CFLAGS)  GraphTest.cpp
# *******************************************
# *******Testing Path************************
# PathTest : PathTest.o  Path.o
# 	$(CC) $(LFLAGS)  PathTest.o  -o PathTest

# PathTest.o : PathTest.cpp Path.cpp
# 	$(CC) $(CFLAGS)  PathTest.cpp
# *******************************************

# Graph.o : Graph.cpp Path.cpp
# 	$(CC) $(CFLAGS)  Graph.cpp
	
Path.o : Path.cpp
	$(CC) $(CFLAGS)  Path.cpp

clean:
	\rm *.o TravelingSalesPerson
