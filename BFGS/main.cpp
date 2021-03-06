﻿/**
 * alglibを使った、L-BFGS のテスト
 *
 * 以下の関数の最小値を求める。
 * f(x) = 100*(x0+3)^4 + (x1-3)^4 + (x2+1)^2
 * 解は、[-3, 3, -1]。
 *
 * @author Gen Nishida
 * @date 4/15/2015
 */

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "optimization.h"

using namespace alglib;
void function1_grad(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr)  {
    //
    // 関数の値を計算する： f(x0,x1) = 100*(x0+3)^4 + (x1-3)^4 + (x2+1)^2
    // また、偏微分も計算する：df/dx0, df/dx1, df/dx2
    //
    func = 100*pow(x[0]+3,4) + pow(x[1]-3,4) + pow(x[2]+1,2);
    grad[0] = 400*pow(x[0]+3,3);
    grad[1] = 4*pow(x[1]-3,3);
	grad[2] = 2*(x[2]+1);

	printf("Cost: %lf\n", func);
}

int main(int argc, char **argv) {
    real_1d_array x = "[0,0,0]";		// 初期値

    double epsg = 0.0000000001;
    double epsf = 0;
    double epsx = 0;
    ae_int_t maxits = 400;				// 最大繰り返し数
    minlbfgsstate state;
    minlbfgsreport rep;

    minlbfgscreate(1, x, state);
    minlbfgssetcond(state, epsg, epsf, epsx, maxits);
    alglib::minlbfgsoptimize(state, function1_grad);
    minlbfgsresults(state, x, rep);

	printf("----------------------------------------\n");
	if (rep.terminationtype < 0) {
		printf("Some error occured.\n");
	} else if (rep.terminationtype == 1) {
		printf("Function is converged.\n");
	} else if (rep.terminationtype == 2) {
		printf("Step is converged.\n");
	} else if (rep.terminationtype == 4) {
		printf("Gradient is converged.\n");
	} else if (rep.terminationtype == 5) {
		printf("MaxIts steps was taken.\n");
	} else if (rep.terminationtype == 7) {
		printf("Converged.\n");
	} else {
		printf("Unknown return type: %d\n", rep.terminationtype);
	}
    printf("Solution: %s\n", x.tostring(2).c_str());

	return 0;
}