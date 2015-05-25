#include "Linux.h"
int main() {
    newBlankWindow(500, 500, 500);
    while (!closed) {
        displayOBJ(openOBJ("/home/user/test.obj"), true, 200, 300, 200, 300, 250, 150);
        sleep(500);
        removeOBJ(0);
    }
    return(0);
}
