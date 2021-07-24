// Graph program using cairo.h

#include "graphs.h"

int main(int argc, char* argv[]) {
  // Initialization of context and surface
  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 2000, 2000);
  cairo_t* cr = cairo_create(surface);
  // Define coordinate space
  cairo_scale(cr, 2000, 2000);
  // Drawing part
  int scale = 1;
  int notches = 20;
  unsigned int size = 3;
  double** data = (double**) calloc(size, sizeof(double*));
  data[0] = (double*) calloc(2, sizeof(double));
  data[1] = (double*) calloc(2, sizeof(double));
  data[2] = (double*) calloc(2, sizeof(double));
  data[0][0] = 0.0;
  data[0][1] = 0.0;
  data[1][0] = 1.0;
  data[1][1] = 1.0;
  data[2][0] = 2.0;
  data[2][1] = 3.0;
  plot_data(cr, data, PLOT_COLOR_RED, PLOT_STYLE_BOTH, size, notches, scale);
  free(data[0]);
  free(data[1]);
  free(data[2]);
  free(data);
  // Freeing memory of context and surface, and saving to png file
  cairo_surface_write_to_png(surface, "graphs.png");
  cairo_destroy(cr);
  cairo_surface_destroy(surface);
  return 0;
}
