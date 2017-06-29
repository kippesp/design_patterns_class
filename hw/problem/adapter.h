/*
 * adapter.h
 *
 *  Created on: Sep 1, 2015
 *      Author: aldgoff
 *
 * Varies: If the interfaces are varying, use the Adapter pattern.
 *
 * Desc: Adapt interfaces so classes can work together polymorphically.
 *
 * Category: Structural
 *
 *  URLs:
 *    http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Adapter
 *    http://www.dofactory.com/net/adapter-design-pattern
 *    http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter7
 *    http://sourcemaking.com/design_patterns/adapter
 */

#ifndef PROBLEMS_ADAPTER_H_
#define PROBLEMS_ADAPTER_H_

/* Consider the case where an installed and heavily used class hierarchy
 * for simple shapes needs to be extended by incorporating a commercial
 * class hierarchy containing more complex shapes.
 * The problem is that the two class hierarchies use different API's.
 * The original uses the function "draw()" the other the function "display()".
 * This breaks the polymorphism that kept the client code simple.
 * This causes 4 maintenance headaches:
 *   1) Client code will become more complicated.
 *   2) Changes will be required in existing client code.
 *   3) Likely become littered w/ if statements of the sort "what type are you"?
 *   4) Need for error detection.
 * Solve this problem by writing new classes that 'adapt' the new interface
 * (namespace commercial) to the old (namespace home_grown).
 */

namespace home_grown {

class ShapeInterfaceDraw {  // Home grown classes.
 public:
  virtual ~ShapeInterfaceDraw() {
    DTOR("  ~ShapeInterfaceDraw\n", Homework);
  }

 public:
  virtual void draw() = 0;
};

class Point : public ShapeInterfaceDraw {
 public:
  ~Point() {
    DTOR("  ~Point", Homework);
  }

 public:
  void draw() {
    cout << "  Draw point.\n";
  }
};

class Line : public ShapeInterfaceDraw {
 public:
  ~Line() {
    DTOR("  ~Line", Homework);
  }

 public:
  void draw() {
    cout << "  Draw line.\n";
  }
};

class Rect : public ShapeInterfaceDraw {
 public:
  ~Rect() {
    DTOR("  ~Rect", Homework);
  }

 public:
  void draw() {
    cout << "  Draw rectangle.\n";
  }
};

}  // home_grown

namespace legacy {

using namespace home_grown;

void clientCode(ShapeInterfaceDraw* shape) {  // Interface adapts to Client.
  shape->draw();
}

void demo(int seqNo) {
  cout << seqNo << ") << adapter::homework::legacy::demo() >>\n";
  vector<ShapeInterfaceDraw*> shapes;
  shapes.push_back(new Point);
  shapes.push_back(new Line);
  shapes.push_back(new Rect);

  for (size_t i = 0; i < shapes.size(); i++) {  // Polymorphic client code.
    clientCode(shapes[i]);
  }
  for (size_t i = 0; i < shapes.size(); i++) delete shapes[i];
  cout << endl;
}

}  // legacy

namespace commercial {

class ShapeInterfaceDisplay {  // Commercial classes.
 public:
  virtual ~ShapeInterfaceDisplay() {
    DTOR("  ~ShapeInterfaceDisplay\n", Homework);
  }

 public:
  virtual void display() = 0;
};

class Polygon : public ShapeInterfaceDisplay {
 public:
  ~Polygon() {
    DTOR("  ~commercial::Polygon", Homework);
  }

 public:
  void display() {
    cout << "  Display polygon.\n";
  }
};

class Torus : public ShapeInterfaceDisplay {
 public:
  ~Torus() {
    DTOR("  ~commercial::Torus", Homework);
  }

 public:
  void display() {
    cout << "  Display torus.\n";
  }
};

class Bezel : public ShapeInterfaceDisplay {
 public:
  ~Bezel() {
    DTOR("  ~commercial::Bezel", Homework);
  }

 public:
  void display() {
    cout << "  Display bezel.\n";
  }
};

}  // commercial

namespace problem {

using namespace home_grown;

// Adapt commercial version of Polygon
struct Polygon : public ShapeInterfaceDraw {
  commercial::Polygon polygon;

  ~Polygon() {
    DTOR("  ~Polygon\n", Problem);
  }

  void draw() {
    cout << "  Adaptor ::";
    polygon.display();
  }
};

// Adapt commercial version of Torus
struct Torus : public ShapeInterfaceDraw {
  commercial::Torus torus;

  ~Torus() {
    DTOR("  ~Torus\n", Problem);
  }

  void draw() {
    cout << "  Adaptor ::";
    torus.display();
  }
};

// Adapt commercial version of Bezel
struct Bezel : public ShapeInterfaceDraw {
  commercial::Bezel bezel;

  ~Bezel() {
    DTOR("  ~Bezel\n", Problem);
  }

  void draw() {
    cout << "  Adaptor ::";
    bezel.display();
  }
};

void clientCode(ShapeInterfaceDraw* shape) {
  shape->draw();
}

void demo(int seqNo) {
  cout << seqNo << ") << adapter::homework::problem::demo() >>\n";
  vector<ShapeInterfaceDraw*> shapes;
  shapes.push_back(new Point);
  shapes.push_back(new Line);
  shapes.push_back(new Rect);
  shapes.push_back(new Polygon);
  shapes.push_back(new Torus);
  shapes.push_back(new Bezel);

  for (size_t i = 0; i < shapes.size(); i++) {
    clientCode(shapes[i]);
  }

  for (size_t i = 0; i < shapes.size(); i++) {
    delete shapes[i];
  }

  cout << endl;
}

}  // problem

#endif /* PROBLEMS_ADAPTER_H_ */
