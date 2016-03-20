#include "display_func.h"
#define YUV_DEBUG

ShowObject::ShowObject(){
    pFrame=avcodec_alloc_frame();//给视频帧分配空间以便存储解码后的图片

    bmp = SDL_CreateYUVOverlay(pCodecCtx->width, pCodecCtx->height, SDL_YV12_OVERLAY, screen);
    img_convert_ctx = sws_getContext(pCodecCtx->width,pCodecCtx->height,pCodecCtx->pix_fmt,pCodecCtx->width,pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
    if (img_convert_ctx == NULL){
        cout<<"img_convert_ctx == NULL\n";
        exit(-1);
    }

#ifdef YUV_DEBUG
    store_v_yuv = fopen(".//test.yuv", "wb+");
    if(store_v_yuv == NULL)
    {
        printf("cannot open test.yuv\n");
        exit(1);
    }
#endif

}

ShowObject::~ShowObject(){
    SDL_FreeYUVOverlay(bmp);
    SDL_FreeSurface(screen);
    SDL_Quit();

    av_free(pFrame);
    fclose(store_v_yuv);
}


void ShowObject::dealShowVideo(){
    int frameFinished = 0;
    int decode = 0;

    int dataLength = 0;
    char *showData = NULL;

    if(s_fullShow.tryAcquire(1,0)){
        dataLength = showBuf[sigGetShow].size;
        showData = (char*)malloc((dataLength+1)*sizeof(char));
        memcpy(showData, showBuf[sigGetShow].h264node, dataLength);
        showData[dataLength] = '\0';

        s_emptyShow.release();

        sigGetShow++;
        sigGetShow %= MAXBUFSIZE;
    }

    if(showData)
    {

    }

    if(showData){
        decode = avcodec_decode_video(pCodecCtx, pFrame, &frameFinished, (const unsigned char*)showData, dataLength);
        free(showData);
        showData = NULL;
    }

    if(frameFinished > 0){
        SDL_LockYUVOverlay(bmp);
        pict.data[0] = bmp->pixels[0];
        pict.data[1] = bmp->pixels[2];
        pict.data[2] = bmp->pixels[1];

        pict.linesize[0] = bmp->pitches[0];
        pict.linesize[1] = bmp->pitches[2];
        pict.linesize[2] = bmp->pitches[1];

        sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pict.data, pict.linesize);
        SDL_UnlockYUVOverlay(bmp);

#ifdef YUV_DEBUG
            int xx, yy, zz;
            char g_yuv[(480*272)+(480*272)/2];

            for(xx=0;xx<pCodecCtx->height;xx++)
                memcpy(g_yuv+pCodecCtx->width*xx, pFrame->data[0]+pFrame->linesize[0]*xx,pCodecCtx->width);
            for(yy=0;yy<pCodecCtx->height/2;yy++)
                memcpy(g_yuv+pCodecCtx->width*xx+pCodecCtx->width/2*yy,pFrame->data[1]+pFrame->linesize[1]*yy,pCodecCtx->width/2);
            for(zz=0;zz<pCodecCtx->height/2;zz++)
                memcpy(g_yuv+pCodecCtx->width*xx+pCodecCtx->width/2*yy+pCodecCtx->width/2*zz, pFrame->data[2]+pFrame->linesize[2]*zz, pCodecCtx->width/2);

            fwrite(g_yuv, 1, (480*272)+(480*272)/2, store_v_yuv);
            fflush(store_v_yuv);
#endif

        dst.x = 0;
        dst.y = 0;
        dst.w = pCodecCtx->width;
        dst.h = pCodecCtx->height;
    }

    frameFinished = 0;

    SDL_DisplayYUVOverlay(bmp, &dst);
}


ShowThread::ShowThread(){

}

ShowThread::~ShowThread(){
    quit();
    wait();
    deleteLater();
}

void ShowThread::run(){
    ShowObject obj;
    obj.moveToThread(this);

    connect(this, SIGNAL(dataArrived()), &obj, SLOT(dealShowVideo()), Qt::BlockingQueuedConnection);

    exec();
}
