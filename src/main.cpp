
#include "window.h"
#include "setting.h"
#include "tools.h"
#include <iostream>
#include <vector>
#include "matrix.h"

int main(int argc, char const *argv[])
{
    GeoSetting::GetInstance()->Init("setting.json");

    // double data[] = {3, 4, 5, 11, 2, 5, 4, 9, 5, 3, 2, 12, 14, -11, 21, 29};

    // GeoMatrix m(4, 4, data);

    // std::cout << m.Det() << std::endl;

    GeoWindow window("geometry");

    window.CreateGeoWindow();
    window.ShowGeoWindow();

    return 0;
}
