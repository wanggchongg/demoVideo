#include "decode_func.h"

Object::Object()
{
    inputBuf = NULL;
    outputBuf = NULL;
    inputBufSize = 0;
    outputBufSize = 0;

    cur_frame_no = 1;
    last_frame_no = 0;
    old_frame_no = -1;

    store_v = fopen(".//test.264", "wb+");
    if(store_v == NULL)
    {
        printf("cannot open test.264\n");
        exit(1);
    }

    list_cur = NULL;
    raptor_K_temp = 0;
    raptor_R_temp = 0;
    raptor_N_temp = 0;
    raptor_K_recieve = 0;
    raptor_R_recieve = 0;
    raptor_N_recieve = 0;

    loseRate = 0;
    rDecodeN = 100;
    rDecodeSN = 100;
    rDecodeSR = 1;

    sendSocket = new QUdpSocket;
    sendMulAddr.setAddress("239.255.1.2");

    connect(&timer, SIGNAL(timeout()), this, SLOT(dealTimeout()));
}
Object::~Object()
{
    fclose(store_v);
}

void Object::decode(){
    char *tmp_buf_total = new char[MAXLINE];
    memset(tmp_buf_total, 0, MAXLINE);

    s_fullFrame.acquire();
    memcpy(tmp_buf_total, frameBuf[sigGetFrame], MAXLINE);
    s_emptyFrame.release();
    sigGetFrame++;
    sigGetFrame %= MAXBUFSIZE;

    frameHeader = (FrameHeader_t*)malloc(sizeof(FrameHeader_t));
    memcpy((char *)frameHeader, tmp_buf_total, sizeof(FrameHeader_t));

    frameHeader->T = ntohl(frameHeader->T);
    int T_cur = frameHeader->T;
    frameHeader->slice_no = ntohl(frameHeader->slice_no);

    int data_len;
    memcpy(&data_len, tmp_buf_total+T_cur+sizeof(FrameHeader_t), 4);
    data_len = ntohl(data_len);

    if(!timer.isActive()){
        timer.start(2 * 1000);
    }

    if(loseRate)
    {
        srand(frameHeader->slice_no);
        unsigned int rand_num = rand()%100;

        if(rand_num<=loseRate)
        {
            cout << "lost packet!!!!!!!" <<endl;
            delete[] tmp_buf_total;
            tmp_buf_total = NULL;
            delete[] frameHeader;
            frameHeader = NULL;
            return;
        }
    }

    for(int i = 0; i < data_len + 1; i++)
    {
        char *frame_data = new char[T_cur+1];
        memset(frame_data, 0, T_cur+1);

        if(i == 0){
            frameHeader->frame_no = ntohl(frameHeader->frame_no);
            frameHeader->frame_type = ntohl(frameHeader->frame_type);
            frameHeader->F = ntohl(frameHeader->F);
            frameHeader->K = ntohl(frameHeader->K);
            frameHeader->R = ntohl(frameHeader->R);
            frameHeader->esi = ntohl(frameHeader->esi);

            memcpy((char *)frame_data, tmp_buf_total+sizeof(FrameHeader_t), frameHeader->T);

            if(i == data_len){
                free(tmp_buf_total);
                tmp_buf_total = NULL;
            }
        }
        else{
            (frameHeader->slice_no)++;
            (frameHeader->esi)++;

            memcpy((char *)frame_data, tmp_buf_total+i*T_cur+sizeof(FrameHeader_t)+sizeof(int), frameHeader->T);

            if(i == data_len){
                free(tmp_buf_total);
                tmp_buf_total = NULL;
            }
        }

        if(frameHeader->frame_no != cur_frame_no)//当收到的分片的帧号与预计收到的不同时 cur_frame_no 是当前应该收到的帧号
            //两种特殊情况：1.收到超前的分片 2.接收到已经过期的分片
        {
            if(frameHeader->frame_no > cur_frame_no)//情况1
            {
                last_frame_no = cur_frame_no;

                if(frameHeader->frame_type == 1)//raptor
                {
                    //printf("recount\n");
                    cur_frame_no = frameHeader->frame_no;//重新开始计数

                    //保存上一帧的相关数据计数信息
                    raptor_K_recieve = raptor_K_temp;
                    raptor_R_recieve = raptor_R_temp;
                    raptor_N_recieve = raptor_N_temp;

                    //重新计数
                    raptor_K_temp = 0;
                    raptor_R_temp = 0;

                    if(frameHeader->esi < frameHeader->K)
                        raptor_K_temp = 1;
                    else
                        raptor_R_temp = 1;
                    raptor_N_temp = 1;

                    list_temp = frameHeader->esi;
                }
                else//非raptor 直接进入解码上一帧的流程
                {
                    cur_frame_no = frameHeader->frame_no;
                }
            }
            else//情况2
            {
                //视频持续播放但是帧编号达到最大值并从0开始 或 视频回放过程中后退进度条
                if(frameHeader->frame_no <= 10)
                {
                    last_frame_no = cur_frame_no;

                    if(frameHeader->frame_type == 1)//raptor
                    {
                        //printf("recount\n");
                        cur_frame_no = frameHeader->frame_no;//重新开始计数

                        //保存上一帧的相关数据计数信息
                        raptor_K_recieve = raptor_K_temp;
                        raptor_R_recieve = raptor_R_temp;
                        raptor_N_recieve = raptor_N_temp;

                        //重新计数
                        raptor_K_temp = 0;
                        raptor_R_temp = 0;

                        if(frameHeader->esi < frameHeader->K)
                            raptor_K_temp = 1;
                        else
                            raptor_R_temp = 1;
                        raptor_N_temp = 1;

                        list_temp = frameHeader->esi;
                    }
                    else//非raptor 直接进入解码上一帧的流程
                    {
                        cur_frame_no = frameHeader->frame_no;
                    }
                }
                else//直接丢弃
                {
                    continue;
                }
            }//情况2
        }
        else//接收到预计帧的分片
        {
            if(frameHeader->frame_type == 1)//raptor
            {
                if(raptor_K_temp == K_old)
                    continue;

                if(frameHeader->esi < frameHeader->K)
                    raptor_K_temp++;
                else
                    raptor_R_temp++;
                raptor_N_temp++;

                if(!list_cur){
                    list_cur = (uint16 *)malloc(sizeof(uint16)*(frameHeader->K+frameHeader->R));
                }
                list_cur[raptor_N_temp-1] = frameHeader->esi;

                if(!inputBuf)
                {
                    int buf_size = (frameHeader->K+frameHeader->R)*T_cur;
                    inputBuf = new char[buf_size+1];
                    memset(inputBuf, 0, buf_size+1);

                    K_old = frameHeader->K;
                    R_old = frameHeader->R;
                }
                memcpy(inputBuf+(raptor_N_temp-1)*T_cur, frame_data, T_cur);

                free(frame_data);
                frame_data = NULL;

                continue;
            }
            else//非raptor
            {
                if(!outputBuf){
                        int buf_size = (frameHeader->K)*T_cur;
                        cout<<"buf_size="<<buf_size<<endl;
                        outputBuf = new char[buf_size+1];
                }

                outputBufSize = frameHeader->K*T_cur;
                memcpy(outputBuf+frameHeader->esi*T_cur, frame_data, T_cur);//将数据copy到等待加入264解码队列的输入区

                free(frame_data);
                frame_data = NULL;

                continue;//继续接收分片
            }
        }


        if(frameHeader->frame_type == 1)//raptor解码
        {
            int result_dec = 0;

            if(raptor_N_recieve > 0)
            {
                if(K_old == raptor_K_recieve && K_old)
                {
                    outputBufSize = K_old*T_cur;

                    if(outputBuf)
                    {
                        delete[] outputBuf;
                        outputBuf = NULL;
                    }
                    outputBuf = new char[outputBufSize+1];
                    memset(outputBuf, 0, outputBufSize+1);

                    memcpy(outputBuf, inputBuf, outputBufSize);
                    outputBuf[outputBufSize] = '\0';
                }
                else
                {
                    if(raptor_N_recieve > K_old)
                    {
                        rDecodeN++;
                        rDecodeN %= INT_MAX;
                        RParam_dec para = (RParam_dec)malloc(sizeof(RaptorParam_dec));

                        raptor_init(K_old, raptor_N_recieve, para);

                        for(uint32 i=0; i<raptor_N_recieve; i++)
                        {
                            para->list[i] = list_cur[i];
                        }
                        uint8 *temp = (uint8 *)malloc((para->S+para->H+raptor_N_recieve)*T_cur);
                        memset(temp, 0, (para->S+para->H+raptor_N_recieve)*T_cur);
                        memcpy(temp+(para->S+para->H)*T_cur,inputBuf, raptor_N_recieve*T_cur);

                        uint8 *output = (uint8 *)malloc(K_old*T_cur);

                        result_dec = raptor_decode(para, temp, output, T_cur);
                        if(result_dec)
                        {
                            cout<<"use raptor_decode && success"<<endl;
                            rDecodeSN++;
                            rDecodeSN %= INT_MAX;

                            if(outputBuf)
                            {
                                delete[] outputBuf;
                                outputBuf = NULL;
                            }
                            outputBufSize = K_old*T_cur;
                            outputBuf = new char[outputBufSize+1];
                            memset(outputBuf, 0, outputBufSize+1);
                            memcpy(outputBuf, output, outputBufSize);
                            outputBuf[outputBufSize] = '\0';
                        }
                        else
                        {
                            cout<<"raptor_decode error!!!"<<endl;
                            outputBufSize = (K_old+R_old)*T_cur;
                            if(outputBufSize)
                            {
                                if(outputBuf)
                                {
                                    delete[] outputBuf;
                                    outputBuf = NULL;
                                }
                                outputBuf = new char[outputBufSize+1];
                                memset(outputBuf, 0, outputBufSize+1);

                                for(uint32 i=0; i<raptor_N_recieve; i++)
                                {
                                    memcpy(outputBuf+list_cur[i]*T_cur, inputBuf+i*T_cur, T_cur);
                                }
                            }
                        }
                        raptor_parameterfree(para);
                        free(para);
                        free(output);
                        free(temp);
                        para = NULL;
                        output = NULL;
                        temp = NULL;
                    }
                    else //如果接收到的分片数不足，则将数据按esi存储进相应的位置
                    {
                        cout<<"lack of raptor_decode's slice"<<endl;
                        outputBufSize = (K_old+R_old)*T_cur;
                        if(outputBufSize)
                        {
                            if(outputBuf)
                            {
                                delete[] outputBuf;
                                outputBuf = NULL;
                            }
                            outputBuf = new char[outputBufSize+1];
                            memset(outputBuf, 0, outputBufSize+1);

                            for(uint32 i=0; i<raptor_N_recieve; i++)
                            {
                                memcpy(outputBuf+list_cur[i]*T_cur, inputBuf+i*T_cur, T_cur);
                            }
                        }
                    }
                }
            }

            delete[] inputBuf;
            inputBuf = NULL;
            inputBufSize = 0;
            K_old = 0;
            R_old = 0;

            rDecodeSR = (float)rDecodeSN/rDecodeN;
        }//raptor解码

        ///////////////////视频存储帧号可能不从1开始，因而导致视与源视频帧不对齐
        if(outputBufSize)
        {
            //qDebug()<<"frame= "<<last_frame_no<<" out_buf_size = "<<outputBufSize<<endl;

            if(s_emptyShow.tryAcquire(1,0)){
                showBuf[sigPutShow].frameNo = last_frame_no;
                showBuf[sigPutShow].size = outputBufSize;
                memset(showBuf[sigPutShow].h264node, 0, 1000000);
                memcpy(showBuf[sigPutShow].h264node, outputBuf, outputBufSize);
                showBuf[sigPutShow].h264node[outputBufSize] = '\0';
                s_fullShow.release();

                sigPutShow++;
                sigPutShow %= MAXBUFSIZE;
            }

            emit dataObjReady();

            fwrite(outputBuf, 1, outputBufSize, store_v);
            fflush(store_v);

            sendSocket->writeDatagram(outputBuf, outputBufSize, sendMulAddr, 8899);
            outputBufSize = 0;

            /*************************/
            delete[] outputBuf;
            outputBuf = NULL;
            /*************************/
        }

        //解码上一帧后，处理当前帧的第一个分片相关数据
        if(frameHeader->frame_type == 1)
        {
            if(list_cur){
                free(list_cur);
                list_cur = NULL;
            }
            list_cur = (uint16*)malloc(sizeof(uint16)*(frameHeader->K+frameHeader->R));

            list_cur[0] = list_temp;

            /************************/
            int buf_size = (frameHeader->K+frameHeader->R)*T_cur;
            inputBuf = new char[buf_size+1];
            memset(inputBuf, 0, buf_size+1);

            K_old = frameHeader->K;
            R_old = frameHeader->R;
            /************************/

            memcpy(inputBuf, frame_data, T_cur);
            inputBufSize = T_cur;

            free(frame_data);
            frame_data = NULL;
        }
        else
        {
            /************************/
            int buf_size = frameHeader->K*T_cur;//cannot frameHeader->F!!!
            outputBuf = new char[buf_size+1];
            /************************/

            outputBufSize = frameHeader->K*T_cur;
            memcpy(outputBuf+frameHeader->esi*T_cur, frame_data, T_cur);

            free(frame_data);
            frame_data = NULL;
        }
    }//for

    free(frameHeader);
    frameHeader = NULL;
}

void Object::loseRateChanged()
{
    loseRate = lose_num;
    rDecodeN = 100;
    rDecodeSN = 100;
}

void Object::dealTimeout()
{
    emit decodeRateChanged(rDecodeSR);
}

DecodeThread::DecodeThread()
{
}

DecodeThread::~DecodeThread()
{
    quit();
    wait();
    deleteLater();
}

void DecodeThread::run()
{
    Object obj;
    obj.moveToThread(this);

    connect(this, SIGNAL(dataArrived()), &obj, SLOT(decode()), Qt::BlockingQueuedConnection);
    connect(&obj, SIGNAL(dataObjReady()), this, SIGNAL(dataDecoReady()));
    connect(this, SIGNAL(loseRateChange()), &obj, SLOT(loseRateChanged()));
    connect(&obj, SIGNAL(decodeRateChanged(float)), this, SIGNAL(decodeRateChanged(float)));
    exec();
}
