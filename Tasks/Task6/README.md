**In English** 

> ! *How to compile* ! 
> gcc -o child child.c 

> gcc Task6.c 

>./a.out num_child time 

Where 

*num_child* - number of children 

*time* - duration of the game 


There are global variables, but I don't know how to do without them - how to call a handler function with the necessary parameters from another process?

*About the implementation* 

We write one number to the shared memory area - the number of apples. Processes, according to their role, change this number. The child processes are described by a separate program, since the implementation of the child process is quite voluminous, and the code would be less readable if the children were described in ``C if (fork() == 0)`` (or in something at home). Maybe that's not a good thing either. 

```C #define playTime 1 ``` - 

sets the time that children play - you can change the program by making it random, if necessary. And so, it is the same for all children. 


**На русском** 

> ! *Как компилировать* ! 

> gcc -o child child.c 

> gcc Task6.c 

>./a.out num_child time 

Где 

*num_child* - количество детей 

*time* - длительность игры 


Есть глобальные переменные, но не знаю, как без них сделать - как из дркгого процесса вызвать функцию обработчик с нужными параметрами?

*О реализации* 

В разделяемую область памяти записываем одно число - количество яблок. Процессы, в соответствии с их ролью, это число меняют. Процессы-дети описаны отдельной программой,поскольку реализация процесса-ребенка довольно объемна, и код был бы менее читаемым, будь дети описаны в ```C if (fork() == 0) ``` (или в чем-то подомном). Возможно, это тоже не очень хорошо. 

```C #define playTime 1 ``` - 

задает время, которое дети играют - можно изменить программу, сделав его случайным, если нужно. А так, оно у всех детей одинаково.


