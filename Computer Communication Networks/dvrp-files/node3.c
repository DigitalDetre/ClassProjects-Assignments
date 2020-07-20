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
	int row, column;
    printf("At t=%.3f, rtinit3() is called\n", clocktime);

    for(row = 0; row < 4; row++)
        for(column = 0; column < 4; column++)
            if(connection3[row] && row == column)
                dt3.costs[row][column] = lkcost3[row];
            else
                dt3.costs[row][column] = INFINITY;

    printdt3(&dt3);

    rtpkt3.sourceid = 3;

	for(row = 0; row < 4; row++)
	    rtpkt3.mincost[row] = lkcost3[row];

    for(row = 0; row < 3; row++)
        if(connection3[row])
        {
            rtpkt3.destid = row;
            printf("At time t=%.3f, Node 3 sends packet to Node %d\n", clocktime, row);
            tolayer2(rtpkt3);
        }
}


void rtupdate3(struct rtpkt *rcvdpkt)
{
	int sourceid = rcvdpkt->sourceid;
	int node, tempPath, update = 0;

    printf("At time t=%.3f, rtupdate3() called. Node 3 receives a packet from Node %d\n", clocktime, sourceid);
    
    for(node = 0; node < 3; node++)
    {
        tempPath = lkcost3[sourceid] + rcvdpkt->mincost[node];
        if(tempPath < dt3.costs[node][sourceid])
        {
            dt3.costs[node][sourceid] = tempPath;
	        if(tempPath < spath3[node])
	        {
	            update = 1;
	            spath3[node] = tempPath;
	        }
    	}
    }

    rtpkt3.sourceid = 3;

	for(node = 0; node < 4; node++)
	    rtpkt3.mincost[node] = spath3[node];

    if(update)
    {
		printdt3(&dt3);
        for(node = 0; node < 3; node++)
            if(connection3[node])
            {
                rtpkt3.destid = node;
            	printf("At time t=%.3f, Node 3 sends packet to Node %d\n", clocktime, node);
                tolayer2(rtpkt3);
            }
        printf("\n");
    }
    else
		printdt3(&dt3);
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

void linkhandler3(int linkid, int newcost)   
/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're not doing the extra credit. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in dvrp.c from 0 to 1 */	
{
    int row;
    printf("At t=%.3f, linkhandler3() is called\n", clocktime);

    rtpkt3.sourceid = 3;

    for(row = 0; row < 4; row++)
    {
        dt3.costs[row][linkid] += newcost;
        rtpkt3.mincost[linkid] += newcost;
    }

    for(row = 0; row < 3; row++)
        if(connection3[row])
        {
            rtpkt3.destid = row;
            printf("At time t=%.3f, Node 0 sends packet to Node %d\n", clocktime, row);
            tolayer2(rtpkt3);
        }
    printdt3(&dt3);
}
