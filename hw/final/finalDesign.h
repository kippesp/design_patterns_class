
/*
 * finalDesign.h
 *
 *  Created on: <MMDDCCYY>
 *      Author: <student name>
 */

#ifndef FINAL_FINAL_DESIGN_H_
#define FINAL_FINAL_DESIGN_H_

#include <cassert>

namespace final_design
{

const bool on = true; // Useful macro to turn dtor instrumentation on/off.
#define DTORF(x)                                                               \
  if (on)                                                                      \
  {                                                                            \
    cout << x;                                                                 \
  }

namespace legacy_classes
{ // Can't change these.

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
  void carbonize()
  { // Use only on stainless steel.
    cout << "    Clean PET steel mold: heat to 895 C.\n";
  }
  void purify()
  { // Use only on aluminum.
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

namespace adapter
{ // DP 2.

// Seam point - add another interface.
}

namespace strategy
{ // DP 1.

// Seam point - add another algorithm.
}

namespace observer
{ // DP 5.

// Seam point - add another listener.
}

namespace abstract_factory
{ // DP 9.

// Seam point - add another type 1.
// Seam point - add another type 2.
// Seam point - add another type 3.
// Seam point - add another ...
// Seam point - add another type N.
// Seam point - add another family.
}

namespace bridge
{ // DP 8.

// Seam Point - add another implementation.
// Seam Point - add another abstraction.
}

namespace chain_of_resp
{ // DP 7.

// Seam points - add another responder.
}

namespace decorator
{ // DP 6.

// Seam point - add another option.
}

namespace factory_method
{ // DP 4.

// Seam point - add another class.
}

namespace template_method
{ // DP 3.

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
  assert(orderFilePtr != NULL);

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
