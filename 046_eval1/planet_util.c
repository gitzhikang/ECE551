#include "planet_util.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "provided.h"

point_t get_location_at(const planet_t * p, double time) {
  // Step 2: WRITE THIS
  point_t ans;
  double period = p->year_len;
  double movedRadius = time * 2 * M_PI / period;
  double newRadius = movedRadius + p->init_pos;
  while (newRadius >= 2 * M_PI) {
    newRadius -= 2 * M_PI;
  }
  double x = p->orbital_radius * cos(newRadius);
  double y = p->orbital_radius * sin(newRadius);
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
  printf("Planet %s not found!\n", name);
  exit(EXIT_FAILURE);
}
