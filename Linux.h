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
#include <vector>

Display *dis;
Window win;
int junk = 0;
extern bool closed = false;
extern bool minimized = false;
//needs function for this v & ^
//needs resizing support & mouse support
extern char lastkey;
extern bool mouseClicked = false;
extern double mouseLocX;
extern double mouseLocY;
XEvent event;
struct OBJ
{
    std::vector<std::string> lines;
    std::vector<std::string> colors;

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

std::vector<std::string> mtllib(std::string line)
{
    std::vector<std::string> lines;
    //parse line to get second token
    //open mtl a.k.a. second token ^^
    //parse to lines
    return lines;
}
std::vector<std::string> parseTexture(std::string line)
{
    std::vector<std::string> colors;
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
        if(filepath.substr(0, 6).compare("mtllib"))
        {
            object.lines.insert(object.lines.end(), mtllib(filepath).begin(), mtllib(filepath).end());
            object.colors.insert(object.colors.end(), mtllibColors(filepath).begin(), mtllibColors(filepath).end());
        }
    }
}
#endif
