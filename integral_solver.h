#pragma once
//The Solution Function
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <fstream>


std::vector<std::string> keys;



//typedef boost::numeric::ublas::matrix<double> mat_out;

namespace odeint = boost::numeric::odeint;
typedef boost::numeric::ublas::vector<double> state_type;
typedef boost::numeric::ublas::matrix<double> mat_out;

typedef std::map<std::string, double>  dict;
typedef std::map<std::string, std::vector<double>>  output_dict;

dict outputs;
struct ODE
{
    void (*func)(double t, dict& outputs);

    ODE(void(*fun)(double t, dict& outputs)){
        func = fun;
    };

    void operator()(const state_type& x,
        state_type& dxdt, double t) const
    {
        for (int i = 0; i < integral::get_N_integrals(); i++) {
            integral::instances[i]->set_output(x[i]);
        };

        func(t, outputs);

        for (int i = 0; i < integral::get_N_integrals(); i++) {
            dxdt[i] = integral::instances[i]->get_input();
        };

    }
};



output_dict my_solver(void(*fun)(double t, dict& outputs),state_type time_vector) {

    odeint::runge_kutta4 <state_type > stepper;

    ODE p(fun);

    int N = integral::get_N_integrals();

    state_type x(N, 0);

    output_dict returns_dict;

    boost::numeric::ublas::matrix<double> output_mat(time_vector.size(), N);
    
    for (int i = 0; i < N; i++) {

        x[i] = integral::instances[i]->get_output();

        output_mat(0,i) = 1.0;

    }; 

    //std::cout << time_vector[0] << " " << x[0] << " " << x[1] << "\n";
    double dt;

    p.func(time_vector[0], outputs);

    for (auto it = outputs.begin(); it != outputs.end(); it++) {
        keys.push_back(it->first);
    };

    for (int it = 0; it < keys.size(); it++) {
        returns_dict[keys[it]].push_back(outputs[keys[it]]);
    };


    for (int i = 1; i < time_vector.size(); i++) {


        dt = time_vector[i] - time_vector[i - 1];
 
        stepper.do_step(p, x, time_vector[i-1], dt);

        //p.func(time_vector[i], outputs);

        for (int j = 0; j < N; j++) {
            integral::instances[j]->set_output(x[j]);
            //output_mat(i, j) = x[j];
        };

        
        for (int it = 0; it < keys.size(); it++) {
            returns_dict[keys[it]].push_back(outputs[keys[it]]);
        };

    }

    /*
        for (int i = 0; i < output_mat.size1(); i++) {
        for (int j = 0; j < output_mat.size2(); j++) {
            std::cout << output_mat(i, j) << "\t";
        };
        std::cout << std::endl;
    };

    */

    return returns_dict;
};


int pos;
void write_results(std::string myPath, output_dict res) {

    std::fstream myFile;
    myFile.open(myPath, std::ios::out);

    for (int k = 0; k < keys.size(); k++) {
        myFile << keys[k] << ",";
    };

    pos = myFile.tellp();
    myFile.seekp(pos - 1);

    myFile << std::endl;

    for (int i = 0; i < res[keys[0]].size(); i++) {
        for (int k = 0; k < keys.size(); k++) {
            myFile << res[keys[k]][i] << ",";
        };
        
        pos = myFile.tellp();
        myFile.seekp(pos - 1);
        myFile << std::endl;
        
    };

    //myFile << keys[keys.size()-1] << std::endl;

};