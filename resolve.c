#include "libraries.h"
#include "matrix.h"
#include "resolve.h"

#define DEMO 1

int resolve(MATRIX matrix, int position_x, int position_y, int exit_x, int exit_y){

	int x_,y_;
	int i,a;
	int possible = 0;
	int deadEnd = 0;
	int available[4];

	markThrough(matrix,position_x,position_y);

	if(DEMO){
		displayMatrix(matrix);
		usleep(10000);	
	}

	//if end
	if(position_x == exit_x && position_y == exit_y){
		return 1;
	}

	for(i = 0; i < 4; i++){
		available[i] = 0;
		switch(i){
			case 0://go left
				x_ = position_x - 1;
				y_ = position_y;
				break;
			case 1://go down
				x_ = position_x;
				y_ = position_y + 1;
				break;
			case 2://go right
				x_ = position_x + 1;
				y_ = position_y;
				break;
			case 3://go up
				x_ = position_x;
				y_ = position_y - 1;
				break;
		}

		if(notAnEdge_(matrix, x_, y_)){
			if(noThrough(matrix,x_,y_) && noPossibilities(matrix,x_,y_) && noBacktrack(matrix,x_,y_) && !isWall(matrix, x_, y_,i)){
				a = i;//put possibe direction to a
				++possible;
				available[i] = 1;
			}
		}else{
			++deadEnd;
		}
	}

	//take random direction if more than one direction possible
	if(deadEnd < 4 && possible > 1){
		markPossibilities(matrix,position_x,position_y);
		do{
			a = (rand() % (4));

		}while(available[a] != 1);
	}

	if(deadEnd < 4 && possible > 0){
		switch(a){
			case 0://left
				if(!resolve(matrix, position_x-1, position_y,exit_x,exit_y)){//if can't go left
					if(noPossibilities(matrix,position_x,position_y)){
						markBacktrack(matrix,position_x,position_y);
						return 0;
					}
					else{
						if(!resolve(matrix, position_x, position_y,exit_x,exit_y)){
							markBacktrack(matrix,position_x,position_y);
							return 0;
						}else{
							return 1;
						}
					}
				}else{
					return 1;
				}
				break;
			case 1://down
				if(!resolve(matrix, position_x, position_y+1,exit_x,exit_y)){//if can't go down
					if(noPossibilities(matrix,position_x,position_y)){
						markBacktrack(matrix,position_x,position_y);
						return 0;
					}
					else{
						if(!resolve(matrix, position_x, position_y,exit_x,exit_y)){
							markBacktrack(matrix,position_x,position_y);
							return 0;
						}else{
							return 1;
						}
					}
				}else{
					return 1;
				}
				break;
			case 2://right
				if(!resolve(matrix, position_x+1, position_y,exit_x,exit_y)){//if can't go right
					if(noPossibilities(matrix,position_x,position_y)){
						markBacktrack(matrix,position_x,position_y);
						return 0;
					}
					else{
						if(!resolve(matrix, position_x, position_y,exit_x,exit_y)){
							markBacktrack(matrix,position_x,position_y);
							return 0;
						}else{
							return 1;
						}
					}
				}else{
					return 1;
				}
				break;
			case 3://up
				if(!resolve(matrix, position_x, position_y-1,exit_x,exit_y)){//if can't go up
					if(noPossibilities(matrix,position_x,position_y)){
						markBacktrack(matrix,position_x,position_y);
						return 0;
					}
					else{
						if(!resolve(matrix, position_x, position_y,exit_x,exit_y)){
							markBacktrack(matrix,position_x,position_y);
							return 0;
						}else{
							return 1;
						}
					}
				}else{
					return 1;
				}
				break;
		}
	}
	else{//dead lock
		if(noPossibilities(matrix,position_x,position_y))
			markBacktrack(matrix,position_x,position_y);
		return 0;
	}
	return 0;
}

//return 1 if wall
int isWall(MATRIX matrix, int x, int y, int i){

	switch(i){
		case 0://left
			if((matrix->matrix[x][y] & 0x4) == 0x4)//0b0100 = right
				return 1;
			else
				return 0;
		case 1://down
			if((matrix->matrix[x][y] & 0x8) == 0x8)//0b1000 = top
				return 1;
			else
				return 0;
		case 2://right
			if((matrix->matrix[x][y] & 0x1) == 0x1)//0b0001 = left
				return 1;
			else
				return 0;
		case 3://up
			if((matrix->matrix[x][y] & 0x2) == 0x2)//0b0010 = bottom
				return 1;
			else
				return 0;
	}
}

//through mark
void markThrough(MATRIX matrix, int x, int y){

	matrix->matrix[x][y] |= 0x20;//0b100000
}

//more than one possibility mark
void markPossibilities(MATRIX matrix, int x, int y){

	matrix->matrix[x][y] |= 0x40;//0b1000000
}

//backtrak mark
void markBacktrack(MATRIX matrix, int x, int y){

	matrix->matrix[x][y] |= 0x80;//0b10000000
}

//return 0 if edge
int notAnEdge_(MATRIX matrix, int x, int y){
	if(x < 0 || y < 0 || x >= matrix->x || y >= matrix->y)
		return 0;
	else
		return 1;
}

//return 1 if 0b100000 mark not found
int noThrough(MATRIX matrix, int x, int y){
	if(((matrix->matrix[x][y] >> 5) & 0x1) == 0)
		return 1;
	else
		return 0;
}

//return 1 if 0b1000000 mark not found
int noPossibilities(MATRIX matrix, int x, int y){
	if(((matrix->matrix[x][y] >> 6) & 0x1) == 0)
		return 1;
	else
		return 0;
}

//return 1 if 0b10000000 mark not found
int noBacktrack(MATRIX matrix, int x, int y){
	if(((matrix->matrix[x][y] >> 7) & 0x1) == 0)
		return 1;
	else
		return 0;
}

