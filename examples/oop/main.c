#include <stdio.h>
#include "vec3.h"

void vec_process(vec2d* v)
{
	printf("%lf\n", vec2d_length(v));
}

int main()
{
	vec2d_init();
	vec3d_init();

	//vec2d* v1 = vec2d_new(1.2, -5.8);
	vec3d* v1 = vec3d_new(1.2, -5.8, -2.5);

	vec_process((vec2d*)v1);
}
