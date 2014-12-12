#include <stdio.h>
int main(){
    int check = 0;
    int test = 1;
    int i;
    ////////
    for(i=10;i>=1;i--){
        check++;
    }
    if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    for(int j=10;j>0;j--){
        check++;
    }
    if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    for(i=0;i<10;i++){
         check++;
    }
    if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    for(i=1;i<=10;i++){
         check++;
    }
    if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    for(i=10;i>0;--i){
         check++;
    }
   if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    for(i=1;i<=10;++i){
         check++;
    }
    if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    for(i=1;i<=10;i=i+1){
         check++;
    }
    if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    for(i=10;i>0;i=i-1){
        check++;
    }
    if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    for(i=10;i>=1;i=-1+i){
        check++;
    }
    if(check!=10) { printf("ERROR TEST %d(c: %d)\n",test, check);return -1;}check = 0;test++;
     ////////
    printf("OK!\n");
    return 0;
}
