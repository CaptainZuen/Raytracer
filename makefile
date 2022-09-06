s := Source/
ss := Source/Source/
so := Source/.o/

output: $(so)main.o $(so)vec3D.o $(so)ray.o $(so)objects.o $(so)rayScanner.o $(so)io.o
	g++ -std=c++17 -pthread $(so)main.o $(so)vec3D.o $(so)ray.o $(so)objects.o $(so)rayScanner.o $(so)io.o -o rayTracer

$(so)main.o: $(s)main.cpp $(s)main.hpp
	g++ -o $(so)main.o -c $(s)main.cpp

$(so)vec3D.o: $(ss)vec3D.cpp $(s)vec3D.hpp
	g++ -o $(so)vec3D.o -c $(ss)vec3D.cpp

$(so)ray.o: $(ss)ray.cpp $(s)ray.hpp
	g++ -o $(so)ray.o -c $(ss)ray.cpp

$(so)objects.o: $(ss)objects/objects.cpp $(s)objects.hpp
	g++ -o $(so)objects.o -c $(ss)objects/objects.cpp

$(so)rayScanner.o: $(ss)rayScanner.cpp $(s)rayScanner.hpp
	g++ -o $(so)rayScanner.o -c $(ss)rayScanner.cpp

$(so)io.o: $(ss)io.cpp $(s)io.hpp
	g++ -o $(so)io.o -c $(ss)io.cpp

clean:
	del rayTracer.exe
	cd $(so) && del *.o