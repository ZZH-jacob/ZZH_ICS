#include<stdio.h>
#include<stdlib.h>
int main(){
    short r0,r1,r2,r3,r4,r5,r6,r7;
    scanf("%hd",&r0);
    r5=-r0;
    r2=2;
    r3=0;
    r1=1;
    while(1){
    r3=r2;
    r4=0;
    do{r4=r4+r2;
    r3=r3-1;
    }while(r3!=0);
    r4=r4+r5;
    if(r4<=0) {
    r4=r0;
    r3=-r2;
    do{
        r4=r4+r3;
    }while(r4>0);
    if(r4<0){
        r2=r2+1;
    }
    else{
        r1=0;
        break;}
    }
    else break;
    }
    printf("%hd",r1);
    return 0;
}