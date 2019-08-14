# Data-collector
Hello, To the data collector and related, I know poor choice of naming

OS : Mac OSX

Work:
The idea is to use a data collector to create log files of atime for files in a certain chosen directory(and sort them later).

How it does it:
The data collector uses the stat() system call to gather the data and then store the files in a text based log file in a certain order.This is the first iteration.

Other iteration of the log file : 
Now instead of writing the whole thing we just write down the changes using a hash table.

What happens afterwards:
Later this data is used by a sorter to sort and write the files in a text file in a certain order.

What needs to be done:
Sorter
Data reader
UI implementaion(To actually make it useful)

Status : Development Stage
