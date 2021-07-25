#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int usage(){
printf("Usage:\n");
printf(" ­n <repetitions>\n");
printf(" ­d <char to dispaly>\n");
exit (1);
return 0;
}

int main (int argc, char  **argv){
	int num = 2;
	char disp = '*';
	char c;
	int i;
	int index;
	
	while((c=getopt(argc,argv,":n:d:")) !=  -1)
	{
		//printf("%c\n",c);
		switch (c){
		case 'n':
			num = atoi(optarg);
			break;
		case 'd':
			disp = optarg[0];
			break;
		default:
			usage();
			exit (1);
		}
	}
	printf ("number = %d, display char = %c\n",num, disp);

	for (i=0;i<num;i++){
	printf("%c",disp);
	}
	
	
	//for (index = optind; index < argc; index++)
        //printf("Non-option argument %s\n", argv[index]);
 	
 	return 0;

}





