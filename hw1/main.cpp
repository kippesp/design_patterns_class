#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <list>
#include <map>
#include <set>
#include <vector>

#include <iostream>
using namespace std;

#include "macros.h"  // Redundant, already in the <dp>.h files, but may need if you change the directory structure implied below.

namespace strategy {
namespace homework {
#include "problem/strategy.h"
}
}

#include "solution/strategy.h"

// Seam point - include next design pattern.

int main(int argc, char* args[]) {
  if (argc != 2) {
    printf("Usage: ./a.out <dp-number> (1-9)\n");
    exit(-1);
  }

  int dp = atoi(args[1]);

  switch (dp) {
    case 1:
      strategy::homework::legacy::demo(dp);
      strategy::homework::problem::demo(dp);
      // strategy::homework::solution::demo(dp);
      break;
    // Seam point - add next design pattern.

    default:
      printf("Unknown design pattern number %d.\n", dp);
      break;
  }

  printf("Done.\n");
}
