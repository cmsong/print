#include <unistd.h>
#include <stdarg.h>

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_putstr(char *s)
{
	int i = 0;

	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int 	numlen(long int n)
{
	int i = 0;
	if (n < 0)
	{
		n /= 10;
		n *= -1;
		i += 2;
	}
	while(n > 0)
	{
		n /= 10;
		i++;
	}
	return i;
}

void	ft_putnbr(long int n) //TAKE LONG INT
{
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if ((n / 10) > 0)
	{
		ft_putnbr(n / 10);
	}
	ft_putchar((n % 10) + '0');
}

char	*convertBase(unsigned long int n, unsigned int base)
{
	static char *ref;
	static char buf[50];
	char		*s;

	ref = "0123456789abcdef";
	s = &buf[49];
	*s = '\0';
	while (n > 0)
	{
		*(--s) = ref[n % base];
		n /= base;
	}
	return s;
}

int		handleStr(va_list ap, char spec)
{
	char	*str;
	unsigned char	c;

	if (spec == 's')
	{
		str = va_arg(ap, char *);
		if (str == NULL)
		{
			ft_putstr("(null)");
			return (6);
		}
		return (ft_putstr(str));
	}
	else
	{
		c = (unsigned char)va_arg(ap, int);
		ft_putchar((char)c);
		return (1);
	}
}

int		handleDec(va_list ap, char spec)
{
	int				s_num;
	unsigned int	u_num;

	if (spec == 'd' || spec == 'i')
	{
		s_num = va_arg(ap, int);
		ft_putnbr(s_num);
		return (numlen(s_num));
	}
	else
	{
		u_num = (unsigned int)va_arg(ap, int);
		ft_putnbr(u_num);
		return (numlen(u_num));
	}
}

int		handleBase(va_list ap, char spec)
{
	int				base;
	unsigned int	u_num;
	unsigned long	ul;
	char			*str;

	base = (spec == 'x' || spec == 'p') ? 16 : 8;
	if (spec == 'o' || spec == 'x')
	{
		u_num = (unsigned int)va_arg(ap, int);
		str = convertBase(u_num, base);
		return (ft_putstr(str));
	}
	else
	{
		ul = (unsigned long)va_arg(ap, void *);
		str = convertBase(ul, 16);
		ft_putchar('0');
		ft_putchar('x');
		return (ft_putstr(str) + 2);
	}
}

int		ft_printf(const char *s, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, s);
	while (*s)
	{
		while (*s != '%' && *s)
			count += ft_putchar(*(s++));
		s++;
		if (*s && (*s == 's' || *s == 'c'))
			count += handleStr(ap, *s);
		else if (*s && (*s == 'd' || *s == 'i' || *s == 'u'))
			count += handleDec(ap, *s);
		else if (*s && (*s == 'o' || *s == 'x' || *s == 'p'))
			count += handleBase(ap, *s);
		else if (*s && (*s == '%'))
			count += ft_putstr("%");
		else
			break ;
		s++;
	}
	va_end(ap);
	return count;
}
