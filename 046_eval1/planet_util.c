#include "planet_util.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "provided.h"

point_t get_location_at(const planet_t * p, double time) {
  // Step 2: WRITE THIS
  if (p == NULL) {
    fprintf(stderr, "Planet is NULL!\n");
    exit(EXIT_FAILURE);
  }
  point_t ans;
  double period = p->year_len;
  double movedRadians = time * 2 * M_PI / period;
  double newRadians = movedRadians + p->init_pos;
  //get mod
  while (newRadians >= 2 * M_PI) {
    newRadians -= 2 * M_PI;
  }
  double x = p->orbital_radius * cos(newRadians);
  double y = p->orbital_radius * sin(newRadians);
  ans.x = x;
  ans.y = y;
  return ans;
}
planet_t * find_planet(const planet_list_t * lst, const char * name) {
  //Step 2: WRITE THIS
  planet_t ** list = lst->planets;
  size_t list_size = lst->num_planets;
  for (int i = 0; i < list_size; i++) {
    if (strcmp(list[i]->name, name) == 0) {
      return list[i];
    }
  }
  //if not return in the for loop, can't get the planet in lst
  fprintf(stderr, "Planet %s not found!\n", name);
  exit(EXIT_FAILURE);
}
