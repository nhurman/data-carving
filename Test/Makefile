include Makefile.local
CC=g++
CFLAGS=--std=c++11 -I$(IDIR)
LFLAGS=-L$(LDIR)
LIBS=-lUnitTest++

OUT=out/
DEPS=../BitGrapher/core/BitString.cpp \
     ../BitGrapher/core/Exception.cpp

tests: main.cpp
	@[[ -d $(OUT) ]] || mkdir $(OUT)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(OUT)$@ $^ $(DEPS) $(LIBS)
	@$(OUT)/$@

clean:
	rm -r $(OUT)
