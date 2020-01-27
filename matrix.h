#ifndef _matrix_h_
#define _matrix_h_

typedef struct MAT{
	unsigned short int **matrix;
	int x;
	int y;
} *MATRIX;

void allocMatrix(MATRIX matrix, int x , int y);
void initMatrix(MATRIX matrix, FILE *f);
void displayMatrix(MATRIX matrix);

#endif