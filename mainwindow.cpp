#include "mainwindow.h"
#include "ui_mainwindow.h"

static char frameTmpBuf[MAXLINE];

QSemaphore s_emptyFrame(MAXBUFSIZE);
QSemaphore s_fullFrame(0);
unsigned int sigPutFrame(0);
unsigned int sigGetFrame(0);
char frameBuf[MAXBUFSIZE][MAXLINE];

QSemaphore s_emptyShow(MAXBUFSIZE);
QSemaphore s_fullShow(0);
unsigned int sigPutShow(0);
unsigned int sigGetShow(0);
ShowNode showBuf[MAXBUFSIZE];

SDL_Surface *screen;
AVFormatContext *pFormatCtx;
AVCodecContext *pCodecCtx;
AVCodec *pCodec;

AVFormatContext *ofmt_ctx = NULL;
AVOutputFormat *ofmt = NULL;

int lose_num(0);
int lose_num1(0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(close()));
    ui->loseSlider->setTickInterval(100);
    ui->loseSlider1->setTickInterval(100);
    connect(ui->loseSlider, SIGNAL(valueChanged(int)), this, SLOT(loseNumChange(int)));
    connect(ui->loseSlider1, SIGNAL(valueChanged(int)), this, SLOT(loseNum1Change(int)));

    qDebug()<<"main thread: "<<QThread::currentThreadId()<<endl;

    decodeThread = new DecodeThread;
    connect(this, SIGNAL(frameReady()), decodeThread, SIGNAL(dataArrived()));
    decodeThread->start();

    SDL_init();
    showThread = new ShowThread;
    connect(decodeThread, SIGNAL(dataDecoReady()), showThread, SIGNAL(dataArrived()));
    showThread->start();

    begin();
    connect(ui->losePushButton, SIGNAL(clicked()), decodeThread, SIGNAL(loseRateChange()));
    connect(decodeThread, SIGNAL(decodeRateChanged(float)), this, SLOT(decodeRateChanged(float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::begin()
{
    videoSocket = new QUdpSocket(this);
    videoSocket->bind(8888);
    connect(videoSocket, SIGNAL(readyRead()), this, SLOT(recv_real_videodata()));
}

void MainWindow::recv_real_videodata()
{
    QHostAddress sender4;
    while(videoSocket->hasPendingDatagrams())
    {
        memset(frameTmpBuf, 0, MAXLINE);
        videoSocket->readDatagram(frameTmpBuf, MAXLINE, &sender4, 0);
        if('#' == frameTmpBuf[0])
        {
            //cout<<"###"<<endl;
            continue;
        }

        s_emptyFrame.acquire();
        memset(frameBuf[sigPutFrame], 0, MAXLINE);
        memcpy(frameBuf[sigPutFrame], frameTmpBuf, MAXLINE);
        s_fullFrame.release();
        sigPutFrame++;
        sigPutFrame %= MAXBUFSIZE;

        emit frameReady();
        break;
    }
}

void MainWindow::SDL_init()
{
    char variable[64];

#ifdef Q_OS_WIN
    sprintf(variable, "SDL_WINDOWID=0x%lx", ui->video->winId());
#else
    sprintf(variable, "SDL_WINDOWID=0x%lx", this->winId());
#endif
    putenv(variable);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        cout<<"SDL_Init() failure"<<endl;
        exit(1);
    }

#ifndef __DARWIN__
    screen = SDL_SetVideoMode(ui->video->width(), ui->video->height(), 0, SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL);
#else
    screen = SDL_SetVideoMode(pCodecCtx->width, pCodecCtx->height, 24, 0);
#endif

    if(!screen){
        cout<<"screen == NULL\n";
        exit(1);
    }

    av_register_all();//注册库中含有的所有可用的文件格式和编码器，当打开一个文件时，能够自动选择相应的文件格式和编码器
    pFormatCtx = av_alloc_format_context();//给pFormatCtx分配内存
    if (!pFormatCtx){
        cout<<"av_alloc_format_context() failure"<<endl;
        exit(-1);
    }

    char *filename = "1.264";
    if(av_open_input_file(&pFormatCtx, filename, NULL, 0, NULL)!=0){// 打开视频文件
        cout<<"av_open_input_file() failure"<<endl;
        exit(-1);
    }


    if(av_find_stream_info(pFormatCtx)<0){//取出包含在文件中的流信息
        cout<<"av_find_stream_info() failure"<<endl;
        exit(-1);
    }

    dump_format(pFormatCtx, 0, filename, 0);//把获取到得参数全部输出

    int videoStream = -1;
    for(int i=0; i < (int)(pFormatCtx->nb_streams); i++){
        if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO && videoStream<0)//找到视频流
            videoStream=i;
        break;
    }

    if(videoStream==-1){
        cout<<"videoStream = -1\n";
        exit(-1);
    }
    pCodecCtx=pFormatCtx->streams[videoStream]->codec;

    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);//寻找解码器

    if(pCodec==NULL){
        cout<<"pCodec == NULL\n";
        exit(-1);
    }

    if(avcodec_open(pCodecCtx, pCodec)<0){//打开解码器
        cout<<"cannot open accodec\n";
        exit(-1);
    }
}

void MainWindow::loseNumChange(int num)
{
    lose_num = num;
    QString lose;
    QTextStream(&lose)<<num<<"%";
    ui->loseNum->setText(lose);
}

void MainWindow::loseNum1Change(int num)
{
    lose_num1 = num;
    QString lose;
    QTextStream(&lose)<<num<<"%";
    ui->loseNum1->setText(lose);
}

void MainWindow::decodeRateChanged(float num)
{
    QString rate;
    num *= 100;
    rate.sprintf("%.1f%s",num,"%");
    ui->decodeRate->setText(rate);
}


