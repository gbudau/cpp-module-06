#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>

struct	Data {
	char	*s1;
	int		n;
	char	*s2;
};

char	*make_rand_str(size_t len) {
	const char	charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							"abcdefghijklmnopqrstuvwxyz";
	static bool	seeded = false;
	char		*str = new char[len + 1];

	if (!seeded) {
		std::srand(std::time(nullptr));
		seeded = true;
	}
	for (size_t i = 0; i < len; i++) {
		int	r = rand() % (sizeof(charset) - 1);
		str[i] = charset[r];
	}
	str[len] = '\0';
	return str;
}

void	*serialize(void)  {
	char		*buff = new char[sizeof(char *) + sizeof(int) + sizeof(char *)];
	static bool	seeded = false;
	const char	max_str_len = 64;
	char		*str;
	int			rand_int;

	if (!seeded) {
		std::srand(std::time(nullptr));
		seeded = true;
	}
	rand_int = 1 + std::rand() % (max_str_len - 1);
	str = make_rand_str(rand_int);
	*reinterpret_cast<int64_t *>(buff) = reinterpret_cast<int64_t>(str);
	std::cout << "Random string s1: " << str << "\n";
	rand_int = std::rand();
	*reinterpret_cast<int *>(buff + sizeof(char *)) = rand_int;
	std::cout << "Random int n: " << rand_int << "\n";
	rand_int = 1 + std::rand() % (max_str_len - 1);
	str = make_rand_str(rand_int);
	std::cout << "Random string s2: " << str << "\n";
	*reinterpret_cast<int64_t *>(buff + sizeof(char *) + sizeof(int)) =
												reinterpret_cast<int64_t>(str);
	return buff;
}

Data	*deserialize(void *raw) {
	Data	*data = new Data;

	data->s1 = reinterpret_cast<char *>(*reinterpret_cast<int64_t *>(raw));
	data->n = *(reinterpret_cast<int *>(
							reinterpret_cast<char *>(raw) + sizeof(char *)));
	data->s2 = reinterpret_cast<char *>(*reinterpret_cast<int64_t *>(
				reinterpret_cast<char *>(raw) + sizeof(char *) + sizeof(int)));
	return data;
}

int	main() {
	void	*serialized_data = serialize();
	Data	*deserialized_data = deserialize(serialized_data);

	std::cout << "\nDeserialized data:\n";
	std::cout << deserialized_data->s1 << "\n";
	std::cout << deserialized_data->n << "\n";
	std::cout << deserialized_data->s2 << "\n";

	delete deserialized_data;
	delete [] static_cast<char *>(serialized_data);
}
