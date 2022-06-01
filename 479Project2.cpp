#include<iostream>
#include<omp.h>
#include <sstream>
#include<string.h>

using namespace std;

class ParallelQuickSort{
    //tracks the number of threads
    int threadnum = 0;

    private:    
        //partitions the array based on choosen pivot
        int partition(int arr[], int first, int last){
            //pivot point is choosen by using median of three method
            //after function is ran first element is used as pivot
            medianOfThree(arr, first, last);
            int pivot = arr[first];
            //iterates through the list using the last value and second value
            int i = first + 1;
            int j = last;
            //while loop continues until new partition point is found and returned
            //swaps values in accordance to pivot; values less than pivot go to the left and greater 
            //go to the right
            while(true){
                while(arr[i] <= pivot && i < last)
                    i++;
                while(arr[j] > pivot)
                    j--;
                if(i < j){
                    swap(arr[i], arr[j]);
                }else{
                    swap(arr[first], arr[j]);
                    return j;
                }
            }
        }
        //an ideal pivot point is the median of a list
        //selecting the first element as the pivot increases the chance of the worst possible time complexity
        //however going through the entire list for the median is not efficient
        //taking all that into consideration we used the Median of Three Method to choose a pivot

        //we compare the first, middle, and last elements in the list
        //and use the median element as the pivot

        //the elements are swapped so that
        //middle < first < last
        //because our partition function uses the first element as the pivot
        //we want the first element to be the median of the three
        void medianOfThree(int arr[], int first, int last) {
            int mid = (first + last)/2;
             if(arr[mid] > arr[last]) {
                swap(arr[last], arr[mid]);
            }
            if(arr[last] < arr[first]) {
                swap(arr[first], arr[last]);
            }
            if(arr[mid] > arr[first]) {
                swap(arr[mid], arr[first]);
            }
        }

    public:
    //function to execute QuickSort in parallel
    //n processes partition the list and sort it using selected pivot element (first element of list)
    //Each process finds the next partition point and sorts that sublist based on a new pivot
    //the n processes work on all partitions
    //all sublist are then merged to form the fully sorted array
        void quickSort(int arr[], int first, int last){
            if(first < last){
                int partitionPoint = partition(arr, first, last);
                stringstream msg;
                msg << "partition " << partitionPoint << " found by thread no. " << threadnum << "\n"; 
                cout <<msg.str();

                #pragma omp parallel sections
                {
                    #pragma omp section
                    {
                        threadnum = threadnum + 1;
                        quickSort(arr, first, partitionPoint-1);
                    }
                    #pragma omp section
                    {
                        threadnum = threadnum + 1;
                        quickSort(arr, partitionPoint+1, last);
                    }
                }
            }
        }
       //function to print the array after sorting
        void print(int arr[], int n){
            for(int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << endl;
        }
        //function used to run the sorting algorithm.
        //array to be sorted is inputed here
        void run(){
            int arr[] = {9, 0, 11, 13, 7, 19, 6, 4, 2, 20, 14, 60, 100, 40, 71, 315, 417, 15, 90, 64, 38, 17, 57, 78, 24, 23, 85, 1};
            int size = sizeof(arr)/sizeof(arr[0]);
            quickSort(arr, 0, size-1);
            print(arr, size);
        }
};
//driver function
int main(){
    ParallelQuickSort test;
    test.run();
    return 0;
}