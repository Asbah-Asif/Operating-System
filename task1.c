#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int arr[20]={45, 23, 67, 89, 12, 34, 78, 90, 56, 21, 38, 72,

44, 91, 15, 83, 29, 66, 54, 88};
struct info{
    int start;
int end;
};

void* findMax(void* arg)
{
    struct info *data=(struct info*)arg;
    int max=arr[data->start];
    for(int i = data->start + 1; i <= data->end; i++) {
        if(arr[i] > max)
            max = arr[i];
    }
    printf("thread for elements %d to %d found max = %d\n", data->start, data->end,max );

    int *res=malloc(sizeof(int));
    *res=max;
    return res;
}

int main(){
    pthread_t t[4];
    struct info range[4];
    int part=5;

    for (int i = 0; i < 4; i++)
    {
        range[i].start= i*part;
        range[i].end= range[i].start+part-1;
        pthread_create(&t[i], NULL, findMax, &range[i]);
    
    }
    int finalMax=arr[0];
    for (int i=0; i<4;i++)
    {
        int *localMax;
        pthread_join(t[i], (void**)&localMax);
        if(*localMax>finalMax)
        finalMax=*localMax;
        free(localMax);
}
    printf("\nOverall maximum value = %d\n", finalMax);
    return 0;
}
