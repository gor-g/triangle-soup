#include "Utils.h"
#include <cmath>

// BEGIN ---- Vecteur

Vecteur::Vecteur(float x, float y, float z) : xyz{ x, y, z } {}
Vecteur::Vecteur(IntArr3 v)
  : xyz{ static_cast<float>(v[0]),
         static_cast<float>(v[1]),
         static_cast<float>(v[2]) } {}

float Vecteur::operator[](int i) const { return xyz[i]; }
float& Vecteur::operator[](int i) { return xyz[i]; }
Vecteur Vecteur::operator-(const Vecteur& other) const {
  return Vecteur(xyz[0] - other[0], xyz[1] - other[1], xyz[2] - other[2]);
}
Vecteur Vecteur::operator+(const Vecteur& other) const {
  return Vecteur(xyz[0] + other[0], xyz[1] + other[1], xyz[2] + other[2]);
}
Vecteur Vecteur::operator/(const float& x) const {
  return Vecteur(xyz[0] / x, xyz[1] / x, xyz[2] / x);
}
Vecteur Vecteur::operator/(const Vecteur& other) const {
  return Vecteur(xyz[0] / other[0], xyz[1] / other[1], xyz[2] / other[2]);
}

Vecteur Vecteur::inf(const Vecteur& other) const {
  float x = xyz[0] < other[0] ? xyz[0] : other[0];
  float y = xyz[1] < other[1] ? xyz[1] : other[1];
  float z = xyz[2] < other[2] ? xyz[2] : other[2];
  return Vecteur(x, y, z);
}

Vecteur Vecteur::sup(const Vecteur& other) const {
  float x = xyz[0] > other[0] ? xyz[0] : other[0];
  float y = xyz[1] > other[1] ? xyz[1] : other[1];
  float z = xyz[2] > other[2] ? xyz[2] : other[2];
  return Vecteur(x, y, z);
}

Vecteur Vecteur::cross(const Vecteur& other) const {
  return Vecteur(xyz[1] * other[2] - xyz[2] * other[1],
    xyz[2] * other[0] - xyz[0] * other[2],
    xyz[0] * other[1] - xyz[1] * other[0]);
}

float Vecteur::norm() const {
  return std::sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
}

std::ostream& operator<<(std::ostream& out, Vecteur v) {
  out << v[0] << " " << v[1] << " " << v[2];
  return out;
}

std::istream& operator>>(std::istream& in, Vecteur& v) {
  in >> v[0] >> v[1] >> v[2];
  return in;
}

// END ---- Vecteur

// BEGIN ---- Triangle

Triangle::Triangle(Point A, Point B, Point C) : sommets{ A, B, C } {}


Vecteur Triangle::normal() const {
  Vecteur AB = sommets[1] - sommets[0];
  Vecteur AC = sommets[2] - sommets[0];
  Vecteur ABxAC = AB.cross(AC);
  return ABxAC / ABxAC.norm();
}

std::ostream& operator<<(std::ostream& out, Triangle t) {
  out << t[0] << " " << t[1] << " " << t[2] << std::endl;
  return out;
}

std::istream& operator>>(std::istream& in, Triangle& t) {
  in >> t[0] >> t[1] >> t[2];
  return in;
}

// END ---- Triangle