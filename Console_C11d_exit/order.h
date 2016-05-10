#pragma once

#include <iostream>
using namespace std;
class Order
{
private:
	int ordernumber;
	int itemnumber;
	int quantity;
	friend ostream& operator<<(ostream& os, const Order& order);
public:
	Order(void);
	Order(int on, int in, int q);
	~Order(void);
};
