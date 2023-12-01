# Concurrent Wa-Tor Project 

## GitHub
[https://github.com/N090/Concurrent-Dev./edit/main/](https://github.com/N090/Concurrent-Dev./edit/main/)

## License
[GNU GENERAL PUBLIC LICENSE](https://github.com/N090/Concurrent-Dev./blob/main/LICENSE)  

## Author  
Nojus Satikauskas  
[Email](C00261186@setu.ie)  

## Description:
This project uses OpenMP to implement concurrent development and SFML for the Graphical User Interface in Wa-Tor.  

## Graphs  

### The graphs run through my findings on my Wat-or project  
- The First graph comprises of the threads and their maximum speeds in comparison to one another measured in milliseconds.  
![60fdf67b-c673-4602-8095-370e4a8757ae](https://github.com/N090/Concurrent-Dev./assets/91678195/80152419-eeaf-4cf1-8518-d421313e2b63)
As expected in the above graph we see a downward trend between each set of threads.

  
- The Second graph includes the threads and their minimum speeds in comparison to one another measured milliseconds.  
![a6a800c8-4c64-4c3d-bea1-08861df794fd](https://github.com/N090/Concurrent-Dev./assets/91678195/7fc9b5da-8e41-4324-af15-f457422878ec)
Here are where the neuances between the threads arise, as both the 4 threads and the 8 threads have a similar minimum speed reached. 

  
- The Third graph encompasses the threads and their average speeds in comparison to one another measured milliseconds.  
![f7ca86b6-8a96-4c66-91da-1bcd21ccb1b0](https://github.com/N090/Concurrent-Dev./assets/91678195/8babf9f6-a0af-4524-9831-749d24f260b4)
Again within this example we see the previously established downward trend between the sets of threads.

  
- The final graph contains all the data previously represented and visualises the nuances between them measured in milliseconds.  
![fd7f2ec4-74f2-4a3f-95c0-44ccae6bda4e](https://github.com/N090/Concurrent-Dev./assets/91678195/6d8844f1-a307-4006-be0d-76a534b1411b)

Within this diagram, it is clearly represented exactly what the differences are and how extreme or minimal they appear when measured in different ways.
In conclusion, we notice that there is a trajectory of increased speed when increasing the amount of threads at play
fortunatly the interesting thing is that the more threads there are the faster the distribution is, but it reaches a peak
in this case it is between the minimums of both 4 threads running parallel and 8 threads running parallel.

Beyond 8 threads I'd expect that the trajectory of distribution time would decrease going above the 8 threads, leading to diminishing returns on utilizing the maximum power available to a powerful machine 
