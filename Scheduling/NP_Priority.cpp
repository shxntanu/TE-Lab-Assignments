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
    int priority; // Lower Number -> Higher Priority
};

void waitingTime(Process processes[], int n, int wt[], int ct[], int tat[])
{
    int remainingTime[n];

    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burst;

    int currentTime = 0, completedTasks = 0, HPT = 0, remBurst = 0, maxPriority = INT_MAX, completionTime = 0;
    bool taskActive = false;

    while(completedTasks != n) {
        for(int j=0;j<n;j++) {
            if(processes[j].arrival <= currentTime && remainingTime[j] > 0 && processes[j].priority < maxPriority) {
                HPT = j;
                maxPriority = processes[j].priority;
                taskActive = true;
            }
        }

        if(!taskActive) {
            currentTime++;
            continue;
        }

        currentTime += processes[HPT].burst;
        remainingTime[HPT] = 0;
        maxPriority = INT_MAX;
        taskActive = false;
        completedTasks++;
        wt[HPT] = currentTime - processes[HPT].arrival - processes[HPT].burst;
        ct[HPT] = currentTime;
        tat[HPT] = ct[HPT] - processes[HPT].arrival;
    }
}

int main () {
    Process proc[] = { {1, 11, 0, 2}, {2, 28, 5, 0}, {3, 2, 12, 3}, {4, 10, 2, 1}, {5, 16, 9, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];
    waitingTime(proc, n, wt, ct, tat);

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
}
