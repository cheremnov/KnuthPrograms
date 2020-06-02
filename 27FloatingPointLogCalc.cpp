#include <cmath>
#include <cfenv>
#include <cassert>
#include <iostream>
#include <limits>
namespace logarithm_calculate{
	enum { LOG_BASE = 2 };
	/*
		Calculate the max possible approximation error
		log_arg - logarithm is calculated for the log_arg
	*/
	double calcMaxEps(float log_arg){
		assert(("Incorrect value", log_arg >= 1 && log_arg < 2));
		const int MANTISSA_BITS = std::numeric_limits<float>::digits;
		float eps = 0, calc_log = 0, subst_num=log_arg / 2;
		// Standard C calculation
		double true_log = log(log_arg) / log(LOG_BASE);
		// Using algorithm, calculate logarithm
		for(int i = 0; i < MANTISSA_BITS; ++i){
			if( log_arg - subst_num > 1 ){
				log_arg -= subst_num;
				calc_log += log((float) (1 << (i + 1) ) / 
					(float) ((1 << (i + 1)) - 1)) / log(LOG_BASE);
			}
			subst_num /= 2;
			// sum all the logarithm
		}
		std::cout << std::fixed << calc_log << " " << true_log << std::endl;
		// Calculating max(| calc_expr - 1 |), 
		// calc_expr < 1, thus round it down (to float)
		std::fesetround(FE_DOWNWARD);
		eps = calc_log / ((float) true_log);
		eps = 1 - eps;
		return eps;
	}
}
int main(){
	//std::cout << std::numeric_limits<float>::digits << std::endl;
	float log_arg;
	std::cin >> log_arg;
	std::cout << logarithm_calculate::calcMaxEps(log_arg);
	return 0;
}