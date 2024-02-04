/// \file Viewer.h
#include "TriangleSoup.h"
#include <QGLViewer/qglviewer.h>
#include <vector>

typedef float Color[4];

class Viewer : public QGLViewer {
public:
  TriangleSoup* ptrSoup;
  Viewer(TriangleSoup* aSoup = 0) : QGLViewer(), ptrSoup(aSoup) {}

  Color colorBronzeDiff = { 0.8, 0.6, 0.0, 1.0 };
  Color colorRedDiff = { 1.0, 0.0, 0.0, 1.0 };
  Color colorGreenDiff = { 0.0, 1.0, 0.0, 1.0 };
  Color colorBlueDiff = { 0.0, 0.0, 1.0, 1.0 };

  Color colorBronzeSpec = { 1.0, 1.0, 0.4, 1.0 };
  Color colorWhite = { 1.0, 1.0, 1.0, 1.0 };
  Color colorGray = { 0.6, 0.6, 0.6, 1.0 };
  Color colorNull = { 0.0, 0.0, 0.0, 1.0 };

protected:
  /// Called at each draw of the window
  virtual void draw();

  static void draw(Triangle t);

  /// Called before the first draw
  virtual void init();
  /// Called when pressing help.
  virtual QString helpString() const;
};
