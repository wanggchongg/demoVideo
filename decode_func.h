#ifndef DECODE_FUNC_H
#define DECODE_FUNC_H

#include <QObject>
#include <QThread>
#include "externvar.h"
#include "raptorcode.h"
#include <stdlib.h>
#include <QTimer>

class Object:public QObject
{
Q_OBJECT
public:
    Object();
    ~Object();

private:
    FrameHeader_t *frameHeader;
    char *inputBuf;
    char *outputBuf;
    long inputBufSize;
    long outputBufSize;

    int K_old, R_old;

    int cur_frame_no;
    int last_frame_no;
    int old_frame_no ;

    uint32 raptor_K_recieve;
    uint32 raptor_R_recieve;
    uint32 raptor_N_recieve;
    uint32 raptor_K_temp;
    uint32 raptor_R_temp;
    uint32 raptor_N_temp;

    uint16 *list_cur;
    uint16 list_temp;
    FILE *store_v;

    unsigned int loseRate;
    unsigned int rDecodeN;
    unsigned int rDecodeSN;
    float rDecodeSR;
    QTimer timer;
    QUdpSocket *sendSocket;
    QHostAddress sendMulAddr;
signals:
    void dataObjReady();
    void decodeRateChanged(float);

public slots:
    void decode();
    void loseRateChanged();
    void dealTimeout();
};

class DecodeThread:public QThread
{
Q_OBJECT
public:
    DecodeThread();
    ~DecodeThread();
    void run();

signals:
    void dataArrived();
    void dataDecoReady();
    void loseRateChange();
    void decodeRateChanged(float);
};

#endif // DECODE_FUNC_H
