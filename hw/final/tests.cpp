#include <list>
#include <map>
#include <iostream>

using namespace std;

#include "finalDesign.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

stringstream captured_stdout;
streambuf* sbuf;

void capture_on()
{
  captured_stdout.str(std::string());
  sbuf = cout.rdbuf();
  cout.rdbuf(captured_stdout.rdbuf());
}

void capture_off()
{
  // output
  cout.rdbuf(sbuf);
}

TEST_CASE("This is a test", "something")
{

  final_design::legacy_classes::CleanABS c;
  final_design::legacy_classes::CleanPolys d;

  capture_on();
  c.clean();
  REQUIRE(captured_stdout.str() ==
          "    Clean ABS mold: soak in alcohol, rinse with water, dry.\n");
  capture_off();

  capture_on();
  d.prepForReuse();
  REQUIRE(captured_stdout.str() ==
          "    Clean Poly mold: rinse with acetone, dry.\n");
  capture_off();
}
