#include <stdio.h>
#include "dvrp.h"

extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

/*The link cost between node 1 and other nodes*/
int lkcost1[4] = {1, 0, 1, INFINITY};   

/*The shortest path between node 1 and other nodes*/
int spath1[4] = {INFINITY, 0, INFINITY, INFINITY}; 

// Connections to Node 1
int connection1[4] = {1, 0, 1, 0};

/*define distance table*/
struct distance_table 
{
    int costs[4][4];
} dt1;

/**** Declarations internal to node1  ****/
void printdt1(struct distance_table *dtptr);

// Packet that holds the minimum distances
struct rtpkt rtpkt1;

/* students to write the following two routines, and maybe some others */
void rtinit1() 
{
    int i;

    printf("Node1 Initialization at t = %f\n", clocktime);

    for(i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if((connection1[i] == 1) && (i == j))
                dt1.costs[i][j] = lkcost1[i];
            else
                dt1.costs[i][j] = INFINITY;
        }

    rtpkt1.sourceid = 1;
    for (i = 0; i < 4; i++)
        rtpkt1.mincost[i] = lkcost1[i];

    for (i = 0; i < 4; i++)
    {
        if (connection1[i])
        {
            rtpkt1.destid = i;
            tolayer2(rtpkt1);
        }
    }
    printdt1(&dt1);
}

void rtupdate1(struct rtpkt *rcvdpkt)
{
    int i, tempPath, update = 0;
    int sourceid = rcvdpkt->sourceid;

    printf("rtupdate1 called at t = %f\n", clocktime);
    printf("Node 1 is receiving a packet from Node %d\n", rcvdpkt->sourceid);

    for (i = 0; i < 4; i++)
    {
        if (i != 1)
        {
            tempPath = lkcost1[sourceid] + rcvdpkt->mincost[i];
            if (tempPath < dt1.costs[i][sourceid])
            {
                dt1.costs[i][sourceid] = tempPath;
            }
            if (tempPath < spath1[i])
            {
            update = 1;
            spath1[i] = update;
            }
        }
    }

    if (update)
    {
        printf("Table Node 1 updated\n");
        printdt1(&dt1);
        rtpkt1.sourceid = 1;
        for (i = 0; i < 4; i++)
        {
            if (connection1[i])
            {
                rtpkt1.destid = i;
                for(int j = 0; j < 4; j++)
                    rtpkt1.mincost[j] = spath1[j];
                tolayer2(rtpkt1);
            }
        }
    }
    else
    {
        printf("Table Node 1 did not update\n");
        printdt1(&dt1);
    }
}

void printdt1(struct distance_table *dtptr)
{
    printf("                via     \n");
    printf("   D1 |    0     2 \n");
    printf("  ----|-----------------\n");
    printf("     0|  %3d   %3d \n", dtptr->costs[0][0], dtptr->costs[0][2]);
    printf("dest 2|  %3d   %3d \n", dtptr->costs[2][0], dtptr->costs[2][2]);
    printf("     3|  %3d   %3d \n", dtptr->costs[3][0], dtptr->costs[3][2]);
}

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're not doing the extra credit. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in dvrp.c from 0 to 1 */ 
void linkhandler1(int linkid, int newcost)   
{ 
    dt1.costs[1][linkid] = newcost;
    rtpkt1.sourceid = 1;
    rtpkt1.destid = 1;
    rtpkt1.mincost[linkid] = newcost;
    tolayer2(rtpkt1);
    rtpkt1.destid = 2;
    tolayer2(rtpkt1);
}
