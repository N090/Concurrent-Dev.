/**
 * @file main.cpp
 * @author Nojus Satikauskas (C00261186)
 * @brief This main function creates at least two threads demonstrating a reusable barrier in action.
 * @date 15/11/2023
 * @copyright GPL-3.0
 */

#include "Barrier.h"
#include <thread>
#include <vector>

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<Barrier> barrierObj){

  // Each thread will execute this task multiple times
  for(int i = 0; i < 5; ++i){
    std::cout << "first " << std::endl;
    barrierObj->waitForAll();
    std::cout << "second" << std::endl;
    barrierObj->waitForAll();
  }
}

int main(void){

  /*!< An array of threads*/
  std::vector<std::thread> threadArray(5);  // Vector to store threads
  /*!< Pointer to barrier object*/
  std::shared_ptr<Barrier> barrierObj( new Barrier);  // Creating a shared pointer to Barrier object

  barrierObj->setCount(5);  // Setting the count for the barrier

  for(std::vector<std::thread>::size_type i = 0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,barrierObj);
  }

  for(std::vector<std::thread>::size_type i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}
