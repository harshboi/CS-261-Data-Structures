/*
 * This is a small program to test your priority queue implementation.
 */

#include <stdio.h>
#include <assert.h>

#include "pq.h"

/*
 * This is the struct we'll insert into the priority queue to test it.  It
 * is a very simple representation of an operating system process.
 */
struct process {
  int pid;
};


/*
 * This is the data that will be used to test your priority queue
 * implementation.
 */
#define NUM_TEST_DATA 16
struct process TEST_DATA[NUM_TEST_DATA] = {
  { .pid = 3072 },//0
  { .pid = 1471 },//1
  { .pid = 713 },//2
  { .pid = 489 },//3
  { .pid = 1895 },//4
  { .pid = 2001 },//0
  { .pid = 2048 },//1
  { .pid = 3113 },//2
  { .pid = 32 },//3
  { .pid = 893 },//4
  { .pid = 1127 },//0
  { .pid = 2833 },//1
  { .pid = 1789 },//2
  { .pid = 3140 },//3
  { .pid = 2565 },//4
  { .pid = 440 }//0
};


int main(int argc, char** argv) {

  /*
   * Create priority queue and insert testing data with assorted priority
   * values.
   */
  struct pq* pq = pq_create();
  for (int i = 0; i < NUM_TEST_DATA; i++) {
    pq_insert(pq, &TEST_DATA[i], i % 5);
    // printf("%d\n",i%5);
  }

  /*
   * Execute some processes and put them back into the priority queue with
   * new priority values.
   */
  printf("== Executing processes in this order (priority value in parens):\n");
  for (int i = 0; i < NUM_TEST_DATA; i++) {
    int priority = pq_first_priority(pq);
    struct process* proc = pq_remove_first(pq);
    assert(proc);
    printf("  - %5d (%d)\n", proc->pid, priority);
    pq_insert(pq, proc, 4 + (i % 5));
  }

  /*
   * Finish executing the processes by draining the priority queue.
   */
  while (!pq_isempty(pq)) {
    int priority = pq_first_priority(pq);
    struct process* first = pq_first(pq);
    struct process* proc = pq_remove_first(pq);
    assert(first == proc);
    printf("  - %5d (%d)\n", proc->pid, priority);
  }

  pq_free(pq);
  return 0;

}
