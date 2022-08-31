COMPILER = g++
FLAGS = -std=c++17 -Wall
INCLUDE_PATH = ../
CPP_FILES = $(INCLUDE_PATH)*.cpp main.cpp
LIBS = -lwthttp -lwt
TARGET = app


$(TARGET): $(CPP_FILES)
	$(COMPILER) -I$(INCLUDE_PATH) $(FLAGS) $(CPP_FILES) -o $(TARGET) $(LIBS)
	

all: $(TARGET)


run:
	./$(TARGET) --docroot . --http-address 127.0.0.1 --http-port 8080
	

clean:
	rm -f $(TARGET)
