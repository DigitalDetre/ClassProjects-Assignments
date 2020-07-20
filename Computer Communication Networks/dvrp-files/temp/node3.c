#include <stdio.h>
#include "dvrp.h"

extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

/*The link cost between node 3 and other nodes*/
int lkcost3[4] = {7, INFINITY, 2, 0};       

/*The shortest path between node 3 and other nodes*/
int spath3[4] = {INFINITY, INFINITY, INFINITY, 0};    

// Connections to Node 3
int connection3[4] = {1, 0, 1, 0};   

/*define distance table*/
struct distance_table 
{
    int costs[4][4];
} dt3;

/**** Declarations internal to node3  ****/
void printdt3(struct distance_table *dtptr);

// Packet that holds the minimum distances
struct rtpkt rtpkt3;

/* students to write the following two routines, and maybe some others */
void rtinit3() 
{
    int i;

    printf("Node3 Initialization at t = %f\n", clocktime);

    for(i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if((connection3[i] == 1) && (i == j))
                dt3.costs[i][j] = lkcost3[i];
            else
                dt3.costs[i][j] = INFINITY;
        }

    rtpkt3.sourceid = 3;

    for (i = 0; i < 4; i++)
        rtpkt3.mincost[i] = lkcost3[i];

    for (i = 0; i < 4; i++)
    {
        if (connection3[i])
        {
            rtpkt3.destid = i;
            tolayer2(rtpkt3);
        }
    }
    printdt3(&dt3);
}

void rtupdate3(struct rtpkt *rcvdpkt)
{
    int i, tempPath, update = 0;
    int sourceid = rcvdpkt->sourceid;

    printf("rtupdate3 called at t = %f\n", clocktime);
    printf("Node 3 is receiving a packet from Node %d\n", rcvdpkt->sourceid);

    for (i = 0; i < 3; i++)
    {
        tempPath = lkcost3[sourceid] + rcvdpkt->mincost[i];
        if (tempPath < dt3.costs[i][sourceid])
        {
            dt3.costs[i][sourceid] = tempPath;
        }
        if (tempPath < spath3[i])
        {
            update = 1;
            spath3[i] = update;
        }
    }

    if (update)
    {
        printf("Table Node 3 updated\n");
        printdt3(&dt3);
        rtpkt3.sourceid = 3;
        for (i = 0; i < 4; i++)
        {
            if (connection3[i])
            {
                rtpkt3.destid = i;
                for (int j = 0; j < 4; j++)
                    rtpkt3.mincost[j] = spath3[j];
                tolayer2(rtpkt3);
            }
        }
    }
    else
    {
        printf("Table Node 3 did not update\n");
        printdt3(&dt3);
    }
}

void printdt3(struct distance_table *dtptr)
{
    printf("                via     \n");
    printf("   D3 |    0     2 \n");
    printf("  ----|-----------------\n");
    printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
    printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
    printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're not doing the extra credit. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in dvrp.c from 0 to 1 */ 
void linkhandler3(int linkid, int newcost)
{

}
