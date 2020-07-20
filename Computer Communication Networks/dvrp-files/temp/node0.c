#include <stdio.h>
#include "dvrp.h"

extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

/*The link cost between node 0 and other nodes*/
int lkcost0[4] = {0, 1, 3, 7};		

/*The shortest path between node 0 and other nodes*/
int spath0[4]= {0, INFINITY, INFINITY, INFINITY};	

// Connections to Node 0
int connection0[4] = {0, 1, 1, 1}; 

/*Define distance table*/
struct distance_table 		
{
	int costs[4][4];
} dt0;

/**** Declarations internal to node0  ****/
void printdt0(struct distance_table *dtptr);

// Packet that holds the minimum distances
struct rtpkt rtpkt0;	

/* students to write the following two routines, and maybe some others */
void rtinit0() 
{
	int i;

	printf("Node0 Initialization at t = %f\n", clocktime);

    for(i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if((connection0[i] == 1) && (i == j))
                dt0.costs[i][j] = lkcost0[i];
            else
                dt0.costs[i][j] = INFINITY;
        }


	rtpkt0.sourceid = 0;
    for (i = 0; i < 4; i++)
        rtpkt0.mincost[i] = lkcost0[i];

    for (i = 0; i < 4; i++)
    {
        if (connection0[i])
        {
            rtpkt0.destid = i;
            tolayer2(rtpkt0);
        }
    }
    printdt0(&dt0);
}

void rtupdate0(struct rtpkt *rcvdpkt)
{
	int i, tempPath, update = 0;
	int sourceid = rcvdpkt->sourceid;

    printf("rtupdate0 called at t = %f\n", clocktime);
    printf("Node 0 is receiving a packet from Node %d\n", sourceid);

	for (i = 0; i < 4; i++)
	{
		if (i != 0)
		{
	        tempPath = lkcost0[sourceid] + rcvdpkt->mincost[i];
	        if (tempPath < dt0.costs[i][sourceid])
	        {
	            dt0.costs[i][sourceid] = tempPath;
	        }
	        if (tempPath < spath0[i])
	        {
	        	update = 1;
	        	spath0[i] = update;
	        }
    	}
	}

	rtpkt0.sourceid = 0;

	for(i = 0; i < 4; i++)
	    rtpkt0.mincost[i] = spath0[i];

	if (update)
	{
		printf("Table Node 0 updated\n");
		
		printdt0(&dt0);

        for (i = 0; i < 4; i++)
        {
            if (connection0[i])
            {
                rtpkt0.destid = i;
                tolayer2(rtpkt0);
            }
        }
	}
	else
	{
		printf("Table Node 0 did not update\n");
    	printdt0(&dt0);
	}
}

void printdt0(struct distance_table *dtptr)
{
	printf("                via     \n");
	printf("   D0 |    1     2    3 \n");
	printf("  ----|-----------------\n");
	printf("     1|  %3d   %3d   %3d\n", dtptr->costs[1][1], dtptr->costs[1][2], dtptr->costs[1][3]);
	printf("dest 2|  %3d   %3d   %3d\n", dtptr->costs[2][1], dtptr->costs[2][2], dtptr->costs[2][3]);
	printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][1], dtptr->costs[3][2], dtptr->costs[3][3]);
}

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're not doing the extra credit. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in dvrp.c from 0 to 1 */
void linkhandler0(int linkid, int newcost)
{
    dt0.costs[0][linkid] = newcost;
	rtpkt0.sourceid = 0;
    rtpkt0.destid = 1;
    rtpkt0.mincost[linkid] = newcost;
    tolayer2(rtpkt0);
    rtpkt0.destid = 2;
    tolayer2(rtpkt0);
    rtpkt0.destid = 3;
    tolayer2(rtpkt0);
}
