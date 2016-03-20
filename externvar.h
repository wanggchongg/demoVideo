#ifndef EXTERNVAR_H
#define EXTERNVAR_H
#include <QSemaphore>
#include <stdio.h>
#include <windows.h>
#include <QDebug>
#include <iostream>
#include <QUdpSocket>
#include <QHostAddress>
using namespace std;
#include "def.h"

extern "C"{
    #include "SDL/include/SDL_stdinc.h"
    #include "SDL/include/SDL_mutex.h"
    #include "SDL/include/SDL.h"
    #include "SDL/include/SDL_thread.h"
    #include "SDL/include/SDL_main.h"

    #include "ffmpeg/include/libavcodec/avcodec.h"
    #include "ffmpeg/include/libavdevice/avdevice.h"
    #include "ffmpeg/include/libavformat/avformat.h"
    #include "ffmpeg/include/libswscale/swscale.h"
    #include "ffmpeg/include/libavutil/mathematics.h"
}

typedef struct FrameHeader_t{
    int frame_no;
    long slice_no;
    int frame_type;
    long F;
    int T;
    int K;
    int R;
    int esi;
    int camera_no;
}FrameHeader_t;

typedef struct ShowNode
{
    char h264node[1000000];
    int size;
    int frameNo;
}ShowNode;


#define T_MAX 1024
#define MAXLINE sizeof(FrameHeader_t)+T_MAX
#define MAXBUFSIZE 2

extern QSemaphore s_emptyFrame;
extern QSemaphore s_fullFrame;
extern unsigned int sigPutFrame;
extern unsigned int sigGetFrame;
extern char frameBuf[MAXBUFSIZE][MAXLINE];

extern QSemaphore s_emptyShow;
extern QSemaphore s_fullShow;
extern unsigned int sigPutShow;
extern unsigned int sigGetShow;
extern ShowNode showBuf[MAXBUFSIZE];

extern SDL_Surface *screen;
extern AVFormatContext *pFormatCtx;
extern AVCodecContext *pCodecCtx;
extern AVCodec *pCodec;

extern int lose_num;
extern int lose_num1;

#endif // EXTERNVAR_H
