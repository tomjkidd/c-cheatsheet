#include <stdio.h>

struct location {
  const int lat;
  const int lon;
};

struct location go_south_east(struct location loc){
  struct location l = { loc.lat - 1, loc.lon + 1 }; // Create a new struct based on the one passed in
  return l;
}

/*
 Using typedef allows a style more similar to a class (with an emphasis on just the data!) 
*/

typedef struct location_alt {
  const int lat;
  const int lon;
} location_alt;

location_alt go_south_east_alt(location_alt loc) {
  location_alt l = { loc.lat - 1, loc.lon + 1 };
  return l;
}

int main() {
  int latitude = 32; // Set an initial latitude
  int longitude = -64; // Set an initial longitude

  struct location l = { latitude, longitude };
  struct location m = go_south_east(l);

  location_alt x = { latitude, longitude };
  location_alt y = go_south_east_alt(x);

  printf("latitude is stored at %p\n", &latitude);
  printf("longitude is stored at %p\n", &longitude);

  printf("l at [%i,%i]\n", l.lat, l.lon);
  printf("m at [%i,%i]\n", m.lat, m.lon);

  printf("x at [%i,%i]\n", x.lat, x.lon);
  printf("y at [%i,%i]\n", y.lat, y.lon);
  
  return 0;
}
