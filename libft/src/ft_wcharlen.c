#include "libft.h"
#include <wchar.h>

int		ft_wcharlen(wchar_t wc)
{
	if (wc <= 0x7F)
		return (1);
	else if (wc <= 0x7FF)
		return (2);
	else if (wc <= 0x7FFFF)
		return (3);
	else if (wc <= 0x10FFFF)
		return (4);
	else
		return (-1);
}
