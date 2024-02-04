#include "TriangleSoupZipper.h"

Index TriangleSoupZipper::index(const Vecteur& p) const {
    Index idx = (p - inf) / cellDiag;
    return idx;
}

Point TriangleSoupZipper::centroid(const Index& idx) const {
    Point c;
    c = inf + idx * cellDiag + cellDiag / 2;
    return c;
}



TriangleSoupZipper::TriangleSoupZipper(const TriangleSoup& anInput,
    TriangleSoup& anOutput, Dims size)
    : input{ anInput }, output{ anOutput }, size{ size[0], size[1], size[2] } {

    input.boundingBox(inf, sup);

    cellDiag = (sup - inf) / Vecteur(size);
}

# if ZIPPER == 0 or ZIPPER == 1
void TriangleSoupZipper::zip() {
    for (const Triangle& Ti : input.triangles) {
        Index idxA = index(Ti[0]);
        Index idxB = index(Ti[1]);
        Index idxC = index(Ti[2]);


        if (idxA == idxB || idxB == idxC || idxA == idxC)
        {
            continue;
        }
        else
        {
            Triangle To = Triangle(centroid(idxA), centroid(idxB), centroid(idxC));
            output.triangles.push_back(To);
        }
    }
}
# elif ZIPPER == 2
void TriangleSoupZipper::zip() {
    index2data.clear();
    for (const Triangle& Ti : input.triangles) {
        Index idxA = index(Ti[0]);
        Index idxB = index(Ti[1]);
        Index idxC = index(Ti[2]);
        index2data[idxA].add(Ti[0]);
        index2data[idxB].add(Ti[1]);
        index2data[idxC].add(Ti[2]);


        if (idxA == idxB || idxB == idxC || idxA == idxC)
        {
            continue;
        }
        else
        {
            Triangle To = Triangle(centroid(idxA), centroid(idxB), centroid(idxC));
            output.triangles.push_back(To);
        }
    }
}
# elif ZIPPER == 3
void TriangleSoupZipper::zip() {
    index2data.clear();
    indexTriplets.clear();
    for (const Triangle& Ti : input.triangles) {
        Index idxA = index(Ti[0]);
        Index idxB = index(Ti[1]);
        Index idxC = index(Ti[2]);
        index2data[idxA].add(Ti[0]);
        index2data[idxB].add(Ti[1]);
        index2data[idxC].add(Ti[2]);


        if (idxA == idxB || idxB == idxC || idxA == idxC)
        {
            continue;
        }
        else if (indexTriplets.find({ idxA, idxB, idxC }) == indexTriplets.end())
        {
            Triangle To = Triangle(centroid(idxA), centroid(idxB), centroid(idxC));
            output.triangles.push_back(To);
            indexTriplets.insert({ idxA, idxB, idxC });
        }
    }
}
# endif

void TriangleSoupZipper::smoothZip() {
    zip();
    for (Triangle& T : output.triangles) {
        T[0] = index2data[index(T[0])].barycenter();
        T[1] = index2data[index(T[1])].barycenter();
        T[2] = index2data[index(T[2])].barycenter();
    }
}
