
//Made By Nishant Acharya
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

void storeFilesRecursively(char *path,FILE* fd);

int main()
{
	// Directory path to list files
	char path[1024];
	FILE* fl;
	// Input path from user 
	
	strcpy(path,"/Users/nishantacharya/Downloads");
	
	//open file here 
	if((fl = fopen("/Users/nishantacharya/Desktop/Logs/log.txt","a+"))== NULL){// writing to the file
		printf("Error in opening/creating the file\n");
		exit(0);
	}
	storeFilesRecursively(path,fl);
	
	fclose(fl);

	return 0;
}

void storeFilesRecursively(char* basePath,FILE* fd)//function to store files recursively 
{
	char path[1024];//path variable
	struct dirent *dp;//dirent struct
	struct stat data;//file info storage
	char buffer[1024];//buffer for writing
	int errnum;//error checking
	int fq = 0;//frequency

	DIR *dir = opendir(basePath);

	
	// Unable to open directory stream
	if (!dir){
		return;
	}

	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
		{
			continue;
		}
			// Construct new path from our base path
			strcpy(path, basePath);
			if(strcmp(path,"/") != 0){
				strcat(path, "/");
			}
			strcat(path, dp->d_name);
			
			if(stat(path,&data)!= 0){
				continue;
			}
			
			//writing to the log file
			if(S_ISREG(data.st_mode)){
				fprintf(fd,"PATH:- %s\nTIME:- %lld\nFQ:- %i\n",path,(long long)data.st_atime,fq);//add a unique string to differentiate between the three types of data
			}
			
			if(S_ISDIR(data.st_mode)){
				storeFilesRecursively(path,fd);
			}
		}

		closedir(dir);
	}

