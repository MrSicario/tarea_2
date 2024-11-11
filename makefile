CXX = clang++
EXP = 0

.PHONY: clean

all: 1 2 3 4 5 6 7 8 9 10 clean

1: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.1"
	@./experiment.o $(EXP) 0.1

2: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.2"
	@./experiment.o $(EXP) 0.2

3: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.3"
	@./experiment.o $(EXP) 0.3

4: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.4"
	@./experiment.o $(EXP) 0.4

5: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.5"
	@./experiment.o $(EXP) 0.5

6: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.6"
	@./experiment.o $(EXP) 0.6

7: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.7"
	@./experiment.o $(EXP) 0.7

8: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.8"
	@./experiment.o $(EXP) 0.8

9: experiment.o
	@echo "Corriendo experimento con 10^6 * 0.9"
	@./experiment.o $(EXP) 0.9

10: experiment.o
	@echo "Corriendo experimento con 10^6 * 1"
	@./experiment.o $(EXP) 1

experiment.o: experiment.cpp
	@$(CXX) experiment.cpp -std=c++23 -o experiment.o

clean:
	@rm -f experiment.o