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

void waitingTime (Process processes[], int n, int wt[], int ct[], int tat[]) {
    int wait = 0;
    for(int i=0;i<n;i++) {
        wt[i] = wait - processes[i].arrival;
        ct[i] = wait + processes[i].burst;
        tat[i] = ct[i] - processes[i].arrival;
        wait += processes[i].burst;
    }

}

int main() {
    Process proc[] = { {1, 6, 2 }, {2, 2, 5}, {3, 8, 1 }, {4, 3, 0}, {5, 4, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];

    // Bubble Sort
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(proc[j].arrival > proc[j+1].arrival) {
                Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }

    for(int i=0;i<n;i++)
        cout<<"{"<<proc[i].id<<", "<<proc[i].burst<<", "<<proc[i].arrival<<"}"<<endl;

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
    return 0;
}
