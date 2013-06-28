#include <iostream>

/*
GS_Component: abstract base class for every component
*/
class GS_Component
{
public:
	virtual void read_data() = 0;
	virtual void calculate() = 0;
	virtual void check_streams() = 0;

protected:
	int nStreamsIn;
};

class GS_Int : public GS_Component
{
public:
	void calculate() { std::cout << "I'm an intermediate!" << std::endl; }
	virtual void calculate(int a) { std::cout << "I'm an intermediate! int a" << std::endl; }
	virtual void read_data() {}
	virtual void check_streams() {}
};

class GS_Pump : public GS_Int
{
public:
	//virtual void calculate() { std::cout << "I'm a pump!" << std::endl; }
	virtual void calculate(int a) { std::cout << "I'm a pump! int a" << std::endl; }
	virtual void read_data() {}
	virtual void check_streams() {}
	void test() { std::cout << "test pump" << std::endl; }
};

class GS_G : public GS_Pump
{
public:
	void test() { std::cout << "test G" << std::endl; }
};