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

  const char** line = &lines[0];

  while (*line != NULL)
  {
    if (strstr(*line, "endOfOrder"))
    {
      return (order);
    }
    else
    {
      keyValue = final_design::parse(*line);
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

  ////////////////////////////////////////////////////////////////////////////
  // ORDER PLASTIC (1)
  ////////////////////////////////////////////////////////////////////////////

  SECTION("Plastic not specified - default ABS")
  {
    raw_order.erase("plastic");

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown plastic || defaulting to 'ABS'.\n");
    REQUIRE(order.plastic_m == final_design::Order::PLASTIC_ABS);
  }

  SECTION("Plastic: bogus (unknown)")
  {
    raw_order["plastic"] = "bogus";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown plastic |bogus| defaulting to 'ABS'.\n");
    REQUIRE(order.plastic_m == final_design::Order::PLASTIC_ABS);
  }

  SECTION("Plastic: ABS")
  {
    raw_order["plastic"] = "ABS";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plastic_m == final_design::Order::PLASTIC_ABS);
  }

  SECTION("Plastic: Polypropylene")
  {
    raw_order["plastic"] = "Polypropylene";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plastic_m == final_design::Order::PLASTIC_POLYPROPYLENE);
  }

  SECTION("Plastic: Polyethelene")
  {
    raw_order["plastic"] = "Polyethelene";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plastic_m == final_design::Order::PLASTIC_POLYETHELENE);
  }

  SECTION("Plastic: PET")
  {
    raw_order["plastic"] = "PET";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plastic_m == final_design::Order::PLASTIC_PET);
  }

  ////////////////////////////////////////////////////////////////////////////
  // ORDER SIZE (2)
  ////////////////////////////////////////////////////////////////////////////

  SECTION("Size not specified - default 100")
  {
    raw_order.erase("size");

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.\n");
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
            "  <>No size specified, defaulting to 100.\n");
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
                                     "defaulting to MediumOrder of 50000.\n");
    REQUIRE(order.size_m == 50000);
  }

  ////////////////////////////////////////////////////////////////////////////
  // ORDER PACKAGER (3)
  ////////////////////////////////////////////////////////////////////////////

  SECTION("Packager not specified - default to Bulk")
  {
    raw_order.erase("packager");

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown packager || defaulting to 'None'.\n");
    REQUIRE(order.packager_m == final_design::Order::PACKAGER_BULK);
  }

  SECTION("Packager: none (bulk)")
  {
    raw_order["packager"] = "Bulk";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.packager_m == final_design::Order::PACKAGER_BULK);
  }

  SECTION("Packager: bogus (unknown)")
  {
    raw_order["packager"] = "bogus";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown packager |bogus| defaulting to 'None'.\n");
    REQUIRE(order.packager_m == final_design::Order::PACKAGER_BULK);
  }

  SECTION("Packager: ShrinkWrap")
  {
    raw_order["packager"] = "ShrinkWrap";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.packager_m == final_design::Order::PACKAGER_SHRINK_WRAP);
  }

  SECTION("Packager: HardPack")
  {
    raw_order["packager"] = "HardPack";

    capture_on();
    auto order = final_design::Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.packager_m == final_design::Order::PACKAGER_HARD_PACK);
  }
}

TEST_CASE("Null Order", "[null_orders]")
{
  const char* null_order[] = {
    "	orderNum	= 1",
    "	comment		= Null order - check default behaviors.",
    "	endOfOrder",
  };

  map<string, string> raw_null_order = getCompleteOrder(null_order);

  SECTION("Full output")
  {
    capture_on();
    auto order = final_design::Order(raw_null_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown plastic || defaulting to 'ABS'.\n"
            "  <>No size specified, defaulting to 100.\n"
            "  <>Unknown packager || defaulting to 'None'.\n");
    REQUIRE(order.packager_m == final_design::Order::PACKAGER_BULK);
  }
}
