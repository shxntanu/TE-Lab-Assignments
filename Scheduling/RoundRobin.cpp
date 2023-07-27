/*
Author: Shantanu Wable
*/

#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    int id;
    int burst;
    int arrival;
};

void waitingTime( Process processes[], int n, int ts, int wt[], int ct[], int tat[] ) {
    queue<int> RQ;
    int currentTime = 0, completedTasks = 0;
    int remainingTime[n];
    int curr;

    for(int j=0;j<n;j++) {
        if(processes[j].arrival <= currentTime) {
            RQ.push(j);
        }
    }

    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burst;


    while(completedTasks != n) {
        curr = RQ.front();
        RQ.pop();

        int cntr =0;
        while(cntr != ts && cntr != remainingTime[curr]) {
            currentTime++;
            cntr++;
            for(int j=0;j<n;j++) {
                if(processes[j].arrival == currentTime)
                    RQ.push(j);
            }
            queue<int> TQ = RQ;
            while(!TQ.empty()) {
                int t = TQ.front();
                TQ.pop();
                wt[t]++;
            }
        }
        remainingTime[curr] -= cntr;
        if(remainingTime[curr] == 0) {
            ct[curr] = currentTime;
            tat[curr] = ct[curr] - processes[curr].arrival;

            completedTasks++;
        }
        else 
            RQ.push(curr);
    }
}

int main() {
    Process proc[] = { {1, 8, 0 }, {2, 2, 5}, {3, 7, 1 }, {4, 3, 6}, {5, 5, 8} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];
    for(int i=0;i<n;i++)
        wt[i] = 0;

    waitingTime(proc, n, 3, wt, ct, tat);

    cout.width(5);
    cout<<"ID";
    cout.width(5);
    cout<<"AT";
    cout.width(5);
    cout<<"BT";
    cout.width(5);
    cout<<"CT";
    cout.width(5);
    cout<<"TAT";
    cout.width(5);
    cout<<"WT"<<endl;

    for(int i=0;i<n;i++) {
        cout.width(5);
        cout<<proc[i].id;
        cout.width(5);
        cout<<proc[i].arrival;
        cout.width(5);
        cout<<proc[i].burst;
        cout.width(5);
        cout<<ct[i];
        cout.width(5);
        cout<<tat[i]; 
        cout.width(5);
        cout<<wt[i]<<endl;
    }     

    return 0;
}
