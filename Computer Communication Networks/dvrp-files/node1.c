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
	int row, column;
    printf("At t=%.3f, rtinit1() is called\n", clocktime);

    for(row = 0; row < 4; row++)
        for(column = 0; column < 4; column++)
            if(connection1[row] && row == column)
                dt1.costs[row][column] = lkcost1[row];
            else
                dt1.costs[row][column] = INFINITY;

	printdt1(&dt1);

    rtpkt1.sourceid = 1;

    for(row = 0; row < 4; row++)
        rtpkt1.mincost[row] = lkcost1[row];

    for(row = 0; row < 3; row++)
        if(connection1[row])
        {
            rtpkt1.destid = row;
            printf("At time t=%.3f, Node 1 sends packet to Node %d\n", clocktime, row);
            tolayer2(rtpkt1);
        }
}


void rtupdate1(struct rtpkt *rcvdpkt)
{
	int sourceid = rcvdpkt->sourceid;
	int node, tempPath, update = 0;

    printf("At time t=%.3f, rtupdate1() called. Node 1 receives a packet from Node %d\n", clocktime, sourceid);
    
    for(node = 0; node < 4; node++)
    {
        if(node != 1)
        {
            tempPath = lkcost1[sourceid] + rcvdpkt->mincost[node];
            if(tempPath < dt1.costs[node][sourceid])
            {
                dt1.costs[node][sourceid] = tempPath;
	            if(tempPath < spath1[node])
	            {
	                update = 1;
	                spath1[node] = tempPath;
	            }
        	}
        }
    }

    rtpkt1.sourceid = 1;

	for(node = 0; node < 4; node++)
	    rtpkt1.mincost[node] = spath1[node];

    if(update)
    {
        printdt1(&dt1);
        for(node = 0; node < 3; node++)
            if(connection1[node])
            {
                rtpkt1.destid = node;
            	printf("At time t=%.3f, Node 1 sends packet to Node %d\n", clocktime, node);
                tolayer2(rtpkt1);
            }
    	printf("\n");
    }
    else
		printdt1(&dt1);
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

void linkhandler1(int linkid, int newcost)   
/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're not doing the extra credit. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in dvrp.c from 0 to 1 */	
{
    int row;
    printf("At t=%.3f, linkhandler1() is called\n", clocktime);

    rtpkt1.sourceid = 1;

    for(row = 0; row < 4; row++)
    {
        dt1.costs[row][linkid] += newcost;
        rtpkt1.mincost[linkid] += newcost;
    }

    for(row = 0; row < 3; row++)
        if(connection1[row])
        {
            rtpkt1.destid = row;
            printf("At time t=%.3f, Node 1 sends packet to Node %d\n", clocktime, row);
            tolayer2(rtpkt1);
        }
    printdt1(&dt1);
}
