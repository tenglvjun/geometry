
#include "window.h"
#include "setting.h"
#include "tools.h"
#include <iostream>
#include <vector>
#include "matrix.h"

int main(int argc, char const *argv[])
{
    // double data[] = {2, 3, 2, 1, 3, 2, 3, 4, 1};

    // GeoMatrix m(3, 3, data);

    // GeoMatrix up(3, 3);
    // GeoMatrix low(3, 3);

    // if (!m.LUDecompose(up, low))
    // {
    //     std::cout << "LUDecompose failed" << std::endl;
    //     return 0;
    // }
    // m.Dump();
    // std::cout << "=====================================" << std::endl;
    // up.Dump();
    // std::cout << "=====================================" << std::endl;
    // low.Dump();

    GeoSetting::GetInstance()->Init("setting.json");
    GeoWindow window("geometry");

    window.CreateGeoWindow();
    window.ShowGeoWindow();

    return 0;
}
