# $@ == nome da regra
# $< == nome da primeira dependência
# $^ == lista de dependências
# % == para casamento de padrões
# @ suprime mensagens

#compilador
CC=g++

#flags
CFLAGS=-O3 -std=c++11 -c #-Wall -pedantic -W 

#linkar
LDFLAGS=-lglut -lGLU -lGL -lm

#remover
RM=rm -f

#executável
EXEC=t4

#arquivos .cpp
CPPSRC=$(wildcard ./src/*.cpp)

#arquivos .h
HPPSRC=$(wildcard ./src/*.h)

#arquivos .o
OBJ=$(subst .cpp,.o,$(subst src,obj,$(CPPSRC)))

#regras
all: object $(EXEC)

$(EXEC):$(OBJ)
	@$(CC) $^ -o $@ $(LDFLAGS)

#gerar arquivos .o
./obj/%.o: ./src/%.cpp ./src/%.h
	@$(CC) $< $(CFLAGS) -o $@

./obj/main.o: ./src/main.cpp $(HPPSRC)
	@$(CC) $< $(CFLAGS) -o $@

#gerar pasta dos arquivos .o
object:
	@mkdir -p obj

#limpar
clean:
	@rm -rf obj $(EXEC)

#executar -  @ para não mostrar no terminal
run:
	@./$(EXEC)

#alvo falso
.PHONY: all clean run