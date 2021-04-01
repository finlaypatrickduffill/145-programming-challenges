#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <curses.h>
#include <math.h>

int opcode_ptr[3],stack_ptr;

typedef struct arith{
int arithmetic_set[20], arithmetic_opptr, arithmetic_ptr;
}arith;

typedef struct threading_struct{
	int arith[2];
	int operator_thread;
} threading_struct;

typedef struct st_task_queue{
	int arith_1[15];
	int arith_2[15];
	int arith_operator[15];
} st_task_queue;

typedef struct st_out{
	int out[15];
} st_out;

arith arith_t;
threading_struct threading_t[15];
st_task_queue tqueue;
st_out stout;

#define OP_ADD 1 
#define OP_SUBTRACT 2
#define OP_MULTIPLY 3
#define EACH_THREADS 15

void *prod_queue(void *taskcqe){
   long tid;
   int thread_id;
	while (1) {
	if (stack_ptr>15)
	{
	stack_ptr=0;
	}
		tid = (long)taskcqe;
		thread_id = (int)taskcqe;
	if (stack_ptr<16){
		opcode_ptr[1] = rand()%19+1;
		opcode_ptr[2] = rand()%19+1;
		opcode_ptr[3] = rand()%2+1;
		threading_t[thread_id].arith[1] = opcode_ptr[1];
		threading_t[thread_id].arith[2] = opcode_ptr[2];
		threading_t[thread_id].operator_thread = opcode_ptr[3];
		tqueue.arith_1[stack_ptr] = threading_t[thread_id].arith[1];
		tqueue.arith_2[stack_ptr] = threading_t[thread_id].arith[2];
		tqueue.arith_operator[stack_ptr] = threading_t[thread_id].operator_thread;
		
		if (stack_ptr!=15)
		{stack_ptr++;}
	}
	fseek(stdin,0,SEEK_END);
	}
}

void *task_queue(void *taskcqe){
   long tid;
   int thread_id;
   char char_a = 'N';
   	while (1) {
	if (stack_ptr>15)
	{
	stack_ptr=0;
	}
		tid = (long)taskcqe;
		thread_id = (int)taskcqe;
	if (stack_ptr>=2)
	{
	if ( tqueue.arith_operator[thread_id] == OP_MULTIPLY )
	{
		stout.out[stack_ptr] = tqueue.arith_1[stack_ptr] * tqueue.arith_2[stack_ptr];
		char_a = '*';
	}
	if ( tqueue.arith_operator[thread_id] == OP_ADD)
	{
		stout.out[stack_ptr] = tqueue.arith_1[stack_ptr] + tqueue.arith_2[stack_ptr];
		char_a = '+';
	}
	if ( tqueue.arith_operator[thread_id] == OP_SUBTRACT )
	{
		stout.out[stack_ptr] = tqueue.arith_1[stack_ptr] - tqueue.arith_2[stack_ptr];
		char_a = '-';
	}
		for (int x=1;x!=16;x++)
		{
			mvprintw(x+3,15,"[%d] %d || %d\n",x,threading_t[x].arith[1], threading_t[x].arith[2]);
		}
		for (int x=1;x!=16;x++)
		{
		mvprintw(x+3,30,"%d %c %d\n",threading_t[x].arith[1], char_a, threading_t[x].arith[2]);
		if (threading_t[x].arith[1] == 0)
		{
			mvprintw(x+3,18,"NULL");
		}
		if (threading_t[x].arith[2] == 0)
		{
			mvprintw(x+3,18,"NULL");
		}
		
		}
		stack_ptr--;
	
	}
		fseek(stdin,0,SEEK_END); 
	}
}

void *cons_queue(void *taskcqe){
   long tid;
   int thread_id;
   while (1) {
	tid = (long)taskcqe;
   thread_id = (int)taskcqe;
	if (stout.out[thread_id]!=0)
	{
		for (int x=1;x!=16;x++)
		{
		mvprintw(x+3,42,"out: %d (%d | %d)\n",stout.out[x],threading_t[x].arith[1], threading_t[x].arith[2]);
		}
	if (stack_ptr>15)
	{
	stack_ptr=0;
	}
	mvprintw(1,14,"-an asynchronous producer/consumer task_cue-");
	mvprintw(2,14,"--------------------------------------------");
	mvprintw(3,6+8,"._PRODUCER_.");
	mvprintw(3,18+12,"._T_C_.");
	mvprintw(3,32+8,".____CONSUMER____.");
	mvprintw(0,0,"##############################################################################################");
	for (int m=1; m!=19;m++)
	{
	mvprintw(m+1,0,"##############");
	}
	for (int m=1; m!=19;m++)
	{
	mvprintw(m+19,0,"##############################################################################################");
	}
	for (int m=1; m!=20;m++)
	{
	mvprintw(m,58,"######################");
	}
	mvprintw(19,0,"##############_Press Q to quit____________________________");
	refresh();
	}
   fseek(stdin,0,SEEK_END); 
   }
}


void init() {
	
	initscr();
	refresh();
	PDC_set_title("Asynchronous Producer/Consumer Task Queue");
	int random,rc,vi,i;
	pthread_t threads[EACH_THREADS*3];
	srand(time(NULL));
	stack_ptr=1;
	
	for (int x=1;x!=16;x++)
	{
	rc = pthread_create(&threads[x], NULL, prod_queue, (void *)x);
	rc = pthread_create(&threads[x+15], NULL, task_queue, (void *)x);
	rc = pthread_create(&threads[x+30], NULL, cons_queue, (void *)x);
	}
	for (int x=1;x!=16;x++)
	{
	arith_t.arithmetic_set[x] = rand()%19+1;
	}
}

int main(){
	init();
	
	while (getch()!='q')
	{
		// do stuff here
	}
	return 0;
}