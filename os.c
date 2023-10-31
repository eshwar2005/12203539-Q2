#include <stdio.h>

#define MAX_PROCESSES 100

int main() {
  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  int arrival_time[MAX_PROCESSES];
  int burst_time[MAX_PROCESSES];
  int completed_time[MAX_PROCESSES] = {0};
  int total_waiting_time = 0;

  for (int i = 0; i < n; i++) {
    printf("Enter arrival time and burst time for process %d: ", i + 1);
    scanf("%d %d", &arrival_time[i], &burst_time[i]);
  }

  int current_time = 0;
  int completed = 0;

  printf("\nPriority Calculation:\n");

  while (completed != n) {
    int idx = -1;
    double max_priority = -1;

    for (int i = 0; i < n; i++) {
      if (arrival_time[i] <= current_time && completed_time[i] == 0) {
        double priority = 1.0 + (double)(current_time - arrival_time[i]) / burst_time[i];
        if (priority > max_priority) {
          max_priority = priority;
          idx = i;
        }
      }
    }

    if (idx != -1) {
      printf("Priority of P%d: %lf\n", idx + 1, max_priority);
      completed_time[idx] = current_time + burst_time[idx];
      total_waiting_time += current_time - arrival_time[idx];
      current_time += burst_time[idx];
      completed++;
    } else {
      current_time++;
    }
  }

  printf("\nGANTT CHART:\n");
  int i, j;
  for (i = 0; i < n; i++) {
    printf("| P%d ", i + 1);
    for (j = arrival_time[i]; j < completed_time[i]; j++) {
      printf("  |");
    }
  }
  printf("\n");

  double avg_waiting_time = (double)total_waiting_time / n;
  printf("\nAverage waiting time = %lf ms\n", avg_waiting_time);

  printf("\nIndividual waiting times:\n");
  for (int i = 0; i < n; i++) {
    int waiting_time = completed_time[i] - arrival_time[i] - burst_time[i];
    printf("P%d: %d ms\n", i + 1, waiting_time);
  }

  return 0;
}
