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
extern char lastkey; //need to turn this into
//needs resizing support & mouse support
extern bool mouseClicked = false;
extern double mouseLocX;
extern double mouseLocY;
static XEvent event;
static int *frontx = NULL;
static int *fronty = NULL;
static GC gc;

struct pointColor
{
    double x=-1, y=-1, z=-1;
    std::string hex = "#008000";
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

struct OBJ
{
    std::vector<OBJv> points;
    //points turns into lines
    std::vector<std::vector<Line>> lines;
    std::vector<pointColor> colors; //Hex values in string format per pixel, defaultly green
    double xlength, ylength, zlength;
    double x1, x2, y1, y2, z1, z2; //closest and farthest points on each axis
    int vcount = 0, vncount = 0, vtcount = 0;
};

static std::vector<OBJ> scene;

struct point3d
{
    int x, y, z;
};

static void checkEvents ()
{
    while(true)
    {
        /*
        Quote Originally Posted by sandbucket  View Post
        anybody know where i can find a list of possible values the XEvent's type variable?
        Theyr'e listed in the /usr/include/X11/X.h header file:
        Code :
        #define KeyPress                2
        #define KeyRelease              3
        #define ButtonPress             4
        #define ButtonRelease           5
        #define MotionNotify            6
        #define EnterNotify             7
        #define LeaveNotify             8
        #define FocusIn                 9
        #define FocusOut                10
        #define KeymapNotify            11
        #define Expose                  12
        #define GraphicsExpose          13
        #define NoExpose                14
        #define VisibilityNotify        15
        #define CreateNotify            16
        #define DestroyNotify           17
        #define UnmapNotify             18
        #define MapNotify               19
        #define MapRequest              20
        #define ReparentNotify          21
        #define ConfigureNotify         22
        #define ConfigureRequest        23
        #define GravityNotify           24
        #define ResizeRequest           25
        #define CirculateNotify         26
        #define CirculateRequest        27
        #define PropertyNotify          28
        #define SelectionClear          29
        #define SelectionRequest        30
        #define SelectionNotify         31
        #define ColormapNotify          32
        #define ClientMessage           33
        #define MappingNotify           34
        #define GenericEvent            35
        */
        XNextEvent(dis ,&event);
        switch (event.type)
        {
        case ClientMessage:
            closed = true;
            break;
        case //cases for other events
            }
    }
    return;
}
void newBlankWindow(int x, int y, int z)
{
    unsigned int white = WhitePixel(dsp,screen);
    numbers = (int*) realloc (frontx, x *sizeof(int));
    fronty = (int*) realloc (fronty, y *sizeof(int));
    dis = XOpenDisplay(NULL);
    win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 1, 1, x, y, \
                              0, BlackPixel (dis, 0), BlackPixel(dis, 0));
    XMapWindow(dis, win);
    XFlush(dis);
    Atom wmDelete=XInternAtom(dis, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(dis, win, &wmDelete, 1);
    std::thread (checkEvents).detach();
    gc = XCreateGC(dis, win,
                 0,
                 NULL);

    XSetForeground(dis, gc, BlackPixel (dis, 0));
}

void grabPointer()
{

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
    //junk v
    int jk = 0;
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
            //need knowledge on what w does
            if (iss)
            {
                iss >> v.w;
            }
            else
            {
                v.w = 1;
            }
            object.points.push_back(v);
            object.vcount++;
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
        if(filepath.substr(0,2).compare("s "))
        {
            continue;
        }
        if(filepath.substr(0,2).compare("g "))
        {
            continue;
        }
        if(filepath.substr(0,3).compare("vn "))
        {
            //need knowledge on what vn is
            object.vncount++;
        }
        if(filepath.substr(0,2).compare("s "))
        {
            continue;
        }
        if(filepath.substr(0,2).compare("f "))
        {
            filepath+=" ";
            filepath = filepath.substr(2, filepath.length() - 2);
            bool first = true;
            for(int i = 0; !filepath.compare(""); i++)
            {
                if(first)
                {
                    int slashLoc = filepath.find("/");
                    int line = std::stoi(filepath.substr(0, slashLoc));
                    filepath = filepath.substr(filepath.find(" ") + 1, filepath.length() - filepath.find(" ") + 1);
                    point3d line1 = object.points[line-1];
                    object.lines[jk][i].x1 = line1.x;
                    object.lines[jk][i].y1 = line1.y;
                    object.lines[jk][i].z1 = line1.z;
                    int slashLoc = filepath.find("/");
                    int line = std::stoi(filepath.substr(0, slashLoc));
                    filepath = filepath.substr(filepath.find(" ") + 1, filepath.length() - filepath.find(" ") + 1);
                    object.lines[jk][i].x2 = line1.x;
                    object.lines[jk][i].y2 = line1.y;
                    object.lines[jk][i].z2 = line1.z;
                }
                else
                {
                    object.lines[jk][i].x1 = object.lines[i-1].x2;
                    object.lines[jk][i].z1 = object.lines[i-1].z2;
                    object.lines[jk][i].y1 = object.lines[i-1].y2;
                    int slashLoc = filepath.find("/");
                    int line = std::stoi(filepath.substr(0, slashLoc));
                    filepath = filepath.substr(filepath.find(" ") + 1, filepath.length() - filepath.find(" ") + 1);
                    object.lines[jk][i].x2 = line1.x;
                    object.lines[jk][i].y2 = line1.y;
                    object.lines[jk][i].z2 = line1.z;
                }
                first = false;
            }
        }
        jk++;
    }
    return object;
}

static void renderPixel(int x, int y) {
    XDrawPoint(dsp, win, gc, x, y);
}

static void render() {
    XClearWindow(dis, win);
}

void displayOBJ(OBJ toDisplay, bool shaderEnable)
{
    //calculate 2D view and display pixels with correct colors. Darken colors for the farther they are IF shade is true.
    //darkness formula with col beinnnng a int inn hex format ((col & 0x7E7E7E) >> 1) | (col & 0x808080)
    for(int i = 0; i< object.lines.size(); i++) {
      for (int k = 0; k < object.lines[i].size(); k++) {
        //calculate what pixels to display
        if(frontx[object.lines[i][k].x1] < object.lines[i][k].z1 && fronty[object.lines[i][k].y1] < object.lines[i][k].z1) {
            double ys = object.lines[i][k].y1 - object.lines[i][k].y2;
            double xs = object.lines[i][k].x1 - object.lines[i][k].x2;        
            //for() {
                //to be finished
            //}
        }
    }
    render();
}
void removeOBJ(int toRemove)
{
    scene.erase(toRemove);
    render();
}
#endif
