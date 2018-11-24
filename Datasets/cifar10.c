#include "cifar10.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

long slurp(char const* path, char **buf, bool add_nul);
/*
 * 'slurp' reads the file identified by 'path' into a character buffer
 * pointed at by 'buf', optionally adding a terminating NUL if
 * 'add_nul' is true. On success, the size of the file is returned; on
 * failure, -1 is returned and ERRNO is set by the underlying system
 * or library call that failed.
 *
 * WARNING: 'slurp' malloc()s memory to '*buf' which must be freed by
 * the caller.
 */
long slurp(char const* path, char **buf, bool add_nul)
{
    FILE  *fp;
    size_t fsz;
    long   off_end;
    int    rc;

    /* Open the file */
    fp = fopen(path, "rb");
    if( NULL == fp ) {
        return -1L;
    }

    /* Seek to the end of the file */
    rc = fseek(fp, 0L, SEEK_END);
    if( 0 != rc ) {
        return -1L;
    }

    /* Byte offset to the end of the file (size) */
    if( 0 > (off_end = ftell(fp)) ) {
        return -1L;
    }
    fsz = (size_t)off_end;

    /* Allocate a buffer to hold the whole file */
    *buf = malloc( fsz+(int)add_nul );
    if( NULL == *buf ) {
        return -1L;
    }

    /* Rewind file pointer to start of file */
    rewind(fp);

    /* Slurp file into buffer */
    if( fsz != fread(*buf, 1, fsz, fp) ) {
        free(*buf);
        return -1L;
    }

    /* Close the file */
    if( EOF == fclose(fp) ) {
        free(*buf);
        return -1L;
    }

    if( add_nul ) {
        /* Make sure the buffer is NUL-terminated, just in case */
        buf[fsz] = '\0';
    }

    /* Return the file size */
    return (long)fsz;
}

void write_file(unsigned int** red, unsigned int** green, unsigned int** blue, int class);
void write_file(unsigned int** red, unsigned int** green, unsigned int** blue, int class){
  FILE *f;
  unsigned char *img = NULL;
  int filesize = 54 + 3*32*32;  //w is your image width, h is image height, both int
  int w = 32;
  int h = 32;
  img = (char *)malloc(3*w*h);
  memset(img,0,3*32*32);

  int x;
  int y;

  for(int i=0; i<32; i++)
  {
      for(int j=0; j<32; j++)
      {
          x=i; y=(h-1)-j;
          int r = red[i][j];
          int g = green[i][j];
          int b = blue[i][j];
          printf("Element %d %d is %u, %u, %u\n", i, j, r, g, b);
          if (r > 255) r=255;
          if (g > 255) g=255;
          if (b > 255) b=255;
          printf("=> %d %d is %u, %u, %u\n", i, j, r, g, b);
          img[(x+y*32)*3+2] = (unsigned char)(r);
          img[(x+y*32)*3+1] = (unsigned char)(g);
          img[(x+y*32)*3+0] = (unsigned char)(b);
      }
  }

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
  unsigned char bmppad[3] = {0,0,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    );
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(       w    );
  bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
  bmpinfoheader[ 6] = (unsigned char)(       w>>16);
  bmpinfoheader[ 7] = (unsigned char)(       w>>24);
  bmpinfoheader[ 8] = (unsigned char)(       h    );
  bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
  bmpinfoheader[10] = (unsigned char)(       h>>16);
  bmpinfoheader[11] = (unsigned char)(       h>>24);

  printf("Class is %d\n", class);
  f = fopen("img.bmp","wb");
  fwrite(bmpfileheader,1,14,f);
  fwrite(bmpinfoheader,1,40,f);
  for(int i=0; i<h; i++)
  {
      fwrite(img+(w*(h-i-1)*3),3,w,f);
      fwrite(bmppad,1,(4-(w*3)%4)%4,f);
  }

  free(img);
  fclose(f);
}



dataset* load_CIFAR_10(){
  FILE  *fp;
  size_t fsz;

  dataset* data = alloc_dataset();
  data->train_input_sequence_length = 1034;
  data->validation_input_sequence_length = 1034;
  data->test_input_sequence_length = 1034;
  data->warmups = 100;

  data->train_input_sequence = malloc(1034 * sizeof(gsl_matrix*));
  for(int i = 0; i < 1034; i++){
    data->train_input_sequence[i] = gsl_matrix_calloc(4, 45000);
  }
  data->train_output = gsl_matrix_calloc(10, 45000);
  data->validation_input_sequence = malloc(1034 * sizeof(gsl_matrix*));
  for(int i = 0; i < 1034; i++){
    data->validation_input_sequence[i] = gsl_matrix_calloc(4, 5000);
  }
  data->validation_output = gsl_matrix_calloc(10, 5000);
  data->test_input_sequence = malloc(1034 * sizeof(gsl_matrix*));
  for(int i = 0; i < 1034; i++){
    data->test_input_sequence[i] = gsl_matrix_calloc(4, 10000);
  }
  data->test_output = gsl_matrix_calloc(10, 10000);

  char* batch;

  int postfile = 3;

  long file_size = slurp("Datasets/cifar-10/data_batch_1.bin", &batch, false);
  int i = 0;
  int element = 0;
  for(i = 0; i < 10000; i++){
    int class = (int)batch[element];
    gsl_matrix_set(data->train_output, (int)batch[element], i, 1.0);
    element++;
    unsigned int** red;
    unsigned int** blue;
    unsigned int** green;
    red = malloc(32 * sizeof(unsigned int*));
    green = malloc(32 * sizeof(unsigned int*));
    blue = malloc(32 * sizeof(unsigned int*));
    for(int x = 0; x < 32; x++){
      red[x] = malloc(32 * sizeof(unsigned int));
      green[x] = malloc(32 * sizeof(unsigned int));
      blue[x] = malloc(32 * sizeof(unsigned int));
    }
    int x = 0;
    int y = 0;
    int col = 0;
    for(int e = 0; e < 3072; e++){
      if(col == 0){
        red[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }
      }
      else if(col == 1){
        green[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      else if(col == 2){
        blue[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      element++;
    }

    for(int y = 0; y < 32; y++){
      for(int x = 0; x < 32; x++){
        int entry = (y * 32) + x;
        gsl_matrix_set(data->train_input_sequence[entry], 0, i, (double)red[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 1, i, (double)green[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 2, i, (double)blue[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 3, i, 1.0);
      }
    }

    for(int x = 0; x < 32; x++){
      free(red[x]);
      free(green[x]);
      free(blue[x]);
    }
    free(red);
    free(green);
    free(blue);
  }
  free(batch);
  file_size = slurp("Datasets/cifar-10/data_batch_2.bin", &batch, false);
  element = 0;
  for(i = 10000; i < 20000; i++){
    int class = (int)batch[element];
    gsl_matrix_set(data->train_output, (int)batch[element], i, 1.0);
    element++;
    unsigned int** red;
    unsigned int** blue;
    unsigned int** green;
    red = malloc(32 * sizeof(unsigned int*));
    green = malloc(32 * sizeof(unsigned int*));
    blue = malloc(32 * sizeof(unsigned int*));
    for(int x = 0; x < 32; x++){
      red[x] = malloc(32 * sizeof(unsigned int));
      green[x] = malloc(32 * sizeof(unsigned int));
      blue[x] = malloc(32 * sizeof(unsigned int));
    }
    int x = 0;
    int y = 0;
    int col = 0;
    for(int e = 0; e < 3072; e++){
      if(col == 0){
        red[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }
      }
      else if(col == 1){
        green[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      else if(col == 2){
        blue[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      element++;
    }

    for(int y = 0; y < 32; y++){
      for(int x = 0; x < 32; x++){
        int entry = (y * 32) + x;
        gsl_matrix_set(data->train_input_sequence[entry], 0, i, (double)red[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 1, i, (double)green[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 2, i, (double)blue[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 3, i, 1.0);
      }
    }

    for(int x = 0; x < 32; x++){
      free(red[x]);
      free(green[x]);
      free(blue[x]);
    }
    free(red);
    free(green);
    free(blue);
  }
  free(batch);
  file_size = slurp("Datasets/cifar-10/data_batch_3.bin", &batch, false);
  element = 0;
  for(i = 20000; i < 30000; i++){
    int class = (int)batch[element];
    gsl_matrix_set(data->train_output, (int)batch[element], i, 1.0);
    element++;
    unsigned int** red;
    unsigned int** blue;
    unsigned int** green;
    red = malloc(32 * sizeof(unsigned int*));
    green = malloc(32 * sizeof(unsigned int*));
    blue = malloc(32 * sizeof(unsigned int*));
    for(int x = 0; x < 32; x++){
      red[x] = malloc(32 * sizeof(unsigned int));
      green[x] = malloc(32 * sizeof(unsigned int));
      blue[x] = malloc(32 * sizeof(unsigned int));
    }
    int x = 0;
    int y = 0;
    int col = 0;
    for(int e = 0; e < 3072; e++){
      if(col == 0){
        red[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }
      }
      else if(col == 1){
        green[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      else if(col == 2){
        blue[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      element++;
    }

    for(int y = 0; y < 32; y++){
      for(int x = 0; x < 32; x++){
        int entry = (y * 32) + x;
        gsl_matrix_set(data->train_input_sequence[entry], 0, i, (double)red[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 1, i, (double)green[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 2, i, (double)blue[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 3, i, 1.0);
      }
    }

    for(int x = 0; x < 32; x++){
      free(red[x]);
      free(green[x]);
      free(blue[x]);
    }
    free(red);
    free(green);
    free(blue);
  }
  free(batch);
  file_size = slurp("Datasets/cifar-10/data_batch_4.bin", &batch, false);
  element = 0;
  for(i = 30000; i < 40000; i++){
    int class = (int)batch[element];
    gsl_matrix_set(data->train_output, (int)batch[element], i, 1.0);
    element++;
    unsigned int** red;
    unsigned int** blue;
    unsigned int** green;
    red = malloc(32 * sizeof(unsigned int*));
    green = malloc(32 * sizeof(unsigned int*));
    blue = malloc(32 * sizeof(unsigned int*));
    for(int x = 0; x < 32; x++){
      red[x] = malloc(32 * sizeof(unsigned int));
      green[x] = malloc(32 * sizeof(unsigned int));
      blue[x] = malloc(32 * sizeof(unsigned int));
    }
    int x = 0;
    int y = 0;
    int col = 0;
    for(int e = 0; e < 3072; e++){
      if(col == 0){
        red[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }
      }
      else if(col == 1){
        green[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      else if(col == 2){
        blue[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      element++;
    }

    for(int y = 0; y < 32; y++){
      for(int x = 0; x < 32; x++){
        int entry = (y * 32) + x;
        gsl_matrix_set(data->train_input_sequence[entry], 0, i, (double)red[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 1, i, (double)green[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 2, i, (double)blue[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 3, i, 1.0);
      }
    }

    for(int x = 0; x < 32; x++){
      free(red[x]);
      free(green[x]);
      free(blue[x]);
    }
    free(red);
    free(green);
    free(blue);
  }
  free(batch);
  file_size = slurp("Datasets/cifar-10/data_batch_5.bin", &batch, false);
  element = 0;
  for(i = 40000; i < 45000; i++){
    int class = (int)batch[element];
    gsl_matrix_set(data->train_output, (int)batch[element], i, 1.0);
    element++;
    unsigned int** red;
    unsigned int** blue;
    unsigned int** green;
    red = malloc(32 * sizeof(unsigned int*));
    green = malloc(32 * sizeof(unsigned int*));
    blue = malloc(32 * sizeof(unsigned int*));
    for(int x = 0; x < 32; x++){
      red[x] = malloc(32 * sizeof(unsigned int));
      green[x] = malloc(32 * sizeof(unsigned int));
      blue[x] = malloc(32 * sizeof(unsigned int));
    }
    int x = 0;
    int y = 0;
    int col = 0;
    for(int e = 0; e < 3072; e++){
      if(col == 0){
        red[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }
      }
      else if(col == 1){
        green[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      else if(col == 2){
        blue[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      element++;
    }

    for(int y = 0; y < 32; y++){
      for(int x = 0; x < 32; x++){
        int entry = (y * 32) + x;
        gsl_matrix_set(data->train_input_sequence[entry], 0, i, (double)red[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 1, i, (double)green[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 2, i, (double)blue[x][y] / 128.0);
        gsl_matrix_set(data->train_input_sequence[entry], 3, i, 1.0);
      }
    }

    for(int x = 0; x < 32; x++){
      free(red[x]);
      free(green[x]);
      free(blue[x]);
    }
    free(red);
    free(green);
    free(blue);
  }
  for(int i = 1024; i < 1034; i++){
    for(int j = 0; j < 45000; j++){
      gsl_matrix_set(data->train_input_sequence[i], 0, j, 0.0);
      gsl_matrix_set(data->train_input_sequence[i], 1, j, 0.0);
      gsl_matrix_set(data->train_input_sequence[i], 2, j, 0.0);
      gsl_matrix_set(data->train_input_sequence[i], 3, j, 1.0);
    }
  }
  for(i = 0; i < 5000; i++){
    int class = (int)batch[element];
    gsl_matrix_set(data->validation_output, (int)batch[element], i, 1.0);
    element++;
    unsigned int** red;
    unsigned int** blue;
    unsigned int** green;
    red = malloc(32 * sizeof(unsigned int*));
    green = malloc(32 * sizeof(unsigned int*));
    blue = malloc(32 * sizeof(unsigned int*));
    for(int x = 0; x < 32; x++){
      red[x] = malloc(32 * sizeof(unsigned int));
      green[x] = malloc(32 * sizeof(unsigned int));
      blue[x] = malloc(32 * sizeof(unsigned int));
    }
    int x = 0;
    int y = 0;
    int col = 0;
    for(int e = 0; e < 3072; e++){
      if(col == 0){
        red[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }
      }
      else if(col == 1){
        green[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      else if(col == 2){
        blue[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      element++;
    }

    for(int y = 0; y < 32; y++){
      for(int x = 0; x < 32; x++){
        int entry = (y * 32) + x;
        gsl_matrix_set(data->validation_input_sequence[entry], 0, i, (double)red[x][y] / 128.0);
        gsl_matrix_set(data->validation_input_sequence[entry], 1, i, (double)green[x][y] / 128.0);
        gsl_matrix_set(data->validation_input_sequence[entry], 2, i, (double)blue[x][y] / 128.0);
        gsl_matrix_set(data->validation_input_sequence[entry], 3, i, 1.0);
      }
    }

    for(int x = 0; x < 32; x++){
      free(red[x]);
      free(green[x]);
      free(blue[x]);
    }
    free(red);
    free(green);
    free(blue);
  }
  free(batch);
  for(int i = 1024; i < 1034; i++){
    for(int j = 0; j < 5000; j++){
      gsl_matrix_set(data->validation_input_sequence[i], 0, j, 0.0);
      gsl_matrix_set(data->validation_input_sequence[i], 1, j, 0.0);
      gsl_matrix_set(data->validation_input_sequence[i], 2, j, 0.0);
      gsl_matrix_set(data->validation_input_sequence[i], 3, j, 1.0);
    }
  }

  file_size = slurp("Datasets/cifar-10/test_batch.bin", &batch, false);
  element = 0;
  for(i = 0; i < 10000; i++){
    int class = (int)batch[element];
    gsl_matrix_set(data->test_output, (int)batch[element], i, 1.0);
    element++;
    unsigned int** red;
    unsigned int** blue;
    unsigned int** green;
    red = malloc(32 * sizeof(unsigned int*));
    green = malloc(32 * sizeof(unsigned int*));
    blue = malloc(32 * sizeof(unsigned int*));
    for(int x = 0; x < 32; x++){
      red[x] = malloc(32 * sizeof(unsigned int));
      green[x] = malloc(32 * sizeof(unsigned int));
      blue[x] = malloc(32 * sizeof(unsigned int));
    }
    int x = 0;
    int y = 0;
    int col = 0;
    for(int e = 0; e < 3072; e++){
      if(col == 0){
        red[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }
      }
      else if(col == 1){
        green[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      else if(col == 2){
        blue[x][y] = (unsigned int)batch[element];
        x++;
        if(x == 32){
          x = 0;
          y++;
        }
        if(y == 32){
          col++;
          x = 0;
          y = 0;
        }

      }
      element++;
    }

    for(int y = 0; y < 32; y++){
      for(int x = 0; x < 32; x++){
        int entry = (y * 32) + x;
        gsl_matrix_set(data->test_input_sequence[entry], 0, i, (double)red[x][y] / 128.0);
        gsl_matrix_set(data->test_input_sequence[entry], 1, i, (double)green[x][y] / 128.0);
        gsl_matrix_set(data->test_input_sequence[entry], 2, i, (double)blue[x][y] / 128.0);
        gsl_matrix_set(data->test_input_sequence[entry], 3, i, 1.0);
      }
    }

    for(int x = 0; x < 32; x++){
      free(red[x]);
      free(green[x]);
      free(blue[x]);
    }
    free(red);
    free(green);
    free(blue);
  }
  free(batch);
  for(int i = 1024; i < 1034; i++){
    for(int j = 0; j < 10000; j++){
      gsl_matrix_set(data->test_input_sequence[i], 0, j, 0.0);
      gsl_matrix_set(data->test_input_sequence[i], 1, j, 0.0);
      gsl_matrix_set(data->test_input_sequence[i], 2, j, 0.0);
      gsl_matrix_set(data->test_input_sequence[i], 3, j, 1.0);
    }
  }
  return data;

}
