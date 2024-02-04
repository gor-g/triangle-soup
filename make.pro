# Ceci est un fichier de configuration pour une application Qt
# Il faut peut-etre legerement l adapter pour votre ordinateur.

# nom de votre executable
# pour le veiwer 
equals(VERSION, 0){
    TARGET  = viewer.out
    DEFINES += "VIEWER=1"
    DEFINES += "ZIPPER=0"
}
# pour le zipper basique
equals(VERSION, 1){
    TARGET  = zipper1.out
    DEFINES += "VIEWER=0"
    DEFINES += "ZIPPER=1"
}
# pour le zipper smooth
equals(VERSION, 2) {
    TARGET  = zipper2.out
    DEFINES += "VIEWER=0"
    DEFINES += "ZIPPER=2"
}
# pour le zipper smooth sans doublons
equals(VERSION, 3) {
    TARGET  = zipper3.out
    DEFINES += "VIEWER=0"
    DEFINES += "ZIPPER=3"
}

# config de l executable
QMAKE_CXXFLAGS = --std=c++11
CONFIG *= qt opengl release c++11

# config de Qt
QT     *= opengl xml
# décommenter pour Qt6 seulement  
# QT     += openglwidgets

# Noms de vos fichiers entete
HEADERS = Viewer.h Utils.h TriangleSoup.h TriangleSoupZipper.h
# Noms de vos fichiers source (vous pouvez en mettre dautres)
SOURCES = main.cpp Viewer.cpp Utils.cpp TriangleSoup.cpp TriangleSoupZipper.cpp

###########################################################
# Commentez/decommentez selon votre config/systeme
# (Une config windows est possible)
###########################################################

# Exemple de configuration Linux de Qt et libQGLViewer Qt5
# Ubuntu 20.04
LIBS *= -L/usr/lib/x86_64-linux-gnu -lQGLViewer-qt5

# Exemple de configuration MacOSX avec macports
# INCLUDEPATH *= /opt/local/include
# LIBS *= -L/opt/local/lib -lQGLViewer 

# Exemple de configuration MacOSX/Qt6 avec frameworks
# INCLUDEPATH *= /Users/lachaud/local/src/libQGLViewer-2.9.1
# LIBS *= -F/Users/lachaud/local/src/libQGLViewer-2.9.1/QGLViewer -framework QGLViewer

# Exemple de configuration Windows :
# LIBS *= -lopengl32 -lglu32
# INCLUDEPATH *= D:\Cours\Info805\TP1\libQGLViewer-2.7.1
# LIBS *= -LD:\Cours\Info805\TP1\libQGLViewer-2.7.1\QGLViewer -lQGLViewer2
