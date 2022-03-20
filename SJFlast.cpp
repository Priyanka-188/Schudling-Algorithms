#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <iomanip>
using namespace std;

struct Process_struct
{
    int Process_id;
    int Arrival_time;
    int Burst_time;
    int completion_time;
    int waiting_time, turnaround_time;
    int start_time;
} ps[100];

int comparatorAT(const void *a, const void *b)
{
    int x = ((struct Process_struct *)a)->Arrival_time;
    int y = ((struct Process_struct *)b)->Arrival_time;
    if (x < y)
        return -1;   // No sorting
    else if (x >= y) // = is for stable sort
        return 1;    // sort
}
int comparatorBurstT(const void *a, const void *b)
{
    int x = ((struct Process_struct *)a)->Burst_time;
    int y = ((struct Process_struct *)b)->Burst_time;
    if (x < y)
        return -1;   // No sorting
    else if (x >= y) // = is for stable sort
        return 1;    // sort
}

int main()
{
    int n;
    bool is_completed[100] = {false}, is_first_process = true;
    int current_time = 0;

    int completed = 0; // represent no. processes completed initially

    int sum_tat = 0, sum_wait = 0;

    cout << fixed << setprecision(2);
    cout << "Enter total number of process:";
    cin >> n;

    // Taking Arrival time from the user
    for (int i = 0; i < n; i++)
    {
        cout << "\n Enter Process " << i + 1 << " Arrival Time :";
        cin >> ps[i].Arrival_time;
        ps[i].Process_id = i + 1;
    }

    // Taking Burst time from the user
    for (int i = 0; i < n; i++)
    {
        cout << "\n Enter Process " << i + 1 << " Burst Time :";
        cin >> ps[i].Burst_time;
    }

    while (completed != n)
    {
        // find process with min. burst time in ready queue at current time
        int min_index = -1;    // min_index will tell the index of the process with min. burst time
        int minimum = INT_MAX; // minimum will contain the actual CPU burst time which is min.
        for (int i = 0; i < n; i++)
        {
            if (ps[i].Arrival_time <= current_time && is_completed[i] == 0)
            {
                if (ps[i].Burst_time < minimum)
                {
                    minimum = ps[i].Burst_time;
                    min_index = i;
                }

                if (ps[i].Burst_time == minimum)
                {
                    if (ps[i].Arrival_time < ps[min_index].Arrival_time)
                    {
                        minimum = ps[i].Burst_time;
                        min_index = i;
                    }
                }
            }
        }

        if (min_index == -1) // means no process inside the ready queue
        {
            current_time++;
        }
        else
        {
            ps[min_index].start_time = current_time;
            ps[min_index].completion_time = ps[min_index].start_time + ps[min_index].Burst_time;
            ps[min_index].turnaround_time = ps[min_index].completion_time - ps[min_index].Arrival_time;
            ps[min_index].waiting_time = ps[min_index].turnaround_time - ps[min_index].Burst_time;

            sum_tat += ps[min_index].turnaround_time;
            sum_wait += ps[min_index].waiting_time;

            completed++;
            is_completed[min_index] = true;
            current_time = ps[min_index].completion_time;
            is_first_process = false;
        }
    }
    
    // display on Screen
    cout << "\nProcessNo.\tArrival_time\tBurst_time\tcompletion time\tTurnAround \tWaiting time\n";
    for (int i = 0; i < n; i++)
    {
        cout << ps[i].Process_id << "\t\t" << ps[i].Arrival_time << "\t\t" << ps[i].Burst_time << "\t\t" << ps[i].completion_time
             << "\t\t" << ps[i].turnaround_time << "\t\t" << ps[i].waiting_time << "\t\t";
        cout << endl;
    }
    cout << "\nAverage Turn Around time is :" << (float)sum_tat / n;
    cout << "\nAverage Waiting time is :" << (float)sum_wait / n;
    cout << endl;

    return 0;
}
