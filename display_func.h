#ifndef DISPLAY_FUNC_H
#define DISPLAY_FUNC_H

#include <QThread>
#include "externvar.h"

class ShowObject:public QObject{
    Q_OBJECT
public:
    ShowObject();//contain initialization
    ~ShowObject();

public slots:
    void dealShowVideo();

private:
    AVFrame *pFrame;
    SDL_Overlay *bmp;
    SDL_Rect dst;

    struct SwsContext *img_convert_ctx;
    AVPicture pict;

    FILE *store_v_yuv;
};

class ShowThread:public QThread{
    Q_OBJECT
public:
    ShowThread();
    ~ShowThread();
    void run();

signals:
    void dataArrived();
};

#endif // DISPLAY_FUNC_H
