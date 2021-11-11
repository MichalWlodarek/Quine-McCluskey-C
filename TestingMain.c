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
int noPiCount=0;
int n=1;
int m=2;
int nVar;
int charRow=0;
int pointCharRow;
int primeCol=0;
int countZero=0;
int howManyOnes=0;
int howManyTwos=0;
int howManyThrees=0;
int primeImplicants[255][255]={0};
int primeImpCount;
char primeImpChar[255][255]={0};
char finalBoolean[255][255]={0};
int finalRow=0;
int limitCount=0;

void primeImpTable(int array[255][255],int minterm_max, int var_max, int nVar){
    printf("\nPrime Implicants Table\nGroups");
    if(nVar<=2){
        printf("    Minterms");
    }
    else if(nVar==4){
        printf("          Minterms");
    }
    else if(nVar==8){
        printf("                      Minterms");
    }
    printf("\n------------------------------------------------------------------\n");
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
                if(b>=1 && primeImplicants[a][b]==0 && primeImplicants[a][0]!=0){
                    primeImplicants[a][c] = 0;
                }
                else{
                    primeImplicants[a][c] = 1;
                }
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

void decToBinTable(int array[255][255],int minterm_max, int var_max){
    for(int a=0; a<varNumber;a++){
        printf("%c    ",65+a);
    }
    printf("\n------------------------------------------------------------------\n");
    for(int i = 0; i < minterm_max; i++)
    {
        for(int j = 0; j <= var_max; j++)
        {
            printf("%4d ", array[i][j] );
        }
        printf("\n");
    }
}

void comparisonPrint(int array[255][255],int minterm_max, int var_max, int varN){
    printf("\nGroup  Min   ");
    if(varN==1){
        printf("      ");
    }
    else if(varN==2){
        printf("                  ");
    }
    else if(varN==4){
        printf("                                    ");
    }
    for(int a=0; a<varNumber;a++){
        printf("%c    ",65+a);
    }
    printf("\n------------------------------------------------------------------\n");
    for(int i = 0; i < minterm_max; i++)
    {
        for(int j = 0; j <= var_max; j++)
        {
            if(j==2){
                putchar(',');
            }
            if(varN==2){
                if(j==3 || j==4){
                    putchar(',');
                }
            }
            printf("%4d ", array[i][j] );
        }
        printf("\n");
    }
}

void primeImplicantTable(int array[255][255],int minterm_max, int var_max){
    printf("\n------------------------------------------------------------------\n");
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

int decToBinConversion(int mintermArray[255][255],int minterm_max, int var_max){
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

int groupMinterms(int mintermArray[255][255]){
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

void bubbleSort(int arr[255][255], int mintermNumber, int varNumber){
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
    m=n+1;
    int counter=0;
    int sameCount=0;
    int tempArr[255][255]={0};
    int limit=0;
    int numRows=0;
    for(int move=0; move<(n+n)*(int)pow(2,varNumber);move++){
                if(mintermArray[move][0]>0 || mintermArray[move+1][0]>0 || mintermArray[move][1]>0 || mintermArray[move+1][1]>0 || mintermArray[move][2]>0 || mintermArray[move+1][2]>0){
                    numRows++;
                }
                if(minCopy[move][0]>0 || minCopy[move+1][0]>0 || minCopy[move][1]>0 || minCopy[move+1][1]>0 || minCopy[move][2]>0 || minCopy[move+1][2]>0){
                    limit++;
                }
            }
    for(int colOne=0; colOne<numRows; colOne++){
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
            if(noMatchCount==0){
            for(int i=0; i<=varNumber+n; i++){
                tempArr[noMatchCount][i] = mintermArray[colOne][i];
            }
            noMatchCount ++;
            }
            else if(noMatchCount>0){
                for(int row =0; row<noMatchCount;row++){
                    for(int col = m; col<m+n; col++){
                        if(mintermArray[colOne][col]==tempArr[row][col]){
                            sameCount++;
                        }
                    }
                }
                if(sameCount<varNumber){
                    for(int i=0; i<=varNumber+n; i++){
                        tempArr[noMatchCount][i] = mintermArray[colOne][i];
                    }
                    noMatchCount ++;
                }
                sameCount=0;
            }
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
    noPiCount++;

    for(int i=0;i<newCount;i++){
        for(int j=0; j<n;j++){
            if(noPiCount==1){
                primeImplicants[i+1][j] = notMatched[i][j+1];
            }
            else if(noPiCount>1){
                primeImplicants[primeImpCount+i][j] = notMatched[i][j+1];
            }
        }
    }
    if(noPiCount==1){
        primeImpCount = newCount+1;
        piBinToChar(notMatched,newCount,n,0,charRow);
    }
    else if(noPiCount>1){
        primeImpCount=newCount+primeImpCount;
        piBinToChar(notMatched,newCount,n,0,pointCharRow);
    }
    if(newCount>0){
        printf("\nNo match table\nGroup  Min   ");
        if(n==2){
            printf("     ");
        }
        else if(n==4){
            printf("               ");
        }
        else if(n==8){
            printf("                              ");
        }
        decToBinTable(notMatched,newCount,varNumber+n);
    }
    noMatchCount = 0;
}

int removeDuplicates(int mintermArray[255][255], int n){
    m=n+1;
    int thisAdded=0;
    int anotherAdded=0;
    int wasntThere=0;
    int wasThere=0;
    int counter=0;
    int breaking=0;
    int numRows=0;
    int disposableArray[255][255]={0};
    int newMax = (n+n)*(int)pow(2,varNumber);
    for(int move=0; move<(n+n)*(int)pow(2,varNumber);move++){
                if(mintermArray[move][0]>0 || mintermArray[move+1][0]>0 || mintermArray[move][1]>0 || mintermArray[move+1][1]>0 || mintermArray[move][2]>0 || mintermArray[move+1][2]>0){
                    numRows++;
                }
            }
    for(int j=0;j<varNumber+(m+n);j++){
            disposableArray[counter][j] = mintermArray[0][j];
        }
    for (int row = 0; row < numRows ; row++){
        for(int point = 1; point < newMax; point++){
            if(mintermArray[row+point][2] >0){
                for(int i=(m+n); i<varNumber+(m+n); i++){
                    if(mintermArray[row][i] == mintermArray[row+point][i]){
                        breaking++;
                    }
                }
                if(breaking==varNumber){
                        thisAdded++;
                }
                else if(breaking<varNumber){
                        for(int rowA=0; rowA<counter+1;rowA++){
                            for(int colA=(m+n);colA<varNumber+(m+n);colA++){
                                if(mintermArray[row+point][colA]== disposableArray[rowA][colA]){
                                    anotherAdded++;
                                }
                            }
                            if(anotherAdded<varNumber){
                                wasntThere++;
                            }
                            else if(anotherAdded==varNumber){
                                wasThere++;
                            }
                            anotherAdded=0;
                        }
                    if(wasThere==0){
                    counter++;
                    for(int j=0;j<varNumber+(m+n);j++){
                        disposableArray[counter][j] = mintermArray[row+point][j];
                        }
                        row=row + thisAdded;
                    }
                    wasntThere=0;
                    wasThere=0;
                }
                breaking = 0;
            }
        }
        newMax--;
    }
    if(counter>0){
        for(int a = 0; a<=counter; a++){
            for(int b = 0; b<n+n; b++){
                primeImplicants[primeImpCount+a][b] = disposableArray[a][b+1];
            }
        }
        primeImpCount = primeImpCount+counter+1;
        printf("\nFinal Matched");
        comparisonPrint(disposableArray,counter+1,varNumber+n+n,n);
        piBinToChar(disposableArray,counter+1,n,n,pointCharRow);
    }
    else if(counter==0){
        for(int a = 0; a<1; a++){
            for(int b = 0; b<n+n; b++){
                primeImplicants[primeImpCount+a][b] = mintermArray[a][b+1];
            }
        }
        primeImpCount = primeImpCount+1;
        piBinToChar(mintermArray,1,n,n,pointCharRow);
    }
    primeCol=n+n;
}

int comparison(int mintermNumber, int mintermArray[255][255], int varNumber, int n, int m){
    int disposableArray[255][255]={0};
    int justTest[255][255]={0};
    for(int p = 0; p<(n+n)*(int)pow(2,varNumber);p++){
        for(int q = 0; q<40;q++){
            justTest[p][q] = mintermArray[p][q];
        }
    }
    int row=0;
    int flag = 0;
    int nomatch = 0;
    int counter = 0;
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
    printf("\nMatched table");
    comparisonPrint(minCopy,counter,varNumber+2,n);
    }
    else if(n>1){
        printf("\nMatched table");
        comparisonPrint(minCopy,counter,varNumber+n+n,n);
    }
    noMatchedTable(justTest, minCopy, n);
    n=n+n;
    m=n+1;
    nVar=n;
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

int countingOnesPI(){
    int rowPICount=0;
    int countPI=0;
    countZero=0;
    int primeCounter=0;
    howManyOnes = 0;
    for(int col=primeCol; col<mintermNumber+primeCol;col++){
        for(int row=1; row<primeImpCount;row++){
            if(primeImplicants[row][col]==1){
                primeCounter++;
            }
        }
        if(primeCounter>0){
            primeImplicants[primeImpCount][col] = primeCounter;
            if(primeCounter == 1){
                howManyOnes++;
            }
            else if(primeCounter == 2){
                howManyTwos++;
            }
            else if(primeCounter == 3){
                howManyThrees++;
            }
        }
        else if(primeCounter==0){
            primeImplicants[primeImpCount][col] = 0;
            countZero++;
        }
        primeCounter=0;
        if(countZero==mintermNumber){
            for(int a=0;a<primeImpCount;a++){
                for(int b=0;b<varNumber*2;b++){
                    if(finalBoolean[a][b]== 0){
                        countPI++;
                    }
                }
                if(countPI != varNumber*2){
                    rowPICount++;
                }
                countPI=0;
            }
            printf("\nFinal minimised expression: \n");
            for(int i = 0; i < rowPICount; i++){
                    printf("(");
                for(int j = 0; j < 20; j++){
                    if(finalBoolean[i][j]!= '\0'){
                        printf("%c", finalBoolean[i][j] );
                    }
                }
                if(i<rowPICount-1){
                    printf(") + ");
                }
            }
            printf(")\n\n");
        }
    }
}

int essentialPI(int valueNum){
    int numOnes=0;
    int numOnesTwo=0;
    int countOfOnes=0;
    for(int nums=primeCol ; nums<mintermNumber+primeCol; nums++){
        if(primeImplicants[primeImpCount][nums]==valueNum){
            if(valueNum == 1){
                for(int row=1; row<primeImpCount;row++){
                    if(primeImplicants[row][nums] == 1){
                        for(int minT=0; minT<primeCol; minT++){
                            for(int cols=primeCol ; cols<mintermNumber+primeCol; cols++){
                                if(primeImplicants[row][minT] == primeImplicants[0][cols]){
                                    for(int removeCol=1; removeCol<primeImpCount;removeCol++){
                                        primeImplicants[removeCol][cols] = 0;
                                    }
                                    limitCount++;
                                    if(limitCount==1){
                                        for(int h = 0; h<varNumber*2;h++){
                                            finalBoolean[finalRow][h] = primeImpChar[row-1][h];
                                        }
                                    }
                                }
                            }
                        }
                        finalRow++;
                        limitCount=0;
                    }
                }
            }
            else if(valueNum==2){
                for(int row=1; row<primeImpCount;row++){
                    if(primeImplicants[row][nums] == 1){
                        countOfOnes++;
                        for(int checkOnes=primeCol; checkOnes<mintermNumber+primeCol;checkOnes++){
                            if(primeImplicants[row][checkOnes] == 1){
                                numOnes++;
                            }
#
                        }
                        if(numOnes>1){
                                for(int minT=0; minT<primeCol; minT++){
                            for(int cols=primeCol ; cols<mintermNumber+primeCol; cols++){
                                if(primeImplicants[row][minT] == primeImplicants[0][cols]){
                                    for(int removeCol=1; removeCol<primeImpCount;removeCol++){
                                        primeImplicants[removeCol][cols] = 0;
                                    }
                                    limitCount++;
                                    if(limitCount==1){
                                        for(int h = 0; h<varNumber*2;h++){
                                            finalBoolean[finalRow][h] = primeImpChar[row-1][h];
                                        }
                                    }
                                }
                            }
                        }
                        finalRow++;
                        limitCount=0;
                        }
                        else if(numOnes==1 && countOfOnes>1){
                            for(int minT=0; minT<primeCol; minT++){
                            for(int cols=primeCol ; cols<mintermNumber+primeCol; cols++){
                                if(primeImplicants[row][minT] == primeImplicants[0][cols]){
                                    for(int removeCol=1; removeCol<primeImpCount;removeCol++){
                                        primeImplicants[removeCol][cols] = 0;
                                    }
                                    limitCount++;
                                    if(limitCount==1){
                                        for(int h = 0; h<varNumber*2;h++){
                                            finalBoolean[finalRow][h] = primeImpChar[row-1][h];
                                        }
                                    }
                                }
                            }
                        }
                        finalRow++;
                        limitCount=0;
                        }
                        numOnes=0;
                    }
                }
            }
        }
    }
}

int main(){
    int mintermArray[255][255]={0};
    int mintermList[255][255]={0};
    printf("Enter the number of Variables between 1-6:\n");
    scanf("%d", &varNumber);
    while(varNumber <=0 || varNumber>6){
        printf("Out of bounds, please enter the number of Variables between 1-6:");
        scanf("%d",&varNumber);
    }
    printf("Enter the number of Minterms between 1-%d:\n",(int)pow(2,varNumber)-1);
    scanf("%d", &mintermNumber);
     while(mintermNumber <=0 || mintermNumber>((int)pow(2,varNumber)-1)){
        printf("Out of bounds, please enter the number of Minterms between 1-%d:",(int)pow(2,varNumber)-1);
        scanf("%d", &mintermNumber);
    }

    for(int i=0;i<mintermNumber;i++){
        printf("Enter Minterm between 0-%d [M%d]:\n",(int)pow(2,varNumber)-1,i+1);
        scanf("%d", &mintermArray[i][0]);
        while(mintermArray[i][0] <0 || mintermArray[i][0]>((int)pow(2,varNumber)-1)){
            printf("Out of bounds, Minterm value has to be between 0-%d:",(int)pow(2,varNumber)-1);
            scanf("%d", &mintermArray[i][0]);
        }
    }
    for(int a = 0; a<mintermNumber;a++){
        mintermList[0][a]=mintermArray[a][0];
    }

    decToBinConversion(mintermArray,mintermNumber,varNumber);
    printf("Entered 2-D array is:\n");
    printf("  Min   ");
    decToBinTable(mintermArray,mintermNumber,varNumber);
    groupMinterms(mintermArray);
    printf("\n\nGrouped minterm table:\n");
    printf("Group  Min   ");
    decToBinTable(groupArray,mintermNumber,varNumber+1);
    printf("\n\nOrdered minterm table:\n");
    printf("Group  Min   ");
    bubbleSort(groupArray,mintermNumber,varNumber);
    decToBinTable(groupArray,mintermNumber,varNumber+1);
    comparison(mintermNumber,groupArray, varNumber, n, m);

    while(checkForMoreMatches(minCopy,mintermNumber,varNumber, nVar)==true){
        comparison(mintermNumber, minCopy, varNumber, nVar, nVar+1);
    }
    removeDuplicates(minCopy,nVar/2);
    for(int c=0;c<mintermNumber;c++){
        primeImplicants[0][c+primeCol] = mintermList[0][c];
    }
    primeImpDistribution(primeImplicants);
    primeImpTable(primeImplicants,primeImpCount,primeCol+mintermNumber,nVar);

     for(int i = 0; i < primeImpCount; i++){
        for(int j = 0; j < 20; j++){
            printf("%c", primeImpChar[i][j] );
        }
        printf("\n");
    }
    countingOnesPI();
    while(countZero!=mintermNumber){
        if(howManyOnes>0){
            primeImpTable(primeImplicants,primeImpCount+1,primeCol+mintermNumber,nVar);
            essentialPI(1);
            countingOnesPI();

        }
        else if(howManyOnes==0 && howManyTwos>0){
            primeImpTable(primeImplicants,primeImpCount+1,primeCol+mintermNumber,nVar);
            essentialPI(2);
            countingOnesPI();

        }
        else if(howManyOnes==0 && howManyTwos==0 && howManyThrees>0){
            essentialPI(3);
            countingOnesPI();
            primeImpTable(primeImplicants,primeImpCount+1,primeCol+mintermNumber,nVar);
        }
    }
} // main end



