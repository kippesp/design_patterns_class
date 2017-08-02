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

//##########################################################################
// ORDER INPUT - FIELD DEFAULTS
//##########################################################################
TEST_CASE("Order defaults")
{
  const char* order_no_size[] = {
    "	orderNum	= 1",
    "	comment		= Separated defaults - check default behaviors.",
    "	plastic		= ABS",
    "	size		= 1000",
    "	packager	= Bulk",
    "	color		= black",
    "	endOfOrder",
  };

  map<string, string> raw_order = getCompleteOrder(order_no_size);

  SECTION("Default plastic (1) - <ABS>")
  {
    raw_order.erase("plastic");

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown plastic || defaulting to 'ABS'.\n");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_ABS);
  }

  SECTION("Default size (2) - <100>")
  {
    raw_order.erase("size");

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.\n");
    REQUIRE(order.size_m == 100);
  }

  SECTION("Default packager (3) - <Bulk>")
  {
    raw_order.erase("packager");

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown packager || defaulting to 'None'.\n");
    REQUIRE(order.packagerPtr_m->getPackagerType() ==
            final_design::Packager::PACKAGER_BULK);
  }

  SECTION("Default color (18) - <>")
  {
    raw_order.erase("color");

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.color_m == final_design::ProcessOrder::COLOR_NONE);
  }
}

//##########################################################################
// Order Input - Invalid Values
//##########################################################################
TEST_CASE("Order input - invalid values")
{
  const char* order_no_size[] = {
    "	orderNum	= 1",
    "	comment		= Separated defaults - check default behaviors.",
    "	plastic		= ABS",
    "	size		= 1000",
    "	packager	= Bulk",
    "	color		= black",
    "	endOfOrder",
  };

  map<string, string> raw_order = getCompleteOrder(order_no_size);

  SECTION("Plastic (1): unknown to <ABS>")
  {
    raw_order["plastic"] = "bogus";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown plastic |bogus| defaulting to 'ABS'.\n");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_ABS);
  }

  SECTION("size (2) == unknown to <100>")
  {
    raw_order["size"] = "";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.\n");
    REQUIRE(order.size_m == 100);
  }

  SECTION("size (2) == 0 to <100>")
  {
    raw_order["size"] = "0";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.\n");
    REQUIRE(order.size_m == 100);
  }

  SECTION("Packager (3): unknown to <bulk>")
  {
    raw_order["packager"] = "bogus";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown packager |bogus| defaulting to 'None'.\n");
    REQUIRE(order.packagerPtr_m->getPackagerType() ==
            final_design::Packager::PACKAGER_BULK);
  }

  SECTION("Color (2): unknown to <>")
  {
    raw_order["color"] = "bogus";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown color |bogus| defaulting to ''.\n");
    REQUIRE(order.color_m == final_design::ProcessOrder::COLOR_NONE);
  }
}

//##########################################################################
// ORDER INPUT - ALL FIELD OPTIONS
//##########################################################################
TEST_CASE("Order field options")
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

  SECTION("Plastic: ABS")
  {
    raw_order["plastic"] = "ABS";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_ABS);
  }

  SECTION("Plastic: Polypropylene")
  {
    raw_order["plastic"] = "Polypropylene";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_POLYPROPYLENE);
  }

  SECTION("Plastic: Polyethelene")
  {
    raw_order["plastic"] = "Polyethelene";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_POLYETHELENE);
  }

  SECTION("Plastic: PET")
  {
    raw_order["plastic"] = "PET";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_PET);
  }

  ////////////////////////////////////////////////////////////////////////////
  // ORDER SIZE (2)
  ////////////////////////////////////////////////////////////////////////////

  SECTION("Order size <= 50000")
  {
    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.size_m == 10000);
  }

  SECTION("Order size == 50000 (max)")
  {
    raw_order["size"] = "50000";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.size_m == 50000);
  }

  SECTION("Order size > 50000")
  {
    raw_order["size"] = "100001";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "  <>Size exceeds mold lifetime |100001| "
                                     "defaulting to MediumOrder of 50000.\n");
    REQUIRE(order.size_m == 50000);
  }

  ////////////////////////////////////////////////////////////////////////////
  // ORDER PACKAGER (3)
  ////////////////////////////////////////////////////////////////////////////

  SECTION("Packager: Bulk")
  {
    raw_order["packager"] = "Bulk";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.packagerPtr_m->getPackagerType() ==
            final_design::Packager::PACKAGER_BULK);
  }

  SECTION("Packager: ShrinkWrap")
  {
    raw_order["packager"] = "ShrinkWrap";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.packagerPtr_m->getPackagerType() ==
            final_design::Packager::PACKAGER_SHRINK_WRAP);
  }

  SECTION("Packager: HardPack")
  {
    raw_order["packager"] = "HardPack";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.packagerPtr_m->getPackagerType() ==
            final_design::Packager::PACKAGER_HARD_PACK);
  }

  ////////////////////////////////////////////////////////////////////////////
  // ORDER COLOR (18)
  ////////////////////////////////////////////////////////////////////////////

  SECTION("Color: black")
  {
    raw_order["color"] = "black";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(order.color_m == final_design::ProcessOrder::COLOR_BLACK);
  }

  SECTION("Color: brown")
  {
    raw_order["color"] = "brown";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(order.color_m == final_design::ProcessOrder::COLOR_BROWN);
  }

  SECTION("Color: red")
  {
    raw_order["color"] = "red";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(order.color_m == final_design::ProcessOrder::COLOR_RED);
  }

  SECTION("Color: orange")
  {
    raw_order["color"] = "orange";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(order.color_m == final_design::ProcessOrder::COLOR_ORANGE);
  }

  SECTION("Color: yellow")
  {
    raw_order["color"] = "yellow";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(order.color_m == final_design::ProcessOrder::COLOR_YELLOW);
  }

  SECTION("Color: green")
  {
    raw_order["color"] = "green";

    capture_on();
    auto order = final_design::ProcessOrder(raw_order);
    capture_off();

    REQUIRE(order.color_m == final_design::ProcessOrder::COLOR_GREEN);
  }
}

//##########################################################################
// NULL ORDER (DEFAULT OPERATIONS)
//##########################################################################
TEST_CASE("Full Orders")
{
  const char* null_order[] = {
    "	orderNum	= 1",
    "	comment		= Null order - check default behaviors.",
    "	endOfOrder",
  };

  map<string, string> raw_null_order = getCompleteOrder(null_order);

  SECTION("Null order output")
  {
    capture_on();
    auto order = final_design::ProcessOrder(raw_null_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown plastic || defaulting to 'ABS'.\n"
            "  <>No size specified, defaulting to 100.\n"
            "  <>Unknown packager || defaulting to 'None'.\n");
    REQUIRE(order.packagerPtr_m->getPackagerType() ==
            final_design::Packager::PACKAGER_BULK);
  }
}
