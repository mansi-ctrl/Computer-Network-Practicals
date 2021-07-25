#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char **argv){
	FILE *read;
	FILE *write;
	char  c,ch;
	char file1[]="sample.txt";
	char file2[]="sample_out.txt";
	while((ch=getopt(argc,argv,"i:o:"))!=-1){
		switch(ch){
			case 'i':
				strcpy(file1,optarg);
				break;
			case 'o':
				strcpy(file2,optarg);
				break;
			default:
			printf("-i <sourcefilename>");
			printf("-o <destinationfilename>");
			exit(1);
		}
	}
	//printf("%s %s\n",file1,file2);
	read=fopen(file1,"r");
	write=fopen(file2,"a");
	if(read==NULL || write == NULL){
	printf("File not found  \n");
	exit(EXIT_FAILURE);
	}
	
	while((c=fgetc(read))!=EOF){
	fputc(c,write);
	}
	
	fclose(write);
	fclose(read);
	return 0; 
}

