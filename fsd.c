/*fsd.c*/
#include "fsd.h"


void usage(int8 *arg){
	fprintf(stderr,"%s <source> <destination>\n",arg);
	return;

}

int8 *readkey(int8 *prompt){
    int8 buf[256];
    int8* p;

    int8 size,idx;

    printf("%s",prompt);
    fflush(stdout);

    changeecho(false);

    memset(buf,0,256);
    read(0,(char*)buf,255);
    size=(int8)strlen((char*)buf);
    idx=size-1;
    p=(int8*)buf+idx;
    *p=0;
    p=(int8* )malloc(size);
    assert(p);
    strncpy((char*)p,(char *)buf,idx);
    changeecho(true);

    return p;
}

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

int16 grabmagic(Arcfour *state,int32 fd){
    int n;
    int16 ret,*p;
    int8 buf[8];

    zero(buf, 8);
    n = read((int)fd, (char *)buf, 2);
    assert(n == 2);

    p = (int16)&buf;
    ret = *p;
    return ret;
}

int main(int argc, char* argv[]){

    Arcfour *state;

    int8 *srcfile,*dstfile;
    int8 *key;
    int16 size,magic;

    int32 in, out;

    if (argc <3){
	usage((int8 *)*argv);
    return -1;
    }

    srcfile=(int8 *)argv[1];
	dstfile=(int8 *)argv[2];

    
    key=readkey((int8 *)"Key:");
    size = (int16)strlen((char *)key);
    assert(size);

    //free(key);
    state = rc4init(key, size);
    assert(state);

    //decrypt first 2 bytes
    in = (int32)open((char *)srcfile, O_RDONLY);
    assert(in > 0);
    out = (int32)open((char *)dstfile, O_WRONLY | O_CREAT, 00600);
    assert(out > 0);

    magic = grabmagic(state,in);

    

    return 0;
}
