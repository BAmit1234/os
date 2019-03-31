#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


pthread_mutex_t e1,e2;
int rcount = 0;
void *reader();
void *writer();


int main()
{
pthread_t readerid,writerid,readerid1,writerid1;

pthread_mutex_init(&e1,NULL);
pthread_mutex_init(&e2,NULL);

printf("*******************************************************************************\n");
printf("*WRITER                             READER                    NUMBER OF READER*\n");
printf("*******************************************************************************\n");


pthread_create(&writerid,NULL,writer,NULL);
pthread_create(&readerid,NULL,reader,NULL);

pthread_create(&writerid1,NULL,writer,NULL);
pthread_create(&readerid1,NULL,reader,NULL);

pthread_join(writerid,NULL);
pthread_join(readerid,NULL);
pthread_join(writerid1,NULL);
pthread_join(readerid1,NULL);

return 0;

}
void *reader()
{
pthread_mutex_lock(&e1);
rcount = rcount++;
if(rcount==1)
{
    pthread_mutex_lock(&e2);
}
pthread_mutex_unlock(&e1);
printf("                            Data read by the reader \n");
pthread_mutex_lock(&e1);
rcount = rcount--;
if(rcount==0)
{
    pthread_mutex_unlock(&e2);
}

pthread_mutex_unlock(&e1);;

}
void *writer()
{
pthread_mutex_lock(&e2);
printf("                                                            Number of reader  %d \n",rcount);
printf("Data writen by the writer \n");

pthread_mutex_unlock(&e2);

}
