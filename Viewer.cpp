/// \file Viewer.cpp
#include "Viewer.h"

void Viewer::draw() {

        glBegin(GL_TRIANGLES);
        glEnable(GL_COLOR_MATERIAL);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorWhite);
        glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
        glColor4fv(colorGray);

        for (std::vector<Triangle>::iterator itTri = ptrSoup->triangles.begin();
                itTri != ptrSoup->triangles.end(); ++itTri) {
                Vecteur n = itTri->normal();
                glNormal3fv(n);
                Color specColor = { n[0], n[1], n[2], 1.0 };
                glMaterialfv(GL_FRONT, GL_SPECULAR, specColor);
                draw(*itTri);
                // for (int i = 0; i < 3; ++i) {
                //   glVertex3fv((*itTri)[i]);
                // }
        }
        glEnd();
}

void Viewer::draw(Triangle t) {
        for (int i = 0; i < 3; ++i) {
                glVertex3fv(t[i]);
        }
}

void Viewer::init() {
        // Restore previous viewer state.
        restoreStateFromFile();
        Vecteur inf, sup;
        ptrSoup->boundingBox(inf, sup);

        qglviewer::Vec min(inf[0], inf[1], inf[2]);
        qglviewer::Vec max(sup[0], sup[1], sup[2]);
        camera()->setSceneBoundingBox(min, max);

        camera()->showEntireScene();

        // Opens help window
        help();
}

QString Viewer::helpString() const {
        QString text("<h2>S i m p l e V i e w e r</h2>");
        text += "Use the mouse to move the camera around the object. ";
        text += "You can respectively revolve around, zoom and translate with the "
                "three mouse buttons. ";
        text += "Left and middle buttons pressed together rotate around the camera "
                "view direction axis<br><br>";
        text += "Pressing <b>Alt</b> and one of the function keys "
                "(<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
        text += "Simply press the function key again to restore it. Several "
                "keyFrames define a ";
        text += "camera path. Paths are saved when you quit the application and "
                "restored at next start.<br><br>";
        text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world "
                "axis, ";
        text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to "
                "save a snapshot. ";
        text += "See the <b>Keyboard</b> tab in this window for a complete "
                "shortcut list.<br><br>";
        text += "Double clicks automates single click actions: A left button double "
                "click aligns the closer axis with the camera (if close enough). ";
        text += "A middle button double click fits the zoom of the camera and the "
                "right button re-centers the scene.<br><br>";
        text += "A left button double click while holding right button pressed "
                "defines the camera <i>Revolve Around Point</i>. ";
        text += "See the <b>Mouse</b> tab and the documentation web pages for "
                "details.<br><br>";
        text += "Press <b>Escape</b> to exit the viewer.";
        return text;
}
