
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* function(void* arg){
   printf("function is invoked");
}
void main() {
   pthread_t thread1;
   
   int res = pthread_create(&thread1,NULL,function,NULL);
   if(res ==0 ){
       printf("thread is created successfully\n");
   } else{
      printf("thread creation failed");
   }

   pthread_join(thread1,NULL);
}

//pthread_t -> this the data type for threads 
//there is main so intially only single thread that is main thread 
//then child thread is created pthread_create(threadvariable , attributes for now null.,
//                                                              , what that child thread should execute, arguments for now null)
//so result is stored in res zero means thread is created and nonzero means thread is not created 
//the res pritn will be handled by the main thread while child thread will do its task that function 
//here if you dont join the main thread will not wait for the child thread to execute that function it will stop after pritning the result 



