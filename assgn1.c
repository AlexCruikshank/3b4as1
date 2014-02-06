/* 
SE 3BB4, assignment 1
student name: Alex Cruikshank
student number: 1139983
file assgn1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#include "log.h"

#define high    0
#define medium  1
#define low     2

#define hpq_times   2
#define mpq_times   4

int logindex = 0;
int* logi = &logindex;

pid_t create_job(int i);
void siga_handler();   // handler for signal SIGALRM
void sigc_handler();   // handler for signal SIGCHLD
sigset_t mymask1;      // normal signal process mask when all signals are free
                       // but SIGALRM and SIGCHLD are blocked
sigset_t mymask2;      // special signal process mask when all signals are free
sigset_t jobmask;      // job signal process mask blocking all signals, leaving
                       // only SIGUSR2 unblocked
struct sigaction sa_alarm;  // disposition for SIGALRM
struct sigaction sa_chld;   // disposition for SIGCHLD

int number_of_jobs;

// TO DO
// your own data structure(s) to handle jobs and the 3 queues
// your own auxialiary variables
// END TO DO
typedef struct node
{
	
}

typedef struct queue
{
	
}

// function main ------------------------------------------------- 
int main(int argc,char** argv) {
  int i, j;
  pid_t pid;
  
//Alex: Check the number of command line arguments
  if (argc == 2) {
	//Alex: 2 arguments exist (argv[0] == name, argv[1] == input) - check that the value is appropriate
	if ((argv[1]>=3)&&(argv[1]<=6)){
	     //Alex: Values are appropriate - set the number of jobs	
	     number_of_jobs = argv[1];
	}else{ 
	     //Alex: Values are inappropriate - terminate the program and display error
	     printf("Value of the argument must be between 3 and 6");
	     break;
	}
   }else{
	//Alex: Number of arguments in incorrect - terminate the program and display error
	printf ("Incorrect number of arguments. This command takes 1 argument(s).");
	break;
   };
	
  
  create_log("assgn1.log");
  
/* TO DO
   prepare mymask1 -- SIGCHLD and SIGALRM blocked, all other signals free 
   using sigemptyset(), sigfillset(), sigaddset(), sigdelset() 
   END TO DO */
  
   //Alex: clears any signals in set of signals (mymask1)
   sigemptyset(&mymask1);
   //Alex: adds SIGCHLD and SIGALRM to set of blocked signals
   sigaddset(&mymask1,SIGCHLD);
   sigaddset(&mymask1,SIGALRM);
   //Alex: Checks that the signals in mymask1 are blocked
   if (sigprocmask(SIG_BLOCK,&mymask1,NULL)<0)
   {
	perror("Could not block the signal");
   }

 
/* TO DO
   install mymask1 as the process signal mask using sigprocmask() 
   END TO DO */

   //Alex: sets up mymask1 as the signal mask set
   sigprocmask(SIG_BLOCK,&mymask1,NULL);
  
/* TO DO
   prepare mymask2 -- all signals free 
   using sigemptyset(), sigfillset(), sigaddset(), sigdelset() 
   END TO DO */
  
   //Alex: clears any signals in the set of signals, mymask2
   sigemptyset(&mymask2);
  
/* TO DO
   prepare jobmask -- all signals blocked except SIGUSR2 
   using sigemptyset(), sigfillset(), sigaddset(), sigdelset() 
   END TO DO */

   //Alex: clears any signals in the set of signals, jobmask
   sigemptyset(&jobmask);
   //Alex: adds all signals to the set jobmask
   sigfillset(&jobmask);
   //Alex: removes SIGUSR2 from jobmask
   sigdelset(&jobmask,SIGUSR2);

/* TO DO
   prepare SIGALRM disposition sa_alarm
   its handler (sa_handler) is siga_handler()
   its signal mask (sa_mask) must block all signals
   its flags (sa_flags) must be set to SA_RESTART 
   END TO DO */

   //Alex: sets signal handler to siga_handler
   sa_alarm.sa_handler = siga_handler();
   //Alex: sets signal mask to block all signals
   sigfillset(&sa_alarm.sa_mask);
   //Alex: sets flags to SA_RESTART
   sa_alarm.sa_flags = SA_RESTART;
  
/* TO DO
   install SIGALRM disposition using sigaction() 
   END TO DO */

   //Alex: installs SIGALRM disposition
   sigaction(SIGALRM,&sa_alarm,NULL);

  
/* TO DO
   prepare SIGCHLD disposition sa_chld
   its handler (sa_handler) is sigc_handler()
   its signal mask (sa_mask) must block all signals
   its flags (sa_flags) must be set to SA_RESTART 
   END TO DO */

   //Alex: sets signal handler to sigc_handler();
   sa_chld.sa_handler = sigc_handler();
   //Alex: sets signal mask to block all signals
   sigfillset(&sa_chld.sa_mask);
   //Alex: sets flags to SA_RESTART
   sa_chld.sa_flags = SA_RESTART;


/* TO DO
   install SIGCHLD disposition using sigaction() 
   END TO DO */

   //Alex: install SIGCHLD using sigaction()
   sigaction(SIGCHLD,&sa_chld,NULL);

  // TO DO
  // create empty high-priority queue
  // create empty medium-priority queue
  // create empty low-priority queue
  // END TO DO
  
  // TO DO
  // create a data structure to keep information about jobs - PID, number of runs
  // for(i = 0; i < number_of_jobs; i++) {
  //   pid = create_job(i);
  //   save pid for job i in your data structure
  // }
  // put all jobs in the high-priority queue
  // END TO DO

  // TO DO
  // in a loop
  //    if all queues are empty
  //       record it in the log by Msg("All jobs done\n");
  //       and display it on the screen by msg("All jobs done\n");
  //       and terminate the loop
  //    "switch on" the first job from the highest-priority non-empty queue
  //    by sending it the SIGUSR1 signal (using sigsend())
  //    Record it in the log using 
  //        Msg("Switched on high-priority job %d\n",job number);  or
  //        Msg("Switched on medium-priority job %d\n",job number); or
  //        Msg("Switched on low-priority job %d\n",job number); 
  //    announce it on the screen using corresponding msg();
  //    set alarm for 1 second using alarm()
  //    switch the current signal process mask mymask1 to mymask2 while
  //    going to suspension using sigsuspend()
  //    (thus only SIGCHLD or SIGALRM will wake it up from suspension
  //    SIGCHLD indicates that the job that is currently executing just
  //    terminated, SIGALRM indicates that the time for the job currently
  //    executing is up and it must be "switched off")
  // end loop
  // END TO DO
    
  return 0;
}// end function main
  
  
// function create_job -------------------------------------------- 
pid_t create_job(int i) {
  pid_t pid;
  char argv0[10];
  char argv1[10];
  
/* TO DO
   switch process signal mask from mymask1 to jobmask 
   using sigprocmask()
   END TO DO*/
  
   //Alex: change mask to jobmask
   sigprocmask(SIG_SETMASK,&jobmask,&mymask1);
  
  if ((pid = fork()) < 0) 
    Sys_exit("fork error\n");
  if (pid == 0) { // child process
    strcpy(argv0,"job");
    sprintf(argv1,"%d",i);
    execl("job",argv0,argv1,NULL);
  }
  
  // parent process
/* TO DO
   switch process signal mask from jobmask back to mymask1 
   using sigprocmask()
   END TO DO */
  
   //Alex: reset current mask to mymask1
   sigprocmask(SIG_SETMASK,&mymask1,NULL); 

  return pid;
}// end function create_job
  
  
// function siga_handler ------------------------------------------ 
void siga_handler() {
  // TO DO
  // "switch off" the currently executing job by sending it SIGUSR2 signal
  // (using sigsend())
  // either put the job back to the queue it came from (you must count
  // how many times it has been through the queue) or "demote it" to the
  // lower-prority queue.
  // record this in the log using 
  //     Msg("Switched off high-priority job %d\n",job number); or
  //     Msg("Switched off medium-priority job %d\n",job number);
  //     Msg("Switched off low-priority job %d\n",job number);
  // announce it on the screen suing corresponding msg();
  // END TO DO 
  return;
}// end function siga_handler
  
  
// function sigc_handler ------------------------------------------ 
void sigc_handler() {
  // TO DO
  // disarm the alarm
  // record in the log that the currently executing job is done by
  // Msg("job %d done\n",job number);
  // END TO DO 
}// end function sigc_handler

// TO DO
// functions for handling your data structures
// END TO DO

