#include <list>
#include <map>
#include <iostream>

using namespace std;

#include "finalDesign.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace final_design::template_method;
using namespace final_design::abstract_factory;
using namespace final_design::factory_method;

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
// INJECTION MACHINE SETUP - CONVEYER BELT
//##########################################################################
TEST_CASE("Injection Machine setup - conveyer belt")
{
  SECTION("Conveyer Belt Criteria (7)")
  {
    ConveyerBelt* belt = ConveyerBelt::makeObject(1);

    REQUIRE(belt->name() == "Linear conveyer belt");
  }

  SECTION("Conveyer Belt Criteria (7)")
  {
    ConveyerBelt* belt = ConveyerBelt::makeObject(2);

    REQUIRE(belt->name() == "Y-Split conveyer belt");
  }
}

//##########################################################################
// INJECTION MACHINE SETUP - MOLD MATERIAL
//##########################################################################
TEST_CASE("Injection Machine setup - mold")
{
  SECTION("Mold Material (5)")
  {
    Mold* mold = Mold::makeObject(10000, 10000);

    REQUIRE(mold->name() == "Aluminum");
    REQUIRE(mold->legacy_name() == "aluminum");
    REQUIRE(mold->type() == Mold::MOLD_ALUMINUM);
    REQUIRE(mold->numCavities() == 1);
  }

  SECTION("Mold Material (5)")
  {
    Mold* mold = Mold::makeObject(1, 1);

    REQUIRE(mold->name() == "Aluminum");
    REQUIRE(mold->legacy_name() == "aluminum");
    REQUIRE(mold->type() == Mold::MOLD_ALUMINUM);
    REQUIRE(mold->numCavities() == 1);
  }

  SECTION("Mold Material (5)")
  {
    Mold* mold = Mold::makeObject(50000, 50000);

    REQUIRE(mold->name() == "Steel");
    REQUIRE(mold->legacy_name() == "steel");
    REQUIRE(mold->type() == Mold::MOLD_STEEL);
    REQUIRE(mold->numCavities() == 1);
  }

  SECTION("Mold Material (5)")
  {
    Mold* mold = Mold::makeObject(20000, 20000);

    REQUIRE(mold->name() == "Aluminum");
    REQUIRE(mold->legacy_name() == "aluminum");
    REQUIRE(mold->numCavities() == 2);
  }

  SECTION("Mold Material (5)")
  {
    Mold* mold = Mold::makeObject(10001, 10001);

    REQUIRE(mold->name() == "Aluminum");
    REQUIRE(mold->legacy_name() == "aluminum");
    REQUIRE(mold->numCavities() == 2);
  }
}

//##########################################################################
// INJECTION MACHINE SETUP - OUTPUT BIN (8)
//##########################################################################
TEST_CASE("Injection Machine setup - output bin")
{
  SECTION("Output Bin Criteria (8)")
  {
    OutputBin* output_bin = OutputBin::makeObject(10000);

    REQUIRE(output_bin->name() == "CardboardBox");
    REQUIRE(output_bin->type() == OutputBin::OUTPUT_BIN_CARDBOARD_BOX);
    REQUIRE(output_bin->capacity() == 10000);
  }

  SECTION("Output Bin Criteria (8)")
  {
    OutputBin* output_bin = OutputBin::makeObject(20000);

    REQUIRE(output_bin->name() == "ShellBox");
    REQUIRE(output_bin->type() == OutputBin::OUTPUT_BIN_SHELL_BOX);
    REQUIRE(output_bin->capacity() == 20000);
  }

  SECTION("Output Bin Criteria (8)")
  {
    OutputBin* output_bin = OutputBin::makeObject(50000);

    REQUIRE(output_bin->name() == "PallotBox");
    REQUIRE(output_bin->type() == OutputBin::OUTPUT_BIN_PALLOT_BOX);
    REQUIRE(output_bin->capacity() == 50000);
  }

  SECTION("Output Bin Criteria (8)")
  {
    OutputBin* output_bin = OutputBin::makeObject(9999); // one less than max

    REQUIRE(output_bin->name() == "CardboardBox");
    REQUIRE(output_bin->type() == OutputBin::OUTPUT_BIN_CARDBOARD_BOX);
    REQUIRE(output_bin->capacity() == 10000);
  }

  SECTION("Output Bin Criteria (8)")
  {
    OutputBin* output_bin = OutputBin::makeObject(19999); // one less than max

    REQUIRE(output_bin->name() == "ShellBox");
    REQUIRE(output_bin->type() == OutputBin::OUTPUT_BIN_SHELL_BOX);
    REQUIRE(output_bin->capacity() == 20000);
  }

  SECTION("Output Bin Criteria (8)")
  {
    OutputBin* output_bin = OutputBin::makeObject(49999); // one less than max

    REQUIRE(output_bin->name() == "PallotBox");
    REQUIRE(output_bin->type() == OutputBin::OUTPUT_BIN_PALLOT_BOX);
    REQUIRE(output_bin->capacity() == 50000);
  }

  SECTION("Output Bin Criteria (8)")
  {
    OutputBin* output_bin = OutputBin::makeObject(100000); // exceeds max

    REQUIRE(output_bin->name() == "PallotBox");
    REQUIRE(output_bin->type() == OutputBin::OUTPUT_BIN_PALLOT_BOX);
    REQUIRE(output_bin->capacity() == 50000);
  }
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
    auto order = Order(raw_order);
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
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.\n");
    REQUIRE(order.getSize() == 100);
  }

  SECTION("Default packager (3) - <Bulk>")
  {
    raw_order.erase("packager");

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown packager || defaulting to 'None'.\n");
    REQUIRE(order.getPackagerType() == final_design::Packager::PACKAGER_BULK);
  }

  SECTION("Default color (18) - <>")
  {
    raw_order.erase("color");

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.getColor() == Order::COLOR_NONE);
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
    auto order = Order(raw_order);
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
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.\n");
    REQUIRE(order.getSize() == 100);
  }

  SECTION("size (2) == 0 to <100>")
  {
    raw_order["size"] = "0";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>No size specified, defaulting to 100.\n");
    REQUIRE(order.getSize() == 100);
  }

  SECTION("Packager (3): unknown to <bulk>")
  {
    raw_order["packager"] = "bogus";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown packager |bogus| defaulting to 'None'.\n");
    REQUIRE(order.getPackagerType() == final_design::Packager::PACKAGER_BULK);
  }

  SECTION("Color (2): unknown to <>")
  {
    raw_order["color"] = "bogus";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown color |bogus| defaulting to ''.\n");
    REQUIRE(order.getColor() == Order::COLOR_NONE);
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
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_ABS);
  }

  SECTION("Plastic: Polypropylene")
  {
    raw_order["plastic"] = "Polypropylene";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_POLYPROPYLENE);
  }

  SECTION("Plastic: Polyethelene")
  {
    raw_order["plastic"] = "Polyethelene";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.plasticPtr_m->getPlasticType() ==
            final_design::Plastic::PLASTIC_POLYETHELENE);
  }

  SECTION("Plastic: PET")
  {
    raw_order["plastic"] = "PET";

    capture_on();
    auto order = Order(raw_order);
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
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.getSize() == 10000);
  }

  SECTION("Order size == 50000 (max)")
  {
    raw_order["size"] = "50000";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.getSize() == 50000);
  }

  SECTION("Order size > 50000")
  {
    raw_order["size"] = "100001";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "  <>Size exceeds mold lifetime |100001| "
                                     "defaulting to MediumOrder of 50000.\n");
    REQUIRE(order.getSize() == 50000);
  }

  ////////////////////////////////////////////////////////////////////////////
  // ORDER PACKAGER (3)
  ////////////////////////////////////////////////////////////////////////////

  SECTION("Packager: Bulk")
  {
    raw_order["packager"] = "Bulk";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.getPackagerType() == final_design::Packager::PACKAGER_BULK);
  }

  SECTION("Packager: ShrinkWrap")
  {
    raw_order["packager"] = "ShrinkWrap";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.getPackagerType() ==
            final_design::Packager::PACKAGER_SHRINK_WRAP);
  }

  SECTION("Packager: HardPack")
  {
    raw_order["packager"] = "HardPack";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(captured_stdout.str() == "");
    REQUIRE(order.getPackagerType() ==
            final_design::Packager::PACKAGER_HARD_PACK);
  }

  ////////////////////////////////////////////////////////////////////////////
  // ORDER COLOR (18)
  ////////////////////////////////////////////////////////////////////////////

  SECTION("Color: black")
  {
    raw_order["color"] = "black";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(order.getColor() == Order::COLOR_BLACK);
  }

  SECTION("Color: brown")
  {
    raw_order["color"] = "brown";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(order.getColor() == Order::COLOR_BROWN);
  }

  SECTION("Color: red")
  {
    raw_order["color"] = "red";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(order.getColor() == Order::COLOR_RED);
  }

  SECTION("Color: orange")
  {
    raw_order["color"] = "orange";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(order.getColor() == Order::COLOR_ORANGE);
  }

  SECTION("Color: yellow")
  {
    raw_order["color"] = "yellow";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(order.getColor() == Order::COLOR_YELLOW);
  }

  SECTION("Color: green")
  {
    raw_order["color"] = "green";

    capture_on();
    auto order = Order(raw_order);
    capture_off();

    REQUIRE(order.getColor() == Order::COLOR_GREEN);
  }
}

//##########################################################################
// INJECTION MOLDING MACHINE (4)
//##########################################################################
TEST_CASE("Injection Molding Machine Choice")
{
  SECTION("IJM_110")
  {
    IMM* imm = IMM::makeObject(10000);

    REQUIRE(imm->type() == IMM::IJM_110);
    REQUIRE(imm->maxBatchSize() == 10000);
    REQUIRE(imm->name() == "IJM_110");
    REQUIRE(imm->getMold().numCavities() == 1);
    REQUIRE(imm->getMold().type() == Mold::MOLD_ALUMINUM);

    delete imm;
  }

  SECTION("IJM_120")
  {
    IMM* imm = IMM::makeObject(20000);

    REQUIRE(imm->type() == IMM::IJM_120);
    REQUIRE(imm->maxBatchSize() == 20000);
    REQUIRE(imm->name() == "IJM_120");
    REQUIRE(imm->getMold().numCavities() == 2);
    REQUIRE(imm->getMold().type() == Mold::MOLD_ALUMINUM);

    delete imm;
  }

  SECTION("IJM_210")
  {
    IMM* imm = IMM::makeObject(50000);

    REQUIRE(imm->type() == IMM::IJM_210);
    REQUIRE(imm->maxBatchSize() == 50000);
    REQUIRE(imm->name() == "IJM_210");
    REQUIRE(imm->getMold().numCavities() == 1);
    REQUIRE(imm->getMold().type() == Mold::MOLD_STEEL);

    delete imm;
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

  SECTION("Null order - Order output")
  {
    capture_on();
    auto order = Order(raw_null_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown plastic || defaulting to 'ABS'.\n"
            "  <>No size specified, defaulting to 100.\n"
            "  <>Unknown packager || defaulting to 'None'.\n");
    REQUIRE(order.getPackagerType() == final_design::Packager::PACKAGER_BULK);
  }

  SECTION("Null order - ProcessOrder output")
  {
    capture_on();
    auto process_order = ProcessOrder(raw_null_order);
    capture_off();

    REQUIRE(captured_stdout.str() ==
            "  <>Unknown plastic || defaulting to 'ABS'.\n"
            "  <>No size specified, defaulting to 100.\n"
            "  <>Unknown packager || defaulting to 'None'.\n");
    REQUIRE(process_order.getOrder().getPackagerType() ==
            final_design::Packager::PACKAGER_BULK);
  }
}
