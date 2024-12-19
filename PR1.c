#include<stdio.h>

void solve(char * arr, int n){
    if((n < 2 )|| (arr[n-1] != 'b' && arr[n-2] != 'b')){
        printf("Invalid String\n");
        return;
    }

    for(int i=n-3; i>=0; i--){
        if(arr[i] != 'a'){
            printf("Invalid String\n");
            return;
        }
    }

    printf("Valid String\n");

}

int main(){
    int n;
    scanf("%d", &n);

    char arr[n];

    scanf("%s", arr);
    // printf("%s", arr);

    solve(arr, n);

}