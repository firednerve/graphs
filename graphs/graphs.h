
#ifndef GRAPHS_H
#define GRAPHS_H

#include "cairo/cairo.h"
#include <math.h>
#include "data.h"
// options for kind of graph
#define PLOT_TYPE_QUADRANT 0
#define PLOT_TYPE_PRIMARY  1
// constants for printing numbers along axes for quadrant graph
#define QUAD_ORIGIN_X  0.485
#define QUAD_ORIGIN_Y  0.520
#define QUAD_MARGIN_X  0.530
#define QUAD_MARGIN_Y  0.460
// constants for printing numbers along axes for primary quadrant-only graph
#define PRIM_ORIGIN_X 0.020
#define PRIM_ORIGIN_Y 0.980
#define PRIM_MARGIN_X 0.995
#define PRIM_MARGIN_Y 0.005

#define NUM_FONT_STYLE  "Deja vu Sans Mono" // font that numbers are printed in
#define NUM_FONT_SIZE   0.017

#define PLOT_LINE_WIDTH 0.001 // line width of line plot
#define PLOT_DOT_RADIUS 0.002 // dot radius of dot plot

#define PLOT_COLOR_RED   1
#define PLOT_COLOR_GREEN 2
#define PLOT_COLOR_BLUE  3

#define PLOT_STYLE_LINE 1
#define PLOT_STYLE_DOT  2
#define PLOT_STYLE_BOTH 3

void draw_quadrant(cairo_t* cr, unsigned int notches, double scale);
void draw_canvas(cairo_t* cr);
void draw_axes(cairo_t* cr);
void draw_scales(cairo_t* cr, unsigned int notches);
void draw_grid(cairo_t* cr, unsigned int notches);
void draw_axes_nums(cairo_t* cr, unsigned int notches, double scale);
void draw_small_grid(cairo_t* cr, unsigned int notches);
void draw_primary_quadrant(cairo_t* cr, unsigned int notches, double scale);
void draw_primary_axes(cairo_t* cr, unsigned int notches);
void draw_primary_scales(cairo_t* cr, unsigned int notches);
void draw_primary_axes_nums(cairo_t* cr, unsigned int notches, double scale);
void draw_data(cairo_t* cr, Data* data, unsigned int color, unsigned int style, unsigned int notches, double scale);
void color_color(cairo_t* cr, unsigned int color);
void draw_data_line(cairo_t* cr, Data* data, unsigned int color, unsigned int notches, double scale);
void draw_data_dot(cairo_t* cr, Data* data, unsigned int color, unsigned int notches, double scale);
void draw_primary_data(cairo_t* cr, Data* data, unsigned int color, unsigned int style, unsigned int notches, double scale);
void draw_primary_data_line(cairo_t* cr, Data* data, unsigned int color, unsigned int notches, double scale);
void draw_primary_data_dot(cairo_t* cr, Data* data, unsigned int color, unsigned int notches, double scale);
void plot_quadrant_data(cairo_t* cr, Data* data, unsigned int color, unsigned int style, unsigned int notches, double scale);
void plot_primary_data(cairo_t* cr, Data* data, unsigned int color, unsigned int style, unsigned int notches, double scale);
void plot_data(cairo_t* cr, Data* data, unsigned int plot_type, unsigned int color, unsigned int style, unsigned int notches, double scale);

/**
* There are seven parameters of interest in plotting:
* cairo_t* cr: this is the cairo object handle that essentially contains all aspects
* of the image we create.
* Data* data: this is a data array. It is assumed that the data is in the form of
* a tuple of x's and y's, that is, an array of (x,y)'s.
* color: a macro that specifies which color the graph should be in. Only red, green
* and blue are supported.
* style: a macro that specifies which style (line plot, dot plot or both) the graph
* should be in.
* size: this is an unsigned int specifying the number of data points in the data
* array.
* notches: this is the number of scales along the axes that we intend to make.
* scale: this is a multiplier that specifies how zoomed in or zoomed out the graph
* is.
*/

/**
* For plotting data, the only functions of interest are plot_data and
* plot_primary_data. These functions create an image containing a graph of the
* points in a quadrant or in the primary quadrant only respectively.
*/

void draw_quadrant(cairo_t* cr, unsigned int notches, double scale) {
  // creates a quadrant graph with no plot in it
  notches += 2;
  draw_canvas(cr);
  draw_grid(cr, notches);
  draw_axes(cr);
  draw_scales(cr, notches);
  draw_axes_nums(cr, notches, scale);
}

void draw_canvas(cairo_t* cr) {
  // creates canvas for the quadrant to be drawn in
  cairo_set_line_width(cr, 0.01);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_rectangle(cr, 0, 0, 1, 1);
  cairo_fill(cr);
}

void draw_axes(cairo_t* cr) {
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  cairo_move_to(cr, 0.5, 0);
  cairo_line_to(cr, 0.5, 1);
  cairo_move_to(cr, 0, 0.5);
  cairo_line_to(cr, 1, 0.5);
  cairo_stroke(cr);
}

void draw_scales(cairo_t* cr, unsigned int notches) {
  // draws scales along axes
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  // y-axis scales
  for (unsigned int i = 0; i <= notches; i++) {
    cairo_move_to(cr, 0.5 + 0.01, i*(1.0/notches));
    cairo_line_to(cr, 0.5 - 0.01, i*(1.0/notches));
  }
  // x-axis scales
  for (unsigned int i = 0; i <= notches; i++) {
    cairo_move_to(cr, i*(1.0/notches), 0.5 + 0.01);
    cairo_line_to(cr, i*(1.0/notches), 0.5 - 0.01);
  }
  cairo_stroke(cr);
}

void draw_grid(cairo_t* cr, unsigned int notches) {
  // draws a graph grid
  draw_small_grid(cr, notches);
  cairo_set_source_rgb(cr, 0.70, 0.70, 0.70);
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  for (unsigned int i = 0; i <= notches; i++) {
    // y-axis lines (vertical)
    cairo_move_to(cr, i*(1.0/notches), 0.0);
    cairo_line_to(cr, i*(1.0/notches), 1.0);
    // x-axis lines (horizontal)
    cairo_move_to(cr, 0.0, i*(1.0/notches));
    cairo_line_to(cr, 1.0, i*(1.0/notches));
  }
  cairo_stroke(cr);
}

void draw_small_grid(cairo_t* cr, unsigned int notches) {
  // draws a smaller graph grid
  cairo_set_source_rgb(cr, 0.86, 0.86, 0.86);
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  for (unsigned int i = 0; i <= 10*notches; i++) {
    cairo_move_to(cr, i*(1.0/(10*notches)), 0.0);
    cairo_line_to(cr, i*(1.0/(10*notches)), 1.0);
    cairo_move_to(cr, 0.0, i*(1.0/(10*notches)));
    cairo_line_to(cr, 1.0, i*(1.0/(10*notches)));
  }
  cairo_stroke(cr);
}

void draw_primary_quadrant(cairo_t* cr, unsigned int notches, double scale) {
  // same as draw_quadrant, except only first quadrant is drawn
  notches += 2;
  draw_canvas(cr);
  draw_grid(cr, notches);
  draw_primary_axes(cr, notches);
  draw_primary_scales(cr, notches);
  draw_primary_axes_nums(cr, notches, scale);
}

void draw_primary_axes(cairo_t* cr, unsigned int notches) {
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  // y-axis
  cairo_move_to(cr, 1.0/notches, 0.0);
  cairo_line_to(cr, 1.0/notches, 1.0);
  // x-axis
  cairo_move_to(cr, 0.0, 1.0 - (1.0/notches));
  cairo_line_to(cr, 1.0, 1.0 - (1.0/notches));
  cairo_stroke(cr);
}

void draw_primary_scales(cairo_t* cr, unsigned int notches) {
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  // y-axis scales
  for (unsigned int i = 0; i <= notches; i++) {
    cairo_move_to(cr, (1.0/notches) + 0.01, i*(1.0/notches));
    cairo_line_to(cr, (1.0/notches) - 0.01, i*(1.0/notches));
  }
  // x-axis scales
  for (unsigned int i = 0; i <= notches; i++) {
    cairo_move_to(cr, i*(1.0/notches), 1.0 - (1.0/notches) + 0.01);
    cairo_line_to(cr, i*(1.0/notches), 1.0 - (1.0/notches) - 0.01);
  }
  cairo_stroke(cr);
}

void draw_axes_nums(cairo_t* cr, unsigned int notches, double scale) {
  // Function that prints numbers along the axes
  cairo_text_extents_t te;
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_select_font_face(cr, NUM_FONT_STYLE,
  CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, NUM_FONT_SIZE);
  cairo_text_extents(cr, "0.0",&te); // buffer overflow occurs here
  cairo_move_to(cr, QUAD_ORIGIN_X, QUAD_ORIGIN_Y);
  cairo_show_text(cr, "0.0"); // prints origin
  for (unsigned int i = 1; i < ceil(notches/2); i++) {
    // prints +ve y-axis numbers
    sds num_txt = sdsempty();
    sdscatprintf(num_txt, "%.1lf", i * scale);
    cairo_text_extents(cr, num_txt,&te);
    cairo_move_to(cr, QUAD_MARGIN_Y, 0.5 - (i*(1.0/notches) - 0.005));
    cairo_show_text(cr, num_txt);
    sdsfree(num_txt);
  }
  for (unsigned int i = 1; i < ceil(notches/2); i++) {
    // prints +ve x-axis numbers
    sds num_txt = sdsempty();
    sdscatprintf(num_txt, "%.1lf", i * scale);
    cairo_text_extents(cr, num_txt,&te);
    cairo_move_to(cr, 0.5 + (i*(1.0/notches)) - 0.005, QUAD_MARGIN_X);
    cairo_show_text(cr, num_txt);
    sdsfree(num_txt);
  }
  for (int i = -1; i > -1*ceil(notches/2); i--) {
    // prints -ve y-axis numbers
    sds num_txt = sdsempty();
    sdscatprintf(num_txt, "%.1lf", i * scale);
    cairo_text_extents(cr, num_txt,&te);
    cairo_move_to(cr, QUAD_MARGIN_Y - 0.01, 0.5 - (i*(1.0/notches) - 0.005));
    cairo_show_text(cr, num_txt);
    sdsfree(num_txt);
  }
  for (int i = -1; i > -1*ceil(notches/2); i--) {
    // prints -ve x-axis numbers
    sds num_txt = sdsempty();
    sdscatprintf(num_txt, "%.1lf", i * scale);
    cairo_text_extents(cr, num_txt,&te);
    cairo_move_to(cr, 0.5 + (i*(1.0/notches)) - 0.015, QUAD_MARGIN_X);
    cairo_show_text(cr, num_txt);
    sdsfree(num_txt);
  }
}

void draw_primary_axes_nums(cairo_t* cr, unsigned int notches, double scale) {
  // Function that prints numbers along the axes
  cairo_text_extents_t te;
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_select_font_face(cr, NUM_FONT_STYLE,
  CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, NUM_FONT_SIZE);
  cairo_text_extents(cr, "0", &te);
  cairo_move_to(cr, PRIM_ORIGIN_X, PRIM_ORIGIN_Y);
  cairo_show_text(cr, "0"); // prints origin
  for (unsigned int i = 1; i < notches - 1; i++) {
    // prints y-axis numbers
    sds num_txt = sdsempty();
    sdscatprintf(num_txt, "%.1lf", i * scale);
    cairo_text_extents(cr, num_txt, &te);
    cairo_move_to(cr, PRIM_MARGIN_Y, (1.0 - (1.0/notches)) - (i*(1.0/notches) - 0.005));
    cairo_show_text(cr, num_txt);
    sdsfree(num_txt);
  }
  for (unsigned int i = 1; i < notches - 1; i++) {
    // prints x-axis numbers
    sds num_txt = sdsempty();
    sdscatprintf(num_txt, "%.1lf", i * scale);
    cairo_text_extents(cr, num_txt, &te);
    cairo_move_to(cr, (1.0/notches) + (i*(1.0/notches)) - 0.005, PRIM_MARGIN_X);
    cairo_show_text(cr, num_txt);
    sdsfree(num_txt);
  }
}

void draw_data(cairo_t* cr, Data* data, unsigned int color, unsigned int style, unsigned int notches, double scale) {
  // plots data on graph
  switch (style) {
    case 1:
      draw_data_line(cr,data,color,notches,scale);
      break;
    case 2:
      draw_data_dot(cr,data,color,notches,scale);
      break;
    case 3:
      draw_data_line(cr,data,color,notches,scale);
      draw_data_dot(cr,data,color,notches,scale);
      break;
    default:
      draw_data_line(cr,data,color,notches,scale);
  }
}

void color_color(cairo_t* cr, unsigned int color) {
  // chooses color based on choice given
  switch (color) {
    case 1: // red color
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    break;
    case 2: // green color
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
    break;
    case 3: // blue color
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    break;
    default: // default: red color
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
  }
}

void draw_data_line(cairo_t* cr, Data* data, unsigned int color, unsigned int notches, double scale) {
  // draws a line plot of data
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  color_color(cr, color);
  cairo_move_to(cr, 0.5, 0.5); // move to origin
  for (unsigned int i = 0; i < data->size - 1; i++) {
    double scaler = 1.0/((notches + 2.0)*scale);
    cairo_move_to(cr, 0.5 + scaler*data->set[i]->x, 0.5 - scaler*data->set[i]->y);
    cairo_line_to(cr, 0.5 + scaler*data->set[i+1]->x, 0.5 - scaler*data->set[i+1]->y);
  }
  cairo_stroke(cr);
}

void draw_data_dot(cairo_t* cr, Data* data, unsigned int color, unsigned int notches, double scale) {
  // draws a dot plot of data
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  color_color(cr, color);
  cairo_move_to(cr, 0.5, 0.5); // move to origin
  for (unsigned int i = 0; i < data->size; i++) {
    double scaler = 1.0/((notches + 2.0)*scale);
    cairo_arc(cr, 0.5 + scaler*data->set[i]->x, 0.5 - scaler*data->set[i]->y, PLOT_DOT_RADIUS, 0.0, 2.0*M_PI);
    cairo_fill(cr);
  }
}

void draw_primary_data(cairo_t* cr, Data* data, unsigned int color, unsigned int style, unsigned int notches, double scale) {
  switch (style) {
    case 1:
      draw_primary_data_line(cr,data,color,notches,scale);
      break;
    case 2:
      draw_primary_data_dot(cr,data,color,notches,scale);
      break;
    case 3:
      draw_primary_data_line(cr,data,color,notches,scale);
      draw_primary_data_dot(cr,data,color,notches,scale);
      break;
    default:
      draw_primary_data_line(cr,data,color,notches,scale);
  }
}

void draw_primary_data_line(cairo_t* cr, Data* data, unsigned int color, unsigned int notches, double scale) {
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  color_color(cr, color);
  cairo_move_to(cr, 1.0/(notches + 2.0), 1.0 - 1.0/(notches + 2.0)); // move to origin
  for (unsigned int i = 0; i < data->size - 1; i++) {
    double scaler = 1.0/((notches + 2.0)*scale);
    cairo_move_to(cr, 1.0/(notches + 2.0) + scaler*data->set[i]->x, 1.0 - 1.0/(notches + 2.0) - scaler*data->set[i]->y);
    cairo_line_to(cr, 1.0/(notches + 2.0) + scaler*data->set[i+1]->x, 1.0 - 1.0/(notches + 2.0) - scaler*data->set[i+1]->y);
  }
  cairo_stroke(cr);
}

void draw_primary_data_dot(cairo_t* cr, Data* data, unsigned int color, unsigned int notches, double scale) {
  cairo_set_line_width(cr, PLOT_LINE_WIDTH);
  color_color(cr, color);
  cairo_move_to(cr, 1.0/(notches + 2.0), 1.0 - 1.0/(notches + 2.0)); // move to origin
  for (unsigned int i = 0; i < data->size; i++) {
    double scaler = 1.0/((notches + 2.0)*scale);
    cairo_arc(cr, 1.0/(notches + 2.0) + scaler*data->set[i]->x, 1.0 - 1.0/(notches + 2.0) - scaler*data->set[i]->y, PLOT_DOT_RADIUS, 0.0, 2.0*M_PI);
    cairo_fill(cr);
  }
}

void plot_quadrant_data(cairo_t* cr, Data* data, unsigned int color, unsigned int style, unsigned int notches, double scale) {
  // sets canvas, draws quadrant and plots data, all in one function
  draw_quadrant(cr, notches, scale);
  draw_data(cr, data, color, style, notches, scale);
}

void plot_primary_data(cairo_t* cr, Data* data, unsigned int color, unsigned int style, unsigned int notches, double scale) {
  // same as plot_data, except only in first quadrant
  draw_primary_quadrant(cr, notches, scale);
  draw_primary_data(cr, data, color, style, notches, scale);
}

void plot_data(cairo_t* cr, Data* data, unsigned int plot_type, unsigned int color, unsigned int style, unsigned int notches, double scale) {
  switch (plot_type) {
    case 0:
      plot_quadrant_data(cr, data, color, style, notches, scale);
      break;
    case 1:
      plot_primary_data(cr, data, color, style, notches, scale);
      break;
    default:
      plot_quadrant_data(cr, data, color, style, notches, scale);
  }
}

#endif
