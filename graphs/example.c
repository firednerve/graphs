// Graph program using cairo.h

#include "graphs.h"
#include <errno.h>

char* get_txt(FILE* fp);

int main(int argc, char* argv[]) {
  // Initialization of context and surface
  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 2000, 2000);
  cairo_t* cr = cairo_create(surface);
  // Define coordinate space
  cairo_scale(cr, 2000, 2000);
  // Drawing part
  Data* data = data_new();
  data_push(data, 0.0, 0.0);
  data_push(data, 1.0, 1.0);
  data_push(data, 2.0, 3.0);
  data_push(data, -1.0, -4.0);
  plot_data(cr, data, PLOT_TYPE_QUADRANT, PLOT_COLOR_RED, PLOT_STYLE_BOTH, 20, 1);
  data_free(data);
  // Freeing memory of context and surface, and saving to png file
  cairo_surface_write_to_png(surface, "graphs.png");
  cairo_destroy(cr);
  cairo_surface_destroy(surface);
  return 0;
}

char* get_txt(FILE* fp) {
 /**
  * Gets all text data from a file and stores it in a string.
  * @param fp file pointer of file to be read (with read access).
  * @return output string that stores all data in file as text.
  */
  if (fp == NULL) { // file does not exist
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  char* output = (char*)calloc(1,sizeof(char));
  if (output == NULL) { // memory cannot be allocated
    printf("Error: %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  char c = fgetc(fp);
  int count = 0;
  while (c != EOF) { // read till end of file
    output = (char*)realloc(output, (count+1)*sizeof(char)); // increase size by 1
    if (output == NULL) { // memory cannot be allocated
      printf("Error: %s\n",strerror(errno));
      exit(EXIT_FAILURE);
    }
    output[count] = c; // add char to string
    c = fgetc(fp); // read next char
    count++;
    if (c == EOF) {
      output = (char*)realloc(output, (count+1)*sizeof(char)); // make space for null char
      output[count] = '\0';
    }
  }
  return output;
}
