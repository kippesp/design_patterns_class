
/*
 * finalDesign.h
 *
 *  Created on: 08012017
 *      Author: Paul M. Kippes <paul.m.kippes@intel.com>
 */

#ifndef FINAL_FINAL_DESIGN_H_
#define FINAL_FINAL_DESIGN_H_

#include <cassert>
#include <cstring>
#include <stdlib.h>

const uint32_t MAX_ORDER_SIZE_PILOT = 10000;
const uint32_t MAX_ORDER_SIZE_SMALL = 20000;
const uint32_t MAX_ORDER_SIZE_MEDIUM = 50000;

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
  ~RawOrder() { DTORF(" ~RawOrder\n"); }

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

  const string getValue(const char* field) const
  {
    if (hasField(field))
    {
      auto value = raw_order_m.find(field);
      return value->second;
    }
    else
    {
      return "";
    }
  }

private:
  const map<string, string> raw_order_m;
  RawOrder() = delete;
};

////////////////////////////////////////////////////////////////////////////
// Plastic (1)
////////////////////////////////////////////////////////////////////////////
struct Plastic
{
  typedef enum {
    PLASTIC_ABS,
    PLASTIC_POLYPROPYLENE,
    PLASTIC_POLYETHELENE,
    PLASTIC_PET,
  } plastic_type_t;

  virtual ~Plastic()
  {
    string inst = " ~Plastic\n";
    DTORF(inst);
  }

  Plastic(const RawOrder& order)
  {
    auto order_copy = order.getLegacyCopy();

    if (!order.hasField("plastic"))
    {
      legacy_classes::defaulting(order_copy, "plastic", "ABS");
      type_m = PLASTIC_ABS;
      return;
    }

    auto plastic = order.getValue("plastic");

    if (plastic == "ABS")
    {
      type_m = PLASTIC_ABS;
    }
    else if (plastic == "Polypropylene")
    {
      type_m = PLASTIC_POLYPROPYLENE;
    }
    else if (plastic == "Polyethelene")
    {
      type_m = PLASTIC_POLYETHELENE;
    }
    else if (plastic == "PET")
    {
      type_m = PLASTIC_PET;
    }
    else
    {
      legacy_classes::defaulting(order_copy, "plastic", "ABS");
      type_m = PLASTIC_ABS;
    }
  }

  plastic_type_t getPlasticType() const { return type_m; }

protected:
  plastic_type_t type_m;
  Plastic() = delete;
};

////////////////////////////////////////////////////////////////////////////
// Packager (3)
////////////////////////////////////////////////////////////////////////////
struct Packager
{
  typedef enum {
    PACKAGER_BULK,
    PACKAGER_SHRINK_WRAP,
    PACKAGER_HARD_PACK,
  } packager_type_t;

  virtual ~Packager()
  {
    string inst = " ~Packager\n";
    DTORF(inst);
  }

  Packager(const RawOrder& order)
  {
    auto order_copy = order.getLegacyCopy();

    if (!order.hasField("packager"))
    {
      legacy_classes::defaulting(order_copy, "packager", "None");
      type_m = PACKAGER_BULK;
      return;
    }

    auto packager = order.getValue("packager");

    if (packager == "ShrinkWrap")
    {
      type_m = PACKAGER_SHRINK_WRAP;
      name_m = "ShrinkWrap";
    }
    else if (packager == "HardPack")
    {
      type_m = PACKAGER_HARD_PACK;
      name_m = "HardPack";
    }
    else if (packager == "Bulk")
    {
      type_m = PACKAGER_BULK;
      name_m = "Bulk";
    }
    else
    {
      legacy_classes::defaulting(order_copy, "packager", "None");
      type_m = PACKAGER_BULK;
    }
  }

  packager_type_t type() const { return type_m; }
  const string& name() const { return name_m; }

protected:
  packager_type_t type_m;
  string name_m;
  Packager() = delete;
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

//##########################################################################
// Factory Method Patterns
//##########################################################################

// DP 4.
namespace factory_method
{

////////////////////////////////////////////////////////////////////////////
// FM - Conveyer Belt Family (7)
////////////////////////////////////////////////////////////////////////////

struct ConveyerBelt
{
  virtual ~ConveyerBelt()
  {
    string inst = " ~ConveyerBelt\n";
    DTORF(inst);
  }

  const string& name() const { return name_m; }

  static ConveyerBelt* makeObject(uint32_t numCavities);

protected:
  ConveyerBelt(const string name)
    : name_m(name)
  {
  }

private:
  string name_m;
};

struct LinearBelt : public ConveyerBelt
{
  virtual ~LinearBelt()
  {
    string inst = " ~LinearBelt";
    DTORF(inst);
  }

  LinearBelt()
    : ConveyerBelt("Linear conveyer belt")
  {
  }
};

struct YSplitBelt : public ConveyerBelt
{
  virtual ~YSplitBelt()
  {
    string inst = " ~YSplitBelt";
    DTORF(inst);
  }

  YSplitBelt()
    : ConveyerBelt("Y-Split conveyer belt")
  {
  }
};

ConveyerBelt* ConveyerBelt::makeObject(uint32_t numCavities)
{
  if (numCavities == 1)
  {
    return new LinearBelt();
  }
  else if (numCavities == 2)
  {
    return new YSplitBelt();
  }
  else
  {
    assert(false);
  }
}

////////////////////////////////////////////////////////////////////////////
// FM - Mold Family (5)
////////////////////////////////////////////////////////////////////////////

struct Mold
{
  typedef enum { MOLD_ALUMINUM, MOLD_STEEL } mold_type_t;

  virtual ~Mold()
  {
    string inst = " ~Mold";
    DTORF(inst);
  }

  const string& name() const { return name_m; }
  const string& legacy_name() const { return legacy_name_m; }
  mold_type_t type() const { return mold_type_m; }
  uint32_t numCavities() const { return num_cavities_m; }
  uint32_t getMaxRunSize() const { return max_run_size_m; }

  static Mold* makeObject(uint32_t max_run_size);

protected:
  Mold(const string name, const string legacy_name, mold_type_t mold_type,
       uint32_t num_cavities, uint32_t max_run_size)
    : name_m(name)
    , legacy_name_m(legacy_name)
    , mold_type_m(mold_type)
    , num_cavities_m(num_cavities)
    , max_run_size_m(max_run_size)
  {
  }

private:
  const string name_m;
  const string legacy_name_m;
  const mold_type_t mold_type_m;
  const uint32_t num_cavities_m;
  const uint32_t max_run_size_m;
};

struct Aluminum : public Mold
{
  virtual ~Aluminum()
  {
    string inst = " ~Aluminum";
    DTORF(inst);
  }

  Aluminum(uint32_t num_cavities, uint32_t max_run_size)
    : Mold("Aluminum", "aluminum", MOLD_ALUMINUM, num_cavities, max_run_size)
  {
  }
};

struct StainlessSteel : public Mold
{
  virtual ~StainlessSteel()
  {
    string inst = " ~Steel";
    DTORF(inst);
  }

  StainlessSteel(uint32_t num_cavities, uint32_t max_run_size)
    : Mold("Steel", "steel", MOLD_STEEL, num_cavities, max_run_size)
  {
  }
};

Mold* Mold::makeObject(uint32_t max_run_size)
{
  if (max_run_size <= MAX_ORDER_SIZE_PILOT)
  {
    return new Aluminum(1 /* cavity */, MAX_ORDER_SIZE_PILOT);
  }
  else if (max_run_size <= MAX_ORDER_SIZE_SMALL)
  {
    return new Aluminum(2 /* cavity */, MAX_ORDER_SIZE_SMALL);
  }
  else if (max_run_size <= MAX_ORDER_SIZE_MEDIUM)
  {
    return new StainlessSteel(1 /* cavity */, MAX_ORDER_SIZE_MEDIUM);
  }
  else
  {
    assert(false);
  }
}

////////////////////////////////////////////////////////////////////////////
// FM - OutputBin (8)
////////////////////////////////////////////////////////////////////////////
struct OutputBin
{
  typedef enum {
    OUTPUT_BIN_CARDBOARD_BOX,
    OUTPUT_BIN_SHELL_BOX,
    OUTPUT_BIN_PALLOT_BOX,
  } output_bin_t;

  virtual ~OutputBin()
  {
    string inst = " ~OutputBin\n";
    DTORF(inst);
  }

  const string& name() const { return name_m; }

  output_bin_t type() const { return type_m; }

  uint32_t maxCapacity() const { return max_capacity_m; }

  // bool add_num_items(uint32_t num_items_to_add) {}

  static OutputBin* makeObject(uint32_t order_size);

protected:
  OutputBin(const string& name, output_bin_t output_bin_type, uint32_t max_capacity)
    : name_m(name)
    , type_m(output_bin_type)
    , max_capacity_m(max_capacity)
  {
  }

private:
  const string name_m;
  const output_bin_t type_m;
  const uint32_t max_capacity_m;
};

struct CardboardBox : public OutputBin
{
  virtual ~CardboardBox()
  {
    string inst = " ~CardboardBox";
    DTORF(inst);
  }

  CardboardBox(uint32_t max_capacity)
    : OutputBin("CardboardBox", OUTPUT_BIN_CARDBOARD_BOX, max_capacity)
  {
  }
};

struct ShellBox : public OutputBin
{
  virtual ~ShellBox()
  {
    string inst = " ~ShellBox";
    DTORF(inst);
  }

  ShellBox(uint32_t max_capacity)
    : OutputBin("ShellBox", OUTPUT_BIN_SHELL_BOX, max_capacity)
  {
  }
};

struct PallotBox : public OutputBin
{
  virtual ~PallotBox()
  {
    string inst = " ~PallotBox";
    DTORF(inst);
  }

  PallotBox(uint32_t max_capacity)
    : OutputBin("PallotBox", OUTPUT_BIN_PALLOT_BOX, max_capacity)
  {
  }
};

OutputBin* OutputBin::makeObject(uint32_t order_size)
{
  if (order_size <= MAX_ORDER_SIZE_PILOT)
  {
    return new CardboardBox(MAX_ORDER_SIZE_PILOT);
  }
  else if (order_size <= MAX_ORDER_SIZE_SMALL)
  {
    return new ShellBox(MAX_ORDER_SIZE_SMALL);
  }
  else if (order_size <= MAX_ORDER_SIZE_MEDIUM)
  {
    return new PallotBox(MAX_ORDER_SIZE_MEDIUM);
  }
  else
  {
    return new PallotBox(MAX_ORDER_SIZE_MEDIUM);
  }
}

// Seam point - add another class.
}

// DP 9.
namespace abstract_factory
{

////////////////////////////////////////////////////////////////////////////
// AF - INJECTION MOLDING MACHINE (4)
////////////////////////////////////////////////////////////////////////////
struct IMM
{
  typedef enum {
    IJM_110,
    IJM_120,
    IJM_210,
  } ijm_type_t;

  virtual ~IMM()
  {
    delete &mold_m;

    string inst = " ~IMM\n";
    DTORF(inst);
  }

  IMM(ijm_type_t type, const string& name, uint32_t order_size,
      const factory_method::Mold& mold)
    : type_m(type)
    , name_m(name)
    , order_size_m(order_size)
    , mold_m(mold)
  {
  }

  const string& name() const { return name_m; }

  ijm_type_t type() const { return type_m; }

  const factory_method::Mold& getMold() const { return mold_m; }

  uint32_t maxBatchSize() const { return order_size_m; }

  static IMM* makeObject(uint32_t order_size);

protected:
  IMM() = delete;

  const ijm_type_t type_m;
  const string name_m;
  const uint32_t order_size_m;
  const factory_method::Mold& mold_m;
};

struct IJM110 : public IMM
{
  virtual ~IJM110()
  {
    string inst = " ~IJM110";
    DTORF(inst);
  }

  IJM110(const factory_method::Mold& mold, uint32_t order_size)
    : IMM(IJM_110, "IJM_110", order_size, mold)
  {
  }
};

struct IJM120 : public IMM
{
  virtual ~IJM120()
  {
    string inst = " ~IJM120";
    DTORF(inst);
  }

  IJM120(const factory_method::Mold& mold, uint32_t order_size)
    : IMM(IJM_120, "IJM_120", order_size, mold)
  {
  }
};

struct IJM210 : public IMM
{
  virtual ~IJM210()
  {
    string inst = " ~IJM210";
    DTORF(inst);
  }

  IJM210(const factory_method::Mold& mold, uint32_t order_size)
    : IMM(IJM_210, "IJM_210", order_size, mold)
  {
  }
};

IMM* IMM::makeObject(uint32_t order_size)
{
  if (order_size <= MAX_ORDER_SIZE_PILOT)
  {
    auto mold_ptr = factory_method::Mold::makeObject(MAX_ORDER_SIZE_PILOT);

    return new IJM110(*mold_ptr, order_size);
  }
  else if (order_size <= MAX_ORDER_SIZE_SMALL)
  {
    auto mold_ptr = factory_method::Mold::makeObject(MAX_ORDER_SIZE_SMALL);

    return new IJM120(*mold_ptr, order_size);
  }
  else if (order_size <= MAX_ORDER_SIZE_MEDIUM)
  {
    auto mold_ptr = factory_method::Mold::makeObject(MAX_ORDER_SIZE_MEDIUM);

    return new IJM210(*mold_ptr, order_size);
  }
  else
  {
    assert(false);
  }
}

////////////////////////////////////////////////////////////////////////////
// AF - INJECTION LINE (9)
////////////////////////////////////////////////////////////////////////////

struct InjectionLine
{
  virtual ~InjectionLine()
  {
    delete &conveyer_belt_m;
    delete &output_bin_m;
    delete &imm_m;

    string inst = " ~InjectionLine\n";
    DTORF(inst);
  }

  InjectionLine(const IMM& imm, const Packager& packager,
                const factory_method::OutputBin& output_bin,
                const factory_method::ConveyerBelt& conveyer_belt,
                uint32_t order_size)
    : imm_m(imm)
    , packager_m(packager)
    , output_bin_m(output_bin)
    , conveyer_belt_m(conveyer_belt)
    , order_size_m(order_size)
  {
  }

  uint32_t getMaxRunSize() const { return imm_m.getMold().getMaxRunSize(); }
  uint32_t getOrderSize() const { return order_size_m; }
  const string& getImmName() const { return imm_m.name(); }
  const string getMoldDescription() const
  {
    return string("") + imm_m.getMold().name() + "(" +
           to_string(imm_m.getMold().numCavities()) + ")";
  }
  Packager::packager_type_t getPackagerType() const
  {
    return packager_m.type();
  }

  const string getBeltConfiguration() const { return conveyer_belt_m.name(); }
  const string getOutputBinName() const { return output_bin_m.name(); }

  void setup() const
  {
    cout << "  Setup injection line for " << getOrderSize() << " order:\n";
    cout << "    " << getImmName() << " - " << getMoldDescription() << " - "
         << getBeltConfiguration() << " - " << getOutputBinName() << ".\n";
  }

  static InjectionLine* makeObject(uint32_t order_size,
                                   const Packager& packager);

private:
  const IMM& imm_m;
  const Packager& packager_m;
  const factory_method::OutputBin& output_bin_m;
  const factory_method::ConveyerBelt& conveyer_belt_m;
  const uint32_t order_size_m;
};

InjectionLine* InjectionLine::makeObject(uint32_t order_size,
                                         const Packager& packager)
{
  auto imm_ptr = IMM::makeObject(order_size);
  auto output_bin_ptr = factory_method::OutputBin::makeObject(order_size);
  auto conveyer_belt_ptr =
    factory_method::ConveyerBelt::makeObject(imm_ptr->getMold().numCavities());

  return new InjectionLine(*imm_ptr, packager, *output_bin_ptr,
                           *conveyer_belt_ptr, order_size);
}

// Seam point - add another type 1.
// Seam point - add another type 2.
// Seam point - add another type 3.
// Seam point - add another ...
// Seam point - add another type N.
// Seam point - add another family.
}

// DP 3.
namespace template_method
{
////////////////////////////////////////////////////////////////////////////
// TM - Order
////////////////////////////////////////////////////////////////////////////
struct Order
{
  typedef enum {
    COLOR_NONE,
    COLOR_BLACK,
    COLOR_BROWN,
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_YELLOW,
    COLOR_GREEN,
  } color_t;

  virtual ~Order()
  {
    delete packagerPtr_m;
    delete plasticPtr_m;

    string inst = " ~Order";
    DTORF(inst);
  }

  Order(const RawOrder& raw_order)
    : MAX_ORDER_SIZE(MAX_ORDER_SIZE_MEDIUM)
    , plasticPtr_m(NULL)
    , size_m(0)
    , color_m(COLOR_NONE)
    , raw_order_m(raw_order)
    , packagerPtr_m(NULL)
  {
    // PLASTIC
    plasticPtr_m = new Plastic(raw_order_m);

    // SIZE
    if (!raw_order_m.hasField("size"))
    {
      cout << "  <>No size specified, defaulting to 100.\n";
      size_m = 100;
    }
    else
    {
      auto sizeStr = raw_order_m.getValue("size");

      size_m = atoi(sizeStr.c_str());
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

    // PACKAGER
    packagerPtr_m = new Packager(raw_order_m);

    // COLOR
    auto color = raw_order.getValue("color");

    if (!raw_order_m.hasField("color"))
    {
      color_m = COLOR_NONE;
    }
    else if (color == "black")
    {
      color_m = COLOR_BLACK;
    }
    else if (color == "brown")
    {
      color_m = COLOR_BROWN;
    }
    else if (color == "red")
    {
      color_m = COLOR_RED;
    }
    else if (color == "orange")
    {
      color_m = COLOR_ORANGE;
    }
    else if (color == "yellow")
    {
      color_m = COLOR_YELLOW;
    }
    else if (color == "green")
    {
      color_m = COLOR_GREEN;
    }
    else
    {
      map<string, string> legacy_order_copy = raw_order_m.getLegacyCopy();
      legacy_classes::defaulting(legacy_order_copy, "color", "");
      color_m = COLOR_NONE;
    }
  }

  uint32_t getSize() const { return size_m; }

  color_t getColor() const { return color_m; }

  Packager::packager_type_t getPackagerType() const
  {
    return packagerPtr_m->type();
  }

  const Packager& getPackager() const { return *packagerPtr_m; }

  const string& getPackagerName() const { return packagerPtr_m->name(); }

private:
  Order() = delete;

  const uint32_t MAX_ORDER_SIZE;

public:
  const Plastic* plasticPtr_m;

protected:
  uint32_t size_m;
  color_t color_m;
  RawOrder raw_order_m;
  Packager* packagerPtr_m;
};

////////////////////////////////////////////////////////////////////////////
// TM - ProcessOrder - Main processing class
////////////////////////////////////////////////////////////////////////////
struct ProcessOrder
{
  ProcessOrder(const map<string, string>& raw_order)
    : order_m(Order(RawOrder(raw_order)))
  {
  }

  virtual ~ProcessOrder()
  {
    string inst = " ~ProcessOrder\n";
    DTORF(inst);
  }

  const Order& getOrder() const { return order_m; }

  void run()
  {
    auto packager = order_m.getPackager();
    auto injection_line_ptr = abstract_factory::InjectionLine::makeObject(
      order_m.getSize(), order_m.getPackager());
    injection_line_ptr->setup();

    delete injection_line_ptr;
  }

private:
  ProcessOrder() = delete;

  const Order order_m;
};

// Seam point - add another polymorphic step.
// Seam point - add another constant step.
// Seam point - convert a constant step into a polymorphic step.
}

void process(map<string, string>& order)
{
  // Fill in the namespaces above with your design pattern class hierarchies.
  // Call your order processing class from here <myProcess>->run(order);
  auto process_order = template_method::ProcessOrder(order);

  process_order.run();
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

  fclose(orderFilePtr);
}

} // final_design

#endif /* FINAL_FINAL_DESIGN_H_ */
