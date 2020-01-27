#include "libraries.h"
#include "matrix.h"
#include "maze.h"
#include "resolve.h"


int main(int args, char **argv){

	srand(time(NULL));
	MATRIX matrix = malloc(sizeof(MATRIX));
	int choice;
	char file[2500];
	FILE *f = NULL;
	int x,y,i,j;
	int x_start,y_start,x_end,y_end;

	printf("\e[1;1H\e[2J------------------------------MAZE MENU------------------------------\n");
	printf("Select between 1 or 2 :\n1. Random maze generation\n2. Load maze from file\n");
	scanf("%d", &choice);

	if(choice == 1){

		SIZE: printf("Select size of maze :\n");
		printf("X : "); scanf("%d",&x);
		printf("Y : "); scanf("%d",&y);

		if(x <= 0 || y <= 0){
			printf("Bad size !\n");
			goto SIZE;
		}

		allocMatrix(matrix,x,y);
		initMatrix(matrix, NULL);
		genMaze(matrix,0,0);
		displayMatrix(matrix);

		COORD:printf("Select start and end coordinates :\n");
		printf("Start X : "); scanf("%d",&x_start);
		printf("Start Y : "); scanf("%d",&y_start);
		printf("End X : "); scanf("%d",&x_end);
		printf("End Y : "); scanf("%d",&y_end);

		if(x_start < 0 || x_start >= matrix->x || y_start < 0 || y_start >= matrix->y || x_end < 0 || x_end >= matrix->x || y_end < 0 || y_end >= matrix->y){
			printf("Bad start and end coordinates !\n");
			goto COORD;
		}
		
		f = fopen("maze.txt", "w+");
		fprintf(f,"%d %d %d %d %d %d\n",x,y,x_start,y_start,x_end,y_end);

		for(i = 0; i < y; i++){
			for(j = 0; j < x; j++){
				fprintf(f, "%d ",matrix->matrix[j][i] - 16);// -16 to supress mark
			}
			fprintf(f, "\n");
		}
		fclose(f);
		

	}
	else if(choice == 2){

		FILE: printf("File name (must be in current directory) :\n");
		scanf("%s", file);

		if((f = fopen(file, "r" )) == NULL){
			printf("Cannot open file %s !\n", file);
			goto FILE;
		}
		else{
			fscanf(f, "%d %d %d %d %d %d", &x, &y, &x_start, &y_start, &x_end, &y_end);
			
			if(x_start < 0 || x_start >= x || y_start < 0 || y_start >= y || x_end < 0 || x_end >= x || y_end < 0 || y_end >= y){
				printf("Bad maze format !\n");
				goto HELL;
			}

			allocMatrix(matrix,x,y);
			initMatrix(matrix,f);
			displayMatrix(matrix);
		}
	}
	else{
		goto HELL;
	}

	if(resolve(matrix,x_start,y_start,x_end,y_end)){
		displayMatrix(matrix);
		printf("Path found !\n");
	}else{
		printf("Path not found ...\n");
	}
	HELL: free(matrix);
	return 0;
}
