#pragma once

#include "Interpolate1d.h"
#include <stdexcept>



interp1dlin::interp1dlin(data_array xin, data_array yin) {
    xdata = xin;
    ydata = yin;

    if (xdata.size() != ydata.size()) {
        throw std::invalid_argument("Sizes or vectors xin and yin are not equal...");
    };

    bool flag = false;

    for (int i = 1; i < xdata.size(); i++) {
        if (xdata[i] <= xdata[i - 1]) {
            flag = true;
        };
    };

    if (flag) {
        throw std::invalid_argument("X vector is not in ascending sequence...");
    }

};


double interp1dlin::operator()(double xi){
    
    //Keep extremes when out of bounds
    if (xi <= xdata[0]) {
        return ydata[0];
    };

    if (xi >= xdata[xdata.size() - 1]) {
        return ydata[xdata.size() - 1];
    };

    double val,a,b;
    for (int i = 1; i < xdata.size(); i++) {
        if (xi < xdata[i]) {

            a = (ydata[i] - ydata[i - 1]) / (xdata[i] - xdata[i - 1]);
            b = ydata[i] - a * xdata[i];
            val = a * xi + b;

            return val;
        };
    };
};
