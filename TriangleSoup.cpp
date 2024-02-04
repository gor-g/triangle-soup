#include "TriangleSoup.h"
#include <fstream>
#include <iostream>
#include <sstream>



void TriangleSoup::read(std::istream& in) {
  std::string line;
  Triangle t;
  while (std::getline(in, line))
    if ((line.size() > 0) && (line[0] != '#')) {
      std::istringstream inputLine(line);
      if (!(inputLine >> t)) {
        throw std::runtime_error("Failed to read triangle from input line : " +
          line);
      }
      else {
        triangles.push_back(t);
      }
    }
}


void TriangleSoup::read(std::string const path) {
  std::ifstream input(path); // input est un flux en entrée
  if (!input.good())
    std::cerr << "ERROR loading file with the path : " << path << std::endl;
  read(input);
}


int TriangleSoup::write(std::ofstream& out) const {
  if (!out.good()) {
    std::cerr << "ERROR writing file" << std::endl;
    return 1;
  }
  for (const Triangle& t : triangles)
    out << t;
  return 0;
}

int TriangleSoup::write(std::string const path) const {
  std::ofstream output(path);
  return write(output);
}


void TriangleSoup::boundingBox(Vecteur& inf, Vecteur& sup) const {
  inf = triangles[0][0];
  sup = triangles[0][0];
  for (const Triangle& t : triangles)
    for (int i = 0; i < 3; ++i) {
      inf = inf.inf(t[i]);
      sup = sup.sup(t[i]);
    }
  return;
}