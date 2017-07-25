#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <list>
#include <map>
#include <set>
#include <vector>

#include <iostream>
using namespace std;

#include "macros.h"  // there can be only one

namespace homework {

namespace strategy {
#include "problem/strategy.h"
#include "solution/strategy.h"
}

namespace adapter {
#include "problem/adapter.h"
#include "solution/adapter.h"
}

namespace factoryMethod {
#include "problem/factoryMethod.h"
#include "solution/factoryMethod.h"
}

namespace templateMethod {
#include "problem/templateMethod.h"
#include "solution/templateMethod.h"
}

namespace observer {
#include "problem/observer.h"
#include "solution/observer.h"
}

namespace decorator {
#include "problem/decorator.h"
#include "solution/decorator.h"
}

namespace chainOfResponsibility {
#include "problem/chainOfResp.h"
#include "solution/chainOfResp.h"
}

namespace bridge {
#include "problem/bridge.h"
#include "solution/bridge.h"
}

namespace abstractFactory {
#include "problem/abstractFactory.h"
#include "solution/abstractFactory.h"
}

// Seam point - include next design pattern.
}

int main(int argc, char* args[]) {
  if (argc != 2) {
    printf("Usage: ./a.out <dp-number> (1-9)\n");
    exit(-1);
  }

  int dp = atoi(args[1]);

  switch (dp) {
    case 1:
      homework::strategy::legacy::demo(dp);
      homework::strategy::problem::demo(dp);
      homework::strategy::solution::demo(dp);
      break;
    case 2:
      homework::adapter::legacy::demo(dp);
      homework::adapter::problem::demo(dp);
      homework::adapter::solution::demo(dp);
      break;
    case 3:
      homework::factoryMethod::legacy::demo(dp);
      homework::factoryMethod::problem::demo(dp);
      homework::factoryMethod::solution::demo(dp);
      break;
    case 4:
      homework::templateMethod::legacy::demo(dp);
      homework::templateMethod::problem::demo(dp);
      homework::templateMethod::solution::demo(dp);
      break;
    case 5:
      homework::observer::legacy::demo(dp);
      homework::observer::problem::demo(dp);
      homework::observer::solution::demo(dp);
      break;
    case 6:
      homework::decorator::legacy::demo(dp);
      homework::decorator::problem::demo(dp);
      homework::decorator::solution::demo(dp);
      break;
    case 7:
      homework::chainOfResponsibility::legacy::demo();
      homework::chainOfResponsibility::problem::demo();
      homework::chainOfResponsibility::solution::demo();
      break;
    case 8:
      homework::bridge::legacy::demo();
      homework::bridge::problem::demo();
      homework::bridge::solution::demo();
      break;
    case 9:
      homework::abstractFactory::legacy::demo();
      homework::abstractFactory::problem::demo();
      homework::abstractFactory::solution::demo();
      break;

    // Seam point - add next design pattern.

    default:
      printf("Unknown design pattern number %d.\n", dp);
      break;
  }

  printf("Done.\n");
}
