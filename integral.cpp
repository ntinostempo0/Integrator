#pragma once

#include "integral.h"


int integral::N_integrals;
std::vector<class integral*> integral::instances;

integral::integral(double init_cond) {
    output_val = init_cond;
    input_val = 0.0;
    id = ++N_integrals;
    instances.push_back(this);
};

void integral::insert_input(double val) {
    input_val = val;
};

double integral::get_output() {
    return output_val;
};

double integral::get_input() {
    return input_val;
};

void integral::set_output(double val) {
    output_val = val;
};


int integral::get_N_integrals() {
    return N_integrals;
};

int integral::get_id() {
    return id;
};









