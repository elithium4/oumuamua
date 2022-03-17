all: start

start: 
	$(MAKE) -C ./source

clean:
	rm -rf *.o program $(&&)
	$(MAKE) clean -C ./source