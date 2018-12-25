@call "%VS150COMNTOOLS%VsDevCmd.bat"

if not exist build (
    mkdir build
)

cd build

echo **********************************************************************
echo ** CMake -G Visual Studio 15 2017 Win64 build type %1
echo **********************************************************************
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=%1 ..

echo Building

if "%1" == "" (
    echo build default
    msbuild geometry.sln
) else (
    echo build %1
    msbuild geometry.sln /p:Configuration=%1
)

echo Done

cd ..