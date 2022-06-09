#include "basic_functions.hpp"

namespace fr::math {
    float q_rsqrt(float number) {  
        // Fast inverse square root from Quake III: Arena
        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        y  = number;
        i  = * ( long * ) &y;                      
        i  = 0x5f3759df - ( i >> 1 );               // wtf?
        y  = * ( float * ) &i;
        y  = y * ( threehalfs - ( x2 * y * y ) );  

        return y;
    }
    float sqrt(float number){ if(number > 0){ for(float factor = 0; factor < number; factor++) { if(factor*factor == number) { return factor; } } } }

    float rad2deg(float rad) { return rad * 180 / PI; }
    float deg2rad(float deg) { return deg * PI / 180; }

    float abs(int num) { return num <= 0 ? 1 : num * fact(num - 1); }
    float abs(float num) { return (num < 0.0f) ? -num : num; }

    int fact(int n) { return n <= 0 ? 1 : n * fact(n - 1); }

    float power(float base, int exp) {if (exp < 0) {
		if (base == 0)
				return -0;
			return 1 / (base * power(base, (-exp) - 1));
		}
		if (exp == 0)
			return 1;
		if (exp == 1)
			return base;
		return base * power(base, exp - 1);
    }

    float sine(int deg){
        deg %= 360;
		float rad = deg * PI / 180;
		float sin = 0;
		for (int i = 0; i < 7; i++) {
			sin += power(-1, i) * power(rad, 2 * i + 1) / fact(2 * i + 1);
		}
		return sin;
    }

    float cosine(int deg){
        deg %= 360; // make it less than 360
		float rad = deg * PI / 180;
		float cos = 0;

		int i;
		for (i = 0; i < 7; i++) {
			cos += power(-1, i) * power(rad, 2 * i) / fact(2 * i);
		}
		return cos;
    }

    float tangent(int deg) { return sine(deg) / cosine(deg); }
    float cotangent(int deg) { return cosine(deg) / sine(deg); }
}