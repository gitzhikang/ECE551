#include "iter_target.h"

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
double cal_distance(point_t a, point_t b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
//compute launch result accoring to the target position
launch_result_t compute_launch_by_target_position(const launch_input_t * this_launch,
                                                  const planet_list_t * planets,
                                                  point_t target_position) {
  launch_result_t result;
  double epsilon = 1e-9;
  planet_t * source_planet = find_planet(planets, this_launch->src);
  double time = this_launch->time;
  point_t location_target = target_position;
  point_t location_source = get_location_at(source_planet, time);
  double distance = sqrt(
      (location_source.x - location_target.x) * (location_source.x - location_target.x) +
      (location_source.y - location_target.y) * (location_source.y - location_target.y));
  double ans_time = distance / this_launch->speed;
  //calculate angle
  double ans_angle = atan((location_target.y - location_source.y) /
                          (location_target.x - location_source.x));
  //post calculation
  if (fabs(location_target.x - location_source.x) < epsilon) {
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
launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  //STEP 4: write this function
  uint64_t max_iterations = this_launch->max_iterations;
  double close_enough = this_launch->close_enough;
  planet_t * target_planet = find_planet(planets, this_launch->dest);
  launch_result_t least_ans = {0.0, DBL_MAX};
  double least_all_time = DBL_MAX;
  //get location of target plane
  point_t target_projected_point = get_location_at(target_planet, this_launch->time);
  //get result to target plane
  launch_result_t ans_to_projected_target =
      compute_launch_by_target_position(this_launch, planets, target_projected_point);
  //get whole time(including wait time) of getting to target planet
  double whole_time =
      when_does_planet_return_to(target_planet,
                                 target_projected_point,
                                 this_launch->time + ans_to_projected_target.duration) -
      this_launch->time;
  //record least time of getting to target planet
  if (whole_time < least_all_time) {
    least_all_time = whole_time;
    least_ans = ans_to_projected_target;
  }
  //set new target plane(the plane location for this iteration)
  point_t next_target_projected_point = get_location_at(
      target_planet, this_launch->time + ans_to_projected_target.duration);
  ;
  double distance = cal_distance(target_projected_point, next_target_projected_point);
  //begin to iterate the same behavior like previous
  uint64_t iterations = 1;
  while (iterations < max_iterations && distance > close_enough) {
    target_projected_point = next_target_projected_point;
    ans_to_projected_target =
        compute_launch_by_target_position(this_launch, planets, target_projected_point);
    whole_time =
        when_does_planet_return_to(target_planet,
                                   target_projected_point,
                                   this_launch->time + ans_to_projected_target.duration) -
        this_launch->time;
    if (whole_time < least_all_time) {
      least_all_time = whole_time;
      least_ans = ans_to_projected_target;
    }
    next_target_projected_point = get_location_at(
        target_planet, this_launch->time + ans_to_projected_target.duration);
    iterations++;
    distance = cal_distance(target_projected_point, next_target_projected_point);
  }
  //if reach to max_iteration, return least ans
  if (iterations >= max_iterations) {
    return least_ans;
  }
  return ans_to_projected_target;
}
