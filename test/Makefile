SRC=../src

all: build plot

build:
	g++ test.cpp $(SRC)/SOS.c -ggdb -o filt.out
	./filt.out
	
plot:
	gnuplot plot_settings

float:
	g++ test2.cpp ../ftoa.cpp -ggdb -o float.out
