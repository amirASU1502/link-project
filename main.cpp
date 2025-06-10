#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "motor.h"
#include "functions2.h"
using namespace std;

int main()
{   
    //part 1
    Material selected = getMaterial(materials);
    CrossSection link = getCrossSection(selected);
    Optimizer optimizer;
    optimizer.optimize(link, selected.yieldpoint);
    
    calculations calc(link);
    calc.get_Required_motor();
}
