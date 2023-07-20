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

void waitingTime(Process processes[], int n, int wt[])
{
    int remainingTime[n];

    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burst;

    int currentTime = 0, completedTasks = 0, shortestTask = 0, remBurst = 0, maxPriority = INT_MAX, completionTime = 0;
    bool taskActive = false;

    while (completedTasks != n)
    {
        for (int j = 0; j < n; j++)
        {
            if (processes[j].arrival <= currentTime && processes[j].priority < maxPriority && remainingTime[j] > 0)
            {
                shortestTask = j;
                maxPriority = processes[j].priority;
                taskActive = true;
            }
        }

        if (taskActive == false)
        {
            currentTime++;
            continue;
        }

        remainingTime[shortestTask]--;

        if (remainingTime[shortestTask] == 0)
        {
            completedTasks++;
            completionTime = currentTime;
            taskActive = false;
            wt[shortestTask] = completionTime - processes[shortestTask].arrival - processes[shortestTask].burst;
            if(wt[shortestTask] < 0)
                wt[shortestTask] = 0;
        }

        currentTime++;
    }
}

int main () {
    Process proc[] = { {1, 6, 2 }, {2, 2, 5}, {3, 8, 1 }, {4, 3, 0}, {5, 4, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n];
    waitingTime(proc, n, wt);
    for(int i=0;i<n;i++)
      cout<<wt[i]<<endl;
}
