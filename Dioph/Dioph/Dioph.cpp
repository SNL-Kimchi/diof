#include <iostream>
using namespace std;
int abs(int a) {
	if (a < 0)
		return -a;
	return a;
}
int max(int a, int b) {
	if (a > b)
		return a;
	return b;
}
int min(int a, int b) {
	if (a > b)
		return b;
	return a;
}
void swap(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}
int gcd(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool fir_point(int a, int b, int c, int& x0, int& y0, int& g) {
	g = gcd(abs(a), abs(b), x0, y0);
	if (c % g != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0)   x0 *= -1;
	if (b < 0)   y0 *= -1;
	return true;
}
void res_replace(int& x, int& y, int a, int b, int cnt) {
	x += cnt * b;
	y -= cnt * a;
}

int search(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
	int x, y, g;
	if (!fir_point(a, b, c, x, y, g)) {
		cout << "wrong";
		return 0;
	}
	a /= g;  b /= g;

	int ba = a > 0 ? +1 : -1;
	int bb = b > 0 ? +1 : -1;

	res_replace(x, y, a, b, (minx - x) / b);
	if (x < minx) {
		res_replace(x, y, a, b, bb);
	}
	if (x > maxx) {
		return 0;
	}
	int lx1 = x;

	res_replace(x, y, a, b, (maxx - x) / b);
	if (x > maxx) {
		res_replace(x, y, a, b, -bb);
	}
	int rx1 = x;

	res_replace(x, y, a, b, -(miny - y) / a);
	if (y < miny) {
		res_replace(x, y, a, b, -ba);
	}
	if (y > maxy) {
		return 0;
	}
	int lx2 = x;

	res_replace(x, y, a, b, -(maxy - y) / a);
	if (y > maxy) {
		res_replace(x, y, a, b, ba);
	}
	int rx2 = x;

	if (lx2 > rx2) {
		swap(lx2, rx2);
	}
	int lef = max(lx1, lx2);
	int rig = min(rx1, rx2);
	cout << "X range output: " << endl;
	for (int z = rig; z <=  lef; z++) {
		for (int i = miny; i < maxy; i++) {
			if (((a * i) + (b * z)) == c) {
				cout << "x: " << i << " | "  << "y: "  << z << endl;
			}
		}
	}
	cout << "Y range output: " << endl;
	for (int i = rig; i <= lef; i = i + 1) {
		for (int z = miny; z < maxy; z = z + 1) {
			if (((a * i) + (b * z)) == c) {
				cout << "x: " << i << " | " << "y: " << z << endl;
			}
		}
	}
}

int main()
{
	cout << "input order:   1.a" << endl;
	cout << "               2.b" << endl;
	cout << "               3.c" << endl;
	cout << "search range:  4. x - min" << endl;
	cout << "               5. x - max" << endl;
	cout << "               6. y - min" << endl;
	cout << "               7. y - max" << endl;
	int a,b,c,minx,maxx,miny,maxy;
	cin >> a >> b >> c >> minx >> maxx >>  miny >> maxy;
	if ((a == 0) &(b == 0)) {
		cout << "uncertainty: a=b=0";
		return 0;
	}
	if (((a == 0) & (b != 0))) {
		if (((minx <= (c / b)) & (maxx >= (c / b))) & (c%b==0)) {
			cout << "x: " << c / b << " | " << "y: " << 0;
			return 0;
		}
		return 0;
	}
	else if (((a != 0) & (b == 0))) {
		if (((miny <= (c / a)) & (maxy >= (c / a))) & (c%a==0)) {
			cout << "x: " << 0 << " | " << "y: " << c/a;
			return 0;
		}
		return 0;
	}
	else {
		search(a, b, c, minx, maxx, miny, maxy);
	}
}
