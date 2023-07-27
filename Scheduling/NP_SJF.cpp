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

void npSJF (Process processes[], int n, int wt[], int ct[], int tat[]) {
    int currentTime = 0, completedTasks = 0, shortestTask = 0, minBurst = INT_MAX;
    int remainingTime[n];
    for(int i=0;i<n;i++)
        remainingTime[i] = processes[i].burst;

    while(completedTasks != n) {
        bool taskIP = false;
        for(int j=0;j<n;j++) {
            if(processes[j].arrival <= currentTime && processes[j].burst < minBurst && remainingTime[j] > 0) {
                shortestTask = j;
                minBurst = processes[shortestTask].burst;
                taskIP = true;
            }
        }

        if(!taskIP) {
            currentTime++;
            continue;
        }

        currentTime += processes[shortestTask].burst;
        remainingTime[shortestTask] = 0;
        minBurst = INT_MAX;
        completedTasks++;
        taskIP = false;
        wt[shortestTask] =  currentTime - processes[shortestTask].arrival - processes[shortestTask].burst;
        ct[shortestTask] = currentTime;
        tat[shortestTask] = ct[shortestTask] - processes[shortestTask].arrival;
    }    
}

int main() {
    Process proc[] = { {1, 6, 2 }, {2, 2, 5}, {3, 8, 1 }, {4, 3, 0}, {5, 4, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];

    npSJF(proc, n, wt, ct, tat);

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
