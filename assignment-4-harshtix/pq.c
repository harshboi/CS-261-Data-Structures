/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Harshvardhan Singh
 * Email: singhhar@oregonstate.edu
 */

 #include <stdio.h>
#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

void percolate_top_three(struct pq *);
void perlocate_down(struct pq *);

// Top most element should be the smallest in this implementation

/* Created pqueue with a dynarray inside it. the dynarray will have a pq for
 * the void data type
 * Comparisons (for Insertions) will be made by calling each specific
 * pq stored inside the void of the dynarray with subsequent logic
 * stuff being pulled after a comparison
 */

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
// struct pq{ 
//   struct dynarray *head;
//   int value;
//   struct dynarray *tail;
//   int logic;
// };

struct pq{
  struct dynarray *priorities;
  struct dynarray *backlog;
  int size;
  int act_size;
  int logic; // Defines the starting index of the priority queue
};

struct my_struct{
  void *data;
  // int value;
  int priority;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq *pqueue = malloc(sizeof(struct pq));
  pqueue->priorities = dynarray_create();
  pqueue->backlog = dynarray_create();
  pqueue->size = 0;
  pqueue->act_size = 0;
  pqueue->logic = 0;
  // pqueue->logic = 0;
  // pqueue->head = dynarray_create(/);
  // pqueue->tail = pqueue->head;
  // return(malloc(sizeof(struct pq)));'
  return pqueue;
}

void percolation(struct pq *pq){
  // int counter = 0, index = pq->size/2;
  int counter = 0, index = pq->size/2-1;
  // int counter = 0, index = pq->size-1;
  // printf("index is %d\n",index);
  
  // Nodes after the (i/2) (including) are all leafs which are self containing heaps
  while(index>0 && pq->size>0 ){
    // printf("Index %d  pq->size %d\n",index,pq->size);    
    struct my_struct *c1 = dynarray_get(pq->priorities,index);
    struct my_struct *c2 = NULL;
    struct my_struct *c3 = NULL;
    int pass = 0;
    if(2*index+1 < pq->size){
      c2 = dynarray_get(pq->priorities,2*index+1);   // Left Child
      pass = 1;
    }

    if(2*index+2 < pq->size){
      c3 = dynarray_get(pq->priorities,2*index+2);   // Right Child
      pass = 1;
    }
    
    if(pass == 1 && ((c3 == NULL || c2->priority<c3->priority) || (c3 == NULL || c2->priority == c3->priority))){  // Checks if c2 < c3 or equal
      
      if(c2->priority<c1->priority){
        struct my_struct *temp = c1;
        dynarray_set(pq->priorities,index,c2);
        dynarray_set(pq->priorities,2*index+1,c1);
      }
    }

    else if(pass == 1 && c3->priority<c2->priority){
    
      if(c3->priority<c1->priority){
        dynarray_set(pq->priorities,index,c3);
        dynarray_set(pq->priorities,2*index+2,c1);
      }
    }
    index = index/2;
    // index--;
  }
  percolate_top_three(pq);

}

void percolate_top_three(struct pq *pq){
  if(pq->size>1){
    struct my_struct *c1 = dynarray_get(pq->priorities,0);
    struct my_struct *c2 = dynarray_get(pq->priorities,1);
    struct my_struct *c3 = NULL;
    if(pq->size>2)
      c3 = dynarray_get(pq->priorities,2);
    
    if(c3 && (c2->priority < c3->priority || c2->priority == c3->priority)){
      
      if(c2->priority < c1->priority){
        dynarray_set(pq->priorities,0,c2);
        dynarray_set(pq->priorities,1,c1);
      }
    }

    else if(c3 && c3->priority < c1->priority){
      dynarray_set(pq->priorities,0,c3);        
      dynarray_set(pq->priorities,2,c1);
    }

    else if(c2->priority < c1->priority){
      dynarray_set(pq->priorities,0,c2);              
      dynarray_set(pq->priorities,1,c1);
    }
  
    // if((c1->priority < c2->priority) && c1->priority < c3->priority){
    //   // dynarray_insert(c1,0);
    //   if(c3->priority < c2->priority){
    //     dynarray_set(pq->priorities,1,c3);
    //     dynarray_set(pq->priorities,2,c2);            
    //  }
    // }
    
    // else if((c2->priority < c1->priority) && (c2->priority < c3->priority || c2->priority == c3->priority)){
    //   dynarray_set(pq->priorities,0,c2);
      
    //   if(c1->priority < c3->priority){
    //     dynarray_set(pq->priorities,1,c1);
    //     // dynarray_insert(pq->priorities,2,c3);
    //   }
      
    //   else
    //     dynarray_set(pq->priorities,1,c3);
    //     dynarray_set(pq->priorities,2,c1);
    //   }
      
    // else if((c3->priority < c1->priority) && c3->priority < c2->priority){
    //   dynarray_set(pq->priorities,0,c3);
      
    //   if(c1->priority < c2->priority){
    //     dynarray_set(pq->priorities,1,c1);
    //     dynarray_set(pq->priorities,2,c2);
    //   }
      
    //   else
    //     dynarray_set(pq->priorities,2,c1);
    // }
  }
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  printf("%d",pq->act_size);
  while(pq->act_size>0){
    struct my_struct *temp = dynarray_get(pq->backlog,0);
    dynarray_remove(pq->backlog,0);
    // free(temp->data);
    free(temp);
    pq->act_size--;
  }
  dynarray_free(pq->priorities);
  dynarray_free(pq->backlog);
  // free(pq->priorities);
  // free(pq->backlog);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if(pq->size == 0)
    return 1;
  return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq. IS A FUCKING MEMORY ADDRESS
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  struct my_struct *node = malloc(sizeof(struct my_struct));
  node->priority = priority;
  node->data = value;
  dynarray_insert(pq->priorities,pq->size++,node);
  percolation(pq);
  // dynarray_insert(pq->values,pq->size,value);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  struct my_struct *node = dynarray_get(pq->priorities,pq->logic);
  return(node->data);
  // return(dynarray_get(pq->priorities,0));
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct my_struct *node =  dynarray_get(pq->priorities,0);
  return(node->priority);
  // return 0;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  struct my_struct *node_removed = dynarray_get(pq->priorities,0);
  struct my_struct *node_replace = dynarray_get(pq->priorities,-1);
  dynarray_set(pq->priorities,0,node_replace);
  dynarray_remove(pq->priorities,-1);
  pq->size--;
  // percolation(pq);
  perlocate_down(pq);
  // percolation(pq);
  // pq->logic++;
  dynarray_insert(pq->backlog,pq->act_size++,node_removed);
  return(node_removed->data);
}

void perlocate_down(struct pq *pq){
  int index = 0;
  // printf("Priority is %d\n",c1->priority);
  
  while(index<pq->size){
    struct my_struct *c1 = dynarray_get(pq->priorities,index);   
    struct my_struct *c2 = NULL;
    struct my_struct *c3 = NULL; 
    if(pq->size > 2*index+1){
      c2 = dynarray_get(pq->priorities,2*index+1);
    
      if(pq->size > 2*index+2){
          c3 = dynarray_get(pq->priorities,2*index+2);
      }
      
      if(c3 && (c2->priority < c3->priority || c2->priority == c3->priority)){
        if(c2->priority < c1->priority){
          dynarray_set(pq->priorities,index,c2);
          dynarray_set(pq->priorities,2*index+1,c1);
          index = 2*index+1;
        }
        else
          break;
      }
      
      else if(c3 && (c3->priority < c1->priority)){
        dynarray_set(pq->priorities,index,c3);
        dynarray_set(pq->priorities,2*index+2,c1);
        index = 2*index+2;
      }
      
      else{
        if(c2->priority < c1->priority){
          dynarray_set(pq->priorities,index,c2);
          dynarray_set(pq->priorities,2*index+1,c1);
          index = 2*index+1;
        }
        else 
          break;
      }
    }
    else
      break;
    }
}