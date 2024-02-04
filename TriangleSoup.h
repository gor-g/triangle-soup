#include "Utils.h"
#include <istream>
#include <iterator>
#include <vector>

struct TriangleSoup {
  std::vector<Triangle> triangles;
  TriangleSoup() {};
  void read(std::istream& in);
  void read(std::string const path);

  int write(std::ofstream& out) const;
  int write(std::string const path) const;

  int size() { return triangles.size(); }
  int size() const { return triangles.size(); }

  Triangle operator[](int i) const { return triangles.at(i); }
  Triangle& operator[](int i) { return triangles.at(i); }



  void boundingBox(Vecteur& inf, Vecteur& sup) const;

};
