#include <stdio.h>
#include <stdint.h>
#include "tinyexpr.h"

double my_low(double a) {
	uint16_t i;
	i = (uint16_t)a;
	return (double)(i & 0x00ff);
}
double my_high(double a) {
	uint16_t i;
	i = (uint16_t)a;
	return (double)((i & 0xff00) >> 8);
}

int main()
{
	double x, result;
	int err = 0;
	te_variable vars[] = {
		{"my_low", my_low, TE_FUNCTION1},
		{"my_high", my_high, TE_FUNCTION1},
		{"x", &x}
	};
	char *strval = "0x3322";
	char expr[100];
	sprintf(expr, "my_high(%s)", strval);

	te_expr *n = te_compile(expr, vars, 3, &err);
	te_expr *m = te_compile("my_low(x)", vars, 2, &err);
	te_expr *o = te_compile("my_high(x)", vars, 3, &err);

	if (o) {
		x = 0x3322;
		result = te_eval(o);
		printf("result %x\n", (uint16_t)result);
	} else {
		printf("error...%d \n", err);
	}
	printf("%x \n", (0x3322 & 0xff00) >> 8);

	err = 0;
	double y = 0x08;
	double c = te_interp("0x08 << 1", &err);
	if (!err) {
		printf("interp: %x\n", (uint16_t)c);
	} else {
		printf("error: %d\n", err);
	}

}



	
	
