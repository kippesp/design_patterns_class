/*
 * templateMethod.h
 *
 *  Created on: Sep 14, 2015
 *      Author: aldgoff
 *
 * Varies: If the steps are varying, use the Template Method pattern.
 *
 * Desc: Define the skeleton of an algorithm.
 *
 * Category: Behavioral
 *
 *  URLs:
 *    http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#TemplateMethod
 *    http://www.dofactory.com/net/templateMethod-design-pattern
 *    http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter19
 *    http://sourcemaking.com/design_patterns/templateMethod
 */

#ifndef PROBLEMS_TEMPLATEMETHOD_H_
#define PROBLEMS_TEMPLATEMETHOD_H_

/* Consider a 6 step protective coating process as implied by
 * the common and legacy namespaces below.
 * Optimization is the only difference between the processes,
 * fast() and economic().
 * Consider new specs (ala new_specs & problem namespaces below):
 *   2 more processes with different optimizations, critical() & npc().
 *   For both of these the cleanup step must be better and different.
 * Refactor using the Template Method design pattern.
 */

namespace common {

bool morning() {
  return true;
}

void fast() {
  cout << "  setup\n";
  cout << "  schedule\n";
  if (morning())
    cout << "  highHeat\n";
  else
    cout << "  lowHeat\n";
  cout << "  Fast optimized\n";  // Always different.
  cout << "  usual cleanup\n";
  cout << "  putaway\n";
  cout << endl;
}

void economic() {
  cout << "  setup\n";
  cout << "  schedule\n";
  if (morning())
    cout << "  highHeat\n";
  else
    cout << "  lowHeat\n";
  cout << "  Economic optimized\n";  // Always different.
  cout << "  usual cleanup\n";
  cout << "  putaway\n";
  cout << endl;
}

}  // common

namespace legacy {

using namespace common;

void demo(int seqNo) {
  cout << seqNo << ") << template_method::homework::legacy::demo() >>\n";
  fast();
  economic();
}

}  // legacy

namespace new_specs {

using namespace common;

void critical() {
  cout << "  setup\n";
  cout << "  schedule\n";
  if (morning())
    cout << "  highHeat\n";
  else
    cout << "  lowHeat\n";
  cout << "  Critical optimized\n";  // This step always different.
  cout << "  detailed cleanup\n";    // Now this step differs also.
  cout << "  putaway\n";
  cout << endl;
}

void npc() {
  cout << "  setup\n";
  cout << "  schedule\n";
  if (morning())
    cout << "  highHeat\n";
  else
    cout << "  lowHeat\n";
  cout << "  NPC optimized\n";       // This step always different.
  cout << "  meticulous cleanup\n";  // Now this step differs also.
  cout << "  putaway\n";
  cout << endl;
}

}  // new_specs

namespace problem {

struct Protective {
  bool morning() {
    return true;
  }

  virtual ~Protective() {
    DTOR("~Coating\n", Problem);
  }

  void coating() {
    setup();
    schedule();

    if (morning())
      highHeat();
    else
      lowHeat();

    optimization();
    cleanup();
    putaway();
    cout << endl;
  }

 private:
  // Non varying steps

  void setup() {
    cout << "  setup\n";
  }

  void schedule() {
    cout << "  schedule\n";
  }

  void highHeat() {
    cout << "  highHeat\n";
  }

  void lowHeat() {
    cout << "  lowHeat\n";
  }

  void putaway() {
    cout << "  putaway\n";
  }

 protected:
  // Varying steps

  virtual void optimization() = 0;

  void cleanup() {
    cout << "  usual cleanup\n";
  }
};

struct Fast : public Protective {
  ~Fast() {
    DTOR("  ~Fast ", Problem);
  }

  void optimization() {
    cout << "  Fast optimized\n";
  }
};

struct Economic : public Protective {
  ~Economic() {
    DTOR("  ~Economic ", Problem);
  }

  void optimization() {
    cout << "  Economic optimized\n";
  }
};

struct Critical : public Protective {
  ~Critical() {
    DTOR("  ~Critical ", Problem);
  }

  void optimization() {
    cout << "  Critical optimized\n";
  }

  void cleanup() {
    cout << "  detailed cleanup\n";
  }
};

struct NPC : public Protective {
  ~NPC() {
    DTOR("  ~NPC ", Problem);
  }

  void optimization() {
    cout << "  NPC optimized\n";
  }

  void cleanup() {
    cout << "  meticulous cleanup\n";
  }
};

void demo(int seqNo) {
  Fast fast;
  Economic economic;
  Critical critical;
  NPC npc;

  cout << seqNo << ") << template_method::";
  cout << "homework::problem::demo() >>\n";
  fast.coating();
  economic.coating();
  critical.coating();
  npc.coating();
}

}  // problem

#endif /* PROBLEMS_TEMPLATEMETHOD_H_ */
