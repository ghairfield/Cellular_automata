#include <iostream>
//#include "display.h"
#include "cgl.h"

int main() {
    //Display d;
    CGL d;
    int ret = 0;
    ret = (d.Run()) ? 0 : 1;
    d.OnDestroy();

    return ret;
}