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

static Display *dis;
static Window win;
extern bool closed = false;
static bool mtlused = false;
extern bool minimized = false;
static std::vector<std::string> mtlIndexer;
//needs function for this v & ^
//needs resizing support & mouse support
extern char lastkey;
extern bool mouseClicked = false;
extern double mouseLocX;
extern double mouseLocY;
static XEvent event;

struct pointColor
{
    double x, y, z;
    std::string hex;
 };

std::vector<std::vector<pointColor>> mtlColors;

struct OBJv
{
    double x, y, z, w;
};
struct Line
{
    double x1, y1, z1, w1;
    double x2, y2, z2, w2;
};

struct Shape
{
    std::vector<Line> lines;
};
struct OBJ
{
    std::vector<OBJv> points;
    //points turns into lines
    std::vector<Line> lines;
    //^^ needs to be sorted into shapes
    std::vector<Shape> shapes;
    std::vector<pointColor> colors; //Hex values in string format per shape
    int xlength, ylength, zlength;
    int x1, x2, y1, y2, z1, z2; //closest and farthest points on each axis
};

static std::vector<OBJ> scene;

struct point3d {
    int x, y, z;
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

static void mtllib(std::string line)
{
    //parse line to get second token
    //open mtl a.k.a. second token ^^
    //parse mtl and find objects
    //put objects names in mtlIndexer
    //put objects into mtlObjects
}
static std::vector<std::string> parseTexture(std::string line)
{
    std::vector<std::string> colors;
    //say colors in hex format and identify point to be located on`
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
        if(filepath.substr(0,2).compare("v "))
        {
            filepath = filepath.substr(2, filepath.length() - 2);
            std::istringstream iss(filepath);
            OBJv v;
            iss >> v.x >> v.y >> v.z;
            iss.ignore();
            if (iss)
            {
                iss >> v.w;
            }
            else
            {
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
            if(mtlused == false)
            {
                continue;
            }
            else
            {
                filepath = filepath.substr(7, filepath.length() - 7);
                for(int i = 0; i < mtlIndexer.size(); i++)
                {
                    if(filepath.compare(mtlIndexer[i]))
                    {
                        object.colors.insert(object.colors.end(), mtlColors[i].begin(), mtlColors[i].end());
                        break;
                    }
                }
            }
        }
    }
}
void displayOBJ(OBJ toDisplay, bool shaderEnable, int x1, int x2, int y1, int y2, int z1, int z2)
{
    //calculate 2D view and display pixels with correct colors. Darken colors for the farther they are IF shade is true.
}
void removeOBJ(int toRemove)
{
    //stop displaying OBJ at given index
}
#endif
