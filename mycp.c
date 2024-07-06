#include "myheaders.h"

int mycp(char *part[])
{
	if(part[3] == NULL){
	DIR *de;
	de = opendir(part[2]);
	char buff[1];
	char final[250];
	FILE *source;
	FILE *destination;
	source = fopen(part[1],"rb");
	if(source == NULL)
	{
      	printf("Error: Unable to open source file.\n");
	return 0;
	}
	if(de == NULL)
	{
		strcpy(final, part[2]);
	}else
	{
		sprintf(final,"%s/%s",part[2],part[1]);
	}
	destination = fopen(final,"wb");
	if(destination == NULL)
	{
	 printf("Error: Unable to open destination file.\n");
	 fclose(source);
	 return 1;
   	}
	while(1){
		if(feof(source))
		{
			fclose(source);
			fclose(destination);
			break;
		}else{
		fread(buff,sizeof(buff),1,source);
		fwrite(buff,sizeof(buff),1,destination);
		}
	   }
           }else if(!strcmp(part[1],"-i"))
	   {
		DIR *de;
        de = opendir(part[3]);
        char buff[1];
        char final[250];
        FILE *source;
        FILE *destination;
        source = fopen(part[2],"rb");
        if(source == NULL)
        {
        printf("Error: Unable to open source file.\n");
        return 0;
        }
        if(de == NULL)
        {
                strcpy(final, part[3]);
        }else
        {
                sprintf(final,"%s/%s",part[3],part[2]);
        }
        destination = fopen(final,"wb");
        if(destination == NULL)
        {
         printf("Error: Unable to open destination file.\n");
         fclose(source);
         return 1;
        }
	char a;
	printf("Do you want to overwrite? If yes type y or if no type n\n");
	scanf("%c",&a);
	if(a == 'y'){
        while(1){
                if(feof(source))
                {
                        fclose(source);
                        fclose(destination);
                        break;
                }else{
                fread(buff,sizeof(buff),1,source);
                fwrite(buff,sizeof(buff),1,destination);
                }
	}
	}else{
		    fclose(source);
		    fclose(destination);
	    }
	}
	   else if(!strcmp(part[1],"-v"))
	   {
		DIR *de;
        de = opendir(part[3]);
        char buff[1];
        char final[250];
        FILE *source;
        FILE *destination;
        source = fopen(part[2],"rb");
        if(source == NULL)
        {
        printf("Error: Unable to open source file.\n");
        return 0;
        }
        if(de == NULL)
        {
                strcpy(final, part[3]);
        }else
        {
                sprintf(final,"%s/%s",part[3],part[2]);
        }
        destination = fopen(final,"wb");
        if(destination == NULL)
        {
         printf("Error: Unable to open destination file.\n");
         fclose(source);
         return 1;
        }
        while(1){
                if(feof(source))
                {
                        fclose(source);
                        fclose(destination);
                        break;
                }else{
                fread(buff,sizeof(buff),1,source);
                fwrite(buff,sizeof(buff),1,destination);
                }
            }
	printf("'%s' -> '%s'\n",part[2],part[3]);

	   }else if(!strcmp(part[1],"-n"))
	   {
		   DIR *de;
        de = opendir(part[3]);
        char buff[1];
        char final[250];
        FILE *source;
        FILE *destination;
	if(access(part[3],F_OK) == -1)
	{
        source = fopen(part[2],"rb");
        if(source == NULL)
        {
        printf("Error: Unable to open source file.\n");
        return 0;
        }
        if(de == NULL)
        {
                strcpy(final, part[3]);
        }else
        {
                sprintf(final,"%s/%s",part[3],part[2]);
        }
        destination = fopen(final,"wb");
        if(destination == NULL)
        {
         printf("Error: Unable to open destination file.\n");
         fclose(source);
         return 1;
        }
        while(1){
                if(feof(source))
                {
                        fclose(source);
                        fclose(destination);
                        break;
                }else{
                fread(buff,sizeof(buff),1,source);
                fwrite(buff,sizeof(buff),1,destination);
                }
            }
	}else
	{
		printf("The destination already exits\n");
	}
	   }else if(!strcmp(part[1],"-u"))
	   {
		DIR *de;
        de = opendir(part[3]);
        char buff[1];
        char final[250];
        FILE *source;
        FILE *destination;
	struct stat modtimesource,modtimedestination;
        source = fopen(part[2],"rb");
	if(modtimesource.st_mtime > modtimedestination.st_mtime){
        if(source == NULL)
        {
        printf("Error: Unable to open source file.\n");
        return 0;
        }
        if(de == NULL)
        {
                strcpy(final, part[3]);
        }else
        {
                sprintf(final,"%s/%s",part[3],part[2]);
        }
        destination = fopen(final,"wb");
        if(destination == NULL)
        {
         printf("Error: Unable to open destination file.\n");
         fclose(source);
         return 1;
        }
        while(1){
                if(feof(source))
                {
                        fclose(source);
                        fclose(destination);
                        break;
                }else{
                fread(buff,sizeof(buff),1,source);
                fwrite(buff,sizeof(buff),1,destination);
                }
              }
	     }else
	     {
		     printf("Destination is newer than source\n");
	     }
	   }
}

