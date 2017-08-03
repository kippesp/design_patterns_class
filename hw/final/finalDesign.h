
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
  ~RawOrder() { DTORF("~RawOrder\n"); }

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
    }
    else if (packager == "HardPack")
    {
      type_m = PACKAGER_HARD_PACK;
    }
    else if (packager == "Bulk")
    {
      type_m = PACKAGER_BULK;
    }
    else
    {
      legacy_classes::defaulting(order_copy, "packager", "None");
      type_m = PACKAGER_BULK;
    }
  }

  packager_type_t getPackagerType() const { return type_m; }

protected:
  packager_type_t type_m;
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

  const string& name() { return name_m; }

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
    string inst = " ~Mold\n";
    DTORF(inst);
  }

  const string& name() const { return name_m; }
  const string& legacy_name() const { return legacy_name_m; }
  mold_type_t type() const { return mold_type_m; }
  uint32_t numCavities() const { return num_cavities_m; }

  static Mold* makeObject(uint32_t batchSize, uint32_t orderSize);

protected:
  Mold(const string name, const string legacy_name, mold_type_t mold_type,
       uint32_t num_cavities)
    : name_m(name)
    , legacy_name_m(legacy_name)
    , mold_type_m(mold_type)
    , num_cavities_m(num_cavities)
  {
  }

private:
  string name_m;
  string legacy_name_m;
  mold_type_t mold_type_m;
  uint32_t num_cavities_m;
};

struct Aluminum : public Mold
{
  virtual ~Aluminum()
  {
    string inst = " ~Aluminum";
    DTORF(inst);
  }

  Aluminum(uint32_t num_cavities)
    : Mold("Aluminum", "aluminum", MOLD_ALUMINUM, num_cavities)
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

  StainlessSteel(uint32_t num_cavities)
    : Mold("Steel", "steel", MOLD_STEEL, num_cavities)
  {
  }
};

Mold* Mold::makeObject(uint32_t batchSize, uint32_t orderSize)
{
  // batchSize always is <= orderSize since orderSize can not be greater than
  // 50000.
  assert(batchSize == orderSize);

  if (batchSize <= 10000)
  {
    return new Aluminum(1);
  }
  else if (batchSize <= 20000)
  {
    return new Aluminum(2);
  }
  else if (batchSize <= 50000)
  {
    return new StainlessSteel(1);
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

  uint32_t capacity() const { return capacity_m; }

  // bool add_num_items(uint32_t num_items_to_add) {}

  static OutputBin* makeObject(uint32_t orderSize);

protected:
  OutputBin(const string& name, output_bin_t output_bin_type, uint32_t capacity)
    : name_m(name)
    , type_m(output_bin_type)
    , capacity_m(capacity)
  {
  }

private:
  const string name_m;
  const output_bin_t type_m;
  const uint32_t capacity_m;
};

struct CardboardBox : public OutputBin
{
  virtual ~CardboardBox()
  {
    string inst = " ~CardboardBox";
    DTORF(inst);
  }

  CardboardBox()
    : OutputBin("CardboardBox", OUTPUT_BIN_CARDBOARD_BOX, 10000)
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

  ShellBox()
    : OutputBin("ShellBox", OUTPUT_BIN_SHELL_BOX, 20000)
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

  PallotBox()
    : OutputBin("PallotBox", OUTPUT_BIN_PALLOT_BOX, 50000)
  {
  }
};

OutputBin* OutputBin::makeObject(uint32_t orderSize)
{
  if (orderSize <= 10000)
  {
    return new CardboardBox();
  }
  else if (orderSize <= 20000)
  {
    return new ShellBox();
  }
  else if (orderSize <= 50000)
  {
    return new PallotBox();
  }
  else
  {
    return new PallotBox();
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
    string inst = " ~IMM\n";
    DTORF(inst);
  }

  IMM(ijm_type_t type, const string& name, uint32_t max_batch_size,
      const factory_method::Mold* moldPtr)
    : type_m(type)
    , name_m(name)
    , max_batch_size_m(max_batch_size)
    , moldPtr_m(moldPtr)
  {
  }

  const string& name() { return name_m; }

  ijm_type_t type() const { return type_m; }

  const factory_method::Mold& getMold() const { return *moldPtr_m; }

  uint32_t maxBatchSize() const { return max_batch_size_m; }

  static IMM* makeObject(uint32_t orderSize);

protected:
  IMM() = delete;

  const ijm_type_t type_m;
  const string name_m;
  const uint32_t max_batch_size_m;
  const factory_method::Mold* moldPtr_m;
};

struct IJM110 : public IMM
{
  virtual ~IJM110()
  {
    string inst = " ~IJM110";
    DTORF(inst);
  }

  IJM110(const factory_method::Mold* moldPtr)
    : IMM(IJM_110, "IJM_110", 10000, moldPtr)
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

  IJM120(const factory_method::Mold* moldPtr)
    : IMM(IJM_120, "IJM_120", 20000, moldPtr)
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

  IJM210(const factory_method::Mold* moldPtr)
    : IMM(IJM_210, "IJM_210", 50000, moldPtr)
  {
  }
};

IMM* IMM::makeObject(uint32_t orderSize)
{
  if (orderSize <= 10000)
  {
    auto mold = factory_method::Mold::makeObject(orderSize, orderSize);

    return new IJM110(mold);
  }
  else if (orderSize <= 20000)
  {
    auto mold = factory_method::Mold::makeObject(orderSize, orderSize);

    return new IJM120(mold);
  }
  else if (orderSize <= 50000)
  {
    auto mold = factory_method::Mold::makeObject(orderSize, orderSize);

    return new IJM210(mold);
  }
  else
  {
    assert(false);
  }
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
// TM - Order - Main processing class
////////////////////////////////////////////////////////////////////////////
// TODO - Extract out into just Order
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

    string inst = " ~Order\n";
    DTORF(inst);
  }

  Order(const RawOrder& raw_order)
    : MAX_ORDER_SIZE(50000)
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
    return packagerPtr_m->getPackagerType();
  }

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

  void run() {}

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
  auto process_order = new template_method::ProcessOrder(order);

  process_order->run();

  delete process_order;
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
