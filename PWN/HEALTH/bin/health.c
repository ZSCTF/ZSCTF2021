//考点
// 1.格式化字符串基础(利用栈内变量作为参数)
// 2.堆利用基础　--(off by one)

// 塑料英语　

// 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct student
{
    int stu_no;
    char stu_name[0x8];
    void* stu_punch; 
    /* data */
};
struct punch
{
    void * student;
    void * next;
    long long length;
    char* content;
};

void * student_list[0x10];

void init();
void menu();
void registers();
void punch();
void statistic();
void clear();
void manage();
void manager_menu();
int read_ptr(char* ptr,int limit);



void manage(){

    char tmp[0x20];

    memset(tmp,0,0x20);

    puts("inputs your token!");
    
    read_ptr(tmp,4);
    

    char token[0x8];
    memset(token,0,0x8);
    int fd=open("/dev/urandom",0);

    if(read(fd,token,0x4)==-1){
        close(fd);
        exit(0);
    }
    close(fd);
    
    printf(tmp);

    if(strcmp(tmp,token) == 0 ){
        puts("welcome manager");
        while(1){
            manager_menu();
            int choice;
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                statistic();
                break;
            case 2:
                clear();
                break;
            case 3:
                return;
            default:
                puts("invaild choose!");
                break;
            }
        }
        

    }else{
        puts("token error!");
        return;
    }

}


int read_ptr(char* ptr,int limit){

    char * tmp = ptr;
    int i;
    for ( i = 0; ; i++)
    {
        if(read(0,tmp+i,1)!=1){
            return -1;
        }
        if(*(tmp+i) == '\n'){
            return 0;
        }
        
        if(i==limit) return 0;
    }
}

void init(){
    setbuf(stdin, NULL);
    setbuf(stdout,NULL);
}


void menu(){
    puts("1.register");
    puts("2.punch in");
    puts("3.manage");
    puts("4.exit");
}

void manager_menu(){
    puts("1.statistic");
    puts("2.clear record");
    puts("3.back");
}


void registers(){

    int idx;

    for ( idx= 0; idx<0x10; idx++)
    {
        if(student_list[idx]==NULL){
            break;
        }        
    }
    if(idx >= 0x10){
        puts("student is full!");
        return ;
    }
    struct student * stu = malloc(sizeof(struct  student));
    
    stu->stu_no = idx;

    puts("input your name");

    if(read(0,stu->stu_name,0x8)==-1){
        exit(-1);
    }

    stu->stu_punch=NULL;

    student_list[idx] = stu;

    puts("register success!");
}

void punch(){
   char tmp[0x8];
   int idx = 0;
   puts("please input your student no.");
   
   read(0,tmp,0x8);

   idx = atoi(tmp);

   if(idx<0&&idx>=10){
       exit(-1);
   }

    if(student_list[idx] == NULL){
        puts("student does not exist.");
        return;
    }
    
    struct punch* p = malloc(sizeof(punch));

    p->student = student_list[idx];


    puts("please input content size!");

    read(0,tmp,0x8);

    int size = atoi(tmp);
    
    if(size<0 && size>=0x70){
        exit(-1);
    }

    p->length = size;
    char * content=malloc(size);

    puts("please input content");

    read_ptr(content,size);

    struct student *s =  student_list[idx];

    if(s->stu_punch == NULL){
    
        s->stu_punch = p;
    
    }else{
        
        p->next = (struct punch*)(s->stu_punch);

        s->stu_punch = p;
    }
}


void statistic(){

    puts("please inputs review student no");
    char tmp[0x8];
    int idx = 0;   
    read(0,tmp,0x8);

    idx = atoi(tmp);

    if(idx<0&&idx>=10){
       exit(-1);
    }

    if(student_list[idx] == NULL){
        puts("student does not exist.");
        return;
    }
    struct student *s =  student_list[idx];
    
    struct punch *p = s->stu_punch;

    struct punch *p_tmp = p; 
    

    printf("student:%s\n",s->stu_name);

    while(p_tmp != NULL){
      printf("information: %s\n",p_tmp->content);
      p_tmp = p_tmp->next;      
    }
    
}


void clear(){
    puts("please inputs delete student no");
    char tmp[0x8];
    int idx = 0;
   
    read(0,tmp,0x8);

    idx = atoi(tmp);

    if(idx<0&&idx>=10){
       exit(-1);
    }

    if(student_list[idx] == NULL){
        puts("student does not exist.");
        return;
    }
    struct student *s =  student_list[idx];

    struct punch *p =  s->stu_punch;
    struct punch *p_tmp = p;


    while(p!=NULL){
        p_tmp = p;
        p = p->next;
        free(p_tmp);
    }
    s->stu_punch = NULL;
    free(s);

    student_list[idx] == NULL;

}

int main(int argc, char const *argv[])
{

    init();
    int choice;

    while (1)
    {

        menu();
        scanf("%d",&choice);
        /* code */
        switch (choice)
        {
        case 1:
            registers();
            break;
        case 2:
            punch();
            break;
        case 3:
            manage();
            break;
        case 4:
            exit(0);
        default:
            puts("invaild choose");
            break;
        }
    }
    

    


    return 0;
}
