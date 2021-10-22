/*
CodeMalloc.c Copy, 11/10/21 Testing repeatable comparison clause
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int varNumber=0;
int mintermNumber=0;
int groupArray[255][255]={0};
int minCopy[255][255]={0};
int notMatched[255][255]={0};
int noMatchCount = 0;

int n=1;
int m=2;
int nVar;
int charRow=0;
int pointCharRow;
int primeCol=0;
int primeImplicants[255][255]={0};
int primeImpCount;
char primeImpChar[255][255]={0};

void primeImpTable(int array[255][255],int minterm_max, int var_max){                                                                           //Initial Print
    printf("-------------------------------------------------------------\n");
    for(int i = 0; i < minterm_max; i++)
    {
        for(int j = 0; j < primeCol; j++)
        {
            printf("%3d", array[i][j] );
        }

        for(int j = primeCol; j < var_max; j++)
        {
            if(j==primeCol){
            putchar('|');
        }
            printf("%4d", array[i][j] );
        }

        printf("\n");
    }
}

int primeImpDistribution(int primeImplicants[255][255]){
    for(int a=1; a<primeImpCount; a++){
        for(int b=0; b<primeCol ; b++){
           for(int c=primeCol; c<mintermNumber+primeCol; c++){
            if(primeImplicants[a][b] == primeImplicants[0][c]){
                primeImplicants[a][c] = 1;
            }
            }
        }
    }
}

int piBinToChar(int minterms[255][255], int counter, int n, int varN, int charRow ){
    for(int x=0; x<counter; x++){
        for(int y=1, z=1; y<varNumber+1;y++,z++){
            if(minterms[x][y+n+varN] == 1){
                primeImpChar[charRow][z] = 64+y;
            }
            else if(minterms[x][y+n+varN]== 0){
                primeImpChar[charRow][z] = 64+y;
                primeImpChar[charRow][z+1] = 96;
                z++;
            }
            else{
                primeImpChar[charRow][z] = 0;
            }
        }
        charRow++;
    }
    pointCharRow=charRow;
}



void decToBinTable(int array[255][255],int minterm_max, int var_max){                                                                           //Initial Print
    printf("-------------------------------------------------------------\n");
    for(int i = 0; i < minterm_max; i++)
    {
        for(int j = 0; j <= var_max; j++)
        {
            printf("%4d ", array[i][j] );
        }
        printf("\n");
    }
}

void comparisonPrint(int array[255][255],int minterm_max, int var_max){                                                                         //Print After
    printf("-------------------------------------------------------------\n");                                                                  //It includes ',' between the 2 minterms matched
    for(int i = 0; i < minterm_max; i++)
    {
        for(int j = 0; j <= var_max; j++)
        {
            if(j==2){
                putchar(',');
            }
            printf("%4d ", array[i][j] );
        }
        printf("\n");
    }
}

void primeImplicantTable(int array[255][255],int minterm_max, int var_max){                                                                         //Print After
    printf("-------------------------------------------------------------\n");                                                                  //It includes ',' between the 2 minterms matched
    for(int i = 0; i < minterm_max; i++)
    {
        for(int j = 0; j <= var_max; j++)
        {
            if(j==2){
                putchar(',');
            }
            printf("%4d ", array[i][j] );
        }
        printf("\n");
    }
}

int decToBinConversion(int mintermArray[255][255],int minterm_max, int var_max){                                                                //Converts the minterms entered into binary and stored them inside minCopy Array
    int minCopy[255][255]={0};
    for(int i=0; i<minterm_max; i++){
        minCopy[i][0] = mintermArray[i][0];
    }
    for(int k=0; k<minterm_max;k++){
        while(minCopy[k][0] != 0){
            for(int d=var_max; d>=1; d--){
                mintermArray[k][d]= minCopy[k][0]%2;
                minCopy[k][0]=minCopy[k][0]/2;
            }
        }
        printf("\n");
    }
}

int groupMinterms(int mintermArray[255][255]){                                                                                                  //Counts each minterm's number of 1's and assigns them to a group based on how many 1's they contained
    int count = 0;
    for(int i=0; i<mintermNumber;i++){
        for(int j=1; j<=varNumber;j++){
            if(mintermArray[i][j] == 1){
                count++;
            }
            for(int x = 0; x<=varNumber;x++){
              if(count == x){
                    groupArray[i][0] = x;
                }
                 groupArray[i][x+1] = mintermArray[i][x];
            }
        }
        count = 0;
    }
}

void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[255][255], int mintermNumber, int varNumber){                                                                           //Bubble sort function, simply rearranges the minterms based on their groups, from 0-n
   int i, j;
   for (i = 0; i < mintermNumber-1; i++){
       for (j = 0; j < mintermNumber-i-1; j++){
           if (arr[j][0] > arr[j+1][0]){
              for(int z = 0;z<varNumber+2;z++){
                swap(&arr[j][z], &arr[j+1][z]);
              }
            }
        }
       for (j = 0; j < mintermNumber-i-1; j++){
       if (arr[j][0] == arr[j+1][0]){
            if(arr[j][1] > arr[j+1][1]){
                for(int z = 1;z<varNumber+2;z++){
                    swap(&arr[j][z], &arr[j+1][z]);
                    }
                }
            }
        }
   }
}
int noMatchedTable(int mintermArray[255][255], int minCopy[255][255], int n ){
    m=n+1;                                                                    //Function to derive the table of unmatched minterms, it compares the matched table to original grouped minterm table
    int counter=0;
    int tempArr[255][255]={0};
    int limit = 2*(int)pow(2,varNumber);                                                                                                                               //if it doesn't find the minterm from the original table inside the matched, it will add it to the unmatched table
    for(int colOne=0; colOne<limit; colOne++){
        for(int w = 1; w<=n;w++){
            for(int colTwo=0; colTwo<limit; colTwo++){
                for(int z = 1; z<=(n+n);z++){
                    if((mintermArray[colOne][w] == minCopy[colTwo][z])){
                        counter++;
                    }
                }
            }
        if(counter >=1){
        }
        else if(counter ==0){
            for(int i=0; i<=varNumber+2; i++){
                tempArr[noMatchCount][i] = mintermArray[colOne][i];
            }
            noMatchCount ++;
        }

        counter = 0;
        }
    }

    int breaking = 0;
    int newCount=0;
    for(int a = 0; a<=noMatchCount;a++){
        for(int b = m; b<=varNumber+n;b++){
                if(tempArr[a][b]==tempArr[a+1][b]){
                    breaking++;
                }
        }
        if(breaking==varNumber){
            for(int j=0;j<varNumber+(m+n);j++){
                notMatched[newCount][j] = tempArr[a][j];
            }
            a++;
            breaking=0;
            newCount++;
        }
        else if(breaking<varNumber){
            for(int j=0;j<varNumber+(m+n);j++){
                notMatched[newCount][j] = tempArr[a][j];
            }
            newCount++;
        }
        breaking=0;
    }
newCount--;
    for(int i=0;i<newCount;i++){
        for(int j=0; j<n;j++){
            primeImplicants[i+1][j] = notMatched[i][j+1];
        }
    }
    piBinToChar(notMatched,newCount,n,0,charRow);
    primeImpCount = newCount+1;
    printf("No match table \n");
    decToBinTable(notMatched,newCount,varNumber+n);
    noMatchCount = 0;
}
int removeDuplicates(int mintermArray[255][255], int n){
    m=n+1;
    int counter=0;
    int breaking=0;
    int newCount=0;
    int disposableArray[255][255]={0};
    int newMax = (n+n)*(int)pow(2,varNumber);
    for (int row = 0; row < (n+n)*(int)pow(2,varNumber) ; row++){
        for(int point = 1; point < newMax; point++){
            while((mintermArray[row+point][0] - mintermArray[row][0])> 0){
                break;
            }
            if((mintermArray[row][0] == mintermArray[row+point][0]) && (mintermArray[row+point][2] >0)){
                for(int i=(m+n); i<varNumber+(m+n); i++){
                    if(mintermArray[row][i] == mintermArray[row+point][i]){
                        breaking++;
                        if(breaking==varNumber){
                                counter++;
                            for(int j=0;j<varNumber+(m+n);j++){
                                disposableArray[counter-1][j] = mintermArray[row][j];
                            }
                        }
                    }
                    else if(breaking<varNumber){
                        newCount++;
                    }
                }
                breaking = 0;
            }
        }
        newMax--;
    }
//Moving either minimised version or original matched minterms to prime implicant tables V
    if(counter>0){
        for(int a = 0; a<counter; a++){
            for(int b = 0; b<n+n; b++){
                primeImplicants[primeImpCount+a][b] = disposableArray[a][b+1];
            }
        }
        primeImpCount = primeImpCount+counter;
        printf("\nFinal Matched\n");
        comparisonPrint(disposableArray,counter,varNumber+n+n);
        //Prime implicants in Char form V
        piBinToChar(disposableArray,counter,n,n,pointCharRow);
    }


    else if(counter==0){
        for(int a = 0; a<newCount; a++){
            for(int b = 0; b<n+n; b++){
                primeImplicants[primeImpCount+a][b] = mintermArray[a][b+1];
            }
        }
        primeImpCount = primeImpCount+newCount;
        //Prime implicants in Char form V
        piBinToChar(mintermArray,newCount,n,n,pointCharRow);
    }




    primeCol=n+n;
}

int comparison(int mintermNumber, int mintermArray[255][255], int varNumber, int n, int m){                                                     //Comparison function, it compares the binary values of the minterms. Minterms have to be within reach based on groupings,
    int disposableArray[255][255]={0};

    int justTest[255][255]={0};
    for(int p = 0; p<(n+n)*(int)pow(2,varNumber);p++){
        for(int q = 0; q<20;q++){
            justTest[p][q] = mintermArray[p][q];
        }
    }
    int row=0;                                                                                                                                  //only groups with difference of 1 can be compared, e.g. Group 0 and 2 cannot be compared, but Group 1-2 can.
    int flag = 0;                                                                                                                               //During comparison, we look for a difference of a single element so e.g. minterm 2 and 3 would be a match
    int nomatch = 0;                                                                                                                            // minterm 2 : 0 0 1 0
    int counter = 0;                                                                                                                            // minterm 3 : 0 0 1 1
    //int noMatchCount = 0;                                                                                                                      // so when matched we will end up with M2,3 : 0 0 1 X, X being a "don't care"
    int newMax = (n+n)*(int)pow(2,varNumber);
       for (row = 0; row < (n+n)*(int)pow(2,varNumber) ; row++){
        for(int point = 1; point < newMax; point++){
            while((mintermArray[row][0] == mintermArray[row+point][0]) || ((mintermArray[row+point][0] - mintermArray[row][0])> 1)){
                    break;
            }
            if((mintermArray[row+point][0] - mintermArray[row][0])==1){
                for(int countMatch = m; countMatch <= varNumber+n; countMatch++){
                    if(mintermArray[row][countMatch] != mintermArray[row+point][countMatch]){
                        nomatch = countMatch;
                        flag++;
                    }
                }
                if(flag == 1){
                    for(int i=(m+n); i<varNumber+(m+n); i++){
                        disposableArray[counter][i] = mintermArray[row][i-n];
                        disposableArray[counter][nomatch+n] = 9;

                        }
                    for(int q = 1; q<=n; q++){
                        disposableArray[counter][q+n] = mintermArray[row+point][q];
                        }
                    for(int a = 0; a<m; a++){
                        disposableArray[counter][a] = mintermArray[row][a];
                        }
                    flag = 0;
                    counter ++;
                }
                else{
                    flag = 0;
                }
            }
        }
        newMax--;
    }


    for(int p = 0; p<(n+n)*(int)pow(2,varNumber);p++){
        for(int q = 0; q<20;q++){
        minCopy[p][q] = disposableArray[p][q];
        }
    }

    if(n==1){
    printf("Matched table\n");
    comparisonPrint(minCopy,counter,varNumber+2);


    }
    else if(n>1){
        printf("Matched table\n");
        comparisonPrint(minCopy,counter,varNumber+n+n);
    }

    noMatchedTable(justTest, minCopy, n);

        n=n+n;
        m=n+1;
        nVar=n;
    if(checkForMoreMatches(minCopy,mintermNumber,varNumber, n)==true){
        comparison(mintermNumber, minCopy, varNumber, n, m);  // n m
    }
    else{
    }
}


int checkForMoreMatches(int minCopy[255][255], int mintermNumber, int varNumber, int n){
    m = n+1;
    int flag = 0;
    int newMax = (n+n)*(int)pow(2,varNumber);
    for (int row = 0; row < (n+n)*(int)pow(2,varNumber) ; row++){
    for (int point = 1; point < newMax; point++){
        while((minCopy[row][0] == minCopy[row+point][0]) || ((minCopy[row+point][0] - minCopy[row][0])> 1)){
                break;
            }
        if((minCopy[row+point][0] - minCopy[row][0])==1){
                for(int countMatch = m; countMatch <= varNumber+n; countMatch++){
                    if(minCopy[row][countMatch] != minCopy[row+point][countMatch]){
                        flag++;
                    }
                }
                if(flag==1){
                    return true;
                    flag = 0;
                }
                else{
                    flag = 0;
                }
            }
        }
        newMax--;
    }
}


int main(){
    int mintermArray[255][255]={0};
    int mintermList[255][255]={0};
    printf("Enter how many Variables\n");
    scanf("%d", &varNumber);
    printf("Enter how many minterms\n");
    scanf("%d", &mintermNumber);

    for(int i=0;i<mintermNumber;i++){
        printf("Enter minterm\n");
        scanf("%d", &mintermArray[i][0]);
    }
    for(int a = 0; a<mintermNumber;a++){
        mintermList[0][a]=mintermArray[a][0];
    }

decToBinConversion(mintermArray,mintermNumber,varNumber);
printf("\nEntered 2-D array is:\n");
printf("Group  Min   A    B    C    D\n");
decToBinTable(mintermArray,mintermNumber,varNumber);
groupMinterms(mintermArray);
printf("\n\nGrouped minterm table:\n");
printf("Group  Min   A    B    C    D\n");
decToBinTable(groupArray,mintermNumber,varNumber+1);
printf("\n\nAnd this ordered:\n");
printf("Group  Min   A    B    C    D\n");
bubbleSort(groupArray,mintermNumber,varNumber);
decToBinTable(groupArray,mintermNumber,varNumber+1);

comparison(mintermNumber,groupArray, varNumber, n, m);
removeDuplicates(minCopy,nVar/2);

printf("\n PRIME IMPLICANTS\n");
for(int c=0;c<mintermNumber;c++){
    primeImplicants[0][c+primeCol] = mintermList[0][c];
}
primeImpDistribution(primeImplicants);
primeImpTable(primeImplicants,primeImpCount,primeCol+mintermNumber);

 for(int i = 0; i < primeImpCount; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            printf("%c", primeImpChar[i][j] );
        }
        printf("\n");
    }


}



