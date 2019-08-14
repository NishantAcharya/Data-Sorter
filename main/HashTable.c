//Made by Nishant Acharya
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

struct data {
	long long atime;
	int frequency;
	char path[1024];
};
 
struct data* array;
int capacity = 3;
int size = 0;

void rehash();

/* this function gives a unique hash code to the given key */
int hashcode(char* path){
	return (strlen(path) % capacity);
}

/* to check if given input is prime or not */
int if_prime(int n){
	int i;
	if ( n == 1  ||  n == 0){
		return 0;
	}
	for (i = 2; i < n; i++){
		if (n % i == 0){
			return 0;
		}
	}
	return 1;
}

/* it returns prime number just greater than array capacity */
int get_prime(int n){
	if (n % 2 == 0){
		n++;
	}
	for (; !if_prime(n); n += 2);
 
	return n;
}

void init_array(){
	int i;
	capacity = get_prime(capacity);
	array = (struct data*) malloc(capacity * sizeof(struct data));
	for (i = 0; i < capacity; i++) {
		strcpy(array[i].path,"");
		array[i].atime = -1;
		array[i].frequency = -1;
	}
}

int size_of_hashtable(){
	return size;
}

int probe(int hashcode, char key[]){
	//find the next empty unit or the next unit with the same key, quadratic probing
	int i = 1;
	int temp = hashcode;
	//printf("this is the index value :- %s,this is the inserted value :- %s\n",array[temp].path,key);
	while(strcmp(array[temp].path,"") != 0){//not working
		//printf("%i - %s\n",i,array[temp].path);
		if(strcmp(array[temp].path,key) == 0){
			break;
		}
		temp = (hashcode + (i*i)) % capacity;
		i++;
	}
	return temp;
}

// add insert such that it uses the above function to insert
//reshash is to be used when size > capacity/2

void insert(char pth[],long long time,int fq){
	int index = hashcode(pth);
	if(size > (capacity/2)){
		printf("rehash time\n");
		rehash();
	}
	printf("this is the index value :- %s,this is the inserted value :- %s\n",array[index].path,pth);
	if(array[index].atime == -1){
		strcpy(array[index].path,pth);
		array[index].atime = time;
		array[index].frequency = fq;
		size++;
	}
	else if(strcmp(array[index].path,pth) == 0){
		array[index].atime = time;
		array[index].frequency = fq;
	}
	else{
		index = probe(index,pth);
		strcpy(array[index].path,pth);
		array[index].atime = time;
		array[index].frequency = fq;
		size++;
	}
}

/* rehashes the given table*/
//works
void rehash(){
	int i;
	int Newcapacity;
	int index;
	struct data* newArray;
	Newcapacity = get_prime(2*capacity);
	printf("this is the newcapacity ---> %i and this is 2*capacity ---> %i and this is 2* capacity next prime ---> %i\n",Newcapacity,2*capacity,get_prime(2*capacity));
	newArray = (struct data*)malloc(capacity * sizeof(struct data));
	for (i = 0; i < capacity; i++) {
		strcpy(newArray[i].path,array[i].path);
		newArray[i].atime = array[i].atime;
		newArray[i].frequency = array[i].frequency;
	}
	
	array = (struct data*)realloc(array,Newcapacity);
	
	for (i = 0; i < Newcapacity; i++) {//sets the values in the new array
		strcpy(array[i].path,"");
		array[i].atime = -1;
		array[i].frequency = -1;
	}
	
	for(i = 0; i < capacity; i++){
		if(strcmp(newArray[i].path,"") == 0){
			continue;
		}
		
		//insertion
		index = hashcode(newArray[i].path);
		if(array[index].atime == -1){
			strcpy(array[index].path,newArray[index].path);
			array[index].atime = newArray[index].atime;
			array[index].frequency = newArray[index].frequency;
		}
		else if(strcmp(array[index].path,newArray[index].path) == 0){
			array[index].atime = newArray[index].atime;
			array[index].frequency = newArray[index].frequency;
		}
		else{
			index = probe(index,newArray[index].path);
			strcpy(array[index].path,newArray[index].path);
			array[index].atime = newArray[index].atime;
			array[index].frequency = newArray[index].frequency;
		}
		
	}
	capacity = Newcapacity;
	free(newArray);
}

//For testing purposes
void display(){
	int i;
	for (i = 0; i < capacity; i++){
		if (array[i].atime == -1){
			printf(" Array[%d] has no elements\n",i);
		}
		else{
			printf(" Array[%d] has elements -: key(%s) and value(%lld)\n", i, array[i].path, array[i].atime);
		}
	}
}

int main(){
	//printf("bump\n");
	init_array();
	int i;
	insert("hello",5,6);
	display();
	insert("hello",9,8);
	display();
	insert("dello",11,8);
		display();
	insert("dello",0,0);
		display();
	insert("cello",10,0);
	display();
	return 0;
}
