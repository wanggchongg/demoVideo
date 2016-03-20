#include <map>
#include <time.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gilbert.h"

long cnt_lost = 0;
//extern float global_PB;

void calcute(struct EBR_data * data, float P_b, int L_b)
{
    data->P_bg = (float)1/L_b;//1/150
    data->P_gb = (data->P_bg)*(P_b/(1-P_b));//150*（0.009/0.991)
}

int gilbert(void * EBR_data_addr, int frame_len, FILE * fd, int state, long Fnum)
{
    struct EBR_data * data;
    data = (struct EBR_data *)EBR_data_addr;
    float P_B;
    float P_BG, P_GB;
    float tmp;
    int P_GB_int, P_BG_int;
    //int L_B;
    int i;
    int ran;

    for(i = 0, tmp = 1; i < frame_len; ++i)
        tmp = tmp*(1 - data->P_gb);//（1-0.009=0.991）
    P_B = 1 - (1 - P_b)*tmp;
    //global_PB = P_B;
    if(Fnum == 1) printf(">>>>>> P_B = %lf\n", P_B);
    P_GB = 1 - (1 - data->P_gb)*tmp;
    P_BG = P_GB*(1 - P_B)/P_B;
    //L_B = 1/P_BG;

    P_GB_int = (int)(P_GB*10000);
    P_BG_int = (int)(P_BG*10000);

    ran = (int)(10000*rand()/(RAND_MAX+1.0));
    switch(state)
    {
        fprintf(fd, "%ld ", state);
        fflush(fd);
        case 0:
            if(ran <= P_GB_int)
            {
                cnt_lost++;
                if(fprintf(fd, "%ld ", Fnum) < 0)
                {
                    fprintf(fd, "error");
                    fflush(fd);
                    exit(1);
                }
                fflush(fd);
                state = 1;
                break;
            }
            else
            {
                state = 0;
                break;
            }
        case 1:
            if(ran <= P_BG_int)
            {
                state = 0;
                break;
            }
            else
            {
                cnt_lost++;
                if(fprintf(fd, "%ld ", Fnum) < 0)
                {
                    exit(1);
                }
                fflush(fd);
                state = 1;
                break;
            }
        default:
            break;
    }//switch
    //printf(">>>>>> cnt_lost: %ld, Fnum: %ld, rate: %lf%%\n", cnt_lost, Fnum, 100*double(cnt_lost)/Fnum);
    return state;
}

