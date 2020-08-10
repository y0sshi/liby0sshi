default: main

run:  main
	sudo ./main

main: main.cpp
	g++ main.cpp -o main `pkg-config --libs y0sshi`

clean:
	rm -f main
