all: myExercises someSorts

myExercises: Declarations_Expressions.c SearchAlg.c SortAlg.c
	gcc -o myExercises Declarations_Expressions.c SearchAlg.c SortAlg.c -lm

someSorts: SortCall.c SortAlg.c SearchAlg.c
	gcc -o someSorts SortCall.c SortAlg.c SearchAlg.c -lm
