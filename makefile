all:
	@g++ value_right.cpp -fno-elide-constructors -std=c++11 -o Decrypt.out
	@echo success
clean:
	@rm a.out
	@echo rm all

rebuild:clean all