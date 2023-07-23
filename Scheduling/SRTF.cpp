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

void waitingTime(Process processes[], int n, int wt[])
{
    int remainingTime[n];

    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burst;

    int currentTime = 0, completedTasks = 0, shortestTask = 0, minBurst = INT_MAX, finishTime = 0;
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
            finishTime = currentTime + 1;
            taskActive = false;
            wt[shortestTask] = finishTime - processes[shortestTask].arrival - processes[shortestTask].burst;
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
