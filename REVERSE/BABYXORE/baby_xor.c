#include<stdlib.h>
#include<stdio.h>
void encode(char* );


char identify[0x8] = "\x11\xa7\xcb\xc9\x9d\x63\xfd\x89";

void encode(char* input){

    long long unsigned* tmp = input;  

    long long unsigned calc1 = *tmp;
    long long unsigned calc2 = *tmp;

    calc1 = calc1<<7;
    calc1 = calc1 ^ calc2;

    calc2 = calc1;
    calc1 = calc1>>11;
    calc1 = calc1^calc2;

    calc2 = calc1;
    calc1 = calc1<<31;
    calc1 = calc1^calc2;

    calc2 = calc1;
    calc1 = calc1>>13;
    calc1 = calc1^calc2;

    *tmp = calc1;
}

int main(int argc, char const *argv[])
{

    char input[0x8];
    puts("Plz input your flag!");
    
    scanf("%8s",input);

    encode(input);



    

    for (size_t i = 0; i < 8; i++)
    {
        if(input[i] != identify[i]){
            printf("fail flag!");
            system("pause");
            exit(-1);
        }
    }
    
    printf("congratulations!");

    system("pause");
    return 0;
}
