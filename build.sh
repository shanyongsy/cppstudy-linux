cmake CMakeLists.txt -B _build/
cd _build
make
cp hello ../install
cp ./generated/version.h ../include/
cd ..
