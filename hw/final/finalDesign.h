
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
