#include "givenA1.h"
#include "helper.h"

int main() {
     // Task 1 Variables
    struct Animal dataZoo [NUM_SAMPLES];
    char textFile[30];
    int choice = 0;
    int task1 = 0;

    // Task 2 Variables
    int mode;
    float mean;
    int whichFeature = 0;
    int task2 = 0;

    // Task 3 Variables
    // None

    // Task 4, 5 and 6 Variables
    int vector1[NUM_FEATURES];
    int vector2[NUM_FEATURES];

    float task4 = 0;
    int task5 = 0;
    float task6 = 0;

    // Task 7, 8 Variables
    int newSample[NUM_FEATURES];
    int k = 0;
    int whichDistanceFunction = 0;
    int kN[NUM_SAMPLES];
    int classPrediction = 0;

    // Task 9 Variables
    struct Animal testData [NUM_SAMPLES];
    char csvFile[30];
    float acc = 0;
    int rCSV = 0;

    // Testing for Task 1
    strcpy(textFile, "a1Data.txt");
    task1 = readFromFile (textFile, dataZoo);

    if (task1 == 1) {
        printf("Reading data was successful");
    } else {
        printf("Error reading the file.\n");
    }


// menu
    do {
        printf ("\nHere is the menu - enter a number between 1 and 9 \n\n");
        printf ("1. Task 2 – find the mean and mode of a certain feature\n");
        printf ("2. Task 3 – display a vertical histogram showing the amount of each class label\n");
        printf ("3. Task 4 – find the euclidean distance between two vectors of size 16\n");
        printf ("4. Task 5 – find the hamming distance between two vectors of size 16\n");
        printf ("5. Task 6 – find the jaccard similarity between two vectors of size 16\n");
        printf ("6. Task 7 – find the k nearest neighbors of a new sample\n");
        printf ("7. Task 8 – predict the class of a new sample\n");
        printf ("8. Task 9 – find the accuracy of the ML algorithm with a new data set\n");
        printf ("9. Exit\n");

        printf ("Enter your choice: ");

        // validate choice here - should be a integer between 1 and 9
        while(scanf ("%d", &choice) != 1 ||choice < 1 || choice > 9){
            printf("Invalid input.\nEnter another choice: ");
            // clear input stream; varifies the input stream for a new line and then stops loop
            while(fgetc(stdin) != '\n');
        }
        switch (choice) {
            case 1:
                // Task 2 - mean and mode
                // asks user to enter a feature number to which mean and mode will be calculated and displayed
                printf("Enter a feature number between 0 and 15: ");

                // check if scanf return 1 (input is an integer) and if its a positive number
                while(scanf ("%d", &whichFeature) < 0 || whichFeature > 15){
                    printf("Invalid input.\nEnter another choice: ");
                    // clear input stream; varifies input stream for new line and then stops loop
                    while(fgetc(stdin) != '\n');
                }
                // call and print mean and mode
                task2 = generateStatisticsFeatureX (dataZoo, whichFeature, &mean, &mode);
                if (task2 == 1){
                    printf("\nMean and Mode were found.");
                } else if (task2 == -2){
                    printf("\nThere is no mode.");
                } else if (task2 == -1){
                    printf("\nInvalid feature number.");
                }
                printf("\nThe Mean of Feature %d is: %.2f, The Mode of Feature %d is: %d\n", whichFeature, mean, whichFeature, mode);

                break;

            case 2:
                // Task 3 - print verical histogram
                classDistribution(dataZoo);
                break;

            case 3:
                // Task 4 - find euclidean distance between two vectors
                // ask user for vectors 1 and 2
                printf("Enter 16 entries for the first vector:\n");
                for (int i = 0; i < NUM_FEATURES; i++){
                    if(i == NUM_FEATURES - 1){
                        scanf("%d", &vector1[i]);
                    } else {
                        scanf("%d ", &vector1[i]);
                    }
                }
                printf("Enter the second vectors entries:\n");
                for (int j = 0; j < NUM_FEATURES; j++){
                    if(j == NUM_FEATURES - 1){
                        scanf("%d", &vector2[j]);
                    } else {
                        scanf("%d ", &vector2[j]);
                    }
                }
                // calculate euclidean distance
                task4 = euclideanDistance (vector1, vector2);
                printf("\nThe Euclidean Distance between V1 and V2 is: %.2f\n", task4);
                break;

            case 4:
                // Task 5 - find hamming distance between two vectors
                // ask user for vectors 1 and 2
                printf("Enter 16 entries for the first vector:\n");
                for (int i = 0; i < NUM_FEATURES; i++){
                    if(i == NUM_FEATURES - 1){
                        scanf("%d", &vector1[i]);
                    } else {
                        scanf("%d ", &vector1[i]);
                    }
                }
                printf("Enter the second vectors entries:\n");
                for (int j = 0; j < NUM_FEATURES; j++){
                    if(j == NUM_FEATURES - 1){
                        scanf("%d", &vector2[j]);
                    } else {
                        scanf("%d ", &vector2[j]);
                    }
                }
                // calculate hamming distance
                task5 = hammingDistance (vector1, vector2);
                printf("\nThe Hamming Distance between V1 and V2 is:  %d\n", task5);
                break;

            case 5:
                // Task 6 - find the jaccard similarity between two vectors
                // ask user for vectors 1 and 2
                printf("Enter 16 entries for the first vector:\n");
                for (int i = 0; i < NUM_FEATURES; i++){
                    if(i == NUM_FEATURES - 1){
                        scanf("%d", &vector1[i]);
                    } else {
                        scanf("%d ", &vector1[i]);
                    }
                }
                printf("Enter the second vectors entries:\n");
                for (int j = 0; j < NUM_FEATURES; j++){
                    if(j == NUM_FEATURES - 1){
                        scanf("%d", &vector2[j]);
                    } else {
                        scanf("%d ", &vector2[j]);
                    }
                }
                // calculate jaccard simalarity
                task6 = jaccardSimilarity(vector1, vector2);
                printf("\nThe Jaccard Similarity between V1 and V2 is: %.2f\n", task6);

                break;

            case 6:
                // Task 7 - Find the k nearest neighbors of a new sample
                // ask for the value of k neighbors
                printf("\nEnter how many k neighbors that will be returned: ");
                scanf("%d", &k);
                // ask for one of three distance formulas to be used
                printf("\nEnter the distance formula to be used for Task 7, 8, and 9: ");
                scanf("%d", &whichDistanceFunction);
                // fill sample
                printf("Fill a new sample with 16 integer features:\n");
                for (int i = 0; i < NUM_FEATURES; i++){
                    if(i == NUM_FEATURES - 1){
                        scanf("%d", &newSample[i]);
                    } else {
                        scanf("%d ", &newSample[i]);
                    }
                }
                // set output array entries to zero
                for(int j = 0; j < NUM_SAMPLES; j++){
                    kN[j] = 0;
                }
                // function call
                findKNearestNeighbors (dataZoo, newSample, k, whichDistanceFunction, kN);
                // print the k nearest neighbours
                printf("\nThe %d nearest neightbors are: ", k);
                // exclude comma for the last k neighbor
                for (int a = 0; a < k; a++){
                    if (a != k - 1){
                        printf("%d, ", kN[a]);
                    } else {
                        printf("%d\n", kN[a]);
                    }
                }
                break;
            case 7:
                // Task 8 - predict the class of a new sample with the previous distance formula
                // ask for the value of k neighbors in the prediction
                printf("\nEnter how many k neighbors that will be used to predict a class label: ");
                scanf("%d", &k);
                printf("Fill a new sample with 16 integer features:\n");
                // fill sample
                for (int i = 0; i < NUM_FEATURES; i++){
                    if(i == NUM_FEATURES - 1){
                        scanf("%d", &newSample[i]);
                    } else {
                        scanf("%d ", &newSample[i]);
                    }
                }
                // set output array entries to zero
                for(int i = 0; i < NUM_SAMPLES; i++){
                    kN[i] = 0;
                }
                // predict the class label
                classPrediction = predictClass(dataZoo, kN, newSample, k);
                printf("\nClass Label Prediction: %d\n", classPrediction);
                break;

            case 8:
                // Task 9 - find the accuracy of the prediction
                // call the helper function to read from CSV file
                strcpy(csvFile, "testData.csv");
                rCSV = readCSV(csvFile, testData);
                // ask for the value of k neighbors in the prediction
                printf("\nEnter how many k neighbors that will be used to find the accuracy of class label predictions: ");
                scanf("%d", &k);
                // call function and multiply by 100 to get percentage value
                acc = 100 * findAccuracy(dataZoo, testData, k);
                if (rCSV == 1){
                    printf("\nReading from CSV successful.");
                } else {
                    printf("\nError reading from CSV file");
                }

                printf("\nThe Accuracy of the ML Algorithm is %.2f Percent\n", acc);
                break;
            //invalid choice
            default: printf ("That is an invalid choice\n");
        }
    // exit program
    } while (choice != 9);
        return 0;
}

