
output=trie`python3-config --extension-suffix`
target=trie.cpp

all: compile

compile:
	c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` ${target} -o ${output}

clean:
	rm trie`python3-config --extension-suffix`
