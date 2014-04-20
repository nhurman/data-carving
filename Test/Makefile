include Makefile.local
CC=g++
CFLAGS=--std=c++11 -I$(IDIR) -I../BitGrapher
LFLAGS=-L$(LDIR)
LIBS=-lUnitTest++

OUT=out/
DEPS=../BitGrapher/core/bitstring.cpp \
  ../BitGrapher/algorithms/diagonal.cpp

tests: main.cpp
	@[[ -d $(OUT) ]] || mkdir $(OUT)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(OUT)$@ $^ $(DEPS) $(LIBS)
	@$(OUT)/$@

clean:
	rm -r $(OUT)
