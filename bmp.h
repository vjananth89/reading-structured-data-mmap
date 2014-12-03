/* MS .bmp format header file by sdc, based on wikipedia article */
/* Assumes Little-endian, 32-bit arch. */

struct bmp_header {
  char magic[2];          /*should be BM */
  unsigned int size __attribute__ ((packed)); 
  /*the size of the BMP file in bytes*/
  short int reserved1 __attribute__ ((packed));
  short int reserved2  __attribute__ ((packed));
  unsigned int offset  __attribute__ ((packed)); 
  /*the offset, i.e. starting address, of the byte where the bitmap image 
    data (pixel array) can be found.*/
};

struct BITMAPINFOHEADER {
  unsigned int header_size; /*should be 40 == 0x28 */
  int width;  /*the bitmap width in pixels (signed integer)*/
  int height; /*the bitmap height in pixels (signed integer)*/
  short int n_color_planes  __attribute__ ((packed)); 
    /*the number of color planes must be 1*/
  short int depth  __attribute__ ((packed)); 
    /*the number of bits per pixel, which is the color depth 
      of the image. Typical values are 1, 4, 8, 16, 24 and 32.*/
  int compression;
    /*the compression method being used. 
      See the wikipedia article for a list of possible values*/
  int h_resolution;
    /*the horizontal resolution of the image. (pixel per meter, signed integer) */
  int v_resolution;
    /*the vertical resolution of the image. (pixel per meter, signed integer) */
  int n_colors;
    /*the number of colours in the colour palette, or 0 to default to 2^n*/
  int n_important_colors;
    /*the number of important colours used, 
      or 0 when every colour is important; generally ignored */
};

struct bgr8 {
  unsigned char blue ;
  unsigned char green ;
  unsigned char red  ;
};

#define ROWSIZE(BPP,IWIDTH) ((((BPP)*(IWIDTH)+31)/32)*4)
#define PIXARRAYSIZE(ROWSIZE,HEIGHT) ((ROWSIZE)*((unsigned) (HEIGHT)))


