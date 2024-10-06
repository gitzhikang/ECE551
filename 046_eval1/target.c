#include "target.h"

#include <stdio.h>
launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets) {
  //STEP 3: Write this
  launch_result_t result;
  planet_t * source_planet = find_planet(planets, this_launch->src);
  planet_t * target_planet = find_planet(planets, this_launch->dest);
  double time = this_launch->time;
  point_t location_target = get_location_at(target_planet, time);
  point_t location_source = get_location_at(source_planet, time);
  double distance = sqrt(
      (location_source.x - location_target.x) * (location_source.x - location_target.x) +
      (location_source.y - location_target.y) * (location_source.y - location_target.y));
  double ans_time = distance / this_launch->speed;
  double ans_angle = atan((location_target.y - location_source.y) /
                          (location_target.x - location_source.x));
  //post calculation
  if (location_target.x - location_source.x == 0) {
    if (location_target.y > location_source.y) {
      ans_angle = M_PI / 2;
    }
    else {
      ans_angle = 3 * M_PI / 2;
    }
  }
  else {
    if (location_target.x - location_source.x < 0) {
      ans_angle += M_PI;
    }
  }
  //Normalization
  if (ans_angle < 0) {
    ans_angle += 2 * M_PI;
  }
  result.duration = ans_time;
  result.theta = ans_angle;
  return result;
}

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time) {
  //STEP 3: Write this
  //convert pos into radians
  double radians_xy = atan(pos.y / pos.x);
  if (pos.x == 0) {
    if (pos.y > 0) {
      radians_xy = M_PI / 2;
    }
    else {
      radians_xy = 3 * M_PI / 2;
    }
  }
  else {
    if (pos.x < 0) {
      radians_xy += M_PI;
    }
  }
  //Normalization
  if (radians_xy < 0) {
    radians_xy += 2 * M_PI;
  }
  double moved_radians_in_start_time = start_time * 2 * M_PI / planet->year_len;
  double planet_radians_in_start_time = moved_radians_in_start_time + planet->init_pos;
  while (planet_radians_in_start_time > 2 * M_PI) {
    planet_radians_in_start_time -= 2 * M_PI;
  }
  double speed = 2 * M_PI / planet->year_len;
  double distance_radians = 0;
  if (planet_radians_in_start_time > radians_xy) {
    distance_radians = 2 * M_PI - planet_radians_in_start_time + radians_xy;
  }
  else {
    distance_radians = radians_xy - planet_radians_in_start_time;
  }
  return distance_radians / speed + start_time;
}
