#include "Linux.h"
int main() {
    newBlankWindow(500, 500, 500);
    while (!closed) {
        displayOBJ(openOBJ("/home/lukep/cube.obj"), true);
        sleep(500);
        removeOBJ(0);
    }
    return(0);
}
