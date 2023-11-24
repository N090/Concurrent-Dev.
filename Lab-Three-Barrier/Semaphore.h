/**
 * @file Semaphore.h
 * @author Nojus Satikauskas (C00261186)
 * @brief A Semaphore Implementation
 * @date 11/10/2023
 * @copyright GPL-3.0
 */

#ifndef SEMAPHORE_H
#define SEMAPHORE_H 
#include <mutex>
#include <condition_variable>
#include <chrono>
/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/


class Semaphore
{
private:
    unsigned int m_uiCount; /*!< Holds the Semaphore count */
    std::mutex m_mutex;
    std::condition_variable m_condition;

public:
    Semaphore(unsigned int uiCount=0)
          : m_uiCount(uiCount) { };
    void Wait();
    template< typename R,typename P >
    bool Wait(const std::chrono::duration<R,P>& crRelTime);
    void Signal();

};

#endif
