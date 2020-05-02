#ifndef __Data_H__
#define __Data_H__

typedef struct _Node {
	int nData;
	struct _Node **Link;//0:Left, 1:Right
}Node;



#endif

#define NUM_OF_LINK 2

#define LL 100
#define LR 150
#define RL 200
#define RR 250
#define CBT_LL 300
#define CBT_LR 350
#define CBT_RL 400
#define CBT_RR 450

#define TRUE 1
#define FALSE 0
#define FAIL -1
