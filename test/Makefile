SRC=../src

all: build plot

build:
	g++ test.cpp $(SRC)/SOS.cpp $(SRC)/FIR.cpp $(SRC)/IIR.cpp $(SRC)/LinearRegression.cpp -ggdb -o filt.out
	./filt.out
	
plot:
	gnuplot plot_settings

float:
	g++ test2.cpp ../ftoa.cpp -ggdb -o float.out
