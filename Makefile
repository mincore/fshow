BINS=$(patsubst %.cpp,%,$(shell find . -name "*.cpp"))

all:$(BINS)

clean:
	rm -f $(BINS)
