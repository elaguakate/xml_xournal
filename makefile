# compiler
CC = g++

# compiler flags:
CFLAGS = -g -Wall

default: xml_xournal

xml_xournal: xml_xournal.o pugixml.o
	$(CC) $(CFLAGS) -o xml_xournal xml_xournal.o pugixml.o

xml_xournal.o: xml_xournal.cpp pugixml.hpp
	$(CC) $(CFLAGS) -c xml_xournal.cpp 

pugixml.o: pugixml.cpp pugixml.hpp pugiconfig.hpp
	$(CC) $(CFLAGS) -c pugixml.cpp 

clean:
	$(RM) xml_xournal *.o *~
