#pragma once

#include "integral.h"
#include "integral_solver.h"
#include "Interpolate1d.h"
#include <stdio.h>

// Here create some input vectors with intepolation to declare input function F(t)
std::vector<double> x = { 0.,1.,2.,3.,4. };
std::vector<double> y = { 10,1.,-5.,3.,40.0 };

interp1dlin aint(x, y);


// This is what user must code. His/Her ODE function...
integral x0(1.0), x1;   //the integrator for use with IC
void my_ode( double t , dict& outputs) {
    double x0dot = x1.get_output()+aint(t);
    double x1dot = -sin(x0.get_output()) - 1 * x1.get_output() + 1 * sin(x1.get_output() * t);

    x0.insert_input(x0dot);
    x1.insert_input(x1dot);

    outputs["x0dot"] = x0dot;
    outputs["x1dot"] = x1dot;
    outputs["_time"] = t;

    outputs["x0"] = x0.get_output();
    outputs["x1"] = x1.get_output();

    outputs["custom"] = t * t * 100 - 10;

};

int main(int argc, char** argv) {


    std::string name = "my_outputs.csv";

    //This creates the time vector
    state_type t(101,0);
    for (int i = 1; i < t.size(); i++) {
        t[i] = t[i - 1] + 0.01;
    };
    
    //This solves the ODE and returns results to Dictionary/Map
    output_dict mat=my_solver(my_ode, t);


    // Here Prints the Outputs:
    /*
    * for (int j = 0; j < keys.size(); j++) {
        std::cout << keys[j] << "\t";
    };
    std::cout << std::endl;

    for (int i = 0; i < t.size(); i++) {

        std::cout << "time: " << "\t";

        for (int j = 0; j < keys.size(); j++) {
            std::cout << mat[keys[j]][i] << "\t";
        }

        std::cout << std::endl;

    };
    */
    
    // This Function export Outputs in CSV file
    if (argc >= 2) {
        name = argv[1];
    };
    write_results(name, mat);

};




