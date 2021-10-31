//#define F_CPU 4000000UL

#ifndef F_CPU
#warning CPU frequency not defined
#define F_CPU 8000UL
#endif


void _delay_ms(unsigned ms)
{
	ms *= F_CPU / 1000;
	for(; ms > 0; --ms)
		;
}

int main()
{
	_delay_ms(1000);
}
