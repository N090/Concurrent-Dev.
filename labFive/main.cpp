// main.cpp --- 
// 
// Filename: main.cpp
// Description: 
// Author: Nojus Satikauskas C00261186
// Maintainer: Nojus Satiakuskas
// Created: Nov 17 2023
// Last-Updated: Thur Nov 24 2023
//           By: Nojus Satikauskas
// 
// 
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
//
// Code:

/*! \mainpage Concurrency Lab Five
 *
 * \section Description
 *
 * Completed version of Lab Five.
 *
 * Demonstrates a solution to the Dining Philosopher's problem
 *
 * \section p How to Run
 *
 *  main.cpp:
 *
 *  Compiled using g++, run make -k to create
 *
 *  Run ./philosophers to run the program
 *
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h>

/*! \file main.cpp
    \brief An Implementation of a solution to the Dining Philosopher's problem
*/

const int COUNT = 5;
const int THINKTIME=3;
const int EATTIME=5;
std::shared_ptr<Semaphore> footman;
std::vector<Semaphore> forks(COUNT);

/*! \fn think(int myID)
    \brief Make the thread sleep for a random amount of time in the range supplied, simulating the philosopher thinking

    \param myID The threadID of the current thread
*/
void think(int myID){
  int seconds=rand() % THINKTIME + 1;
  std::cout << myID << " is thinking! " << std::endl;
  sleep(seconds);
}

/*! \fn get_forks(int philID)
    \brief Allows a philospher to hold their fork and the next fork in sequence, forcing the last thread to arrive to wait
    \param philID The threadID of the current thread
*/
void get_forks(int philID){
  footman->Wait();     /**< The footman shared semaphore is one less than the philosopher count, blocking the last thread to arrive here */
  forks[philID].Wait();    /**< Philosopher picks up first fork */
  forks[(philID+1)%COUNT].Wait();    /**< Philosopher picks up next fork */
  std::cout << philID << " holds forks! " << std::endl;
}

/*! \fn put_forks(int philID)
    \brief Allows a philospher to put their fork and the next fork in sequence back down, making them available to other threads
    \param philID The threadID of the current thread
*/
void put_forks(int philID){
  forks[philID].Signal();   /**< Philosopher puts down first fork */
  forks[(philID+1)%COUNT].Signal();   /**< Philosopher puts down next fork */
  std::cout << philID << " releases forks! " << std::endl;
  footman->Signal();    /**< footman is signalled, unblocking the first philosopher from getting forks */
}

/*! \fn eat(int myID)
    \brief Make the thread sleep for a random amount of time in the range supplied, simulating the philosopher eating
    \param myID The threadID of the current thread
*/
void eat(int myID){
  int seconds=rand() % EATTIME + 1;
  std::cout << myID << " is chomping! " << std::endl;
  sleep(seconds);  
}

/*! \fn philosopher(int id)
    \brief Execute the think, get_forks, eat and put_forks functions until the program is stopped
    \param id The threadID of the current thread
*/
void philosopher(int id){
  while(true){
    think(id);
    get_forks(id);
    eat(id);
    put_forks(id);
  }
}

int main(void){
  srand (time(nullptr)); /**< Initialise a random seed */ 
  std::vector<std::thread> vt(COUNT);   /**< Initialise a thread of vectors to the count of philosophers */
  for (int i = 0; i < COUNT; ++i){
    forks[i].Signal();    /**< Signal each fork in the fork array to start each one in a signalled position */
  }
  footman = std::make_shared<Semaphore>(COUNT - 1);   /**< Initialise footman to a value one less than the amount of philosophers */
  int id=0;
  for(std::thread& t: vt){
    t=std::thread(philosopher,id++);    /**< Run philosopher until the program is executed */
  }
  for (auto& v :vt){
      v.join();   /**< Join the philosopher threads with the main thread */
  }
  return 0;
}
/* main.c ends here */
