#include <iostream>
#include <cstdlib>
#include <ctime>

class Base {
 public:
	virtual	~Base() {}
};

class A : public Base {
};

class B : public Base {
};

class C : public Base {
};

Base *	generate(void) {
	static bool	seeded = false;

	if (!seeded) {
		std::srand(std::time(nullptr));
		seeded = true;
	}
	int	r = rand() % 3;
	switch (r) {
		case 0:
			return new A;
		case 1:
			return new B;
		case 2:
			return new C;
		default:
			return 0;
	}
}

void	identify_from_pointer(Base * p) {
	A	*a_ptr = dynamic_cast<A *>(p);
	if (a_ptr) {
		std::cout << "A\n";
		return;
	}
	B	*b_ptr = dynamic_cast<B *>(p);
	if (b_ptr) {
		std::cout << "B\n";
		return;
	}
	C	*c_ptr = dynamic_cast<C *>(p);
	if (c_ptr) {
		std::cout << "C\n";
	}
}

void	identify_from_reference(Base & p) {
	identify_from_pointer(&p);
}

int	main() {
	Base *base_ptr = generate();

	std::cout << "Identify from pointer:\n";
	identify_from_pointer(base_ptr);
	std::cout << "Identify from reference:\n";
	identify_from_reference(*base_ptr);
	delete base_ptr;
}
