#include <iostream>
#include <stdlib.h>
using namespace std;

struct Process
{
    int Process_id;
    int Arrival_time;
    int Burst_time;
    int completion_time;
    int waiting_time, turnaround_time;
    int start_time;
} ps[100];

int findmax(int a, int b)
{
    return a > b ? a : b;
}

int comparatorAT(const void *a, const void *b)
{
    int x = ((struct Process *)a)->Arrival_time;
    int y = ((struct Process *)b)->Arrival_time;
    if (x < y)
        return -1;   // No sorting
    else if (x >= y) // = is for stable sort
        return 1;    // sort
}
int comparatorPID(const void *a, const void *b)
{
    int x = ((struct Process *)a)->Process_id;
    int y = ((struct Process *)b)->Process_id;
    if (x < y)
        return -1;   // No sorting
    else if (x >= y) // = is for stable sort
        return 1;    // sort
}

int main()
{
    int n;
    cout << "Enter total number of Processes : ";
    cin >> n;

    float sum_tat = 0, sum_wait = 0;

    // Taking Arrival time from the user
    for (int i = 0; i < n; i++)
    {
        cout << "\n Enter Process " << i+1<< " Arrival Time :";
        cin >> ps[i].Arrival_time;
        ps[i].Process_id = i + 1;
    }

    // Taking Burst time from the user
    for (int i = 0; i < n; i++)
    {
        cout << "\n Enter Process " << i+1 << " Burst Time :";
        cin >> ps[i].Burst_time;
    }

    // sort
    for (int i = 0; i < n; i++)
    {
        if (ps[i].Arrival_time == ps[i + 1].Arrival_time)
        {
            qsort((void *)ps, n, sizeof(ps[0]), comparatorPID);
        }
        else
        {
            qsort((void *)ps, n, sizeof(ps[0]), comparatorAT);
        }
    }

    // calculations
    for (int i = 0; i < n; i++)
    {
        ps[i].start_time = (i == 0) ? ps[i].Arrival_time : findmax(ps[i].Arrival_time, ps[i - 1].completion_time);
        ps[i].completion_time = ps[i].start_time + ps[i].Burst_time;
        ps[i].turnaround_time = ps[i].completion_time - ps[i].Arrival_time;
        ps[i].waiting_time = ps[i].turnaround_time - ps[i].Burst_time;

        sum_tat += ps[i].turnaround_time;
        sum_wait += ps[i].waiting_time;
    }

    // display on Screen
    cout << "\nProcess No.\tArrival_time\tCPU Burst_time\tcompletion time\tTurnAround time\tWaiting time\n";
    for (int i = 0; i < n; i++)
    {
        cout << ps[i].Process_id << "\t\t" << ps[i].Arrival_time << "\t\t" << ps[i].Burst_time << "\t\t" << ps[i].completion_time
             << "\t\t" << ps[i].turnaround_time << "\t\t" << ps[i].waiting_time << "\t\t";
        cout << endl;
    }
    cout << "\nAverage Turn Around time is :" << sum_tat / n;
    cout << "\nAverage Waiting time is :" << sum_wait / n;
    cout << endl;

    return 0;
}