#pragma once

#include <vector>

class integral {

private:
    double input_val;
    double output_val;
    int id;
    static int N_integrals;


public:
    integral(double init_cond=0.0);
    void insert_input(double val);
    double get_output();
    double get_input();
    void set_output(double val);
    static int get_N_integrals();
    int get_id();

    static std::vector<class integral*> instances;
};
