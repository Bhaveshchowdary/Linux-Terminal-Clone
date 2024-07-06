#include "myheaders.h"

int myps(char *part[])
{
	if(part[1] == NULL){
	DIR *dr;
	struct dirent *de;

	dr = opendir("/proc");
	if(dr == NULL)
	{
		perror("opendir");
		return 0;
	}

	printf("   PID\tTTY\t\tTIME\t CMD\n");
	while((de = readdir(dr)) != NULL)
	{
		if(isdigit(*de->d_name))
		{
			char *pid=de->d_name;
			char filename[300];
			sprintf(filename,"/proc/%s/stat",pid);
			char pathname[300];
			sprintf(pathname,"/proc/%s/fd/0",pid);

			if(access(pathname,F_OK) != 0)continue;
			int fpath;
			if((fpath = open(pathname,O_RDWR)) < 0)continue;
			if(ttyname(fpath) == NULL){
			close(fpath);
			continue;
			}

			FILE *fptr;
			fptr = fopen(filename,"r");

			int pidno;
			char command[300];
			unsigned long int timeu,times;

			fscanf(fptr,"%d %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lu %lu",&pidno,command,&timeu,&times);
			fclose(fptr);
			long int time =(long int) (float)(timeu+times)/sysconf(_SC_CLK_TCK);
			char timeformat[30];
			sprintf(timeformat,"%02ld:%02ld:%02ld",(time/3600)%3600,(time/60)%60,time%60);

			char ttyname[30];
			size_t size = readlink(pathname,ttyname,30);
			if(size >= 0)
			{
				ttyname[size] = '\0';
			}else
			{
				ttyname[0]='?'; 
				strcat(ttyname,"          ");
			}

			printf("   %d %s\t\t%s %s\n",pidno,ttyname+5,timeformat,command);
			}
		}
	}else if(!strcmp(part[1],"-aF"))
	{
		DIR *dr;
        struct dirent *de;

        dr = opendir("/proc");
        if(dr == NULL)
        {
                perror("opendir");
                return 0;
        }

        printf("UID\tPID\tPPID\tC\tSZ\tRSS\tPSR\tSTIME\tTTY\t\tTIME\t\tCMD\n");
        while((de = readdir(dr)) != NULL)
        {
                if(isdigit(*de->d_name))
                {
			struct passwd* userid;
			struct tm* local;
                        char *pid=de->d_name;
                        char filename[300];
                        sprintf(filename,"/proc/%s/stat",pid);
                        char pathname[300];
                        sprintf(pathname,"/proc/%s/fd/0",pid);

                        if(access(pathname,F_OK) != 0){continue;}
                        int fpath;
                        if((fpath = open(pathname,O_RDWR)) < 0){continue;}
                        if(ttyname(fpath) == NULL){
                        close(fpath);
                        continue;
                        }

                        FILE *fptr;
                        fptr = fopen(filename,"r");

                        char command[300];
                        unsigned long int timeu,times;
			unsigned long long int starttime;
			long int rss,sz;
			int uid,sid,psr,c,ppidno,pidno;

                        fscanf(fptr,"%d %s %*s %u %*s %d %*s %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %u %d",&pidno,command,&ppidno,&sid,&timeu,&times,&starttime,&psr,&c);
			fclose(fptr);

			sprintf(filename,"/proc/%s/statm",pid);
			fptr = fopen(filename,"r");
			fscanf(fptr,"%ld %ld",&sz,&rss);
			fclose(fptr);

			double uptime;
			fptr = fopen("/proc/uptime","r");
			fscanf(fptr,"%lf",&uptime);
			fclose(fptr);

			sprintf(filename,"/proc/%s/status",pid);
			fptr = fopen(filename,"r");
			char buff[300];
			for(int i = 0;i<8;i++)
			{
				fgets(buff,sizeof(buff),fptr);
			}
			fgets(buff,sizeof(buff),fptr);
			sscanf(buff,"Uid:\t%d",&uid);
			userid = getpwuid(uid);

			char *finaluid = userid->pw_name;

			time_t modstart = time(NULL) - (uptime -((double)starttime/sysconf(_SC_CLK_TCK)));
			local = localtime(&modstart);

			char finaltime[30];
			strftime(finaltime,30,"%H:%M",local);

                        long int time =(long int) (float)(timeu+times)/sysconf(_SC_CLK_TCK);
                        char timeformat[30];
                        sprintf(timeformat,"%02ld:%02ld:%02ld",(time/3600)%3600,(time/60)%60,time%60);

                        char ttyname[30];
                        size_t size = readlink(pathname,ttyname,30);
                        if(size >= 0)
                        {
                                ttyname[size] = '\0';
                        }else
                        {
                                ttyname[0]='?';
                                strcat(ttyname,"          ");
                        }

	                if(pidno != sid) printf("%s\t%d\t%d\t%d\t%ld\t%ld\t%d\t%s\t%s\t\t%s\t%s\n",finaluid,pidno,ppidno,c,sz,rss,psr,finaltime,ttyname+5,timeformat,command);
                        }
                }
	}else if(!strcmp(part[1],"-af"))
	{
		DIR *dr;
        struct dirent *de;

        dr = opendir("/proc");
        if(dr == NULL)
        {
                perror("opendir");
                return 0;
        }

        printf("UID\tPID\tPPID\tC STIME\tTTY\tTIME\t CMD\n");
        while((de = readdir(dr)) != NULL)
        {
                if(isdigit(*de->d_name))
                {
                        struct passwd* userid;
                        struct tm* local;
                        char *pid=de->d_name;
                        char filename[300];
                        sprintf(filename,"/proc/%s/stat",pid);
                        char pathname[300];
                        sprintf(pathname,"/proc/%s/fd/0",pid);

                        if(access(pathname,F_OK) != 0){continue;}
                        int fpath;
                        if((fpath = open(pathname,O_RDWR)) < 0){continue;}
                        if(ttyname(fpath) == NULL){
                        close(fpath);
                        continue;
                        }

                        FILE *fptr;
                        fptr = fopen(filename,"r");

                        char command[300];
                        unsigned long int timeu,times;
                        unsigned long long int starttime;
                        long int rss,sz;
                        int uid,sid,psr,c,ppidno,pidno;

                        fscanf(fptr,"%d %s %*s %u %*s %d %*s %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d",&pidno,command,&ppidno,&sid,&timeu,&times,&starttime,&c);
                        fclose(fptr);

                        double uptime;
                        fptr = fopen("/proc/uptime","r");
                        fscanf(fptr,"%lf",&uptime);
                        fclose(fptr);

                        sprintf(filename,"/proc/%s/status",pid);
                        fptr = fopen(filename,"r");
                        char buff[300];
                        for(int i = 0;i<8;i++)
                        {
                                fgets(buff,sizeof(buff),fptr);
                        }
                        fgets(buff,sizeof(buff),fptr);
                        sscanf(buff,"Uid:\t%d",&uid);
                        userid = getpwuid(uid);

                        char *finaluid = userid->pw_name;

                        time_t modstart = time(NULL) - (uptime -((double)starttime/sysconf(_SC_CLK_TCK)));
                        local = localtime(&modstart);

                        char finaltime[30];
                        strftime(finaltime,30,"%H:%M",local);

                        long int time =(long int) (float)(timeu+times)/sysconf(_SC_CLK_TCK);
                        char timeformat[30];
                        sprintf(timeformat,"%02ld:%02ld:%02ld",(time/3600)%3600,(time/60)%60,time%60);

                        char ttyname[30];
                        size_t size = readlink(pathname,ttyname,30);
                        if(size >= 0)
                        {
                                ttyname[size] = '\0';
                        }else
                        {
                                ttyname[0]='?';
                                strcat(ttyname,"          ");
                        }

                       if(pidno != sid) printf("%s\t%d\t%d\t%d %s\t%s\t%s %s\n",finaluid,pidno,ppidno,c,finaltime,ttyname+5,timeformat,command);
                        }
                }

	}else if(!strcmp(part[1],"-p"))
	{		
       		int givenpid = atoi(part[2]);	
		DIR *dr;
        struct dirent *de;

        dr = opendir("/proc");
        if(dr == NULL)
        {
                perror("opendir");
                return 0;
        }

        printf("   PID\tTTY\t\tTIME\t CMD\n");
        while((de = readdir(dr)) != NULL)
        {
                if(isdigit(*de->d_name))
                {
                        char *pid=de->d_name;
                        char filename[300];
                        sprintf(filename,"/proc/%s/stat",pid);
                        char pathname[300];
                        sprintf(pathname,"/proc/%s/fd/0",pid);

                        if(access(pathname,F_OK) != 0){continue;}
                        int fpath;
                        if((fpath = open(pathname,O_RDWR)) < 0){continue;}
                        if(ttyname(fpath) == NULL){
                        close(fpath);
                        continue;
                        }

                        FILE *fptr;
                        fptr = fopen(filename,"r");

                        int pidno;
                        char command[300];
                        unsigned long int timeu,times;

                        fscanf(fptr,"%d %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lu %lu",&pidno,command,&timeu,&times);
                        fclose(fptr);
                        long int time =(long int) (float)(timeu+times)/sysconf(_SC_CLK_TCK);
                        char timeformat[30];
                        sprintf(timeformat,"%02ld:%02ld:%02ld",(time/3600)%3600,(time/60)%60,time%60);

                        char ttyname[30];
                        size_t size = readlink(pathname,ttyname,30);
                        if(size >= 0)
                        {
                                ttyname[size] = '\0';
                        }else
                        {
                                ttyname[0]='?';
                                strcat(ttyname,"          ");
                        }
			if(pidno == givenpid){
                        printf("   %d %s\t\t%s %s\n",pidno,ttyname+5,timeformat,command);
			}
                        }
                }

        }else if(!strcmp(part[1],"-a"))
	{
		DIR *dr;
        struct dirent *de;

        dr = opendir("/proc");
        if(dr == NULL)
        {
                perror("opendir");
                return 0;
        }

        printf("   PID\tTTY\t\tTIME\t CMD\n");
        while((de = readdir(dr)) != NULL)
        {
                if(isdigit(*de->d_name))
                {
                        char *pid=de->d_name;
                        char filename[300];
                        sprintf(filename,"/proc/%s/stat",pid);
                        char pathname[300];
                        sprintf(pathname,"/proc/%s/fd/0",pid);

                        if(access(pathname,F_OK) != 0){continue;}
                        int fpath;
                        if((fpath = open(pathname,O_RDWR)) < 0){continue;}
                        if(ttyname(fpath) == NULL){
                        close(fpath);
                        continue;
                        }

                        FILE *fptr;
                        fptr = fopen(filename,"r");

                        int pidno;
                        char command[300];
                        unsigned long int timeu,times;
			int sid;

                        fscanf(fptr,"%d %s %*s %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %lu %lu",&pidno,command,&sid,&timeu,&times);
                        fclose(fptr);
                        long int time =(long int) (float)(timeu+times)/sysconf(_SC_CLK_TCK);
                        char timeformat[30];
                        sprintf(timeformat,"%02ld:%02ld:%02ld",(time/3600)%3600,(time/60)%60,time%60);

                        char ttyname[30];
                        size_t size = readlink(pathname,ttyname,30);
                        if(size >= 0)
                        {
                                ttyname[size] = '\0';
                        }else
                        {
                                ttyname[0]='?';
                                strcat(ttyname,"          ");
                        }
			if(sid != pidno) printf("   %d %s\t\t%s %s\n",pidno,ttyname+5,timeformat,command);
                        }
                }

	}
}
