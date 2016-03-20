#ifndef RAPTORCODE_H
#define RAPTORCODE_H

#include "StdAfx.h"
#include "def.h"
#include "matrix.h"

typedef struct RaptorParam{
    uint32 K;
    uint32 S;
    uint32 L;
    uint32 H;
    mymatrix Amat;
    mymatrix A_1mat;
}*RParam;

typedef struct Triple{
    uint32 a;
    uint32 b;
    uint8 d;
}*triple;

typedef struct RaptorParam_dec{
    uint32 K;
    uint32 S;
    uint32 L;
    uint32 H;
//	uint32 M;
    uint32 N;
    char timestamp[20];/*********addition : 时间戳***********/
    mymatrix Amat_dec;
    uint16* list;
}*RParam_dec;

//static void trip(int K, int X, triple trp);
//static uint8 deg(uint32 v);
//static uint16 gray_m(int j,float k);
//static uint32 rand(int x,int i,int m);


//static void my_xor(uint8 * x, uint8 * y, uint32 size);

//static void raptor_intermediate(RParam_dec parameter);
//static void raptor_getLDPC(RParam_dec parameter);
//static void raptor_getH(RParam_dec parameter);
//static void raptor_getLT(RParam_dec parameter);
//static void raptor_dec_stepone(RParam_dec para_dec);
//static void raptor_getLTrow(uint32 L, uint8* input, triple trp,uint32 l1);




void raptor_init(uint32 k,uint32 n, RParam_dec parameter);

void raptor_parameterfree(RParam_dec parameter);

uint32 raptor_decode(RParam_dec parameter, uint8* input_src, uint8* output_return, uint32 T);
void raptor_free(uint8* pointer);

#endif // RAPTORCODE_H
