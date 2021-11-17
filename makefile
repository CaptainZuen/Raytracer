output: main.o vec3D.o ray.o objects.o rayScanner.o io.o
	g++ -std=c++17 main.o vec3D.o ray.o objects.o rayScanner.o io.o -o rayTracer

main.o: main.cpp main.hpp
	g++ -c main.cpp

vec3D.o: vec3D.cpp vec3D.hpp
	g++ -c vec3D.cpp

ray.o: ray.cpp ray.hpp
	g++ -c ray.cpp

objects.o: objects.cpp objects.hpp
	g++ -c objects.cpp

rayScanner.o: rayScanner.cpp rayScanner.hpp
	g++ -c rayScanner.cpp

io.o: io.cpp io.hpp
	g++ -c io.cpp

clean:
	del *.o rayTracer