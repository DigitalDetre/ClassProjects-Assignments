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
    int row, column;
    printf("At t=%.3f, rtinit0() is called\n", clocktime);
    
    for(row = 0; row < 4; row++)
        for(column = 0; column < 4; column++)
            if(connection0[row] && row == column)
                dt0.costs[row][column] = lkcost0[row];
            else
                dt0.costs[row][column] = INFINITY;

	printdt0(&dt0);

    rtpkt0.sourceid = 0;

    for(row = 0; row < 4; row++)
        rtpkt0.mincost[row] = lkcost0[row];

    for(row = 1; row < 4; row++)
        if(connection0[row])
        {
            rtpkt0.destid = row;
            printf("At time t=%.3f, Node 0 sends packet to Node %d\n", clocktime, row);
            tolayer2(rtpkt0);
        }
}


void rtupdate0(struct rtpkt *rcvdpkt)
{
	int sourceid = rcvdpkt->sourceid;
 	int node, tempPath, update = 0;

    printf("At time t=%.3f, rtupdate0() called. Node 0 receives a packet from Node %d\n", clocktime, sourceid);
    
    for(node = 1; node < 4; node++)
    {
        tempPath = lkcost0[sourceid] + rcvdpkt->mincost[node];
        if(tempPath < dt0.costs[node][sourceid])
        {
            dt0.costs[node][sourceid] = tempPath;
            if(tempPath < spath0[node])
            {
                update = 1;
                spath0[node] = tempPath;
            }
        }
    }

    rtpkt0.sourceid = 0;

	for(node = 0; node < 4; node++)
	    rtpkt0.mincost[node] = spath0[node];

    if(update)
    {
        printdt0(&dt0);
        for(node = 1; node < 4; node++)
            if(connection0[node])
            {
                rtpkt0.destid = node;
            	printf("At time t=%.3f, Node 0 sends packet to Node %d\n", clocktime, node);
                tolayer2(rtpkt0);
            }
        printf("\n");
    }
    else
		printdt0(&dt0);
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

void linkhandler0(int linkid, int newcost)   
/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're not doing the extra credit. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in dvrp.c from 0 to 1 */	
{
    int row;
    printf("At t=%.3f, linkhandler0() is called\n", clocktime);

    rtpkt0.sourceid = 0;

    for(row = 0; row < 4; row++)
    {
        dt0.costs[row][linkid] += newcost;
        rtpkt0.mincost[linkid] += newcost;
    }

    for(row = 1; row < 4; row++)
        if(connection0[row])
        {
            rtpkt0.destid = row;
            printf("At time t=%.3f, Node 0 sends packet to Node %d\n", clocktime, row);
            tolayer2(rtpkt0);
        }
    printdt0(&dt0);
}


