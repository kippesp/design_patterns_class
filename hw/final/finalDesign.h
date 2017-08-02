
/*
 * finalDesign.h
 *
 *  Created on: <MMDDCCYY>
 *      Author: <student name>
 */

#ifndef FINAL_FINAL_DESIGN_H_
#define FINAL_FINAL_DESIGN_H_

#include <cassert>
#include <cstring>
#include <stdlib.h>

namespace final_design
{

const bool on = true && DTORF_ENABLE; // Useful macro to turn dtor instrumentation on/off.
#define DTORF(x)                                                               \
  if (on)                                                                      \
  {                                                                            \
    cout << x;                                                                 \
  }

/////////////////////////////////////////////////////////////////////////////
// Can't change these.
namespace legacy_classes
{

int cycleTime_sec(string metal, int volume_cc)
{
  int heatCapacityAdjustment = 0;

  if (metal == "aluminum")
    heatCapacityAdjustment = -2;
  else if (metal == "steel")
    heatCapacityAdjustment = +5;

  return 20 + heatCapacityAdjustment + 0.1 * volume_cc;
}

const int setupAvg_min = 118;
const int teardownAvg_min = 54;
const float rejectRateLow_pcnt = 0.2;
const float rejectRateHigh_pcnt = 1.1;

class CleanABS
{
public:
  ~CleanABS() { DTORF("~legacy_classes::CleanABS "); }

  void clean()
  {
    cout << "    Clean ABS mold: soak in alcohol, rinse with water, dry.\n";
  }
};

class CleanPolys
{
public:
  ~CleanPolys() { DTORF("~legacy_classes::CleanPolys "); }

  void prepForReuse()
  {
    cout << "    Clean Poly mold: rinse with acetone, dry.\n";
  }
};

class PETCleanup
{
public:
  ~PETCleanup() { DTORF("~legacy_classes::PETCleanup "); }

  // Use only on stainless steel.
  void carbonize()
  {
    cout << "    Clean PET steel mold: heat to 895 C.\n";
  }

  // Use only on aluminum.
  void purify()
  {
    cout << "    Clean PET aluminum mold: rinse with soap and water, dry.\n";
  }
};

void defaulting(map<string, string>& order, const string& option,
                string def = "simulation")
{
  cout << "  <>Unknown " << option << " |";
  cout << order[option] << "|";
  order[option] = def;
  cout << " defaulting to '" << order[option] << "'.\n";
}
}

////////////////////////////////////////////////////////////////////////////
// RawOrder - Data structure
////////////////////////////////////////////////////////////////////////////

struct RawOrder
{
  RawOrder(const map<string, string>& raw_order)
    : raw_order_m(raw_order)
  {
  }

  map<string, string> getLegacyCopy() const { return raw_order_m; }

  bool hasField(const char* field) const
  {
    auto value = raw_order_m.find(field);

    return (value == raw_order_m.end()) ? false : true;
  }

  const string getfield(const char* field) const
  {
    if (hasField(field))
    {
      auto value = raw_order_m.find(field);
      return value->second;
    }
    else
    {
      return NULL;
    }
  }

private:
  const map<string, string> raw_order_m;
  RawOrder() = delete;
};

////////////////////////////////////////////////////////////////////////////
// ProcessOrder - Main processing class
////////////////////////////////////////////////////////////////////////////

struct ProcessOrder
{
  const uint32_t MAX_ORDER_SIZE;
  enum
  {
    PLASTIC_ABS,
    PLASTIC_POLYPROPYLENE,
    PLASTIC_POLYETHELENE,
    PLASTIC_PET,
  } plastic_m;
  uint32_t size_m;
  enum
  {
    PACKAGER_BULK,
    PACKAGER_SHRINK_WRAP,
    PACKAGER_HARD_PACK,
  } packager_m;
  enum
  {
    COLOR_NONE,
    COLOR_BLACK,
    COLOR_BROWN,
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_YELLOW,
    COLOR_GREEN,
  } color_m;

  ProcessOrder(const map<string, string>& raw_order)
    : MAX_ORDER_SIZE(50000)
    , plastic_m(PLASTIC_ABS)
    , size_m(0)
    , packager_m(PACKAGER_BULK)
    , color_m(COLOR_NONE)
  {
    RawOrder order(raw_order);

    auto plastic = raw_order.find("plastic");

    if (!order.hasField("plastic"))
    {
      auto order_copy = order.getLegacyCopy();
      legacy_classes::defaulting(order_copy, "plastic", "ABS");
      plastic_m = PLASTIC_ABS;
    }
    else if (plastic->second == "ABS")
    {
      plastic_m = PLASTIC_ABS;
    }
    else if (plastic->second == "Polypropylene")
    {
      plastic_m = PLASTIC_POLYPROPYLENE;
    }
    else if (plastic->second == "Polyethelene")
    {
      plastic_m = PLASTIC_POLYETHELENE;
    }
    else if (plastic->second == "PET")
    {
      plastic_m = PLASTIC_PET;
    }
    else
    {
      map<string, string> order_copy = raw_order;
      legacy_classes::defaulting(order_copy, "plastic", "ABS");
      plastic_m = PLASTIC_ABS;
    }

    auto size = raw_order.find("size");

    if (size == raw_order.end())
    {
      cout << "  <>No size specified, defaulting to 100.\n";
      size_m = 100;
    }
    else
    {
      size_m = atoi(size->second.c_str());
    }

    if (size_m > MAX_ORDER_SIZE)
    {
      cout << "  <>Size exceeds mold lifetime |" << size_m
           << "| defaulting to MediumOrder of " << MAX_ORDER_SIZE << ".\n";

      size_m = MAX_ORDER_SIZE;
    }

    if (size_m == 0)
    {
      cout << "  <>No size specified, defaulting to 100.\n";
      size_m = 100;
    }

    auto packager = raw_order.find("packager");

    if (packager == raw_order.end())
    {
      map<string, string> order_copy = raw_order;
      legacy_classes::defaulting(order_copy, "packager", "None");
      packager_m = PACKAGER_BULK;
    }
    else if (packager->second == "ShrinkWrap")
    {
      packager_m = PACKAGER_SHRINK_WRAP;
    }
    else if (packager->second == "HardPack")
    {
      packager_m = PACKAGER_HARD_PACK;
    }
    else if (packager->second == "Bulk")
    {
      packager_m = PACKAGER_BULK;
    }
    else
    {
      map<string, string> order_copy = raw_order;
      legacy_classes::defaulting(order_copy, "packager", "None");
      packager_m = PACKAGER_BULK;
    }

    auto color = raw_order.find("color");

    if (color == raw_order.end())
    {
      map<string, string> order_copy = raw_order;
      color_m = COLOR_NONE;
    }
    else if (color->second == "black")
    {
      color_m = COLOR_BLACK;
    }
    else if (color->second == "brown")
    {
      color_m = COLOR_BROWN;
    }
    else if (color->second == "red")
    {
      color_m = COLOR_RED;
    }
    else if (color->second == "orange")
    {
      color_m = COLOR_ORANGE;
    }
    else if (color->second == "yellow")
    {
      color_m = COLOR_YELLOW;
    }
    else if (color->second == "green")
    {
      color_m = COLOR_GREEN;
    }
    else
    {
      map<string, string> order_copy = raw_order;
      legacy_classes::defaulting(order_copy, "color", "");
      color_m = COLOR_NONE;
    }
  }

private:
  ProcessOrder() = delete;
};

// DP 2.
namespace adapter
{

// Seam point - add another interface.
}

// DP 1.
namespace strategy
{

// Seam point - add another algorithm.
}

// DP 5.
namespace observer
{

// Seam point - add another listener.
}

// DP 9.
namespace abstract_factory
{

// Seam point - add another type 1.
// Seam point - add another type 2.
// Seam point - add another type 3.
// Seam point - add another ...
// Seam point - add another type N.
// Seam point - add another family.
}

// DP 8.
namespace bridge
{

// Seam Point - add another implementation.
// Seam Point - add another abstraction.
}

// DP 7.
namespace chain_of_resp
{

// Seam points - add another responder.
}

// DP 6.
namespace decorator
{

// Seam point - add another option.
}

// DP 4.
namespace factory_method
{

// Seam point - add another class.
}

// DP 3.
namespace template_method
{

// Seam point - add another polymorphic step.
// Seam point - add another constant step.
// Seam point - convert a constant step into a polymorphic step.
}

void process(map<string, string>& /* order */)
{
  // Fill in the namespaces above with your design pattern class hierarchies.
  // Call your order processing class from here <myProcess>->run(order);
}

pair<string, string> parse(string line)
{
  char key[83];
  char val[83] = { 0 };

  sscanf(line.c_str(), "%s", key);

  const char* equalSign = strchr(line.c_str(), '=');
  string value = "";
  if (equalSign)
  { // tags = sam i am
    const char* nextToken = equalSign += 2;
    while (nextToken)
    {
      sscanf(nextToken, "%s", val);
      value += val;
      nextToken = strchr(nextToken + 1, ' ');
      value += " ";
    }
    value.erase(value.length() - 1, 1);
  }

  return make_pair(key, value);
}

map<string, string> getCompleteOrder(FILE* orderFilePtr)
{
  map<string, string> order;
  char line[80 + 3];
  pair<string, string> keyValue;

  while (fgets(line, 80, orderFilePtr))
  {
    cout << line;
    if (strstr(line, "endOfOrder"))
    {
      return (order);
    }
    else
    {
      keyValue = parse(line);
      string key = keyValue.first;
      if (strchr(key.c_str(), ':')) // Skip left justified order number.
        continue;
      string value = keyValue.second;
      order[key] = value;
    }
  }

  return order;
}

void demo(const string& orderFile)
{
  cout << "<<< final design >>>\n";

  FILE* orderFilePtr = fopen(orderFile.c_str(), "r");

  for (;;)
  { // Get and process each order.
    map<string, string> order = getCompleteOrder(orderFilePtr);
    if (order.size() == 0)
      break;
    process(order);
  }
}

} // final_design

#endif /* FINAL_FINAL_DESIGN_H_ */
