## Usage

1. Install [OSRM backend library](https://github.com/Project-OSRM/osrm-backend)  
2. ```git clone``` the project  
3. Open CMakeLists.txt in the root and make sure the path is right for you  
4. Open main.cpp to make sure that you have plan_file2018.txt and .osrm file  
5. ```mkdir build``` in the root directory and ```cmake ..```, ```make```  

## Note 

* .osrm is created from  
```
osrm-extract *.osm.pbf -p profiles/car.lua
osrm-partition *.osrm
osrm-customize *.osrm
```

You can also replace the above with ```Generate_osrm *.osm.pbf car.lua```.

* plan_file2018.txt format:
```
100.000 40.000 90.0 2
longitude latitude height attribute
```

Attribute represents different points.
