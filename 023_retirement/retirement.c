#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double computeBalance(int startAge, double initial, retire_info info) {
  int months = info.months;
  double rateOfReturn = info.rate_of_return / 12.0;
  double contribution = info.contribution;
  int beginAge = startAge / 12;
  int beginMonth = startAge % 12;
  for (int i = 0; i < months; i++) {
    printf("Age %3d month %2d you have $%.2f\n",
           beginAge + (i + beginMonth) / 12,
           (i + beginMonth) % 12,
           initial);
    initial = initial * (1.0 + rateOfReturn);
    initial = initial + contribution;
  }
  return initial;
}
void retirement(int startAge,         //in months
                double initial,       //initial savings in dollars
                retire_info working,  //info about working
                retire_info retired)  //info about being retired
{
  initial = computeBalance(startAge, initial, working);
  startAge += working.months;
  computeBalance(startAge, initial, retired);
}

int main() {
  retire_info working;
  retire_info retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return 0;
}
