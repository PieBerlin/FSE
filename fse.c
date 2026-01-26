// fse.c
// #include<stdio.h>
#include "fse.h"

int8 *readkey(char *prompt){
    char buf[256];
    int8* p;

    int8 size,idx;

    printf("%s",prompt);
    fflush(stdout);

    changeecho(false);

    memset(buf,0,256);
    read(0,buf,255);
    size=(int8)strlen(buf);
    idx=size-1;
    p=(int8*)buf+idx;
    *p=0;
    p=(int8* )malloc(size);
    assert(p);
    strncpy((char*)p,buf,idx);
    changeecho(true);

    return p;
}
/*
void changeecho(bool enabled){
    struct termios *t;
    t = (struct termios *)malloc(sizeof(struct termios));

    /*int tcgetattr(int fd, struct termios *termios_p);
       int tcsetattr(int fd, int optional_actions,
                     const struct termios *termios_p);

    tcgetattr(0, t);
    if(enabled){
    t->c_lflag |= ECHO;
        
    }
    else{
        t->c_lflag &= ECHO;

    }
    tcsetattr(0, 0, t);
    free(t);
    return;
}*/
void changeecho(bool enabled) {
    struct termios t; // No need to malloc for a single struct
    tcgetattr(STDIN_FILENO, &t);
    if (enabled) {
        t.c_lflag |= ECHO;
    } else {
        t.c_lflag &= ~ECHO; // Correctly disable ECHO
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}


int8* securerand(int16 size){
    int8 *start,*p;

    ssize_t n;

    assert(size>0);
    p=(int8*) malloc(size);
    assert(p);
    start=p;

    n=getrandom(p,(size_t)size,GRND_RANDOM|GRND_NONBLOCK);
    if(n==size){
        return p;

    }
    else if(n<0){
        free(p);
        return 0;
        
    }
    
    fprintf(stderr,"Warning: Entropy pool is empty. This may take longer than usual.\n");
    p+=n;
    n=getrandom(p,(size-n),GRND_RANDOM);

    if(n==size){
    return start;
}
else{
    free(start);
    return 0;
}


}



int main(int argc,char *argv[]){
    Arcfour *rc4;

    char *infile, *outfile;
    int infd,outfd;

    int8 *key;
    int16 keysize;

    int16 padsize;

    int16 *padsize16;
    int8 *padsize8;
    int8 *padding;

    if(argc<3){
        fprintf(stderr,"Usage: %s <infile> <outfile>\n",*argv);
        //exit(1);
        return -1;
    }
    infile=argv[1];
    outfile=argv[2];

    infd=open(infile,O_RDONLY);
    if(infd<1){
        //printf(stderr,"Error opening %s for reading\n",infile);
        //exit(1);
        perror("open: ");
        return -1;      }
    
        outfd=open(outfile,O_WRONLY | O_CREAT,00600);
        if (outfd<1){
            close(infd);
            perror("Open : ");
        }
;
        key=readkey("Key:");
        assert(key);
        // keysize=(int16)strlen((char *)key)

        padsize8=securerand(2);
        padsize16=(int16 *)padsize8;
        padsize=*padsize16;
        //printf("padsize: %d\n",(int)padsize);
        
        close(infd);
        close(outfd);
        free(padsize8);




}