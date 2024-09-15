#pragma once

#include <vector>

typedef std::vector<double> data_array;


class interp1dlin {

private:
    data_array xdata;
    data_array ydata;


public:
    interp1dlin(data_array x, data_array y);
    double operator()(double xi);
};
