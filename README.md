# CPE 400 Project
## Group
- Benjamin Estela
- Sidney Inouye
- Jonathon Hewitt

## Topic (#2)
**Dynamic routing mechanism design with focus on energy conservation.**

![projectInfo](https://user-images.githubusercontent.com/30031065/69931871-b9451000-147d-11ea-8a64-1d8bc6c2a93f.png)  

Create and simulate a sensor network. The objective is to increase the longevity of the network by using dynamic routing. Sensors are energy constrained and are not super powerful like common computers. Every time a sensor transmits some packets, it will decrease the amount of energy left. The team will create a dynamic routing scheme to try and maintain all nodes of the network online for as long as possible.  

### Implementation
In order to complete the project, a C++ project was created that runs 1000 tests of randomly created networks containing 20 nodes each. A graph class is created for use of the RIP algorithm as well as a modified RIP algorithm using BFS. Each test runs both RIP and "RIPBFS" where the source, destination, route, and energy array information are printed to the terminal. The main.cpp file initializes the values for the graph, test information, and results then aftewards, runs the simulation tests. The graph class information can be found in graph.h and graph.cpp where the test algorithms and constructors are. Lastly the makefile is used to compile the project and .gitignore is for the team to easily use a repository. To find more information, read the attached technical report in CPE400Paper.pdf.

## Build Instructions
Use make with the following commands:
```bash
mkdir build
cp makefile build
cd build
make
```

## Usage Instructions
To run the program, use the following command inside the build directory:
```bash
./cpe
```
