# CPSC479-Project-2
Data Science Project

### GROUP MEMBERS:

Zach Serna serna648@csu.fullerton.edu <br>
Nicole Serna NicoleSerna@csu.fullerton.edu

### LANGUAGE USED: 
C++

### HOW TO COMPILE:

add the file to your directory

compile the .cpp file using:```g++ -fopenmp (filename).cpp -o (desiredexecname)```

run the exe with:```./(desiredexecname)```

### DESCRIPTION:

Parallel implementation of the QuickSort Algorithm utilizing C++ and OpenMP. Quicksort uses a pivot point to partition a list of numbers into sub-arrays, with numbers greater than the pivot put into one array and values less than the pivot in the other; the sub-arrays are then sorted recursively. The pivot point in our program is chosen using the Median of Three method. This method compares the first, middle, and last number of an array and then selects the median of the three values as the pivot.
<br>To make this process parallel, the program uses ```#pragma omp parallel sections``` and ```#pragma omp section``` to divide Quicksort's sorting and partitioning process among parallel running sections. ```#pragma omp parallel sections``` combines Omp Parallel and Omp Sections, which are commands that tell the compiler to parallelize the following lines of code within the block and divide the parallelized block of code among the threads to be executed, respectively. <br>Our motivation behind this project was to make a sorting algorithm that could more efficiently sort large amounts of data. Quicksort’s divide-and-conquer formulation makes it an ideal candidate for parallelization.
