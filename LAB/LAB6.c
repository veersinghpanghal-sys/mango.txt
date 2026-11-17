#include<stdio.h>
#include<pthread.h>

void *threads(void *arg) {
    int id = *(int *)arg;
    printf("Hello from Thread %d\n", id);
    pthread_exit(NULL);
}

int main()
{
    int n;
    printf("Enter No of Threads : ");
    scanf("%d", &n);
    pthread_t threads[n];
    int id[n];
    for (int i = 0; i < n; i++) {
        id[i] = i+1;
        pthread_create(&threads[i], NULL, hello, &id[i])
    }  
    for (int i = 0; i < n; i++) {
        pthread_wait(threads[i], NULL)
    }
return 0;
}