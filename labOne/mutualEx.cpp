/**
 * @file mutualEx.cpp
 * @author Nojus Satikauskas (C00261186)
 * @brief To demonstrate the implementation of Mutual Exclusion using Semaphores, allowing multiple threads to safely update a shared variable.
 * @date 11/10/2023
 * @copyright GPL-3.0
 */


#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \fn updateTask
    \brief An Implementation of Mutual Exclusion using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){

//Call signal
 firstSem->Wait();
  for(int i=0;i<numUpdates;i++){
    sharedVariable++;
  }
//Signal the next thread to start
firstSem->Signal();
}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore);
    std::shared_ptr<Semaphore> bSemaphore( new Semaphore);
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
      if(i == (num_threads - 1)){
        aSemaphore->Signal();
      }
      i++;
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
