all: myExercises someSorts DB_LinkedList Producer Consumer

myExercises: Declarations_Expressions.c SearchAlg.c SortAlg.c
	gcc -o myExercises Declarations_Expressions.c SearchAlg.c SortAlg.c -lm

someSorts: SortCall.c SortAlg.c SearchAlg.c
	gcc -o someSorts SortCall.c SortAlg.c SearchAlg.c -lm

DB_LinkedList: DB_LinkedList_input.c DB_LinkedList_lib.c
	gcc -o DB_LinkedList DB_LinkedList_input.c DB_LinkedList_lib.c

Producer: sh1_prod.c
	gcc -o Producer sh1_prod.c -lpthread

Consumer: sh2_cons.c
	gcc -o Consumer sh2_cons.c -lpthread
