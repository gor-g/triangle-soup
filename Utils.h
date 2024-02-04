#pragma once
#include <iostream>

typedef int IntArr3[3];

class Vecteur {
public:
  Vecteur() :xyz{ 0,0,0 } {};
  Vecteur(float x, float y, float z); // constructeur
  Vecteur(IntArr3 v);                 // constructeur
  float operator[](int i) const;      // opérateur accès en lecture
  float& operator[](int i);           // opératuer accès en écriture
  Vecteur operator-(const Vecteur& other) const;
  Vecteur operator+(const Vecteur& other) const;
  Vecteur operator/(const float& fvar) const;
  Vecteur operator/(const Vecteur& other) const;
  operator const float* () const { return xyz; }
  // Retourne le vecteur dont les composantes sont les minima des
  // composantes de soi-même et de other.
  Vecteur inf(const Vecteur& other) const;

  // Retourne le vecteur dont les composantes sont les maxima des
  // composantes de soi-même et de other.
  Vecteur sup(const Vecteur& other) const;

  Vecteur cross(const Vecteur& other) const;
  float norm() const;

private:
  float xyz[3]; // coordonnées
};
// surcharge de opérateur '<<' pour imprimer des Vecteur-s
std::ostream& operator<<(std::ostream& out, Vecteur v);
// surcharge de opérateur '>>' pour lire des Vecteur-s
std::istream& operator>>(std::istream& in, Vecteur& v);

typedef Vecteur Point;

class Triangle {
public:
  Triangle() {};
  Triangle(Point A, Point B, Point C);

  Point operator[](int i) const { return sommets[i]; }
  Point& operator[](int i) { return sommets[i]; }

  Vecteur normal() const;

private:
  Point sommets[3];
};
std::ostream& operator<<(std::ostream& out, Triangle t);
std::istream& operator>>(std::istream& in, Triangle& t);