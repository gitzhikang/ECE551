#include "myinput.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "provided.h"

void parse_planet_info(planet_t * planet, char * line) {
  //STEP 1: Write this
  int index = 0;
  //convert name
  while (isalpha(line[index])) {
    planet->name[index] = line[index];
    index++;
  }
  if (isdigit(line[index])) {
    fprintf(stderr, "Wrong format!");
    exit(EXIT_FAILURE);
  }
  if (line[index] != ':') {
    fprintf(stderr, "Wrong number of fields!");
    exit(EXIT_FAILURE);
  }
  planet->name[index++] = '\0';
  //convert radius
  double radius = 0;
  while (isdigit(line[index])) {
    radius = 10 * radius + line[index] - '0';
    index++;
  }
  if (isalpha(line[index])) {
    fprintf(stderr, "Wrong format!");
    exit(EXIT_FAILURE);
  }
  if (line[index] != ':') {
    fprintf(stderr, "Wrong number of fields!");
    exit(EXIT_FAILURE);
  }
  planet->orbital_radius = radius;
  index++;
  //convert period
  double period = 0;
  while (isdigit(line[index])) {
    period = 10 * period + line[index] - '0';
    index++;
  }
  if (isalpha(line[index])) {
    fprintf(stderr, "Wrong format!");
    exit(EXIT_FAILURE);
  }
  if (line[index] != ':') {
    fprintf(stderr, "Wrong number of fields!");
    exit(EXIT_FAILURE);
  }
  planet->year_len = period;
  index++;
  //convert position
  double position = 0;
  while (isdigit(line[index])) {
    position = 10 * position + line[index] - '0';
    index++;
  }
  //305a || 305%
  if (line[index] != '\n') {
    fprintf(stderr, "Wrong format!");
    exit(EXIT_FAILURE);
  }
  //370
  if (position > 360) {
    fprintf(stderr, "Wrong position!");
    exit(EXIT_FAILURE);
  }
  planet->init_pos = position / 180 * M_PI;
}
