#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <limits>
using namespace std;

struct process_struct
{
	int Process_id;
	int Arrival_time;
	int Burst_time;
	int comletion_time;
	int waiting_time, turnaround_time;
	int start_time;
} ps[100];

bool comparatorAt(struct process_struct a, struct process_struct b)
{
	int x = a.Arrival_time;
	int y = b.Arrival_time;
	return x < y;
	
}
bool comparatorPID(struct process_struct a, struct process_struct b)
{
	int x = a.Process_id;
	int y = b.Process_id;
	return x < y;
}
int main()
{
	int n, index, tquanta;
	float burst_remaining[100];
	queue<int> q;
	bool visited[100] = {false}, is_first_process = true; //initially  process visitied in the queue is 0 i.e false.
	int current_time = 0;
	int completed = 0;
	float sum_tat = 0, sum_wait = 0;

	cout << fixed << setprecision(2);

	cout << "Enter total number of processes: ";
	cin >> n;

	// Taking Arrival time from the user
	for (int i = 0; i < n; i++)
	{
		cout << "\n Enter Process " << i + 1 << " Arrival Time :";
		cin >> ps[i].Arrival_time;
		ps[i].Process_id = i;
	}

	// Taking Burst time from the user
	for (int i = 0; i < n; i++)
	{
		cout << "\n Enter Process " << i+1 << " Burst Time :";
		cin >> ps[i].Burst_time;
		burst_remaining[i] = ps[i].Burst_time;
	}

	cout << "Enter time quantum :";
	cin >> tquanta;

	// sort process on the basis of arrival time in increasing order
	sort(ps, ps + n, comparatorAt);

	q.push(0); //pushing first process in queue i.e. its index
	visited[0] = true;

	while (completed != n)
	{
		index = q.front();
		q.pop();
		if (burst_remaining[index] == ps[index].Burst_time) // a process is picked for the first time
		{
			ps[index].start_time = max(current_time, ps[index].Arrival_time);
			current_time = ps[index].start_time;           
		}
		if (burst_remaining[index] - tquanta > 0)      // a process is revisited
		{
			burst_remaining[index] -= tquanta;
			current_time += tquanta;
		}
		else
		{
			current_time += burst_remaining[index]; // particular process is completed
			burst_remaining[index] = 0;
			completed++;

			ps[index].comletion_time = current_time;
			ps[index].turnaround_time = ps[index].comletion_time - ps[index].Arrival_time;
			ps[index].waiting_time = ps[index].turnaround_time - ps[index].Burst_time;

			sum_tat += ps[index].turnaround_time;
			sum_wait += ps[index].waiting_time;
		}
		// checking for the new process to be pushed to the Ready queue from input list
		for (int i = 1; i < n; i++)
		{
			if (burst_remaining[i] > 0 && ps[i].Arrival_time <= current_time && visited[i] == false)
			{
				q.push(i);
				visited[i] = true;
			}
		}
		// checking if the process on the CPU needs to be pushed to ready queue
		if (burst_remaining[index] > 0)
			q.push(index);

		// if queue is empty, just add one process from the list,whose remaining burst time >0
		if (q.empty())
		{
			for (int i = 1; i < n; i++)
			{
				if (burst_remaining[i] > 0)
				{
					q.push(i);
					visited[i] = true;
					break;
				}
			}
		}
	} // end of the while

	sort(ps,ps+n,comparatorPID);
    
	// display on Screen
	cout << "\nProcessNo.\tArrival_time\tBurst_time\tcompletion time\tTurnAround \tWaiting time\n";
	for (int i = 0; i < n; i++)
	{
		cout << ps[i].Process_id << "\t\t" << ps[i].Arrival_time << "\t\t" << ps[i].Burst_time << "\t\t" << ps[i].comletion_time
			 << "\t\t" << ps[i].turnaround_time << "\t\t" << ps[i].waiting_time << "\t\t";
		cout << endl;
	}
	cout << "\nAverage Turn Around time is :" << (float)sum_tat / n;
	cout << "\nAverage Waiting time is :" << (float)sum_wait / n;
	cout << endl;

	return 0;
}
