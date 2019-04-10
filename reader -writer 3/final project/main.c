#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>


pthread_mutex_t e1,e2;
int rcount = 0;
int count,n,writerno=1,readers = 0,Data;
void *reader();
void *writer();
int lwr;
int hir;
int number;


int main()
{
printf("number of reader and writer :");
scanf("%d",&n);
printf("write the higher parameter for Random Sleep Number: ");
scanf("%d",&hir);
printf("write the lower parameter for Random Sleep Number:  ");
scanf("%d",&lwr);
srand(time(0));
number =(rand()%hir-lwr)+lwr;
pthread_t readerid[n],writerid[n];
Data =(rand()%900)+100;

pthread_mutex_init(&e1,NULL);
pthread_mutex_init(&e2,NULL);

printf("***************************************************************************************************\n");
printf("|WRITER                                  READER                         NUMBER OF READER          |\n");
printf("***************************************************************************************************\n");

for(count=0;count<n;count++){
pthread_create(&writerid[count],NULL,writer,NULL);
pthread_create(&readerid[count],NULL,reader,NULL);
}
for(count=0;count<n;count++){
pthread_join(writerid[count],NULL);
pthread_join(readerid[count],NULL);
}


printf("***************************************************************************************************\n");
printf("\n");
printf("**All Reader And Writer Are Done With There OPeration");
printf("\n");
return 0;

}
void *reader()
{

pthread_mutex_lock(&e1);


rcount++;
if(rcount==1)
{
    pthread_mutex_lock(&e2);
}

pthread_mutex_unlock(&e1);
Sleep(number);
pthread_mutex_lock(&e1);
rcount--;
if(rcount==0)
{

    pthread_mutex_unlock(&e2);
}
printf("|                                |                               |       Number of reader  %d      |\n",rcount+1);
printf("|                                | Data read by the reader %d: %d|                                | \n",readers+1,Data);
readers++;

pthread_mutex_unlock(&e1);

}
void *writer()
{
pthread_mutex_lock(&e2);
printf("|                                |                               |       Number of reader  %d      |\n",rcount);
Data++;
printf("|Data writen by the writer %d: %d|                               |                                |\n",writerno,Data);
writerno++;
Sleep(number);
pthread_mutex_unlock(&e2);

}
