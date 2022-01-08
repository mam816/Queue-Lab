/* 
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    // if q == Null, then the malloc did not work because there was no value
    // to use the malloc on, so just return null
    if(q == NULL){
      return NULL;
    }
    // if not then just set the head and tail to null and the size to zero to make a new empty queue
    else
    {
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */

    // if q is null, there is no way to free it, so just return 
    if(q == NULL){
     return;
    }
     
    //if head is not null put the value of it into a temporary list element and also crete another list element and put null in it
    if(q->head != NULL)
      { 
       list_ele_t *temp = q->head;
       list_ele_t *node = NULL;
     
       // while temp has value
       while(temp)
        {
	// set the empty node element to temp next basically so you can free the element you are on, but can keep track of which element comes next until you reach
	// the end of the queue structure 
         node = temp->next;
	 if(temp->value != NULL)
           {
            free(temp->value);
	   }
         free(temp);
         temp = node;
	}
      }
      // then at the end just free q
      free(q); 
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    // make a new head element	
    list_ele_t *new_head;
    /* What should you do if the q is NULL? */

    // again if q is Null, return false
    if(q == NULL){
     return false;
   }
    // if not then you malloc the size of the list element, then cast it so it can be assigned to the new head element
    new_head = (list_ele_t*)malloc(sizeof(list_ele_t));

    //if the malloc equals null, then the allocation could not be done, so return false
    if(new_head == NULL){
     return false;
    }
    /* Don't forget to allocate space for the string and copy it */       
   // char *num;
   
   // if not, then you are going to malloc the length of the char pointer s plus 1 for the null terminator, and cast and set it to the new head value
    new_head->value  = (char *)malloc(strlen(s) + 1);
   // newh->value = num;
   
   //if that malloc resulted in null, free the new head and the return false
    if(new_head->value == NULL)
     {
      free(new_head);
      return false;
     }      
   // if(!num){
     // if(newh != NULL){
      // free(newh);
     // }
    // return false;
   // }
   
   //if not, then copy the string to new head
    strcpy(new_head->value, s);


    // and if size was zero, just set both head and tail to new head and its next to null
    if(q->size == 0)
     {
      q->head = new_head;
      q->tail = new_head;
      new_head->next = NULL;
     }

    // if not the set the new heads next to the original head, then assign new head to the head value
    else
     {
       new_head->next = q->head;
       q->head = new_head;
     }
    /* What if either call to malloc returns NULL? */
   
    // the increase size by one and return true
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{   
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    // make a new tail list element
    list_ele_t *new_tail;

    //if q or the tail are Null, return false
    if(q == NULL || q->tail == NULL) 
      {
       return false;
      }
  
    //if not, malloc and cast the size of the list_ele_t and assign it to new tail
    new_tail = (list_ele_t*)malloc(sizeof(list_ele_t));

    //if the malloc returned Null, return false
    if(new_tail == NULL)
    {
     return false;
    }
   // char *num;
   
   //if not, then malloc the strlen of s plus one then assign it to the new tails value
    new_tail->value = (char *)malloc(strlen(s) + 1);
   // newt->value = num;


    // assign new tails next to null. basically the new end spot of the queue
    new_tail->next = NULL;

   //if the malloc returned null, then just free new tail and return false
    if(new_tail->value == NULL)
    {
      free(new_tail); 
      return false;
    }

    //if not then copy s into the value of the value of new tail
    strcpy(new_tail->value, s);
   
    //if head is null, then make new tail the head and and tail
    if(q->head == NULL)
    {
     q->head = new_tail;
     q->tail = new_tail;
    }

    //if not, then make the original tails next new tail and reassign the original tail to the new tail
    else
     {
     q->tail->next = new_tail;
     q->tail = new_tail;
     }

    // then increase size by one and return true
     q->size++;
     return true;

}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
 
    // if head is null, return false	
    if(q == NULL){
     return false;
    }

    //if head is null, return false
    if(q->head == NULL){
     return false;
    }

    //if sp is null also return false
    if(sp == NULL)
    {
      return false;
    }

    //if none are true
    else
    {

     // then if the bufsize is great than the length of the head value
     if(bufsize > strlen(q->head->value))
       {
       
       // then copy the value of head into sp	       
       strcpy(sp, q->head->value);
       }

     else
     {
       // so then for int a as long as its less than bufsize - 1, you assign the values in the index of a from q to the different indexes of sp 	     
       for(int a = 0; a < bufsize - 1; a++)
        {
        *(sp + a) = q->head->value[a];
	}
       // and then add a null terminator at the end
      *(sp + bufsize - 1) = '\0';
     }
    }

    //if the head value ended up being null, just return false
    if(q->head->value == NULL)
     {
      return false;
     }

    //if not, then free the head value
    else
     {
    free(q->head->value);
     }

    // then make a new list element to point to the current head 
    list_ele_t *old = q->head;

    // then make heads neaxt the new head, then free the old head, and decrease size by one
    q->head = q->head->next;
    free(old);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */


    //if q is null, just return 0, and if not just return q->size
    if(q == NULL){
    return 0;
    }
  
    else
     {  
    return q->size;
     }
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */

   //if q id null, return	
   if(q == NULL){
    return;
   }

   //if q head is null, return
   if(q->head == NULL){
    return;
   }
   
   //if size is one, return
   if(q->size == 1)
     {
      return;
     }
   
   // if not, just made three list elements, first, sec, and last 
   list_ele_t *first;
   list_ele_t *sec;
   list_ele_t *last;

   // point first to the head, sec to its next, firsts next to null
   first = q->head;
   sec = q->head->next;
   first->next = NULL;

   while(true){
    
    // set last to the next of sec, the replace that with the value of first	   
    last = sec->next;
    sec->next = first;

    // then set sec to first and last to sec
    first = sec;
    sec = last;
  
   // if sec ends up being null, then just set the head to the tail and first to the head
   if(sec == NULL) 
    {
      q->tail = q->head;
      q->head = first;
      return;
    }
   }
}
   
