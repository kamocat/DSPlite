SRC=../src

all: build plot

build:
	g++ test.cpp $(SRC)/SOS.cpp $(SRC)/FIR.cpp $(SRC)/IIR.cpp $(SRC)/LinearRegression.cpp -ggdb -o filt.out
	./filt.out
	
plot:
	gnuplot plot_settings

float:
	g++ test2.cpp ../ftoa.cpp -ggdb -o float.out

hist:
	g++ -DDEBUG_HISTOGRAM histogram_test.cpp $(SRC)/Histogram.cpp -ggdb -Og -o test_hist.out
	./test_hist.out
	gnuplot plot_hist
