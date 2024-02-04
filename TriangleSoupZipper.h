#include "TriangleSoup.h"
#include <cmath>
#include <map>
#include <set>

typedef Vecteur CellDiagScaledVecteur;

struct Index {
  int idx[3];
  Index(int i0, int i1, int i2) : idx{ i0, i1, i2 } {}
  Index(int* indices) : idx{ indices[0], indices[1], indices[2] } {}
  Index(CellDiagScaledVecteur v) : idx{ static_cast<int>(std::floor(v[0])), static_cast<int>(std::floor(v[1])), static_cast<int>(std::floor(v[2])) } {}  int operator[](int i) const { return idx[i]; }
  int& operator[](int i) { return idx[i]; }
  bool operator<(const Index& other) const {
    return (idx[0] < other.idx[0]) ||
      ((idx[0] == other.idx[0]) &&
        ((idx[1] < other.idx[1]) ||
          ((idx[1] == other.idx[1]) && (idx[2] < other.idx[2]))));
  }
  bool operator==(const Index& other) const {
    return (idx[0] == other.idx[0])
      && (idx[1] == other.idx[1])
      && (idx[2] == other.idx[2]);
  }
  bool operator!=(const Index& other) const {
    return (idx[0] != other.idx[0])
      || (idx[1] != other.idx[1])
      || (idx[2] != other.idx[2]);
  }
  Vecteur operator*(const Vecteur& v) const {
    return Vecteur(idx[0] * v[0], idx[1] * v[1], idx[2] * v[2]);
  }
};

struct IndexTriplet {
  Index tridx[3] = { Index(0,0,0), Index(0,0,0), Index(0,0,0) };
  IndexTriplet(const Index& i0, const Index& i1, const Index& i2) {
    // on permute le triplet pour mettre le plus petit index en premier position
    // c'est pour pouvoir comparer les IndexTriplet plus facilement
    // on ne trie pas car on veut garder l'ordre des sommets pour pas retourner les normales des triangles
    if (i0 < i1 && i0 < i2) {
      tridx[0] = i0;
      tridx[1] = i1;
      tridx[2] = i2;
    }
    else if (i1 < i0 && i1 < i2) {
      tridx[0] = i1;
      tridx[1] = i2;
      tridx[2] = i0;
    }
    else {
      tridx[0] = i2;
      tridx[1] = i0;
      tridx[2] = i1;
    }
  }
  IndexTriplet(const Index* indices) : IndexTriplet(indices[0], indices[1], indices[2]) {}
  Index operator[](int i) const { return tridx[i]; }
  Index& operator[](int i) { return tridx[i]; }
  bool operator<(const IndexTriplet& other) const {
    return (tridx[0] < other.tridx[0]) ||
      ((tridx[0] == other.tridx[0]) &&
        ((tridx[1] < other.tridx[1]) ||
          ((tridx[1] == other.tridx[1]) && (tridx[2] < other.tridx[2]))));
  }
  bool operator==(const IndexTriplet& other) const {
    return (tridx[0] == other.tridx[0])
      && (tridx[1] == other.tridx[1])
      && (tridx[2] == other.tridx[2]);
  }
  bool operator!=(const IndexTriplet& other) const {
    return (tridx[0] != other.tridx[0])
      || (tridx[1] != other.tridx[1])
      || (tridx[2] != other.tridx[2]);
  }
};

// Structure pour calculer le barycentre d'un ensemble de points.
struct CellData {
  Vecteur acc;
  int nb;
  // Crée un accumulateur vide.
  CellData() : acc(), nb(0) {}
  // Ajoute le point v à l'accumulateur.
  void add(const Vecteur& v) {
    acc = acc + v;
    nb++;
  }
  // Retourne le barycentre de tous les points ajoutés.
  Vecteur barycenter() const { return acc / nb; }
};


typedef int Dims[3];

struct TriangleSoupZipper {
  // Construit le zipper avec une soupe de triangle en entrée \a
  // anInput, une soupe de triangle en sortie \a anOutput, et un index \a size
  // qui est le nombre de cellules de la boîte découpée selon les 3 directions.
  TriangleSoupZipper(const TriangleSoup& anInput, TriangleSoup& anOutput,
    Dims size);

  /// @return l'index de la cellule dans laquelle tombe \a p.
  Index index(const Vecteur& p) const;
  /// @return le centroïde de la cellule d'index \a idx (son "centre").
  Vecteur centroid(const Index& idx) const;


  // méthode zip() qui compresse tous les triangles de la soupe en entrée et
  // sort les triangles dont les sommets ont des index différents. La position
  // des sommets en sortie est juste centroid( idx ) si idx est l'index du
  // sommet
  void zip();

  void smoothZip();

  const TriangleSoup& input;
  TriangleSoup& output;
  Dims size;
  Point inf, sup;
  Vecteur cellDiag;
  // Stocke pour chaque cellule son barycentre.
  std::map<Index, CellData> index2data;
  std::set<IndexTriplet> indexTriplets;
};
