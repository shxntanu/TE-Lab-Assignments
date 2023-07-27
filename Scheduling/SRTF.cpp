/*
Author: Shantanu Wable
*/

#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int burst;
    int arrival;
};

void SRTF(Process processes[], int n, int wt[], int ct[], int tat[]) {
    int remainingTime[n];

    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burst;

    int currentTime = 0, completedTasks = 0, shortestTask = 0, minBurst = INT_MAX;
    bool taskActive = false;

    while (completedTasks != n)
    {
        for (int j = 0; j < n; j++)
        {
            if (processes[j].arrival <= currentTime && processes[j].burst < minBurst && remainingTime[j] > 0)
            {
                shortestTask = j;
                minBurst = processes[j].burst;
                taskActive = true;
            }
        }

        if (taskActive == false)
        {
            currentTime++;
            continue;
        }

        remainingTime[shortestTask]--;
        minBurst = remainingTime[shortestTask];
        if (minBurst == 0)
            minBurst = INT_MAX;

        if (remainingTime[shortestTask] == 0)
        {
            completedTasks++;
            taskActive = false;
            ct[shortestTask] = currentTime + 1;
            wt[shortestTask] = ct[shortestTask] - processes[shortestTask].arrival - processes[shortestTask].burst;
            tat[shortestTask] = ct[shortestTask] - processes[shortestTask].arrival;
            if(wt[shortestTask] < 0)
                wt[shortestTask] = 0;
        }

        currentTime++;
    }
}

int main () {
    Process proc[] = { {1, 6, 2}, {2, 2, 5}, {3, 8, 1 }, {4, 3, 0}, {5, 4, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];
    
    SRTF(proc, n, wt, ct, tat);

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
