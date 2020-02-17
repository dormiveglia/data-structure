CC = g++
FLAGS = -I./include -O2 -Wall -std=c++11
SOURCES = $(shell find . -name "*.cpp") 
OBJS = $(SOURCES:.cpp=.o)

all: $(OBJS)

$(OBJS): %.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	-rm -f $(OBJS)



.PHONY: clean
