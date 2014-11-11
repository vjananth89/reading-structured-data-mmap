#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

struct copyspec { void *src, *dst; size_t size; };

void * threadfun(void *p)
{
  struct copyspec *c =   (struct copyspec *) p;
  printf("Thread for copying from %p: My stack contains addr %p\n", c->dst, &c);
  memcpy(c->dst, c->src, c->size);	/* does the file copy */
}

#define CMDSIZE 100

int
main(int argc, char *argv[])
{
	int			fdin, fdout;
	void		*src, *dst;
	struct stat	statbuf;
	
	int pid;
	char cmd[CMDSIZE];

	struct copyspec cop1, cop2;

	pthread_t thread1, thread2;

	pid = getpid();
	snprintf(cmd,CMDSIZE,
		 "echo BEFORE threads; cat /proc/%d/maps; echo ", pid);
	system(cmd);


	if (argc != 3)
		err_quit("usage: %s <fromfile> <tofile>", argv[0]);

	if ((fdin = open(argv[1], O_RDONLY)) < 0)
		err_sys("can't open %s for reading", argv[1]);

	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC,
	  FILE_MODE)) < 0)
		err_sys("can't creat %s for writing", argv[2]);

	if (fstat(fdin, &statbuf) < 0)	/* need size of input file */
		err_sys("fstat error");

	/* set size of output file */
	if (lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1)
		err_sys("lseek error");
	if (write(fdout, "", 1) != 1)
		err_sys("write error");

	if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED,
	  fdin, 0)) == MAP_FAILED)
		err_sys("mmap error for input");

	if ((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE,
	  MAP_SHARED, fdout, 0)) == MAP_FAILED)
		err_sys("mmap error for output");

	cop1.src = src;
	cop1.dst = dst;
	cop1.size = statbuf.st_size/2;
	cop2.src = src + statbuf.st_size/2;
	cop2.dst = dst + statbuf.st_size/2;
	cop2.size = statbuf.st_size/2;

	pthread_create(&thread1, 0,
		       threadfun, &cop1);
	pthread_create(&thread2, 0,
		       threadfun, &cop2);

	snprintf(cmd,CMDSIZE,
		 "echo AFTER threads; cat /proc/%d/maps; echo ", pid);
	system(cmd);
//	pthread_join(thread1,0);
//	pthread_join(thread2,0);
	exit(0);
}
