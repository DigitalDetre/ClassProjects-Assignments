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
	int row, column;
    printf("At t=%.3f, rtinit2() is called\n", clocktime);

    for(row = 0; row < 4; row++)
        for(column = 0; column < 4; column++)
            if(connection2[row] && row == column)
                dt2.costs[row][column] = lkcost2[row];
            else
                dt2.costs[row][column] = INFINITY;

	printdt2(&dt2);

    rtpkt2.sourceid = 2;

	for(row = 0; row < 4; row++)
	    rtpkt2.mincost[row] = lkcost2[row];

    for(row = 0; row < 4; row++)
        if(connection2[row])
        {
            rtpkt2.destid = row;
            printf("At time t=%.3f, Node 2 sends packet to Node %d\n", clocktime, row);
            tolayer2(rtpkt2);
        }
}


void rtupdate2(struct rtpkt *rcvdpkt)
{
	int sourceid = rcvdpkt->sourceid;
	int node, tempPath, update = 0;

    printf("At time t=%.3f, rtupdate2() called. Node 2 receives a packet from Node %d\n", clocktime, sourceid);

    for(node = 0; node < 4; node++)
    {
        if(node != 2)
        {
            tempPath = lkcost2[sourceid] + rcvdpkt->mincost[node];
            if(tempPath < dt2.costs[node][sourceid])
            {
                dt2.costs[node][sourceid] = tempPath;
	            if(tempPath < spath2[node])
	            {
	            	update = 1;
	                spath2[node] = tempPath;
	            }
        	}
        }
    }

    rtpkt2.sourceid = 2;

	for(node = 0; node < 4; node++)
	    rtpkt2.mincost[node] = spath2[node];

    if(update)
    {
        printdt2(&dt2);
        for(node = 0; node < 4; node++)
            if(connection2[node])
            {
                rtpkt2.destid = node;
            	printf("At time t=%.3f, Node 2 sends packet to Node %d\n", clocktime, node);
                tolayer2(rtpkt2);
            }
        printf("\n");
    }
    else
		printdt2(&dt2);
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

void linkhandler2(int linkid, int newcost)   
/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're not doing the extra credit. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in dvrp.c from 0 to 1 */	
{
    int row;
    printf("At t=%.3f, linkhandler2() is called\n", clocktime);

    rtpkt2.sourceid = 2;

    for(row = 0; row < 4; row++)
    {
        dt2.costs[row][linkid] += newcost;
        rtpkt2.mincost[linkid] += newcost;
    }

    for(row = 0; row < 4; row++)
        if(connection2[row])
        {
            rtpkt2.destid = row;
            printf("At time t=%.3f, Node 2 sends packet to Node %d\n", clocktime, row);
            tolayer2(rtpkt2);
        }
    printdt2(&dt2);
}
