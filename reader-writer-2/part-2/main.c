#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>


pthread_mutex_t e1,e2;
int rcount = 0;
int count=0,n;
void *reader();
void *writer();



int main()
{
printf("number of reader and writer :");
scanf("%d",&n);
pthread_t readerid[n],writerid[n];

pthread_mutex_init(&e1,NULL);
pthread_mutex_init(&e2,NULL);

printf("*****************************************************************************************\n");
printf("|WRITER                             READER                    NUMBER OF READER          |\n");
printf("*****************************************************************************************\n");

while(count<n){
pthread_create(&writerid[count],NULL,writer,NULL);
pthread_create(&readerid[count],NULL,reader,NULL);



pthread_join(writerid[count],NULL);
pthread_join(readerid[count],NULL);
count++;
}


printf("****************************************************************************************\n");
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

printf("|                           |                          |       Number of reader  %d      |\n",rcount);
printf("|                           | Data read by the reader %d|                                | \n",count);

Sleep(1000);

pthread_mutex_lock(&e1);
rcount--;
if(rcount==0)
{

    pthread_mutex_unlock(&e2);
}

pthread_mutex_unlock(&e1);

}
void *writer()
{

pthread_mutex_lock(&e2);
printf("|                           |                          |       Number of reader  %d      |\n",rcount);
printf("|Data writen by the writer %d|                          |                                |\n",count);
Sleep(1200);

pthread_mutex_unlock(&e2);


}
