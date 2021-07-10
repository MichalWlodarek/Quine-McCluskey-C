#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void decToBinTable(int mintermArray[8][8],int minterm_max, int var_max){
    printf("\nEntered 2-D array is: \n\n");

    for(int i = 0; i < minterm_max; i++)
    {
        for(int j = 0; j <= var_max; j++)
        {
            printf("%3d ", mintermArray[i][j] );
        }
        printf("\n");
    }
}

int decToBinConversion(int mintermArray[8][8],int minterm_max, int var_max){
    int minCopy[8][8]={0};
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

int main(){
    int mintermArray[8][8]={0};
    int varNumber=0;
    int mintermNumber=0;
    printf("Enter how many Variables\n");
    scanf("%d", &varNumber);
    printf("Enter how many minterms\n");
    scanf("%d", &mintermNumber);

    for(int i=0;i<mintermNumber;i++){
        printf("Enter minterm\n");
        scanf("%d", &mintermArray[i][0]);
    }
decToBinConversion(mintermArray,mintermNumber,varNumber);
decToBinTable(mintermArray,mintermNumber,varNumber);
}

