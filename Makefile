linked_list.out: main.o file_operations.o list.o
	gcc -o linked_list.out main.o file_operations.o list.o
main.o: main.c
	gcc -c -g main.c
file_operations.o: file_operations.c
	gcc -c -g file_operations.c
list.o: list.c
	gcc -c -g list.c
clean:
	rm -f *.o
	rm -f linked_list.out
gdb:
	gdb ./linked_list.out
