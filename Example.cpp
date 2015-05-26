#include "Linux.h"

int main() {
    newBlankWindow(500, 500);
    while (!closed) {
	std::cout << "Opening OBJ\n";
	OBJ toLoad = openOBJ("/home/user/cube.obj");
        displayOBJ(toLoad);
        std::cout << "Displayed\n";
        sleep(500);
        removeOBJ(0);
    }
    return(0);
}
