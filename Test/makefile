
test: main.cpp
	g++ -I../ -std=c++17 -Wall main.cpp -o test -lwthttp -lwt
	

all: test


run:
	./test --docroot . --http-address 0.0.0.0 --http-port 9090
	

clean:
	rm -f test
