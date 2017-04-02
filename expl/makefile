
INCLUDE=./include

explore: explore.o list.o strList.o 
	gcc -o $@ $^ -lncurses -g
explore.o: explore.c 
	gcc -o $@ -c $^ -I $(INCLUDE) -g
list.o: list.c 
	gcc -o $@ -c $< -I $(INCLUDE) -g
strList.o: strList.c 
	gcc -o $@ -c $< -I $(INCLUDE) -g
clean:
	rm explore explore.o list.o strList.o
install:
	sudo cp ./bin/cdg ./explore /bin

