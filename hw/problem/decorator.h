/*
 * decorator.h
 *
 *  Created on: Sep 24, 2015
 *      Author: aldgoff
 *
 * Varies: If the options are varying, use the Decorator pattern.
 *
 * Desc: Dynamically attach additional responsibilities to an object.
 *
 * Category: Structural
 *
 *  URLs:
 *    http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator
 *    http://www.dofactory.com/net/decorator-design-pattern
 *    http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter17
 *    http://sourcemaking.com/design_patterns/decorator
 */

#ifndef PROBLEMS_DECORATOR_H_
#define PROBLEMS_DECORATOR_H_

/* Consider options for a car.
 * One might subclass a base class, Car, for each set of options, but
 * then the options code gets duplicated leading to scaling problems,
 * and the options are statically bound.
 * For the 4 classes and 9 options implied by the following OOP code,
 * rewrite with the Decorator pattern to
 *   1. eliminate the combinatorial explosion
 *   2. reduce duplication
 *   3. improve code locality
 *   4. allow for selection of options at runtime
 *   5. Extra points if you don't have to change the common::Car class.
 * Pay particular attention to the problem of memory leaks with this pattern.
 */

#include "decoratorCommon.h"

namespace legacy {

using namespace common;

class RunAbout : public Car {
 public:
  RunAbout() : Car("RunAbout") {
  }

  ~RunAbout() {
    DTOR("  ~RunAbout ", Homework);
  }

 public:
  string getDesc() {
    string desc = str + " with 4 wheels" + ", 2 doors";
    return desc;
  }

  double getCost() {
    double cost = 12000.00 + 2000.00;
    return cost;
  }
};

class SUV : public Car {
 public:
  SUV() : Car("SUV") {
  }

  ~SUV() {
    DTOR("  ~SUV ", Homework);
  }

 public:
  string getDesc() {
    string desc = str + " with 4 wheels" + ", 4 doors" + ", AC" +
                  ", automatic transmission";
    return desc;
  }

  double getCost() {
    double cost = 12000.00 + 4000.00 + 1500.00 + 3000.00;
    return cost;
  }
};

void demo(int /* seqNo */) {
  Car* cars[] = {new RunAbout, new SUV};

  for (size_t i = 0; i < COUNT(cars); i++) {
    cout << "  " << cars[i]->getDesc();
    cout << " costs $" << cars[i]->getCost() << ".\n";
  }
  cout << endl;

  for (size_t i = 0; i < COUNT(cars); i++) delete cars[i];
  cout << endl;
}

}  // legacy

namespace problem {

using namespace common;

struct BasicCar : public Car {
  BasicCar(string name = "blank") : Car(name + " with 4 wheels") {
  }

  ~BasicCar() {
    DTOR("  ~BasicCar ", Problem);
  }

  string getDesc() {
    return string(str);
  }

  double getCost() {
    return 12000.00;
  }
};

struct OptionsDecorator : public Car {
  OptionsDecorator(Car* build, string str = "OD") : Car(str), build(build) {
  }

  ~OptionsDecorator() {
    build->~Car();
    DTOR("    ~OptionsDecorator ", Problem);
  }

  string getDesc() {
    return build->getDesc() + ", " + str;
  }

  static Car* makeObject(Car* car, string& criteria);

 protected:
  Car* build;
};

struct TwoDoors : public OptionsDecorator {
  TwoDoors(Car* build) : OptionsDecorator(build, "2 doors") {
  }

  ~TwoDoors() {
    DTOR("  ~TwoDoors ", Problem);
  }

  double getCost() {
    return build->getCost() + 2000.00;
  }
};

struct FourDoors : public OptionsDecorator {
  FourDoors(Car* build) : OptionsDecorator(build, "4 doors") {
  }

  ~FourDoors() {
    DTOR("  ~FourDoors ", Problem);
  }

  double getCost() {
    return build->getCost() + 4000.00;
  }
};

struct AC : public OptionsDecorator {
  AC(Car* build) : OptionsDecorator(build, "AC") {
  }

  ~AC() {
    DTOR("  ~AC ", Problem);
  }

  double getCost() {
    return build->getCost() + 1500.00;
  }
};

struct AutomaticTransission : public OptionsDecorator {
  AutomaticTransission(Car* build)
      : OptionsDecorator(build, "AutomaticTransission") {
  }

  ~AutomaticTransission() {
    DTOR("  ~AutomaticTransission ", Problem);
  }

  double getCost() {
    return build->getCost() + 3000.00;
  }
};

struct PremiumSound : public OptionsDecorator {
  PremiumSound(Car* build) : OptionsDecorator(build, "PremiumSound") {
  }

  ~PremiumSound() {
    DTOR("  ~PremiumSound ", Problem);
  }

  double getCost() {
    return build->getCost() + 1000.00;
  }
};

struct Navigation : public OptionsDecorator {
  Navigation(Car* build) : OptionsDecorator(build, "Navigation") {
  }

  ~Navigation() {
    DTOR("  ~Navigation ", Problem);
  }

  double getCost() {
    return build->getCost() + 3000.00;
  }
};

struct SuperCharger : public OptionsDecorator {
  SuperCharger(Car* build) : OptionsDecorator(build, "super-charger") {
  }

  ~SuperCharger() {
    DTOR("  ~SuperCharger ", Problem);
  }

  double getCost() {
    return build->getCost() + 3000.00;
  }
};

struct V8Upcharge : public OptionsDecorator {
  V8Upcharge(Car* build) : OptionsDecorator(build, "V8") {
  }

  ~V8Upcharge() {
    DTOR("  ~V8Upcharge ", Problem);
  }

  double getCost() {
    return build->getCost() + 6000.00;
  }
};

// Seam point - add another set of options.

Car* OptionsDecorator::makeObject(Car* car, string& criteria) {
  if (criteria == "TwoDoors")
    return new TwoDoors(car);
  else if (criteria == "FourDoors")
    return new FourDoors(car);
  else if (criteria == "AC")
    return new AC(car);
  else if (criteria == "AutomaticTransission")
    return new AutomaticTransission(car);
  else if (criteria == "PremiumSound")
    return new PremiumSound(car);
  else if (criteria == "Navigation")
    return new Navigation(car);
  else if (criteria == "SuperCharger")
    return new SuperCharger(car);
  else if (criteria == "V8Upcharge")
    return new V8Upcharge(car);
  // Seam point - add another set of options.
  else
    return car;
};

void demo(int /* seqNo */) {
  Car* mine = new BasicCar("RunAbout");
  mine = new TwoDoors(mine);

  Car* yours = new BasicCar("SUV");
  yours = new FourDoors(yours);
  yours = new AC(yours);
  yours = new AutomaticTransission(yours);

  Car* hers = new BasicCar("Status");
  hers = new FourDoors(hers);
  hers = new AC(hers);
  hers = new PremiumSound(hers);
  hers = new Navigation(hers);
  hers = new AutomaticTransission(hers);

  Car* boss = new BasicCar("Performance");
  boss = new FourDoors(boss);
  boss = new AC(boss);
  boss = new PremiumSound(boss);
  boss = new Navigation(boss);
  boss = new AutomaticTransission(boss);

  Car* cars[] = {mine, yours, hers, boss};

  for (size_t i = 0; i < COUNT(cars); i++) {
    cout << "  " << cars[i]->getDesc();
    cout << " costs $" << cars[i]->getCost() << ".\n";
  }
  cout << endl;

  for (size_t i = 0; i < COUNT(cars); i++) {
    delete cars[i];
  }
  cout << endl;
}

}  // problem

#endif /* PROBLEMS_DECORATOR_H_ */
