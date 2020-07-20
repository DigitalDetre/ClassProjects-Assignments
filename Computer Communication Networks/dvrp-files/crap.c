#include <stdio.h>

extern struct rtpkt
{
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
};

extern int TRACE;
extern int YES;
extern int NO;
struct rtpkt rtpkt0;

struct distance_table
{
  int costs[4][4];
} dt0;


void rtinit0()
{
  dt0.costs[1][1]=1;   dt0.costs[1][2]=999; dt0.costs[1][3]=999;
  dt0.costs[2][1]=999; dt0.costs[2][2]=3;   dt0.costs[2][3]=999;
  dt0.costs[3][1]=999; dt0.costs[3][2]=999; dt0.costs[3][3]=7;
  printdt0(&dt0);
  rtpkt0.mincost[0]=0;
  rtpkt0.mincost[1]=1;
  rtpkt0.mincost[2]=3;
  rtpkt0.mincost[3]=7;
  rtpkt0.sourceid=0;
  rtpkt0.destid=1;
  tolayer2(rtpkt0);
  rtpkt0.destid=2;
  tolayer2(rtpkt0);
  rtpkt0.destid=3;
  tolayer2(rtpkt0);
}

void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int i,costs;
  if(rcvdpkt->sourceid==1 || 2 || 3)
{
  for(i=0; i<4; i++)
   if(rcvdpkt->mincost[i]!=999 || rcvdpkt->destid!=i)
   {     
costs=dt0.costs[rcvdpkt->sourceid][rcvdpkt->sourceid]+rcvdpkt->mincost[i];
       if (costs<dt0.costs[i][rcvdpkt->sourceid])
	   {
		 dt0.costs[i][rcvdpkt->sourceid]=costs;
		 if(costs<rtpkt0.mincost[i])
		 {
           rtpkt0.mincost[i]=costs;
           rtpkt0.sourceid=0;
           rtpkt0.destid=1;
           tolayer2(rtpkt0);
           rtpkt0.destid=2;
           tolayer2(rtpkt0);
           rtpkt0.destid=3;
           tolayer2(rtpkt0);
		 }
	   }
   }
  }
  printdt0(&dt0);
}

printdt0(dtptr)
struct distance_table *dtptr;
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}
#include <stdio.h>



extern int TRACE;
extern int YES;
extern int NO;

int connectcosts1[4] = { 1,  0,  1, 999 };
struct rtpkt rtpkt1;


struct distance_table
{
  int costs[4][4];
} dt1;

struct distance_table *d_t1;


rtinit1()
{
  dt1.costs[0][0]=1;   dt1.costs[0][2]=999;
  dt1.costs[2][0]=999; dt1.costs[2][2]=1;
  dt1.costs[3][0]=999; dt1.costs[3][2]=999;
  printdt1(&dt1);
  rtpkt1.mincost[0]=1;
  rtpkt1.mincost[1]=0;
  rtpkt1.mincost[2]=1;
  rtpkt1.mincost[3]=999;
  rtpkt1.sourceid=1;
  rtpkt1.destid=0;
  tolayer2(rtpkt1);
  rtpkt1.destid=2;
  tolayer2(rtpkt1);
}












rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;

{
  int i,costs;
  if(rcvdpkt->sourceid==0 || 2)
 {
  for(i=0; i<4; i++)
   if(rcvdpkt->mincost[i]!=999 || rcvdpkt->destid!=i)

   {
       
costs=dt1.costs[rcvdpkt->sourceid][rcvdpkt->sourceid]+rcvdpkt->mincost[i];
       if (costs<dt1.costs[i][rcvdpkt->sourceid])
	   {
	    dt1.costs[i][rcvdpkt->sourceid]=costs;
        if(costs<rtpkt1.mincost[i])
		 {
           rtpkt1.mincost[i]=costs;
           rtpkt1.sourceid=1;
           rtpkt1.destid=0;
           tolayer2(rtpkt1);
           rtpkt1.destid=2;
           tolayer2(rtpkt1);
		 }
	   }
   }
  }
  printdt1(&dt1);
}


printdt1(dtptr)
  struct distance_table *dtptr;

{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}
#include <stdio.h>



extern int TRACE;
extern int YES;
extern int NO;

struct rtpkt rtpkt2;

struct distance_table
{
  int costs[4][4];
} dt2;


void rtinit2()
{
  dt2.costs[0][0]=3;   dt2.costs[0][1]=999; dt2.costs[0][3]=999;
  dt2.costs[1][0]=999; dt2.costs[1][1]=1;   dt2.costs[1][3]=999;
  dt2.costs[3][0]=999; dt2.costs[3][1]=999; dt2.costs[3][3]=2;
  printdt2(&dt2);
  rtpkt2.mincost[0]=3;
  rtpkt2.mincost[1]=1;
  rtpkt2.mincost[2]=0;
  rtpkt2.mincost[3]=2;
  rtpkt2.sourceid=2;
  rtpkt2.destid=0;
  tolayer2(rtpkt2);
  rtpkt2.destid=1;
  tolayer2(rtpkt2);
  rtpkt2.destid=3;
  tolayer2(rtpkt2);
}














void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;

{
  int i,costs;
   if(rcvdpkt->sourceid==0 || 1 || 3)
 {
  for(i=0; i<4; i++)
   if(rcvdpkt->mincost[i]!=999 || rcvdpkt->destid!=i)
   {
       
costs=dt2.costs[rcvdpkt->sourceid][rcvdpkt->sourceid]+rcvdpkt->mincost[i];
       if (costs<dt2.costs[i][rcvdpkt->sourceid])
	   {
	    dt2.costs[i][rcvdpkt->sourceid]=costs;
	    if(costs<rtpkt2.mincost[i])
		 {
           rtpkt2.mincost[i]=costs;
           rtpkt2.sourceid=2;
           rtpkt2.destid=0;
           tolayer2(rtpkt2);
           rtpkt2.destid=1;
           tolayer2(rtpkt2);
	    rtpkt2.destid=3;
           tolayer2(rtpkt2);
		 }
	   }
   }
 }
     printdt2(&dt2);
}


printdt2(dtptr)
struct distance_table *dtptr;
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}
#include <stdio.h>



extern int TRACE;
extern int YES;
extern int NO;

struct rtpkt rtpkt3;

struct distance_table
{
  int costs[4][4];
} dt3;


void rtinit3()
{
  dt3.costs[0][0]=7;   dt3.costs[0][2]=999;
  dt3.costs[1][0]=999; dt3.costs[1][2]=999;
  dt3.costs[2][0]=999; dt3.costs[2][2]=2;
  printdt3(&dt3);
  rtpkt3.mincost[0]=7;
  rtpkt3.mincost[1]=999;
  rtpkt3.mincost[2]=2;
  rtpkt3.mincost[3]=0;
  rtpkt3.sourceid=3;
  rtpkt3.destid=0;
  tolayer2(rtpkt3);
  rtpkt3.destid=2;
  tolayer2(rtpkt3);
}
















void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int i,costs;
  if(rcvdpkt->sourceid==0 || 2)
 {
  for(i=0; i<4; i++)
   if(rcvdpkt->mincost[i]!=999 || rcvdpkt->destid!=i)
   {
       
costs=dt3.costs[rcvdpkt->sourceid][rcvdpkt->sourceid]+rcvdpkt->mincost[i];
       if (costs<dt3.costs[i][rcvdpkt->sourceid])
	   {
	    dt3.costs[i][rcvdpkt->sourceid]=costs;
	    if(costs<rtpkt3.mincost[i])
		 {
           rtpkt3.mincost[i]=costs;
           rtpkt3.sourceid=3;
           rtpkt3.destid=0;
           tolayer2(rtpkt3);
           rtpkt3.destid=2;
           tolayer2(rtpkt3);
		 }
	   }
    }
  }
   printdt3(&dt3);
}


printdt3(dtptr)
struct distance_table *dtptr;
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
}
#include <stdio.h>
#include <stdlib.h>

#define LINKCHANGES 0 
/* ******************************************************************
Programming assignment 1: implementing distributed, asynchronous,
                          distance vector routing.

THIS IS THE MAIN ROUTINE.  IT SHOULD NOT BE TOUCHED AT ALL BY STUDENTS!

**********************************************************************/


/* a rtpkt is the packet sent from one routing update process to
   another via the call tolayer3() */

int TRACE = 1;             /* for my debugging */
int YES = 1;
int NO = 0;

creatertpkt( initrtpkt, srcid, destid, mincosts)
struct rtpkt *initrtpkt;
int srcid;
int destid;
int mincosts[];

{
  int i;
  initrtpkt->sourceid = srcid;
  initrtpkt->destid = destid;
  for (i=0; i<4; i++)
    initrtpkt->mincost[i] = mincosts[i];
}  


/*****************************************************************
***************** NETWORK EMULATION CODE STARTS BELOW ***********
The code below emulates the layer 2 and below network environment:
  - emulates the tranmission and delivery (with no loss and no
    corruption) between two physically connected nodes
  - calls the initializations routines rtinit0, etc., once before
    beginning emulation

THERE IS NOT REASON THAT ANY STUDENT SHOULD HAVE TO READ OR UNDERSTAND
THE CODE BELOW.  YOU SHOLD NOT TOUCH, OR REFERENCE (in your code) ANY
OF THE DATA STRUCTURES BELOW.  If you're interested in how I designed
the emulator, you're welcome to look at the code - but again, you should have
to, and you defeinitely should not have to modify
******************************************************************/

struct event {
   float evtime;           /* event time */
   int evtype;             /* event type code */
   int eventity;           /* entity where event occurs */
   struct rtpkt *rtpktptr; /* ptr to packet (if any) assoc w/ this event */
   struct event *prev;
   struct event *next;
 };
struct event *evlist = NULL;   /* the event list */

/* possible events: */
#define  FROM_LAYER2     2
#define  LINK_CHANGE     10

float clocktime = 0.000;


main()
{
   struct event *eventptr;
   
   init();
   printf("The above are initial distance tables in node 0, 1, 2, 3.\n");
   printf("Please press any key to go on with the simulation\n");
   getch();
   while (1) {
     
        eventptr = evlist;            /* get next event to simulate */
        if (eventptr==NULL)
           goto terminate;
        evlist = evlist->next;        /* remove this event from event list */
        if (evlist!=NULL)
           evlist->prev=NULL;
        if (TRACE>1) {
          printf("MAIN: rcv event, t=%.3f, at %d",
                          eventptr->evtime,eventptr->eventity);
          if (eventptr->evtype == FROM_LAYER2 ) {
	    printf(" src:%2d,",eventptr->rtpktptr->sourceid);
            printf(" dest:%2d,",eventptr->rtpktptr->destid);
            printf(" contents: %3d %3d %3d %3d\n", 
              eventptr->rtpktptr->mincost[0], eventptr->rtpktptr->mincost[1],
              eventptr->rtpktptr->mincost[2], eventptr->rtpktptr->mincost[3]);
            }
          }
        clocktime = eventptr->evtime;    /* update time to next event time */
        if (eventptr->evtype == FROM_LAYER2 ) {
            if (eventptr->eventity == 0) 
	      rtupdate0(eventptr->rtpktptr);
	     else if (eventptr->eventity == 1) 
	      rtupdate1(eventptr->rtpktptr);
	     else if (eventptr->eventity == 2) 
	      rtupdate2(eventptr->rtpktptr);
	     else if (eventptr->eventity == 3) 
	      rtupdate3(eventptr->rtpktptr);
             else { printf("Panic: unknown event entity\n"); exit(0); }
	  }
        else if (eventptr->evtype == LINK_CHANGE ) {
            if (clocktime<10001.0) {
	   //   linkhandler0(1,20);
	    //  linkhandler1(0,20);
              }
	    else   {
    	 //     linkhandler0(1,1);
	     // linkhandler1(0,1);
              }
	  }
          else
             { printf("Panic: unknown event type\n"); exit(0); }
        if (eventptr->evtype == FROM_LAYER2 ) 
          free(eventptr->rtpktptr);        /* free memory for packet, if any */
        free(eventptr);                    /* free memory for event struct   */
      }
   

terminate:
   printf("\nSimulator terminated at t=%f, no packets in medium\n", clocktime);
}



init()                         /* initialize the simulator */
{
  int i;
  float sum, avg;
  float jimsrand();
  struct event *evptr;  
  
   //printf("Enter TRACE:");
   //scanf("%d",&TRACE);
  TRACE=1;

   srand(9999);              /* init random number generator */
   sum = 0.0;                /* test random number generator for students */
   for (i=0; i<1000; i++)
      sum=sum+jimsrand();    /* jimsrand() should be uniform in [0,1] */
   avg = sum/1000.0;
   if (avg < 0.25 || avg > 0.75) {
    printf("It is likely that random number generation on your machine\n" ); 
    printf("is different from what this emulator expects.  Please take\n");
    printf("a look at the routine jimsrand() in the emulator code. Sorry. \n");
    exit(0);
    }

   clocktime=0.0;                /* initialize time to 0.0 */
   rtinit0();
   rtinit1();
   rtinit2();
   rtinit3();

   /* initialize future link changes */
  if (LINKCHANGES==1)   {
   evptr = (struct event *)malloc(sizeof(struct event));
   evptr->evtime =  10000.0;
   evptr->evtype =  LINK_CHANGE;
   evptr->eventity =  -1;
   evptr->rtpktptr =  NULL;
   insertevent(evptr);
   evptr = (struct event *)malloc(sizeof(struct event));
   evptr->evtype =  LINK_CHANGE;
   evptr->evtime =  20000.0;
   evptr->rtpktptr =  NULL;
   insertevent(evptr);    
   }
  
}

/****************************************************************************/
/* jimsrand(): return a float in range [0,1].  The routine below is used to */
/* isolate all random number generation in one location.  We assume that the*/
/* system-supplied rand() function return an int in therange [0,mmm]        */
/****************************************************************************/
float jimsrand() 
{
  double mmm = RAND_MAX;   /* largest int  - MACHINE DEPENDENT!!!!!!!!   */
  float x;                   /* individual students may need to change mmm */ 
  x = rand()/mmm;            /* x should be uniform in [0,1] */
  return(x);
}  

/********************* EVENT HANDLINE ROUTINES *******/
/*  The next set of routines handle the event list   */
/*****************************************************/
 

insertevent(p)
   struct event *p;
{
   struct event *q,*qold;

   if (TRACE>3) {
      printf("            INSERTEVENT: time is %lf\n",clocktime);
      printf("            INSERTEVENT: future time will be %lf\n",p->evtime); 
      }
   q = evlist;     /* q points to header of list in which p struct inserted */
   if (q==NULL) {   /* list is empty */
        evlist=p;
        p->next=NULL;
        p->prev=NULL;
        }
     else {
        for (qold = q; q !=NULL && p->evtime > q->evtime; q=q->next)
              qold=q; 
        if (q==NULL) {   /* end of list */
             qold->next = p;
             p->prev = qold;
             p->next = NULL;
             }
           else if (q==evlist) { /* front of list */
             p->next=evlist;
             p->prev=NULL;
             p->next->prev=p;
             evlist = p;
             }
           else {     /* middle of list */
             p->next=q;
             p->prev=q->prev;
             q->prev->next=p;
             q->prev=p;
             }
         }
}

printevlist()
{
  struct event *q;
  printf("--------------\nEvent List Follows:\n");
  for(q = evlist; q!=NULL; q=q->next) {
    printf("Event time: %f, type: %d entity: %d\n",q->evtime,q->evtype,q->eventity);
    }
  printf("--------------\n");
}


/************************** TOLAYER2 ***************/
tolayer2(packet)
  struct rtpkt packet;
  
{
 struct rtpkt *mypktptr;
 struct event *evptr, *q;
 float jimsrand(),lastime;
 int i;

 int connectcosts[4][4];

 /* initialize by hand since not all compilers allow array initilization */
 connectcosts[0][0]=0;  connectcosts[0][1]=1;  connectcosts[0][2]=3;
 connectcosts[0][3]=7;
 connectcosts[1][0]=1;  connectcosts[1][1]=0;  connectcosts[1][2]=1;
 connectcosts[1][3]=999;
 connectcosts[2][0]=3;  connectcosts[2][1]=1;  connectcosts[2][2]=0;
 connectcosts[2][3]=2;
 connectcosts[3][0]=7;  connectcosts[3][1]=999;  connectcosts[3][2]=2;
 connectcosts[3][3]=0;
    
 /* be nice: check if source and destination id's are reasonable */
 if (packet.sourceid<0 || packet.sourceid >3) {
   printf("WARNING: illegal source id in your packet, ignoring packet!\n");
   return;
   }
 if (packet.destid<0 || packet.destid >3) {
   printf("WARNING: illegal dest id in your packet, ignoring packet!\n");
   return;
   }
 if (packet.sourceid == packet.destid)  {
   printf("WARNING: source and destination id's the same, ignoring packet!\n");
   return;
   }
 if (connectcosts[packet.sourceid][packet.destid] == 999)  {
   printf("WARNING: source and destination not connected, ignoring packet!\n");
   return;
   }

/* make a copy of the packet student just gave me since he/she may decide */
/* to do something with the packet after we return back to him/her */ 
 mypktptr = (struct rtpkt *) malloc(sizeof(struct rtpkt));
 mypktptr->sourceid = packet.sourceid;
 mypktptr->destid = packet.destid;
 for (i=0; i<4; i++)
    mypktptr->mincost[i] = packet.mincost[i];
 if (TRACE>2)  {
   printf("    TOLAYER2: source: %d, dest: %d\n              costs:", 
          mypktptr->sourceid, mypktptr->destid);
   for (i=0; i<4; i++)
        printf("%d  ",mypktptr->mincost[i]);
    printf("\n");
   }

/* create future event for arrival of packet at the other side */
  evptr = (struct event *)malloc(sizeof(struct event));
  evptr->evtype =  FROM_LAYER2;   /* packet will pop out from layer3 */
  evptr->eventity = packet.destid; /* event occurs at other entity */
  evptr->rtpktptr = mypktptr;       /* save ptr to my copy of packet */

/* finally, compute the arrival time of packet at the other end.
   medium can not reorder, so make sure packet arrives between 1 and 10
   time units after the latest arrival time of packets
   currently in the medium on their way to the destination */
 lastime = clocktime;
 for (q=evlist; q!=NULL ; q = q->next) 
    if ( (q->evtype==FROM_LAYER2  && q->eventity==evptr->eventity) ) 
      lastime = q->evtime;
 evptr->evtime =  lastime + 2.*jimsrand();

 
 if (TRACE>2)  
     printf("    TOLAYER2: scheduling arrival on other side\n");
 insertevent(evptr);
}