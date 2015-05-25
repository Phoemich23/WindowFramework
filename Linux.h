#ifndef LINUX
#define LINUX
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

Display *dis;
Window win;
extern bool closed = false;
bool mtlused = false;
extern bool minimized = false;
std::vector<std::string> mtlObjects[];
std::string mtlIndexer[];
//needs function for this v & ^
//needs resizing support & mouse support
extern char lastkey;
extern bool mouseClicked = false;
extern double mouseLocX;
extern double mouseLocY;
XEvent event;

std::vector<OBJ> scene;

struct OBJv {
    double x, y, z, w;
};

struct Shape {
    std::vector<std::string> lines;
};
struct OBJ
{
    std::vector<OBJv> points;
    //points turns into lines
    std::vector<std::string> lines;
    //^^ needs to be sorted into shapes
    std::vector<Shape> shapes;
    std::vector<std::string> colors; //Hex values in string format per shape

};
static void checkEvents ()
{
    while(true)
    {
        XNextEvent(dis ,&event);
        switch (event.type)
        {
        case ClientMessage:
            closed = true;
            break;
        //cases for other events
        }
    }
    return;
}
void newBlankWindow(int x, int y)
{
    dis = XOpenDisplay(NULL);
    win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 1, 1, x, y, \
                              0, BlackPixel (dis, 0), BlackPixel(dis, 0));
    XMapWindow(dis, win);
    XFlush(dis);
    Atom wmDelete=XInternAtom(dis, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(dis, win, &wmDelete, 1);
    std::thread (checkEvents).detach();
}

void mtllib(std::string line)
{
    //parse line to get second token
    //open mtl a.k.a. second token ^^
    //parse mtl and find objects
    //put objects names in mtlIndexer
    //put objects into mtlObjects
}
std::vector<std::string> parseTexture(std::string line)
{
    std::vector<std::string> colors;
    //say colors in hex format and identify point to be located on`
    return colors;
}
std::vector<std::string> mtllibColors(std::string line)
{
    std::vector<std::string> colors;
    //parse line to get second token
    //open mtl a.k.a. second token ^^
    //parse to colors
    //if texture
        //parseTexture(line);
    return colors;
}

OBJ openOBJ(std::string filepath)
{
    OBJ object;
    std::ifstream objfile(filepath);
    while(std::getline(objfile, filepath))
    {
        if(filepath.substr(0, 1).compare("#"))
        {
            continue;
        }
        if(filepath.substr(0,2).compare("v ")) {
            filepath = filepath.substr(2, filepath.length() - 2);
            std::istringstream iss(filepath.substr(filepath);
            OBJv v;
            iss >> point.x >> point.y >> point.z;
            iss.ignore();
            if (iss) {
                iss > w;
            } else {
                v.w = 1;
            }
            object.points.push_back(v);
        }
        if(filepath.substr(0, 6).compare("mtllib"))
        {
            mtlused = true;
            mtllib(filepath);
        }
        if(filepath.substr(0, 6).compare("usemtl"))
        {
            if(mtlused == false) {
                continue;
            } else {
                filepath = filepath.substr(0, 7);
                //for loop to compare to elements in mtlIndexer array
            }
        }
    }
}
void displayOBJ(OBJ toDisplay) {
    //calculate 2D view and display pixels with correct colors. Darken colors for the farther they are.
}
void removeOBJ(int toRemove) {
    //stop displaying OBJ at given index
}
#endif
