
/* ******************************************************************
THIS IS THE MAIN HEADER FILE DEFINING THE API.  IT SHOULD NOT BE TOUCHED AT ALL BY STUDENTS!
**********************************************************************/

#define INFINITY 9999

/* a rtpkt is the packet sent from one routing update process to
   another via the call tolayer3() */
struct rtpkt 
{
	int sourceid;       /* id of sending router sending this pkt */
	int destid;         /* id of router to which pkt being sent 
	                     (must be an immediate neighbor) */
	int mincost[4];    /* min cost to node 0 ... 3 */
};

/************************** TOLAYER2 ***************/
void tolayer2(struct rtpkt packet);


void rtinit0();
void rtinit1();
void rtinit2();
void rtinit3();

void rtupdate0(struct rtpkt *rcvdpkt);
void rtupdate1(struct rtpkt *rcvdpkt);
void rtupdate2(struct rtpkt *rcvdpkt);
void rtupdate3(struct rtpkt *rcvdpkt);


void linkhandler0(int linkid, int newcost);
void linkhandler1(int linkid, int newcost);
