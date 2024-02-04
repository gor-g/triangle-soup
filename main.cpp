# if VIEWER == 1
#include "Viewer.h"
# else
#include "TriangleSoupZipper.h"
# endif
#include <fstream>
#include <iostream>
#include <qapplication.h>
#include <sstream>
#include <string>


# if VIEWER == 0
int main(int argc, char** argv) {
  // Read command lines arguments.
  if (argc < 6) {
    std::cout << "Usage: " << argv[0] << " <path_to_tri_file> <path_to_output_tri_file> <size_x> <size_y> <size_z>" << std::endl;
    return 1;
  }

  TriangleSoup iSoup, oSoup;
  std::ifstream input(argv[1]); // Read the .tri file from the command-line argument
  iSoup.read(input);

  Dims size = { std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]) };
  TriangleSoupZipper zipper(iSoup, oSoup, size);

# if ZIPPER == 1
  zipper.zip();
# elif ZIPPER == 2 or ZIPPER == 3
  zipper.smoothZip();
# endif

  std::cout << "Before compression: " << iSoup.size() << " triangles" << std::endl;
  std::cout << "After compression: " << oSoup.size() << " triangles" << std::endl;

  oSoup.write(argv[2]);

  return 0;
}
# elif VIEWER == 1
int main(int argc, char** argv) {
  // Read command lines arguments.
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <path_to_tri_file>" << std::endl;
    return 1;
  }

  QApplication application(argc, argv);
  Viewer viewer;

  TriangleSoup iSoup;
  std::ifstream input(argv[1]); // Read the .tri file from the command-line argument
  iSoup.read(input);
  viewer.ptrSoup = &iSoup;

  viewer.setWindowTitle("Viewer triangle soup");
  viewer.show();
  application.exec();
  return 0;
}
# endif