#include <stdio.h>
#include "dvrp.h"

extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

/*The link cost between node 2 and other nodes*/
int lkcost2[4] = {3, 1, 0, 2};      

/*The shortest path between node 2 and other nodes*/
int spath2[4] = {INFINITY, INFINITY, 0, INFINITY};    

// Connections to Node 2 
int connection2[4] = {1, 1, 0, 1};     

/*define distance table*/
struct distance_table 
{
    int costs[4][4];
} dt2;

/**** Declarations internal to node2  ****/
void printdt2(struct distance_table *dtptr);

// Packet that holds the minimum distances
struct rtpkt rtpkt2;

/* students to write the following two routines, and maybe some others */
void rtinit2()
{
    int i;

    printf("Node2 Initialization at t = %f\n", clocktime);

    for(i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if((connection2[i] == 1) && (i == j))
                dt2.costs[i][j] = lkcost2[i];
            else
                dt2.costs[i][j] = INFINITY;
        }

    rtpkt2.sourceid = 2;
    for (i = 0; i < 4; i++)
        rtpkt2.mincost[i] = lkcost2[i];

    for (i = 0; i < 4; i++)
    {
        if (connection2[i])
        {
            rtpkt2.destid = i;
            tolayer2(rtpkt2);
        }
    }
    printdt2(&dt2);
}

void rtupdate2(struct rtpkt *rcvdpkt)
{
    int i, tempPath, update = 0;
    int sourceid = rcvdpkt->sourceid;

    printf("rtupdate2 called at t = %f\n", clocktime);
    printf("Node 2 is receiving a packet from Node %d\n", rcvdpkt->sourceid);

    for (i = 0; i < 4; i++)
    {
        if (i != 2)
        {
            tempPath = lkcost2[sourceid] + rcvdpkt->mincost[i];
            if (tempPath < dt2.costs[i][sourceid])
            {
                dt2.costs[i][sourceid] = tempPath;
            }
            if (tempPath < spath2[i])
            {
            update = 1;
            spath2[i] = update;
            }
        }
    }

    if (update)
    {
        printf("Table Node 2 updated\n");
        printdt2(&dt2);
        rtpkt2.sourceid = 2;
        for (i = 0; i < 4; i++)
        {
            if (connection2[i])
            {
                rtpkt2.destid = i;
                for(int j = 0; j < 4; j++)
                    rtpkt2.mincost[j] = spath2[j];
                tolayer2(rtpkt2);
            }
        }
    }
    else
    {
        printf("Table Node 2 did not update\n");
        printdt2(&dt2);
    }
}

void printdt2(struct distance_table *dtptr)  
{
    printf("                via     \n");
    printf("   D2 |    0     1    3 \n");
    printf("  ----|-----------------\n");
    printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][1], dtptr->costs[0][3]);
    printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][1], dtptr->costs[1][3]);
    printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][1], dtptr->costs[3][3]);
}

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're not doing the extra credit. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in dvrp.c from 0 to 1 */ 
void linkhandler2(int linkid, int newcost)   
{

}
