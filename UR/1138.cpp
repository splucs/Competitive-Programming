#include <cstdio>

long long int counter[10];
long long int levels[10], pot[10];

void add(int* digits, int level){
    int i=0;
    while(digits[i]==0) i++;
    for(; i<9; i++){
        counter[digits[i]]+=pot[level];
    }
    for(i=0; i<=9; i++) counter[i]+=levels[level];
}

void moveRight(int* digits){
    for(int i=8; i>0; i--){
        digits[i]=digits[i-1];
    }
    digits[0]=0;
}

bool isOne(int *digits){
    bool foundOne = false;
    for(int i=0; i<9; i++){
        if (digits[i]==0) continue;
        else{
            if (foundOne) return false;
            foundOne = true;
            if (i==8) return false;
        }
    }
    return foundOne;
}

void countDigits(int a, int b){
    for (int i=0; i<10; i++) counter[i]=0;
    int digitsA[9];
    int A=a, B=b;
    for(int i=0; i<9; i++){
        digitsA[8-i]=a%10;
        a/=10;
    }
    if (A==B){
        add(digitsA, 0);
        return;
    }
    int digitsB[9];
    for(int i=0; i<9; i++){
        digitsB[8-i]=b%10;
        b/=10;
    }
    if (isOne(digitsB)){
        B++;
        digitsB[8]++;
        int i=0;
        while(digitsB[i]==0) i++;
        while(i<9) counter[digitsB[i++]]--;
    }
    int level=0;
    while(A+pot[level]<B){
        while(digitsA[8]<10 && A+pot[level]<B){
            add(digitsA, level);
            digitsA[8]++;
            A+=pot[level];
        }
        digitsA[7]++;
        moveRight(digitsA);
        level++;
    }
    level=0;
    while(A<=B){
        while(digitsB[8]>=0 && A<=B){
            add(digitsB, level);
            digitsB[8]--;
            B-=pot[level];
        }
        digitsB[7]--;
        moveRight(digitsB);
        level++;
    }
}

int main ()
{
    long long int cont=1;
    for(int i=0; i<10; i++, cont*=10) pot[i]=cont;
    levels[0]=0;
    levels[1]=1;
    levels[2]=20;
    levels[3]=300;
    levels[4]=4000;
    levels[5]=50000;
    levels[6]=600000;
    levels[7]=7000000;
    levels[8]=80000000;
    levels[9]=900000000;
    int A, B;
    while(true){
        scanf("%d %d", &A, &B);
        if (A==0 && B==0) break;
        countDigits(A, B);
        for(int i=0; i<9; i++) printf("%lld ", counter[i]);
        printf("%lld\n", counter[9]);
    }
    return 0;
}
