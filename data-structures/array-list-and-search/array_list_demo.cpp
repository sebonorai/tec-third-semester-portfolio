#include <iostream>

using namespace std;

const int MAX = 100;

class Lista {
private:
	int data [MAX];
	int size;
public:
	Lista() : size(0) {}
	void insert(int value) {
		if (size < MAX) {
			data[size] = value;
			size++;
		}
		else {
			cout << "Error: List is full" << endl;
		}
	}
	void erase() {
		if (size > 0) {
			cout << "Erasing value: " << data[size - 1] << endl;
			size--;
		}
		else {
			cout << "Error: List is empty" << endl;
		}
	}
	int getData(int pos) const {
		return data[pos];
	}
		int getSize() const {
			return size;
	}

		void print() const {
			for (int i = 0; i < size; i++) {
				cout << "[" << i << "] - "<< data[i] << endl;
			}
	}
};

int main() {
	Lista milista;
	milista.insert(154);
	milista.insert(587);
	milista.insert(874);

	cout << "Size of the list: " << milista.getSize() << endl;
	cout << "Actual List: " << endl;
	milista.print();
	cout << "Erasing last value..." << endl;
	milista.erase();
	cout << "First value of the list: " << milista.getData(0) << endl;
	return 0;
}
