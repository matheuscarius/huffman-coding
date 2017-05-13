CPPFLAGS=-std=c++11
MKDIRP=mkdir -p

all: encode text2bin decode

encode:
	$(MKDIRP) bin
	$(CXX) $(CPPFLAGS) -o bin/encode src/encode.cpp

text2bin:
	$(MKDIRP) bin
	$(CXX) $(CPPFLAGS) -o bin/text2bin src/text2bin.cpp

decode:
	$(MKDIRP) bin
	$(CXX) $(CPPFLAGS) -o bin/decode src/decode.cpp

clean:
	rm -R bin/
