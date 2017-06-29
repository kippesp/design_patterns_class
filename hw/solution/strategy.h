/*
 * strat.h
 *
 *  Created on: Jun 13, 2017
 *      Author: aldgoff
 *
 * Desc: Better homework example.
 */

#ifndef SRC_SOLUTIONS_STRAT_H_
#define SRC_SOLUTIONS_STRAT_H_

namespace solution {

enum Way {
  Hard,
  Easy,
  Quick,
  Clear
  // Seam point #1 - add another way.
};

class WayBase {
 public:
  virtual ~WayBase() {
    DTOR("~WayBase()\n", Homework);
  }

 public:
  virtual void way() {
    cout << "  WayBase.way()";
  }
};
class HardWay : public WayBase {
 public:
  ~HardWay() {
    DTOR("~HardWay()\n", Homework);
  }

 public:
  virtual void way() {
    cout << "The hard way.\n";
  }
};
class EasyWay : public WayBase {
 public:
  ~EasyWay() {
    DTOR("~EasyWay()\n", Homework);
  }

 public:
  virtual void way() {
    cout << "The easy way.\n";
  }
};
class QuickWay : public WayBase {
 public:
  ~QuickWay() {
    DTOR("~QuickWay()\n", Homework);
  }

 public:
  virtual void way() {
    cout << "The quick way.\n";
  }
};
class ClearWay : public WayBase {
 public:
  ~ClearWay() {
    DTOR("~ClearWay()\n", Homework);
  }

 public:
  virtual void way() {
    cout << "The clear way.\n";
  }
};
// Seam point #2 - add another way.

void clientCode1(WayBase* my) {
  cout << "  clientCode1 - ";
  my->way();
}
void clientCode2(WayBase* my) {
  cout << "  clientCode2 - ";
  my->way();
}
void clientCode3(WayBase* my) {
  cout << "  clientCode3 - ";
  my->way();
}
//...
void clientCode18(WayBase* my) {
  cout << "  clientCode18 - ";
  my->way();
}

void demo(int seqNo) {  // Test all the daughter classes & clients.
  cout << seqNo << ") << strategy::homework::solution::demo(seqNo) >>\n";
  Way criteria[] = {Hard, Easy, Quick, Clear};
  for (size_t i = 0; i < COUNT(criteria); i++) {
    WayBase* ptr = 0;

    if (criteria[i] == Hard)
      ptr = new HardWay;  // Hint: will become Factory pattern.
    else if (criteria[i] == Easy)
      ptr = new EasyWay;
    else if (criteria[i] == Quick)
      ptr = new QuickWay;
    else if (criteria[i] == Clear)
      ptr = new ClearWay;
    // Seam point #3 - add another way.
    else
      ptr = new WayBase;  // OOPs!

    clientCode1(ptr);
    clientCode2(ptr);
    clientCode3(ptr);
    //...
    clientCode18(ptr);

    free(ptr);
    cout << endl;
  }
  cout << endl;
}

}  // solution

#endif /* SRC_SOLUTIONS_STRAT_H_ */
