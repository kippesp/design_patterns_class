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
    "	mold		= duck",
    "	color		= red",
    "	plastic		= ABS",
    "	moldLoc		= inventory",
    "	tags		= ModelNumber",
    "	UVInhibiter	= 2",
    "	packager	= Bulk",
    "	endOfOrder",
  };

  map<string, string> o = getCompleteOrder(order_no_size);

  capture_on();
  auto order = final_design::Order(o);
  capture_off();

  REQUIRE(captured_stdout.str() == "<>No size specified, defaulting to 100.");
  REQUIRE(order.size_m == 100);
}
