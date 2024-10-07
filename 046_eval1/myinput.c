#include "myinput.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "provided.h"

void parse_planet_info(planet_t * planet, char * line) {
  //STEP 1: Write this
  int index = 0;
  const char * seperator = ":";
  char * current = line;
  char * token;
  //convert name
  token = strsep(&current, seperator);
  if (token == NULL) {
    fprintf(stderr, "Wrong number of fields!");
    exit(EXIT_FAILURE);
  }
  while (token[index] != '\n' && token[index] != '\0' && index < 32) {
    planet->name[index] = line[index];
    index++;
  }
  if (index == 32) {
    fprintf(stderr, "name excced the maxium length!");
    exit(EXIT_FAILURE);
  }
  if (index == 0) {
    planet->name[index] = '\0';
  }
  if (token[index] == '\n') {
    fprintf(stderr, "Wrong number of fields!");
    exit(EXIT_FAILURE);
  }
  planet->name[index] = '\0';
  //convert radius
  token = strsep(&current, seperator);
  index = 0;
  double radius = 0;
  while (token[index] != '\n' && token[index] != '\0') {
    //100.02
    if (!isdigit(token[index]) && token[index] != '.') {
      fprintf(stderr, "Wrong format for radius!");
      exit(EXIT_FAILURE);
    }
    index++;
  }
  if (index == 0) {
    fprintf(stderr, "null input for radius!");
    exit(EXIT_FAILURE);
  }
  if (token[index] == '\n') {
    fprintf(stderr, "Wrong number of fields!");
    exit(EXIT_FAILURE);
  }

  radius = atof(token);
  planet->orbital_radius = radius;
  //convert period
  index = 0;
  token = strsep(&current, seperator);
  double period = 0;
  while (token[index] != '\n' && token[index] != '\0') {
    if (!isdigit(token[index]) && token[index] != '.') {
      fprintf(stderr, "Wrong format for period!");
      exit(EXIT_FAILURE);
    }
    index++;
  }
  if (index == 0) {
    fprintf(stderr, "null input for period!");
    exit(EXIT_FAILURE);
  }
  if (token[index] == '\n') {
    fprintf(stderr, "Wrong number of fields!");
    exit(EXIT_FAILURE);
  }
  period = atof(token);
  planet->year_len = period;
  //convert position
  index = 0;
  token = strsep(&current, seperator);
  double position = 0;
  while (token[index] != '\n' && token[index] != '\0') {
    if (!isdigit(token[index]) && token[index] != '.') {
      fprintf(stderr, "Wrong format for period!");
      exit(EXIT_FAILURE);
    }
    index++;
  }
  if (token[index] != '\n') {
    fprintf(stderr, "Wrong number of fields!");
    exit(EXIT_FAILURE);
  }
  if (index == 0) {
    position = 0.0;
  }
  else {
    position = atof(token);
  }
  planet->init_pos = position / 180 * M_PI;
}
