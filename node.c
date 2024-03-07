#include "node.h"
#define GRIDSIZE 4

void updatePathCost(struct distance_table *table, struct rtpkt *pkt,bool *changed);

//Intitialize table
void rtinit(struct distance_table *table, int node) {
    for (int i = 0; i < GRIDSIZE; i++) {
        if (is_neighbor(node, i)) {
            struct rtpkt pkt = { .sourceid = node, .destid = i };
            for (int j = 0; j < GRIDSIZE; j++) {
                pkt.mincost[j] = table->costs[node][j];
            }
            tolayer2(pkt);
        }
    }
}

//Update current table
void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
    bool changed = false;
    //Update pathcost
	updatePathCost(table, pkt, &changed);

	//if changed call rinit again
    if (changed) {
        rtinit(table, node);
        printdt(table, node);
    }
}

//Functtion to check and update node paths
void updatePathCost(struct distance_table *table, struct rtpkt *pkt, bool *changed) {
    for(int i = 0; i < GRIDSIZE; i++) {
        if(table->costs[pkt->sourceid][i] == INF) {
            table->costs[pkt->sourceid][i] = pkt->mincost[i];
            *changed = true;
        }
        for (int j = 0; j < GRIDSIZE; j++) {
            if(pkt->mincost[j] + table->costs[i][pkt->sourceid] < table->costs[i][j]) {
                table->costs[i][j] = pkt->mincost[j] + table->costs[i][pkt->sourceid];
                *changed = true; 
            }
        }
    }
}

