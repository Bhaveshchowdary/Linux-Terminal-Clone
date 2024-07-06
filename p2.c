#include "myheaders.h"

void myls(char *part[]);
int mycp(char *part[]);
int mymv(char *part[]);
int mygrep(char *part[]);
int myps(char *part[]);
int main()
{
	char *command;

	while(1)
	{
		char *username;
        	username = getlogin();

	        char hostname[PATH_MAX];
        	gethostname(hostname,sizeof(hostname));

		char currentdir[PATH_MAX];
	        getcwd(currentdir,sizeof(currentdir));

		char *syntax;
        	syntax = strcat(username,"@");
	        syntax = strcat(syntax,hostname);
	        syntax = strcat(syntax,":~");
        	syntax = strcat(syntax,currentdir);
	        syntax = strcat(syntax,"$ ");

	command = readline(syntax);
	char duplicate[100];
	strcpy(duplicate,command);
	if(strlen(command)>0)
        {
                add_history(command);
        }
	if(!strcmp(command, "exit"))
        {
                break;
        }

	int start = -1;
        int check = 0;
        int error = 1;
        for(int i = 0;i<strlen(command);i++)
        {
                if(command[i] == ' ')
                {
                        start = i;
                }else
                {
                        break;
                }
        }

	if(command[start+1] == 'c' && command[start+2] == 'd')
        {
                for(int i = start+3;i<strlen(command);i++)
                {
                        if(command[i] == ' ')
                        {
                                check = 1;
                        }else
                        {
                                check = 0;
                                break;
                        }
                }
                if(strlen(command) == 2)
                {
                        check = 1;
                }
                if(check == 1)
                {
                        chdir("/");
                }else{
                char dummy[strlen(command) - 4 - start];

                for(int i = 4+start;i<strlen(command);i++)
                {
                        dummy[i-4 -start] = command[i];
                }

                dummy[strlen(command) -4 -start] = '\0';
                error = chdir(dummy);
                if(error != 0)
                {
                        printf("directory can not be  changed\n");
                }
                }
        }


	char *part[100];

        part[0]=strtok(command," ");
        int i=1;
        while(1){
        part[i]=strtok(NULL," ");
        if(part[i]==NULL)break;
        i++;
        }

	if(part[0] == NULL)continue;

	if(!strcmp(part[0],"ls"))
	{
		myls(part);
	}else if(!strcmp(part[0],"cp"))
        {
                mycp(part);
        }else if(!strcmp(part[0],"mv"))
	{
		mymv(part);
	}else if(!strcmp(part[0],"grep"))
	{
		mygrep(part);
	}else if(!strcmp(part[0],"ps"))
	{
		myps(part);
	}else if(!strcmp(part[0],"man"))
	{
		char buff[100];
		FILE *fptr;
		if(!strcmp(part[1],"ls")){
		fptr = fopen("manls.txt","r");
		while(fgets(buff,100,fptr) != NULL)
		{
			printf("%s",buff);
		}
		fclose(fptr);
		}else if(!strcmp(part[1],"cp"))
		{
		fptr = fopen("mancp.txt","r");
		while(fgets(buff,100,fptr) != NULL)
                {
                        printf("%s",buff);
                }
                fclose(fptr);
		}else if(!strcmp(part[1],"mv"))
                {
                fptr = fopen("manmv.txt","r");
                while(fgets(buff,100,fptr) != NULL)
                {
                        printf("%s",buff);
                }
                fclose(fptr);
                }else if(!strcmp(part[1],"grep"))
                {
                fptr = fopen("mangrep.txt","r");
                while(fgets(buff,100,fptr) != NULL)
                {
                        printf("%s",buff);
                }
                fclose(fptr);
                }else if(!strcmp(part[1],"ps"))
                {
                fptr = fopen("manps.txt","r");
                while(fgets(buff,100,fptr) != NULL)
                {
                        printf("%s",buff);
                }
                fclose(fptr);
                }
	}
}

}
