#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc,char **argv)
{
	if(argc>1){
	  fprintf(2,"Usage: pingpong\n");
	  exit(1);
	}
	int p1[2],p2[2];
	pipe(p1);
	pipe(p2);
	char buf[1];
	if(fork()==0){
	  close(p1[1]);
	  close(p2[0]);
	  if(read(p1[0],buf,1)==1){
	  	close(p1[0]);
	  	printf("%d: received ping\n",getpid());
	  }
	  write(p2[1],buf,1);
	  close(p2[1]);
	}else{
	  close(p1[0]);
	  close(p2[1]);
	  write(p1[1],buf,1);
	  close(p1[1]);
	  if(read(p2[0],buf,1)==1){
	    close(p2[0]);
	    printf("%d: received pong\n",getpid());
	  }
	}
	exit(0);
}
