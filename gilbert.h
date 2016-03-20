struct EBR_data{
	float P_bg;
	float P_gb;
};

extern int lost_cnt;
extern float P_b;
extern int L_b;

void calcute(struct EBR_data *, float, int);
int gilbert(void *, int, FILE *, int, long);

