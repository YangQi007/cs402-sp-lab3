/***************************************************************************************
Copyright: 2020 cs402 sp-lab3
File name: basicstats.c
Description: For this lab, you will implement a program that reads data from a file and
             computes some basic statistical analysis measures for the data.
             1.compute mean of data set
             2.compute standard deviation 
             3.compute median of data set
Author:YangQi
Version: v2.0
Date: 04/29/2020
History:    <author>    <time>       <version >   <desc>
             YangQi   04/26/2020       v1.0       build this mudual
             YangQi   04/28/2020       v2.0       build functions
**************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

FILE *openfile(char *filename){
    if(fopen(filename, "r") == NULL){
        printf("error：reading file failed!");
        exit(0);
    }
}

/*compute the mean of the data set*/
double compute_mean(float *p, int n){
    double sum = 0;
    for(int i=0;i<n;i++)
    sum = sum + p[i];
    double mean = sum/n;
    return mean;
}

/*compute standard deviation*/
double compute_stddev(float *p, int n){
    double stddev = 0;
    double mean = compute_mean(p, n);
    for (int i=0; i<n;i++){
        stddev +=pow(p[i] - mean, 2);//standard deviation function
    } 
    return sqrt(stddev/n);
}

/*compute median of the data set*/
double compute_median(float *arr, int n){
    if(n%2 == 1)
    return (arr[n/2]);
    else{
        double min = arr[n/2-1];
        double max = arr[n/2];
        return (min + max)/2;
    }
}

/*sort array*/ 
void swap(float *p1, float *p2){
    float temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

float sort(float *arr, int n){
    int i, j, min_index;
    for(i = 0; i < n-1; i++){
        min_index = i;
        for(j=i+1; j<n; j++)
        if(arr[j] < arr[min_index])
        min_index = j;
        swap(&arr[min_index], &arr[i]);
    }
}

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Enter your file name\n");
        return 0;
    }
    int n = 20;
    int arr_size = 0;
    float temp;
    float *arr = (float *) malloc (n * sizeof(float));
    char *filename = argv[1];
    FILE *fp = openfile(filename);
    
    while(!feof(fp)){
        fscanf(fp,"%f\n", (arr + arr_size));
        arr_size++;
        if(arr_size == n ){
            float *new_arr = (float *) malloc(n * 2 * sizeof(float));//creat a new array with double size
            memcpy(new_arr, arr, arr_size * sizeof(float));// copy old array to new array
            free(arr);
            arr = new_arr;
            n = n*2;//increase array size
        }
    }
    fclose(fp);
    double mean = compute_mean(arr, arr_size);
    double stddev = compute_stddev(arr, arr_size);
    printf("The mean is:%f\n", mean);
    printf("The stddev is: %f\n", stddev);
    sort(arr, arr_size);
    double median = compute_median(arr, arr_size);
    printf("The median is: %f\n", median);
}