#include <strings.h>
#include <cstdlib>
#include <cerrno>
#include <cctype>
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

bool	str_to_int(int & i, std::string const & s) {
	char	*end;
	long	l;

	errno = 0;
	l = std::strtol(s.c_str(), &end, 10);
	if (errno) {
		return false;
	}
	if (*end ||
			l < std::numeric_limits<int>::min() ||
			l > std::numeric_limits<int>::max()) {
		return false;
	}
	i = static_cast<int>(l);
	return true;
}

bool	str_to_float(float & f, std::string const & s) {
	char	*end;

	errno = 0;
	f = strtof(s.c_str(), &end);
	if (errno || *end != 'f' || s.length() < 2) {
		return false;
	}
	end++;
	if (*end) {
		return false;
	}
	return true;
}

bool	str_to_double(double & d, std::string const & s) {
	char	*end;

	errno = 0;
	d = std::strtod(s.c_str(), &end);
	if (errno || s == "f") {
		return false;
	}
	if (*end == 'f') {
		end++;
	}
	if (*end) {
		return false;
	}
	return true;
}

bool	is_positive_inf(std::string const & str) {
	return str == "+inf" || str == "+inff";
}

bool	is_negative_inf(std::string const & str) {
	return str == "-inf" || str == "-inff";
}

bool	is_nan(std::string const & str) {
	return str == "nan" || str == "nanf";
}

bool	is_strtod_special(std::string const & str) {
	return !strncasecmp(str.c_str(), "0x", 2) ||
		!strncasecmp(str.c_str(), "-0x", 3) ||
		!strncasecmp(str.c_str(), "+0x", 3) ||
		!strcasecmp(str.c_str(), "inf") ||
		!strcasecmp(str.c_str(), "inff") ||
		!strcasecmp(str.c_str(), "infinity") ||
		!strcasecmp(str.c_str(), "-infinity") ||
		!strcasecmp(str.c_str(), "+infinity") ||
		!strcasecmp(str.c_str(), "-nan") ||
		!strcasecmp(str.c_str(), "+nan") ||
		(!strcasecmp(str.c_str(), "nan") && str != "nan");
}

void	print_nan() {
	std::cout << "char: impossible\n"
				"int: impossible\n"
				"float: nanf\n"
				"double: nan\n";
}

void	print_positive_inf() {
	std::cout << "char: impossible\n"
				"int: impossible\n"
				"float: +inff\n"
				"double: +inf\n";
}

void	print_negative_inf() {
	std::cout << "char: impossible\n"
				"int: impossible\n"
				"float: -inff\n"
				"double: -inf\n";
}

void	convert_char(char c) {
	int		i;
	float	f;
	double	d;

	if (std::isprint(c)) {
		std::cout << "char: \'" << c << "\'\n";
	} else {
		std::cout << "char: Non displayable\n";
	}
	i = static_cast<int>(c);
	std::cout << "int: " << i << "\n";
	f = static_cast<float>(c);
	std::cout << std::fixed;
	std::cout << "float: " << std::setprecision(1) << f << "f\n";
	d = static_cast<double>(c);
	std::cout << "double: " << std::setprecision(1) << d << "\n";
}

void	print_impossible() {
	std::cout << "char: impossible\n"
				"int: impossible\n"
				"float: impossible\n"
				"double: impossible\n";
}

void	convert_int(int i) {
	char	c;
	float	f;
	double	d;

	if (i < std::numeric_limits<char>::min() ||
			i > std::numeric_limits<char>::max()) {
			std::cout << "char: impossible\n";
	} else {
		c = static_cast<char>(i);
		if (std::isprint(c)) {
			std::cout << "char: \'" << c << "\'\n";
		} else {
			std::cout << "char: Non displayable\n";
		}
	}
	std::cout << "int: " << i << "\n";
	f = static_cast<float>(i);
	std::cout << std::fixed;
	std::cout << "float: " << std::setprecision(1) << f << "f\n";
	d = static_cast<double>(i);
	std::cout << "double: " << std::setprecision(1) << d << "\n";
}

void	convert_float(float	f, size_t precision) {
	char	c;
	int		i;
	double	d;

	if (f < std::numeric_limits<char>::min() ||
			f >= std::numeric_limits<char>::max() + 1) {
			std::cout << "char: impossible\n";
	} else {
		c = static_cast<char>(f);
		if (std::isprint(c)) {
			std::cout << "char: \'" << c << "\'\n";
		} else {
			std::cout << "char: Non displayable\n";
		}
	}
	i = static_cast<int>(f);
	if (static_cast<double>(f) < std::numeric_limits<int>::min() ||
			static_cast<double>(f) > std::numeric_limits<int>::max()) {
		std::cout << "int: impossible\n";
	} else {
		std::cout << "int: " << i << "\n";
	}
	std::cout << std::fixed;
	std::cout << "float: " << std::setprecision(precision) << f << "f\n";
	d = static_cast<double>(f);
	std::cout << "double: " << std::setprecision(precision) << d << "\n";
}

void	convert_double(double d, size_t precision) {
	char	c;
	int		i;
	float	f;

	if (d < std::numeric_limits<char>::min() ||
			d >= std::numeric_limits<char>::max() + 1) {
			std::cout << "char: impossible\n";
	} else {
		c = static_cast<char>(d);
		if (std::isprint(c)) {
			std::cout << "char: \'" << c << "\'\n";
		} else {
			std::cout << "char: Non displayable\n";
		}
	}
	i = static_cast<int>(d);
	if (d < std::numeric_limits<int>::min() ||
			d > std::numeric_limits<int>::max()) {
		std::cout << "int: impossible\n";
	} else {
		std::cout << "int: " << i << "\n";
	}
	f = static_cast<float>(d);
	std::cout << std::fixed;
	if (f < -std::numeric_limits<float>::max() ||
			f > std::numeric_limits<float>::max()) {
		std::cout << "float: impossible\n";
	} else {
		std::cout << "float: " << std::setprecision(precision) << f << "f\n";
	}
	std::cout << "double: " << std::setprecision(precision) << d << "\n";
}

size_t	float_precision(std::string const & arg) {
	size_t	precision = 1;

	if (arg.find('.') != std::string::npos &&
			arg.find('f') != std::string::npos) {
		precision = arg.find('f') - arg.find('.');
		precision = precision > 1 ? precision - 1 : precision;
	}
	return precision;
}

size_t	double_precision(std::string const & arg) {
	size_t	precision = 1;

	if (arg.find('.') != std::string::npos) {
		precision = arg.length() - arg.find('.');
		precision = precision > 1 ? precision - 1 : precision;
	}
	return precision;
}

void	convert_arg(std::string const & arg) {
	int		i;
	float	f;
	double	d;

	if (is_strtod_special(arg) || std::isspace(*arg.c_str())) {
		print_impossible();
	} else if (is_nan(arg)) {
		print_nan();
	} else if (is_positive_inf(arg)) {
		print_positive_inf();
	} else if (is_negative_inf(arg)) {
		print_negative_inf();
	} else if (str_to_int(i, arg)) {
		convert_int(i);
	} else if (str_to_float(f, arg)) {
		convert_float(f, float_precision(arg));
	} else if (str_to_double(d, arg)) {
		convert_double(d, double_precision(arg));
	} else if (arg.length() == 1) {
		convert_char(*arg.c_str());
	} else {
		print_impossible();
	}
}

int	main(int argc, char **argv) {
	if (argc != 2 || !*argv[1]) {
		std::cout << "Usage: " << argv[0] <<
			" \"STRING\"\n";
		return 1;
	}
	convert_arg(argv[1]);
	return 0;
}
