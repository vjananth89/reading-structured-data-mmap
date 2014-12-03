#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>
#include "bmp.h"

static void analyze(void *bm)
{
  struct bmp_header *pheader = (struct bmp_header *) bm;
  struct BITMAPINFOHEADER *pbminfo = (struct BITMAPINFOHEADER *) 
    (bm + sizeof(struct bmp_header));
  struct bgr8 *prow=(struct bgr8 *) (bm+pheader->offset);
  struct bgr8 *ppix;

  printf("Magic=%c%c\n", pheader->magic[0], pheader->magic[1]);
  printf("sizeof(struct bmp_header)=%d\n", sizeof( struct bmp_header));
  printf("size=%u\n", pheader->size);
  printf("offset=%x\n", pheader->offset);
  printf("bmheadersize=%u\n", pbminfo->header_size);
  printf("width=%d height=%d depth=%d\n", pbminfo->width, pbminfo->height, pbminfo->depth);
  printf("sizeof(struct bgr8)=%d\n",sizeof(struct bgr8));
  
  printf("%u %u %u\n",prow->blue, prow->green, prow->red);
  printf("%u %u %u\n",prow[0].blue, prow[0].green, prow[0].red);

  ppix =  prow+1;
  printf("%u %u %u\n",ppix->blue, ppix->green, ppix->red);
  printf("%u %u %u\n",prow[1].blue, prow[1].green, prow[1].red);}

static void bluestrip(void *bm)
{
  struct bmp_header *pheader = (struct bmp_header *) bm;
  struct BITMAPINFOHEADER *pbminfo = (struct BITMAPINFOHEADER *) 
    (bm + sizeof(struct bmp_header));
  struct bgr8 *prow=(struct bgr8 *) (bm+pheader->offset);
  struct bgr8 *ppix;
unsigned int j=0;
unsigned int i=0;

for (i=0;i<pbminfo->height/2;i++){
       prow[j].blue = 255;
       prow[j].red = 0;
       prow[j].green = 0;
       j += pbminfo -> width;
}

}



int
main(int argc, char *argv[])
{
	int		fdin, fdout;
	void		*src, *dst;
	struct stat	statbuf;
	
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


	analyze(src);



	if ((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE,
	  MAP_SHARED, fdout, 0)) == MAP_FAILED)
		err_sys("mmap error for output");

	memcpy(dst, src, statbuf.st_size);	/* does the file copy */

	bluestrip(dst);
exit(0);
}


