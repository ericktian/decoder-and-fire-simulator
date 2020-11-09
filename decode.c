//
// Torbert, 4 Sept 2015
//
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
//
bool isvalueinarray(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return true;
    }
    return false;
}
int main()
{
	FILE* fin = fopen( "decodeME.txt" , "r" ) ;
	char  msg[10101] ;
	int   numbytes ;
    int m = 28;
	numbytes = fread( msg , 1 , 10000 , fin ) ;
	msg[numbytes] = '\0' ; // null character
    int startofmsg;
    int length = numbytes;//sizeof(msg);
    int i;
    char tree[10000];   //arbitrary large size
    char currchar;
    int currind = 1;
    int newline = 1;    //boolean basically
    float freq[256];  //frequency of tree values
    for (int l = 0; l<sizeof(freq)/sizeof(freq[0]);l++){    //fill those in empty
        freq[l] = 0;
    }
    int savedvals[m];   //all values of saved chars

    for (i=0;i<length;i++){
        if (msg[i]=='\n'){
            newline = 1;
            tree[currind] = currchar;
            currind = 1;
        }
        else if (newline==1){
            currchar = msg[i];
            newline = 0;
        }
        else{
            int c = msg[i] - '0';
            currind = 2*currind + c;
        }
    }


    startofmsg = 218;
    int count = 0;
    int savedIterator = 0;
    int currtree = 1;
    printf("Text: ");
    for (i=startofmsg;i<length;i++){
        if (tree[currtree]!='\0'){
            printf("%c",tree[currtree]);
            count++;    //log for ratio
            freq[tree[currtree]]++;
            currtree = 1;
        }
        int c = msg[i] - '0';
        currtree = 2*currtree+c;
    }
    printf("%c",tree[currtree]);
    count++;    //log for ratio
    freq[tree[currtree]]++;
            
    printf("\n\nCompression ratio: %i/%i", 8*count-(numbytes-218), count*8);

    printf(" = %f", (double)(count*8-numbytes+218)/(count*8));

    float shannon = 0.0;
    for (int l = 0; l<sizeof(freq)/sizeof(freq[0]);l++){    //shannon
        if(freq[l]>0)shannon += (float)freq[l] * -1.0 * (log(freq[l]/count))/(log(2));
    }
    printf("\n\nShannon minimum # bits: %f\n\n", shannon);

	return 0 ;
}
//
// end of file
//