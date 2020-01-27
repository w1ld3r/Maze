#include "libraries.h"
#include "matrix.h"

#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define RESET "\x1B[0m"
#define CLEAR "\e[1;1H\e[2J"
#define POSITION "\033[%d;%dH"
#define BACKTRACK "X"
#define FORWARD "0"

void allocMatrix(MATRIX matrix, int x , int y){

	unsigned short int ** result = malloc(sizeof(unsigned short int*) * x);

	for (int i = 0; i < x; i++){
		
		result[i] = malloc(sizeof(unsigned short int) * y);
	}
	
	matrix->x = x;
	matrix->y = y;
	matrix->matrix = result;
}

void initMatrix(MATRIX matrix, FILE* f){

	int x = matrix->x;
	int y = matrix->y;
	int n;

	if(f == NULL){
		for(int i = 0; i < y ; i++){
			for(int j = 0; j < x; j++){
				matrix->matrix[j][i] = 15; //0b1111
			}
		}
	}
	else{
		for(int i = 0; i < y; i++){
			for(int j = 0; j < x; j++){
				fscanf(f, "%d", &n);
				matrix->matrix[j][i] = n;
			}
		}
	}
}

void displayMatrix(MATRIX matrix){

	int x = matrix->x;
	int y = matrix->y;

	printf(CLEAR);

	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++){
			printf(POSITION,1 + i*2, 1 + j*4);

			if((matrix->matrix[j][i] & 0x8) == 0x8){//0b1000 = top
				printf("+---+\n");
            }else{
				printf("+   +\n");
			}

			if((matrix->matrix[j][i] & 0x5) == 0x5){//0b0101 = left & right
				printf(POSITION,2 + i*2, 1 + j*4);

				if(((matrix->matrix[j][i] >> 5) & 0x1) == 0){
					printf("|   |\n");
				}else if( ( ( matrix->matrix[j][i] >> 7) & 0x1) == 1){
					printf("| ");printf(RED BACKTRACK RESET);printf(" |\n");
				}else{
					printf("| ");printf(GREEN FORWARD RESET);printf(" |\n");
				}

			}else if((matrix->matrix[j][i] & 0x1) == 0x1){//0b0001 = left
				printf(POSITION,2 + i*2, 1 + j*4);

				if(((matrix->matrix[j][i] >> 5) & 0x1) == 0){
					printf("|    \n");
				}else if(((matrix->matrix[j][i] >> 7) & 0x1) == 1){
					printf("| ");printf(RED BACKTRACK RESET);printf("  \n");
				}else{
					printf("| ");printf(GREEN FORWARD RESET);printf("  \n");
				}

			}else if((matrix->matrix[j][i] & 0x4) == 0x4){//0b0100 = right
				printf(POSITION,2 + i*2, 1 + j*4);

				if(((matrix->matrix[j][i]>> 5) & 0x1) == 0){
					printf("    |\n");
				}else if(((matrix->matrix[j][i] >> 7) & 0x1) == 1){
					printf("  ");printf(RED BACKTRACK RESET);printf(" |\n");
				}else{
					printf("  ");printf(GREEN FORWARD RESET);printf(" |\n");
				}

			}else{//no left & no right
				printf(POSITION,2 + i*2, 1 + j*4);
					
				if(((matrix->matrix[j][i] >> 5) & 0x1) == 0){
					printf("     \n");
				}else if(((matrix->matrix[j][i] >> 7) & 0x1) == 1){
					printf("  ");printf(RED BACKTRACK RESET);printf("  \n");
				}else{
					printf("  ");printf(GREEN FORWARD RESET);printf("  \n");
				}
			}

			if((matrix->matrix[j][i] & 0x2) == 0x2){//0b0010 = bottom
				printf(POSITION,3 + i*2, 1 + j*4);
				printf("+---+\n");
			}else{
				printf(POSITION,3 + i*2, 1 + j*4);
				printf("+   +\n");
			}
		}
	}
	printf(POSITION,3 + 2*y,1);
}




