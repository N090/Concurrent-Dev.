/**
 * @file rendezvous.cpp
 * @author Nojus Satikauskas (C00261186)
 * @brief Demonstrating the rendezvous pattern using semaphores.
 * @date 09/11/2023
 * @copyright GPL-3.0
 */
#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

//Variables to used to print "first" correctly
int arrived = 0;
int left = 0;

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, std::shared_ptr<int> threadCount)
{

    std::cout << "first " << std::endl;
    //put barrier code here
    mutexSem->Wait();
    ++arrived;
    --(*threadCount);
    if((*threadCount) == 0)
      {
        barrierSem->Signal();
      }
    mutexSem->Signal();
    barrierSem->Wait();
    mutexSem->Wait();
    ++left;
    if(left < arrived)
      {
      barrierSem->Signal();
      }
    else
      {
      // Clearing for the next run
      arrived = 0;
      left = 0;
      }
    mutexSem->Signal();
    std::cout << "second " << std::endl;
}

int main()
{
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> barrierSem;
  std::shared_ptr<int> barrier;
  int threadCount = 5;
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem=std::make_shared<Semaphore>(0);
  /*!< An array of threads*/
  std::vector<std::thread> threadArray(threadCount);
  /*!< Pointer to barrier object*/
  barrier = std::make_shared<int>(threadCount);
  for(int i=0; i < threadArray.size(); i++)
    {
    threadArray[i]=std::thread(task,mutexSem,barrierSem,barrier);
    }
  for(int i = 0; i < threadArray.size(); i++)
    {
    threadArray[i].join();
    }

  return 0;
}
