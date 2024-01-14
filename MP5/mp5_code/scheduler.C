/*
 File: scheduler.C
 
 Author:
 Date  :
 
 */

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "scheduler.H"
#include "thread.H"
#include "console.H"
#include "utils.H"
#include "assert.H"
#include "simple_keyboard.H"


/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   S c h e d u l e r  */
/*--------------------------------------------------------------------------*/

Scheduler::Scheduler() {
  Console::puts("Constructed Scheduler.\n");
}

void Scheduler::yield() {
  bool flag= false;
  if( Machine::interrupts_enabled()){
    flag= true;
     Machine::disable_interrupts();
  }
   
  Thread* nextThreadToRun = ready_queue.getFront();
  ready_queue.pop();

  if(!Machine::interrupts_enabled() && flag){
      Machine::enable_interrupts();
    }

  Thread :: dispatch_to(nextThreadToRun);
}

void Scheduler::resume(Thread * _thread) {
  bool flag= false;
  if( Machine::interrupts_enabled()){
    flag= true;
     Machine::disable_interrupts();
  }
  ready_queue.insert(_thread);
  if(!Machine::interrupts_enabled() && flag){
      Machine::enable_interrupts();
    }
}

void Scheduler::add(Thread * _thread) {
  bool flag= false;
  if( Machine::interrupts_enabled()){
    flag= true;
     Machine::disable_interrupts();
  }
  ready_queue.insert(_thread);
  if(!Machine::interrupts_enabled() && flag){
      Machine::enable_interrupts();
    }
}

void Scheduler::terminate(Thread * _thread) {
  bool flag= false;
  if( Machine::interrupts_enabled()){
    flag= true;
     Machine::disable_interrupts();
  }
  ready_queue.remove(_thread);
  if(!Machine::interrupts_enabled() && flag){
      Machine::enable_interrupts();
    }
}
