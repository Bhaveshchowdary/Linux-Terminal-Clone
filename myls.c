#include "myheaders.h"

void myls(char *part[])
{
	if(part[1] == NULL){
	struct dirent *de;
	DIR*dr = opendir(".");
	if(dr == NULL)
	{
		printf("could not open current directory");
	}
	char data[500][50];
	int index = 0;
	while((de = readdir(dr)) != NULL)
	{
		if(de->d_name[0] != '.'){
			strcpy(data[index],de->d_name);
		index++;
		}
	}
	for(int i = 0;i<index;i++)
	{
		for(int j = i;j<index;j++)
		{
			if(strcmp(data[i],data[j]) > 0){
			char dummy[50];
			strcpy(dummy,data[i]);
			strcpy(data[i],data[j]);
			strcpy(data[j],dummy);
			}
				
		}
	}
	for(int i = 0;i<index;i++) printf("%s  ",data[i]);
	printf("\n");
	closedir(dr);
	}
	else if (!strcmp(part[1],"-l"))
	{
		 DIR *dr;
	    struct dirent *de;
	    struct stat no;
	    struct tm *time;
	    struct passwd *ownername;
	    struct group *grpname;
	    char date[80];

	    dr = opendir(".");

	    if(dr == NULL)
	    {
	        perror("opendir");
		exit;
            }

	    while((de = readdir(dr)) != NULL)
	    {	
		if(stat(de->d_name,&no) == -1)
		{
			perror("stat");
			continue;
		}

		time = localtime(&no.st_mtime);
                strftime(date, sizeof(date), "%b %d %H:%M", time);

                ownername = getpwuid(no.st_uid);
                grpname = getgrgid(no.st_gid);

		if(de->d_name[0] != '.'){
		printf("-%s%s%s%s%s%s%s%s%s  %1lu %s %s  %4ld %s %s\n", 
               no.st_mode & S_IRUSR ? "r" : "-",
               no.st_mode & S_IWUSR ? "w" : "-",
               no.st_mode & S_IXUSR ? "x" : "-",
	       no.st_mode & S_IRGRP ? "r" : "-",
               no.st_mode & S_IWGRP ? "w" : "-",
               no.st_mode & S_IXGRP ? "x" : "-",
	       no.st_mode & S_IROTH ? "r" : "-",
               no.st_mode & S_IWOTH ? "w" : "-",
               no.st_mode & S_IXOTH ? "x" : "-",
               no.st_nlink,
               ownername->pw_name,
               grpname->gr_name,
               no.st_size,
               date,
               de->d_name);
		}
	    }
	    closedir(dr);
	}else if(!strcmp(part[1],"-o"))
	{
		 DIR *dr;
            struct dirent *de;
            struct stat no;
            struct tm *time;
            struct passwd *ownername;
            char date[80];

            dr = opendir(".");

            if(dr == NULL)
            {
                perror("opendir");
                exit;
            }

            while((de = readdir(dr)) != NULL)
            {
                if(stat(de->d_name,&no) == -1)
                {
                        perror("stat");
                        continue;
                }

                time = localtime(&no.st_mtime);
                strftime(date, sizeof(date), "%b %d %H:%M", time);

                ownername = getpwuid(no.st_uid);

		if(de->d_name[0] != '.'){
                printf("-%s%s%s%s%s%s%s%s%s  %1lu %s %4ld %s %s\n",
               no.st_mode & S_IRUSR ? "r" : "-",
               no.st_mode & S_IWUSR ? "w" : "-",
               no.st_mode & S_IXUSR ? "x" : "-",
               no.st_mode & S_IRGRP ? "r" : "-",
               no.st_mode & S_IWGRP ? "w" : "-",
               no.st_mode & S_IXGRP ? "x" : "-",
               no.st_mode & S_IROTH ? "r" : "-",
               no.st_mode & S_IWOTH ? "w" : "-",
               no.st_mode & S_IXOTH ? "x" : "-",
               no.st_nlink,
               ownername->pw_name,
               no.st_size,
               date,
               de->d_name);
		}
            }

            closedir(dr);
	}else if (!strcmp(part[1],"-s"))
	{
		int total = 0;
           struct dirent *de;
	   struct stat no;
        DIR*dr = opendir(".");
        if(dr == NULL)
        {
                printf("could not open current directory");
        }
	while((de = readdir(dr)) != NULL)
	{
		if(stat(de->d_name,&no) == -1)
		{
			continue;
		}
		if(de->d_name[0] != '.')
		{
			total+=(no.st_blocks/2);
		}
	}
	closedir(dr);
	dr = opendir(".");

	char data[500][50];
	long int  blocksize[500];
        int index = 0;
        while((de = readdir(dr)) != NULL)
        {
		if(de->d_name[0] != '.'){
         strcpy(data[index],de->d_name);
	 blocksize[index] = no.st_blocks/2;
         index++;
		}
        }
        for(int i = 0;i<index;i++)
        {
                for(int j = i;j<index;j++)
                {
                        if(strcmp(data[i],data[j]) > 0){
                        char dummy[50];
                        strcpy(dummy,data[i]);
                        strcpy(data[i],data[j]);
                        strcpy(data[j],dummy);
			long int intermediate = blocksize[i];
			blocksize[i] = blocksize[j];
			blocksize[j] = intermediate;
                        }

                }
        }
	printf("total %d\n",total);
	closedir(dr);
	for(int i = 0;i<index;i++) printf("%ld %s  ",blocksize[i],data[i]);
        printf("\n");
	}else if(!strcmp(part[1],"-a"))
	{
		struct dirent *de;
        DIR*dr = opendir(".");
        if(dr == NULL)
        {
                printf("could not open current directory");
        }
	char data[500][50];
        int index = 0;
        while((de = readdir(dr)) != NULL)
        {
         strcpy(data[index],de->d_name);
         index++;       
        }
        for(int i = 0;i<index;i++)
        {
                for(int j = i;j<index;j++)
                {
                        if(strcmp(data[i],data[j]) > 0){
                        char dummy[50];
                        strcpy(dummy,data[i]);
                        strcpy(data[i],data[j]);
                        strcpy(data[j],dummy);
                        }

                }
        }

        for(int i = 0;i<index;i++) printf("%s  ",data[i]);
        printf("\n");
        closedir(dr);
	}else if(!strcmp(part[1],"-g"))
	{
		DIR *dr;
            struct dirent *de;
            struct stat no;
            struct tm *time;
            struct group *grpname;
            char date[80];

            dr = opendir(".");

            if(dr == NULL)
            {
                perror("opendir");
                exit;
            }

            while((de = readdir(dr)) != NULL)
            {
                if(stat(de->d_name,&no) == -1)
                {
                        perror("stat");
                        continue;
                }

                time = localtime(&no.st_mtime);
                strftime(date, sizeof(date), "%b %d %H:%M", time);

                grpname = getgrgid(no.st_gid);

                if(de->d_name[0] != '.'){
                printf("-%s%s%s%s%s%s%s%s%s  %1lu %s %4ld %s %s\n",
               no.st_mode & S_IRUSR ? "r" : "-",
               no.st_mode & S_IWUSR ? "w" : "-",
               no.st_mode & S_IXUSR ? "x" : "-",
               no.st_mode & S_IRGRP ? "r" : "-",
               no.st_mode & S_IWGRP ? "w" : "-",
               no.st_mode & S_IXGRP ? "x" : "-",
               no.st_mode & S_IROTH ? "r" : "-",
               no.st_mode & S_IWOTH ? "w" : "-",
               no.st_mode & S_IXOTH ? "x" : "-",
               no.st_nlink,
               grpname->gr_name,
               no.st_size,
               date,
               de->d_name);
                }
            }

            closedir(dr);
	}
}
