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

map<string, string> getCompleteOrder(const char* lines[])
{
  map<string, string> order;
  pair<string, string> keyValue;

  const char* line = lines[0];

  while (line != NULL)
  {
    if (strstr(line, "endOfOrder"))
    {
      return (order);
    }
    else
    {
      keyValue = final_design::parse(line);
      string key = keyValue.first;
      if (strchr(key.c_str(), ':')) // Skip left justified order number.
      {
        line++;
        continue;
      }
      string value = keyValue.second;
      order[key] = value;
    }

    line++;
  }

  return order;
}

TEST_CASE("Order defaults", "[orders]")
{
  const char* order_no_size[] = {
    "	orderNum	= 2",
    "	comment		= Example order - one of everything.",
    "	size		= 10000",
    "	mold		= duck",
    "	color		= red",
    "	plastic		= ABS",
    "	moldLoc		= inventory",
    "	tags		= ModelNumber",
    "	UVInhibiter	= 2",
    "	packager	= Bulk",
    "	endOfOrder",
  };

  map<string, string> raw_order = getCompleteOrder(order_no_size);

  SECTION("Default size")
  {
    raw_order.erase("size");

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.");
    REQUIRE(order.size_m == 100);
  }

  SECTION("Order size <= 50000")
  {
    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.size_m == 10000);
  }

  SECTION("Order size == 0")
  {
    raw_order["size"] = "0";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.");
    REQUIRE(order.size_m == 100);
  }

  SECTION("Order size == 50000 (max)")
  {
    raw_order["size"] = "50000";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.size_m == 50000);
  }

  SECTION("Order size > 50000")
  {
    raw_order["size"] = "100001";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "  <>Size exceeds mold lifetime |100001| "
                                     "defaulting to MediumOrder of 50000.");
    REQUIRE(order.size_m == 50000);
  }
}
