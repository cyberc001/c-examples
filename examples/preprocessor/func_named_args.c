#include <stdio.h>
#include <math.h>

#define poly2_log_error 1 // печатаем ошибку
#define poly2_nan 	2 // возвращаем NaN

struct _poly2_args{double a, b, c; int mode; double* out;};

#define poly2(...)\
	_poly2((struct _poly2_args){.a = 0, .b = 0, .mode = poly2_nan, __VA_ARGS__})

void _poly2(struct _poly2_args args)
{
	double a = args.a, b = args.b, c = args.c;
	int mode = args.mode; double* out = args.out;
	if(a == 0 && b == 0){
		if(c != 0){
			if(mode == poly2_log_error)
				printf("ERROR: c != 0, but a = b = 0\n");
			out[0] = out[1] = NAN;
			return;
		}
		else{
			if(mode == poly2_log_error)
				printf("ERROR: any solution is possible\n");
			out[0] = out[1] = NAN;
			return;
		}
	}

	double d = b*b - 4*a*c;
	if(d < 0){
		if(mode == poly2_log_error)
			printf("ERROR: D < 0\n");
		out[0] = out[1] = NAN;
	}
	else if(d == 0){
		out[0] = out[1] = -b / (2*a);
	}
	else{
		out[0] = (-b + sqrt(d)) / (2*a);
		out[0] = (-b - sqrt(d)) / (2*a);
	}
}

int main()
{
	double o[2];
	poly2(.c = 1, .out = o);
	poly2(0, 0, 1, poly2_log_error, o);
}
