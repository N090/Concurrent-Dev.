// reduction.cpp --- 
// 
// Filename: quicksort.cpp
// Description: 
// Author: Joseph Kehoe
// Maintainer: 
// Created: Sat Feb 19 13:23:33 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Sun Oct 22 20:51:32 2023 (+0100)
//           By: Joseph
//     Update #: 106
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
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

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <functional>  /* function type */
#include <limits>
#include <vector>      /* vectors used instead of arrays */
#include <omp.h>
using namespace std ;


const int LENGTH=2000;
int NumThreads=1;


///! Find out how many threads are running!
int get_num_threads(void) {
    int num_threads = 1;
    //must ask in parallel region otherwise 1 is returned
    #pragma omp parallel
    {
        #pragma omp single
        num_threads = omp_get_num_threads();
    }
    return num_threads;
}

float getSerialSum(vector<int> data){
  float sum=0.0;
  for(auto& value:data){
    sum+=value;
  }
  return sum;
}

float getParallelSum(vector<int> data){
  float sum=0.0;
#pragma omp parallel for reduction(+:sum)
  for(int i=0;i<data.size();++i){
    sum+=data[i];
  }
  return sum;
}


float getTiledParallelsum(vector<int> data){
  float result =0.0;
  NumThreads=get_num_threads();
  float tileResult[NumThreads];
  for(int i=0;i<NumThreads;++i) tileResult[i]=0.0;
  //map step here
#pragma omp parallel for 
  for (int i=0; i < data.size(); ++i ){
    int tid = omp_get_thread_num();
    tileResult[tid] =tileResult[tid]+data[i];
  }
  //reude step here
  for (int i=0; i < NumThreads ; ++i ){
    std::cout << i<< ":"<< tileResult[i] << "- ";
    result+=tileResult[i];
  }
  std::cout <<std::endl;
  return result ;
}



int main(void){
  float sum=0.0;
  int average=0;
  NumThreads=omp_get_num_threads();
  srand (time(NULL));
  vector<int> data(1000);
  for(auto& value:data){
    value=10;//rand()%1000;
  }

  sum=getSerialSum(data);
  average=sum/data.size();
  cout <<"Serial Average is: "<<average<<endl;
  sum=getParallelSum(data);
  average=sum/data.size();
  cout <<"Parallel Average is: "<<average<<endl;
  cout << endl;
  sum=getTiledParallelsum(data);
  average=sum/data.size();
  cout <<"Parallel Average is: "<<average<<endl;
  cout << endl;
}
// 
// reduction.cpp ends here
