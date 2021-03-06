
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct student
{
    char stu_name[0x10];
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

static void * student_list[0x10];
static long int auth;


void init();
void menu();
void registers();
void punch();
void statistic();
void clear();
void manage();
void manager_menu();
int read_ptr(char* ptr,int limit);
void modify();


void manage(){

    if(auth == 0 ){

        char tmp[0x10];

        memset(tmp,0,0x10);

        puts("inputs your token!");
        
        read_ptr(tmp,0x10);
        

        char token[0x10];
        memset(token,0,0x10);
        int fd=open("/dev/urandom",0);
        if (fd <= 0) {  
            exit(-1);
        }
        if(read(fd,token,0x4)==-1){
            close(fd);  
            exit(-1);
        }
        close(fd);
        
        if(strncmp(tmp,token,4) != 0 ){
            puts("tocken error!");
            return;
        }else{
            auth = -1;
        }

    }   
    puts("welcome manager");
    while(1){
        manager_menu();
        long int choice;
        scanf("%ld",&choice);
        switch (choice)
        {
        case 1:
            statistic();
            break;
        case 2:
            clear();
            break;
        case 3:
            modify();
            break;
        case 4:
            return;
        default:
            setbuf(stdin,NULL);
            puts("invaild choose!");
            break;
        }
    }


}


int read_ptr(char* ptr,int limit){

    char * tmp = ptr;
    int i;
    for ( i = 0; ; i++)
    {
        
        if(i==limit) return 0;

        if(read(0,tmp+i,1)!=1){
            return -1;
        }
        if(*(tmp+i) == '\n'){
            *(tmp+i) = '\x00';
            return 0;
        }
        
    }
}


void init(){
    setbuf(stdin, NULL);
    setbuf(stdout,NULL);
    auth = 0;
}


void menu(){
    puts("1.register");
    puts("2.punch in");
    puts("3.manage");
    puts("4.exit");
    puts("plz input your choice> ");
}

void manager_menu(){
    puts("1.statistic");
    puts("2.clear record");
    puts("3.modify");
    puts("4.back");
    puts("plz input your choice> ");
}


void registers(){

    long int idx;

    for ( idx= 0; idx<=0x10; idx++)
    {
        if(student_list[idx]==NULL){
            break;
        }        
    }
    if(idx > 0x10){
        puts("student is full!");
        return ;
    }
    struct student * stu = malloc(sizeof(struct  student));
    if(stu == NULL)exit(-1);

    puts("input your name");

    read_ptr(stu->stu_name,0x10);

    stu->stu_punch=NULL;

    student_list[idx] = stu;

    printf("your student no is %ld \n",idx);

    puts("register success!");

}

void punch(){
    long int idx = 0;
    long int size = 0;
    puts("please input your student no.");

    scanf("%ld",&idx);

    if(idx<0 || idx>10){
        puts("you can't hack me!");
        exit(-1);
    }

    if(student_list[idx] == NULL){
        puts("student does not exist.");
        return;
    }
    struct student *s =  student_list[idx];
    struct punch* p = malloc(sizeof(struct punch));

    if(p == NULL)exit(-1);

    p->student = s;


    puts("please input content size!");

    scanf("%ld",&size);

    
    if(size<0 || size>=0x70){
        exit(-1);
    }

    p->length = size;

    char * content=malloc(size);
    
    if(content == NULL)exit(-1);

    puts("please input content");

    read_ptr(content,size);

    p->content = content;

    if(s->stu_punch == NULL){
    
        s->stu_punch = p;
    
    }else{
        
        p->next = (struct punch*)(s->stu_punch);

        s->stu_punch = p;
    }
    puts("punch success");
}

void statistic(){

    puts("please inputs review student no");
    long int idx = 0;   

    scanf("%ld",&idx);

    if(idx<0 || idx>10){
       puts("you can't hack me!");

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
    long int idx = 0;
    scanf("%ld",&idx);

    if(idx<0 || idx>10){
       puts("you can't hack me!");

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
        free(p_tmp->content);
        free(p_tmp);
    }
    free(s);
    puts("clear success!");
}


void modify(){
    puts("please inputs modify student no");
    long int idx = 0;   

    scanf("%ld",&idx);

    if(idx<0 || idx>10){
       puts("you can't hack me!");

       exit(-1);
    }
    if(student_list[idx] == NULL){
        puts("student does not exist.");
        return;
    }
    struct student *s =  student_list[idx];
    
    struct punch *p = s->stu_punch;

    struct punch *p_tmp = p; 

    int i = 0;
    char choice;
    long int size;

    while(p_tmp != NULL){
        printf("%d .information: %s\n",i,p_tmp->content);

        do{
            puts("Is this your want to modify infomation?(y/n)");

            scanf("%c",&choice);
            if(choice == 'y'){
                puts("please input content size!");
                scanf("%ld",&size);
                if(size<0 || size>=0x70){
                    exit(-1);
                }
                puts("please input content");
                p_tmp->content = realloc(p_tmp->content,size);
                if(p_tmp->content == NULL){
                    exit(-1);
                }
                read_ptr(p_tmp->content,size);
                puts("modify success!");
                return;
            }
        }while(choice != 'n');
        p_tmp = p_tmp->next;
        i++;
    }
}

int main(int argc, char const *argv[])
{

    init();
    long int choice;

    while (1)
    {

        menu();
        scanf("%ld",&choice);
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
            setbuf(stdin,NULL);
            puts("invaild choose");
            break;
        }
    }
    
    return 0;
}
