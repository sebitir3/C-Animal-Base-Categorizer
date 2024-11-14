#include "givenA1.h"
#include "helper.h"

// TASK 1
int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]){

    //open file in read mode
    FILE *fptr;
    fptr = fopen (fName, "r");

    //check for errors reading file
    if(fptr == NULL){
        //printf("error");
        return -1;
    }

    for (int i = 0; i < NUM_SAMPLES; i++){
        //fscanf animal name, all features and class label
        fscanf(fptr,"%s ", dataZoo[i].animalName);
        for (int j = 0; j < NUM_FEATURES; j++){
            fscanf(fptr,"%d ", &dataZoo[i].features[j]);
        }
        fscanf(fptr,"%d ", &dataZoo[i].classLabel);
    }
    fclose(fptr);
    // scan was successful
    return 1;
}

// TASK 2
int generateStatisticsFeatureX (struct Animal dataZoo [NUM_SAMPLES], int whichFeature, float * mean, int * mode){
    // mean vars
    float sum = 0;
    // mode vars
    int mostOccurred = 0;
    int modeValue = 0;
    int counter = 0;
    int temp;
    // check if feature number is valid
    if(whichFeature < 0 || whichFeature > 16){
        return -1;
    }
    // if valid
    for(int i = 0; i < NUM_SAMPLES; i++){
        // mean
        sum += dataZoo[i].features[whichFeature];
    }
    *mean = sum / NUM_SAMPLES;
    // mode
    // iterate through a given feature of each animal and compare it
    // to the same feature of all the other animals
    for (int j = 0; j < NUM_SAMPLES; j++){
        // reset the counter for each new animal being compared to everything
        counter = 0;
        // if a feature number is equal to the base animal that is being
        // compared to everything, increase a counter by 1
        for (int k = 0; k < NUM_SAMPLES; k++){
            if (dataZoo[j].features[whichFeature] == dataZoo[k].features[whichFeature]){
                counter++;
            }
        }
        // if the counter is greater than the previously msot occuring
        // feature number, it becomes the new most occured value
        if (counter > mostOccurred){
            // store the previous mostOccured # as a temp
            temp = mostOccurred;
            mostOccurred = counter;
            // if previous most and current most are equal, there are
            // multiple modes
            if (mostOccurred == 1){
                printf("There is no mode");
                return -2;
            } else if(mostOccurred == temp){
                modeValue = dataZoo[j].features[whichFeature];
                printf("There are multiple modes for this feature.");
            } else {
                // set the specific feature value as the mode
                modeValue = dataZoo[j].features[whichFeature];
            }
        }
    }
    // return mode
    *mode = modeValue;
    return 1;
}

// TASK 3
void classDistribution (struct Animal dataZoo [NUM_SAMPLES]){
    // intiialize an array for the totals of each class label
    int classLabelsArr [7];
    // set each to 0
    for(int k = 0; k < NUM_CLASSES; k++){
        classLabelsArr [k] = 0;
    }

    // store the amount of each class label into its respective position
    // in the array (offset by 1, so [0] is label1, [1] is label 2 etc.
    for(int i = 0; i < NUM_SAMPLES; i++){
        for(int j = 0; j < NUM_CLASSES; j++){
            if(dataZoo[i].classLabel == (j + 1)){
                classLabelsArr[j] = classLabelsArr[j] + 1;
            }
        }
    }

    // find the largest total
    int largestClass = classLabelsArr[0];
    for (int r = 0; r < NUM_CLASSES; r++){
        if(classLabelsArr[r] > largestClass){
            largestClass = classLabelsArr[r];
        }
    }

    // variables for histogram drawing
    int verticalBuffer = largestClass;

    // start histogram on new line
    printf("\n");

    // iterate the highest label total + 1 vertically (columns)
    // to account for the (number) at the top of each column
    for (int v = verticalBuffer + 1; v > 0; v--){
        // iterate through each row in the seven colums
        for (int h = 0; h < NUM_CLASSES; h++){
            // when label total + 1 is equal to the current vertical spot
            // print the label total in () --> i.e. above the column
            if (classLabelsArr[h] + 1 == v){
                // add offset to account for single digits
                if(classLabelsArr[h] < 10){
                    printf("  (%d)     ", classLabelsArr[h]);
                } else {
                    // double digits
                    printf("  (%d)   ", classLabelsArr[h]);
                }
            } else if(classLabelsArr[h] >= v){
                // if the label total is larger than the vertical buffer 
                // (counting down), print a star
                printf("   *      ");
            } else {
                // if not, print space
                printf("          ");
            }
        }
        // spacer
        printf("\n");
    }
    // print each class (1, 2, 3, etc.) under the respective column
    for (int a = 0; a < NUM_CLASSES; a++){
        printf("Class %d   ", a + 1);
    }

    // spacer
    printf("\n");

}

// TASK 4
float euclideanDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
    // sum to return (declare as float to avoid casting later)
    float euDistance = 0;
    // apply the summation portion of the euclidean distance for each
    // position in both vectors
    for (int i = 0; i < NUM_FEATURES; i++){
        euDistance += ((vector1[i] - vector2[i])*(vector1[i] - vector2[i]));
    }
    // apply the sqare root function to complete the equation and return the result
    float result = sqrt(euDistance);
    return result;
}

// TASK 5
int hammingDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
    // variable to count how many matching pairs between the two vectors
    int counter = 0;
    // iterate through each postition of both vectors
    // increase counter if the #s at the position DONT match
    for (int i = 0; i < NUM_FEATURES; i++){
        if(vector1[i] != vector2[i]){
            counter++;
        }
    }
    // return the counter, representing the hammingDistance
    return counter;
}

// TASK 6
float jaccardSimilarity (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
    // variables for 1-1 and 0-0 pairs, along with the result to be returned
    int oneToOne = 0, zeroToZero = 0;
    float result = 0;
    // iterate through each feature in both vectors
    for (int i = 0; i < NUM_FEATURES; i++){
        // check for 1-1 pairs, 0-0 pairs
        if(vector1[i] == 1 && vector2[i] == 1){
            oneToOne++;
        } else if (vector1[i] == 0 && vector2[i] == 0){
            zeroToZero++;
        }
    }
    // apply the jaccard similarity formula and convert to float
    result = (float)oneToOne/(float)(NUM_FEATURES - zeroToZero);
    return result;
}

// HELPER FUNCTIONS FOR TASK 7

//swap the postion of two floats w/ pointers
void swapFloats(float* p1, float* p2){
    float temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

//swap the position of two intgeres with pointers
void swapInts(int* p1, int* p2){
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// bubble sorting algorithm
void bubbleSortAlgorithm(float arr[], int arr2[]){
    // position variable and swapped state variable
    int pos1, pos2, swapped = 0;
    // iterate through all of the position1s up to 98, setting swapped to 0
    for (pos1 = 0; pos1 < NUM_SAMPLES - 1; pos1 ++){
        swapped = 0;
        // iterate through all the position2s up to the last term minus the
        // current iteration of position1
        for (pos2 = 0; pos2 < NUM_SAMPLES - pos1 - 1; pos2++) {
            // if the arr at pos2 is greater than the next pos2, swap
            // the positions in the float array and knearestneighbors array
            if (arr[pos2] > arr[pos2 + 1]){
                swapFloats(&arr[pos2], &arr[pos2 + 1]);
                swapInts(&arr2[pos2], &arr2[pos2 + 1]);
                // change swapped state
                swapped = 1;
            }
        }
        // if nothing is swapped in this iteration 
        if (swapped == 0){
            break;
        }
    }
}

/* refereces for the above 3 helper functions: 
“Bubble Sort - Data Structure and Algorithm Tutorials.” GeeksforGe>
     www.geeksforgeeks.org/bubble-sort/.
*/

// TASK 7
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]){
    // use all  to find k nearest neighbours
    // declare a float array to store all values
    float distancesArr[NUM_SAMPLES];
    // fill kNearestNeighbors with each index of all samples (0-99)
    // to manipulate later
    for (int i = 0; i < NUM_SAMPLES; i++){
        kNearestNeighbors[i] = i;
        //printf("%d\n", kNearestNeighbors[i]);
    }
    // fill the distances array with the users choice of distance function
    for (int j = 0; j < NUM_SAMPLES; j++){
        // euclidean distance whichDistanceFunction == 1; hamming distance wDF == 2; jaccard similarity wDF == 3;
        if (whichDistanceFunction == 1){
            distancesArr[j] = euclideanDistance(dataZoo[j].features, newSample);
        } else if (whichDistanceFunction == 2){
            distancesArr[j] = hammingDistance(dataZoo[j].features, newSample);
        } else {
            distancesArr[j] = jaccardSimilarity(dataZoo[j].features, newSample);
        }
    }
    // sort the distances along with the coresponing indexes in kNearestNeighbours
    bubbleSortAlgorithm(distancesArr, kNearestNeighbors);

}



// TASK 8
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int neighborsForNewSample [NUM_SAMPLES], int newSample [NUM_FEATURES], int k){


    // find the nearestkNeighbors to predict the classLabel of new data
    findKNearestNeighbors (dataZoo, newSample, k, 2, neighboursForNewSample);
    // counters and vars
    int occurCounter = 0;
    int mostOccurredLabel = 0;
    int predictedClassLabel = 0;
    // find the most occurring classlabel in the kNearestNeighbor indicies of
    // the dataZoo dataset
    // both for loop are bounded by k, as thats how many array terms
    // we are comparing all kNearestNeighbors to find predicted class
    for (int i = 0; i < k; i++){
        // reset occurCounter every iteration of the dataZoo being
        // compared to the new kNeighbours indecies
        occurCounter = 0;
        // if classLabel are equal for both indices
        // increase a counter by 1
        for (int j = 0; j < k; j++){
            if (dataZoo[neighborsForNewSample[i]].classLabel == dataZoo[neighborsForNewSample[j]].classLabel){
                occurCounter++;
            }
        }
        // if the occurences are greater than the previously highest occuring
        // classLabel, it gets set as the new most occurring classLabel
        // the predicted value is then equal to the datazoo classlabel
        // at the current index (i.e. mode)
        if (occurCounter > mostOccurredLabel){
            mostOccurredLabel = occurCounter;
            predictedClassLabel = dataZoo[neighborsForNewSample[i]].classLabel;

        }
    }
    // return prediction
    return predictedClassLabel;
}

int readCSV (char csvFile[30], struct Animal testData [NUM_SAMPLES]){
    //open file in read mode
    FILE *CSVptr;
    CSVptr = fopen (csvFile, "r");

    //check for errors reading file
    if(CSVptr == NULL){
        return -1;
    }

    for(int i = 0; i < NUM_TEST_DATA; i++){
        // fscanf animal name, all features and class label of the csv file
        // use [^,] to stop reading the string at the comma, and add commas in the fscanfs to ignore
        // the csv commas
        fscanf(CSVptr,"%[^,],", testData[i].animalName);
        for (int j = 0; j < NUM_FEATURES; j++){
            fscanf(CSVptr, "%d,", &testData[i].features[j]);
        }
        fscanf(CSVptr, "%d", &testData[i].classLabel);
    }
    fclose(CSVptr);
    // scan was successful
    return 1;
}

// TASK 9
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], struct Animal testData [NUM_TEST_DATA], int k){
    // counters and variables
    float accuracyOutput = 0;
    int correctPrediction = 0;
    int predictedClass = 0;
    int accuracyNeighborsArr[NUM_SAMPLES];
    // iterate through all test data and predict its class
    for(int i = 0; i < NUM_TEST_DATA; i++){
        predictedClass = predictClass (dataZoo, accuracyNeighborsArr, testData[i].features, k);
        // increase the correct predictions if it mathces its actual classLabel
        if(testData[i].classLabel == predictedClass){
            correctPrediction ++;
        }
    }
    // apply the accuracy formula
    accuracyOutput = (float)correctPrediction/NUM_TEST_DATA;
    return accuracyOutput;
}
