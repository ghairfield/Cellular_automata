#include <iostream>
#include "display.h"

int main() {
    Display d;
    int ret = 0;
    ret = (d.Run()) ? 0 : 1;
    d.OnDestroy();

    return ret;
}