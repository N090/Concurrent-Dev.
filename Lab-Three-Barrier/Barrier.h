/**
 * @file Barrier.h
 * @author Nojus Satikauskas (C00261186)
 * @brief The header file for the Barrier class.
 * @date 15/11/2023
 * @copyright GPL-3.0
 */

#include "Semaphore.h"
#include <iostream>
#include <stdio.h>

/*! \class Barrier
    \brief A Barrier Implementation

   Uses C++11 features such as mutex and condition variables to implement a Barrier class using Semaphores

*/
class Barrier
{
private:

  int count;
  int threadNum;
  bool condition;
  std::shared_ptr<Semaphore> mutex;
  std::shared_ptr<Semaphore> barrier1;
  std::shared_ptr<Semaphore> barrier2;


public:

  Barrier();
  ~Barrier();
  Barrier(int count);
  void setCount(int count);
  int getCount();
  void waitForAll();
};
