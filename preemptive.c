 //q2)premptive priority  priority shedul?
 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_burst_time;
    int waiting_time;
    int turnaround_time;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, i, j, currentTime = 0;
    srand(time(NULL));

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for Process P%d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_burst_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int completed = 0;
    int quantum = 2; // Time quantum for each process

    printf("\nGantt Chart:\n");
    printf("--------------------------------------------------------------\n");
    printf("Time   |  Process\n");
    printf("--------------------------------------------------------------\n");

    while (completed < n) {
        int selected_process = -1;
        int highest_priority = 1000; // Assuming a maximum priority value

        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_burst_time > 0 && processes[i].priority < highest_priority) {
                selected_process = i;
                highest_priority = processes[i].priority;
            }
        }

        if (selected_process == -1) {
            currentTime++;
            continue;
        }

        int next_burst = rand() % 10 + 1; // Generate a random next CPU burst time

        if (next_burst > processes[selected_process].remaining_burst_time) {
            next_burst = processes[selected_process].remaining_burst_time;
        }

        printf("%02d-%02d  |  P%d\n", currentTime, currentTime + next_burst, processes[selected_process].id);
        currentTime += next_burst;
        processes[selected_process].remaining_burst_time -= next_burst;

        if (processes[selected_process].remaining_burst_time == 0) {
            completed++;
            processes[selected_process].turnaround_time = currentTime - processes[selected_process].arrival_time;
            processes[selected_process].waiting_time = processes[selected_process].turnaround_time - processes[selected_process].burst_time;
        }
    }

    printf("--------------------------------------------------------------\n");
    printf("\nTurnaround Time and Waiting Time for each process:\n");
    printf("--------------------------------------------------------------\n");
    printf("Process  |  Turnaround Time  |  Waiting Time\n");
    printf("--------------------------------------------------------------\n");

    float total_turnaround_time = 0, total_waiting_time = 0;

    for (i = 0; i < n; i++) {
        printf("P%d       |  %d                |  %d\n", processes[i].id, processes[i].turnaround_time, processes[i].waiting_time);
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    float average_turnaround_time = total_turnaround_time / n;
    float average_waiting_time = total_waiting_time / n;

    printf("--------------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);

    return 0;
}

