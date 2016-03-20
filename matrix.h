#ifndef MATRIX_H
#define MATRIX_H

#include "StdAfx.h"
#include "def.h"
#include <malloc.h>
#include <math.h>
#include <string.h>

#define LEN_INT 4;
typedef struct MyMatrix{
    uint32 row;
    uint32 colum;
    //uint32 rowlen;
    //uint8 * data;
    uint8 ** rowpoint;
}*mymatrix;

//static uint32 search_col_1(uint8** mat, uint32 start,uint32 row);
//static void row_exchange(uint32 row, uint32 col, uint8** mat,uint32 matsize);
//static void row_sub(uint32 row1,uint32 row2,uint8** mat,uint32 matsize,uint8 temp1,uint8 temp2);
//static void row_or(uint32 row1,uint32 row2,uint8** mat,uint32 matsize);
//static void matrix_free(uint8** mat,uint32 size);
//static void my_xor(uint8 * x, uint8 * y, uint32 size);
//static void my_exchange(uint8* x, uint8* y, uint32 size);

int matrix_init(uint32 rownum, uint32 columnum, mymatrix mat);
int matrix_inverse(mymatrix A,mymatrix A_1);
int matrix_equations(mymatrix A,uint8* D, uint32 size);

#endif // MATRIX_H
