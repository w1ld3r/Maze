#ifndef _resolve_h_
#define _resolve_h_

int isWall(MATRIX matrix, int x, int y, int i);
void markThrough(MATRIX matrix, int x, int y);
void markPossibilities(MATRIX matrix, int x, int y);
void markBacktrack(MATRIX matrix, int x, int y);
int notAnEdge_(MATRIX matrix, int x, int y);
int noThrough(MATRIX matrix, int x, int y);
int noPossibilities(MATRIX matrix, int x, int y);
int noBacktrack(MATRIX matrix, int x, int y);
int resolve(MATRIX matrix, int position_x, int position_y, int end_x, int end_y);

#endif
