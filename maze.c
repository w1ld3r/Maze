#include "libraries.h"
#include "matrix.h"
#include "maze.h"

#define DEMO 0

void genMaze(MATRIX matrix, int x, int y){

	genMaze_(matrix, x, y);
}

int genMaze_(MATRIX matrix, int x, int y){

	if(DEMO){
		displayMatrix(matrix);
		usleep(1000000);
	}

	int x_,y_;
	int i;
	int possible = 0;
	int available[4];

	markCell(matrix,x,y);

	for(i = 0; i < 4; i++){

		available[i] = 0;

		switch(i){
			case 0://go left
				x_ = x - 1;
				y_ = y ;
				break;
			case 1://go down
				x_ = x;
				y_ = y + 1;
				break;
			case 2://go right
				x_ = x + 1;
				y_ = y;
				break;
			case 3://go up
				x_ = x;
				y_ = y - 1;
				break;
		}

		if(notAnEdge(matrix, x_, y_) && noMark(matrix, x_, y_)){
			possible = 1;
			available[i] = 1;
		}
	}

	if(possible){
		do{//take random direction
			i = (rand() % 4);
		}while(available[i] != 1);//while position not mark

		switch(i){
			case 0://go left
				matrix->matrix[x][y] &= 0xFFFE;//0b1110 = top, right, bottom wall
				matrix->matrix[x-1][y] &= 0xFFFB;//0b1011 = top, bottom, left wall to left cell
				if(genMaze_(matrix, x-1, y) == 0){//if left cell is an edge or mark go next
					genMaze_(matrix, x, y);
				}
				break;
			case 1://go down
				matrix->matrix[x][y] &= 0xFFFD;//0b1101 = top,right, left wall
				matrix->matrix[x][y+1] &= 0xFFF7;//0b0111 = right, bottom, left wall to down cell
				if(genMaze_(matrix, x, y+1) == 0){//if down cell is an edge or mark go next
					genMaze_(matrix, x, y);
				}
				break;
			case 2://go right
				matrix->matrix[x][y] &= 0xFFFB;//0b1011 = top, bottom, left wall
				matrix->matrix[x+1][y] &= 0xFFFE;//0b1110 = top, right, bottom wall to right cell
				if(genMaze_(matrix, x+1, y) == 0){//if right cell is an edge or mark go next
					genMaze_(matrix, x, y);
				}
				break;
			case 3://go up
				matrix->matrix[x][y] &= 0xFFF7;//0b0111 = right, bottom, left wall
				matrix->matrix[x][y-1] &= 0xFFFD;//0b1101 = top,right, left to up cell
				if(genMaze_(matrix, x, y-1) == 0){//if up cell is an edge or mark go next
					genMaze_(matrix, x, y);
				}
				break;
		}
	}
	else{
		return 0;
	}
	return 0;
}

void markCell(MATRIX matrix, int x, int y){
	matrix->matrix[x][y] |= 0x10; //0b10000
}

//return 0 if edge
int notAnEdge(MATRIX matrix, int x, int y){
	if(x < 0 || y < 0 || x >= matrix->x || y >= matrix->y)
		return 0;
	else
		return 1;
}

//return 0 if mark found
int noMark(MATRIX matrix, int x, int y){
	if(((matrix->matrix[x][y] >> 4) & 0x1) == 1)
		return 0;
	else
		return 1;
}
