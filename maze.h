#ifndef _maze_h_
#define _maze_h_

void genMaze(MATRIX matrix, int x, int y);
int genMaze_(MATRIX matrix, int x, int y);
void markCell(MATRIX matrix, int x, int y);
int notAnEdge(MATRIX matrix,int x, int y);
int noMark(MATRIX matrix, int x, int y);

#endif
