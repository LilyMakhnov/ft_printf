#include "ft_printf.h"
#include "limits.h"


int main()
{
//	int a = 5;
//	int *p = NULL;
	int i;

	i = printf("-->|%#5X|<--\n", 34);
	printf("%i\n", i);
	i = ft_printf("-->|%#5X|<--\n", 34);
	printf("%i\n", i);
	return (0);
}
