#include "myheaders.h"

int mygrep(char *part[])
{
	int last = 1;
	while(1)
        {
                if(part[last] == NULL)
                {
                        break;
                }else
                {
                        last++;
                }
        }
	int totalcount = 0;

	if(strcmp(part[1], "-c") && strcmp(part[1], "-v") && strcmp(part[1], "-n") && strcmp(part[1], "-m")){
	char *line;
	FILE *fptr;
	for(int i = 2;i<last;i++){
	fptr = fopen(part[i],"r");
	if(fptr == NULL)
	{
		printf("Can not open this file\n");
		return 0;
	}
	size_t length =0;
	while( getline(&line,&length,fptr) != -1)
	{
		if((strstr(line,part[1])) != NULL)
		{
			printf("%s",line);
		}
	}
		fclose(fptr);
	}
	}else if(!strcmp(part[1],"-c"))
	{
		char *line;
        FILE *fptr;
	for(int i = 3;i<last;i++){
        fptr = fopen(part[i],"r");
        if(fptr == NULL)
        {
                printf("Can not open this file\n");
                return 0;
        }
        size_t length =0;
        while( getline(&line,&length,fptr) != -1)
        {
                if((strstr(line,part[2])) != NULL)
                {
                       totalcount++;
                }
        }
		fclose(fptr);
	}
	printf("%d\n",totalcount);

	}else if(!strcmp(part[1],"-v"))
	{
		char *line;
        FILE *fptr;
	for(int i = 3;i<last;i++){
        fptr = fopen(part[i],"r");
        if(fptr == NULL)
        {
                printf("Can not open this file");
                return 0;
        }
        size_t length =0;
        while( getline(&line,&length,fptr) != -1)
        {
                if((strstr(line,part[2])) == NULL)
                {
                        printf("%s",line);
                }
        }
	fclose(fptr);
	}
	}else if(!strcmp(part[1],"-n"))
	{
	char *line;
        FILE *fptr;
	for(int i = 3;i<last;i++){
	int lineno = 0;
        fptr = fopen(part[i],"r");
        if(fptr == NULL)
        {
                printf("Can not open this file");
                return 0;
        }
        size_t length =0;
        while( getline(&line,&length,fptr) != -1)
        {
		lineno++;
                if((strstr(line,part[2])) != NULL)
                {
                        printf("%d: %s",lineno,line);
                }
        }
                fclose(fptr);
	}
	}else if(!strcmp(part[1],"-m"))
        {
        char *line;
        FILE *fptr;
        int num = atoi(part[2]);
	int count =0;
	for(int i = 4;i<last;i++){
        fptr = fopen(part[i],"r");
        if(fptr == NULL)
        {
                printf("Can not open this file");
                return 0;
        }
        size_t length =0;
        while( getline(&line,&length,fptr) != -1)
        {
                if((strstr(line,part[3])) != NULL)
                {
			if(count == num)break;
                        printf("%s",line);
			count++;
                }
        }
                fclose(fptr);
	}
        }
}
