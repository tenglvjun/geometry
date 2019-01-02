
#include "window.h"
#include "setting.h"
#include "tools.h"
#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
    GeoSetting::GetInstance()->Init("setting.json");
    GeoWindow window("geometry");

    window.CreateGeoWindow();
    window.ShowGeoWindow();

    return 0;
}
