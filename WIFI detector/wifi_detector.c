// this Vol content an additional quastion to learn more about a WIFI interface
// this vol content an additional situation of non saved passwords 
// Update 04/08/2020
// now you can delet config.dat file and the script will work even that, 
// Last Update 26/08/2020
// now if there are some opne WI-FIs the script show a message that clarify that the WI-FI is open .



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void logo()
{
	FILE *Config ;
	char buff[100];
	Config=fopen("Config\\Config.dat","r");
	system("cls");
	while(!feof(Config))
	{
		if(!fgets(buff,100,Config))
			break;
		printf("%s",buff);

	}
}

void Enter()
{
	FILE *Config;
	char buff[100];
	Quastion1:
	printf("type yes to start the  script\n");
	printf("type close to exit the script\n");
	printf("type:");
	gets(buff);
	if(!strcmp(buff,"close"))
		exit(1);
	else
	{
		if(!strcmp(buff,"yes"))
		{
			Config=fopen("Config\\Config.dat","r");
			system("cls");
			while(!feof(Config))
			{
				if(!fgets(buff,100,Config))
					break;
				printf("%s",buff);

			}
			fclose(Config);
		}
		else 
			{
				printf("Please try again!\n");
				goto Quastion1;
			}
	}
}


char* SelectPass()
{
	FILE *interface=fopen("Config\\Interface.dat","r");
	char *buff1=(char*)malloc(100*sizeof(char)) , *buff2=(char*)malloc(100*sizeof(char)) ;
	strcpy(buff1,"Null");
	int Exist=0;
	while(!Exist && !feof(interface))
	{
		fscanf(interface,"%s",buff1);
		if(!strcmp(buff1,"Key"))
		{
			fscanf(interface,"%s",buff2);
			if(!strcmp(buff2,"Content"))
			{
				fseek(interface,11,SEEK_CUR);
				fgets(buff2,50,interface);
				Exist=1;
			}
		}
	}
	fclose(interface);
	if(strlen(buff2)<6)
		return "NULL";
	else 
	{
		strcpy(buff2,&buff2[2]);
		return buff2 ;
	}
	
}


int main()
{
	printf("Hello Friends! this script will get you all saved passwords \n");
	printf(" of the WIFIs interfaces that you have been conecting with \n");
	printf("            created by: Mustapha Slimani \n\n");
	Enter();
	start:
	printf("\nGetting your WIFIs passwords\n");	
	system("netsh wlan show profile > Config\\Profiles.dat");
	FILE *profiles ;
	profiles=fopen("Config\\Profiles.dat","r");
	char buff1[100] , buff2[100] ;
	int Position=0;
	while(!Position)
	{
		if(feof(profiles))
		{
			printf("\nOps! SOMTHING IS GOING WRONG, please restart the programe!!\n");
			break; 
		}
		fgets(buff1,14,profiles);
		if(!strcmp(buff1,"User profiles"))
		{
			fgets(buff2,20,profiles);
			if(!strcmp(buff2,"-------------"));
			{
				Position=1;
			}
		}
	}

	fscanf(profiles,"%s",buff1);
	int i=0 ;
	char car ;
	FILE *profiles_name=fopen("Config\\profiles_name.dat","w"); 
	strcpy(buff1,"Zero");
	while(!feof(profiles))
	{
		if(feof(profiles))
			break;
		fscanf(profiles,"%s",buff1);
		while(strcmp(buff1,":")!=0 && !feof(profiles))
			fscanf(profiles,"%s",buff1);
		fscanf(profiles,"%c",&car);
		while(car==' ' && !feof(profiles))
			fscanf(profiles,"%c",&car);
		fgets(buff2,20,profiles);
		buff1[0]=car;
		strcpy(&buff1[1],buff2);
		fputs(buff1,profiles_name);
		i++;
	}
	fclose(profiles_name);
	FILE *interfaces_command=fopen("Config\\interfaces_command.dat","w") ; 
	profiles_name=fopen("Config\\profiles_name.dat","r"); 
	int lenght=i ;
	int Number ;
	if(lenght<=1)
	{
		printf("there are no WIFI passwords saved in your computer !!\n");
		Quastion2:
		printf("1:Exit\n2:Try again\n");
		printf("type:");
		scanf("%d",&Number);
		if(Number==1)
			exit(1);
		else
		{
			if(Number==2)
				goto start ;
			else
			{
				printf("Please try again!!\n");
				goto Quastion2;
			}
		}
	}
	printf("\nSelect a number of the wifi you want!\n");
	for(i=1;i<lenght;i++)
	{
		fgets(buff1,30,profiles_name);
		buff1[strlen(buff1)-1]='\0';
		fprintf(interfaces_command,"netsh wlan show profile name=\"%s\" key=clear > Config\\Interface.dat\n",buff1);
		printf("%d : %s\n",i,buff1);
	}
	printf("type:");
	fclose(interfaces_command);

	scanf("%d",&Number);
	fseek(profiles_name,0,SEEK_SET);
	fseek(interfaces_command,0,SEEK_SET);
	fclose(interfaces_command);
	interfaces_command=fopen("Config\\interfaces_command.dat","r") ; 
	for(;Number>0;Number--)
	{
		fgets(buff1,30,profiles_name);
		fgets(buff2,100,interfaces_command);
	}
	system(buff2);
	char buff3[100];
	strcpy(buff3,buff2);
	system("cls");
	buff1[strlen(buff1)-1]='\0';
	logo();
	printf("\nLooking for passwords for %s WIFI interface\n",buff1);
	char *buff=SelectPass();
	if(!strcmp(buff,"NULL"))
		{
			printf("This WI-FI is open!!\n");
			goto Quastion;
		}
	else 
	{
		printf("the passwords of %s is : %s\n",buff1,buff);goto Quastion;
	}
	int Answer ;
	Quastion:
	printf("1 : back to menu\n2 : Read more about this interface\n3 : exit\ntype: ");
	scanf("%d",&Answer);
	if(Answer==3)
		exit(1);
	else
	{
		if(Answer==1)
			{
				logo();
				goto start ;
			}
		else
			{
				if(Answer==2)
				{
					system("cls");
					logo();
					printf("\n");
					for(i=0;i<strlen(buff3);i++)
						if(buff3[i]=='>')
						{
							buff3[i]='\0';
							break;
						}
					system(buff3);
					goto Quastion ;
				}
				else
				{
					printf("Please try again!!\n");
					goto Quastion;
				}
			}
	}
	return 0 ;
}
