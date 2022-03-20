#include <iostream>
#include <iomanip>
#include <climits>
#include <algorithm>
using namespace std;

struct Process_struct
{
    int Process_id;
    int Arrival_time;
    int Burst_time;
    int comletion_time;
    int waiting_time;
    int turnaround_time;
    int start_time;
} ps[100];

int main()
{
    int n;
    float burst_remaining[100];
    bool is_completed[100] = {false}, is_first_process = true;
    int current_time = 0;
    int completed = 0; // number of processes complete initially
    float sum_tat = 0, sum_wait = 0;

    cout << fixed << setprecision(2);

    cout << "Enter total number of processes :";
    cin >> n;

    // Taking Arrival time from the user
    for (int i = 0; i < n; i++)
    {
        cout << "\n Enter Process " << i+1 << " Arrival Time :";
        cin >> ps[i].Arrival_time;
        ps[i].Process_id = i;
    }

    // Taking Burst time from the user
    for (int i = 0; i < n; i++)
    {
        cout << "\n Enter Process " << i+1 << " Burst Time :";
        cin >> ps[i].Burst_time;
        burst_remaining[i]=ps[i].Burst_time;
    }

    while (completed != n)
    {
        // find process with minimum burst time in ready queue at the current time
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (ps->Arrival_time <= current_time && is_completed[i] == false)
            {
                if (burst_remaining[i] < minimum)
                {
                    minimum = burst_remaining[i];
                    min_index = i;
                }
                if (burst_remaining[i] == minimum)
                {
                    if (ps[i].Arrival_time < ps[min_index].Arrival_time)
                    {
                        minimum = burst_remaining[i];
                        min_index = i;
                    }
                }
            }
        }
        if (min_index == -1) //means no process inside the ready queue
        {
            current_time++;
        }
        else
        {
            if (burst_remaining[min_index] == ps[min_index].Burst_time)  // a process is picked for the first time
            {
                ps[min_index].start_time = current_time;
               // is_first_process = false;
            }

            burst_remaining[min_index] -= 1;
            current_time++;
           
            if (burst_remaining[min_index] == 0)
            {
                ps[min_index].comletion_time = current_time;
                ps[min_index].turnaround_time = ps[min_index].comletion_time - ps[min_index].Arrival_time;
                ps[min_index].waiting_time = ps[min_index].turnaround_time - ps[min_index].Burst_time;

                sum_tat += ps[min_index].turnaround_time;
                sum_wait += ps[min_index].waiting_time;
                completed++;
                is_completed[min_index] = true;
            }
        }
    }
    // display on Screen
    cout << "\nProcessNo.\tArrival_time\tBurst_time\tcompletion time\tTurnAround \tWaiting time\n";
    for (int i = 0; i < n; i++)
    {
        cout << ps[i].Process_id << "\t\t" << ps[i].Arrival_time << "\t\t" << ps[i].Burst_time << "\t\t" << ps[i].comletion_time
             << "\t\t" << ps[i].turnaround_time << "\t\t" << ps[i].waiting_time << "\t\t";
        cout << endl;
    }
    cout << "\nAverage Turn Around time is :" << sum_tat / n;
    cout << "\nAverage Waiting time is :" << sum_wait / n;
    cout << endl;

    return 0;
}