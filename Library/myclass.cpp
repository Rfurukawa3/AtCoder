
// pairの3要素版
template<typename T> struct trio {
	T a, b, c;

	trio(): a(0), b(0), c(0){}
	trio(T a, T b, T c) : a(a), b(b), c(c) {}
	trio(const trio& obj) : a(obj.a), b(obj.b), c(obj.c) {}

	trio operator = (const trio& obj) {
		this->a = obj.a;
		this->b = obj.b;
		this->c = obj.c;
		return *this;
	}
	bool operator == (const trio& obj) { return (this->a == obj.a) && (this->b == obj.b) && (this->c == obj.c); }
	bool operator != (const trio& obj) { return !(*this == obj); }
	bool operator < (const trio& obj) {
		if (this->a == obj.a) {
			if (this->b == obj.b) return this->c < obj.c;
			return this->b < obj.b;
		}
		return this->a < obj.a;
	}
	bool operator > (const trio& obj) {
		if (this->a == obj.a) {
			if (this->b == obj.b) return this->c > obj.c;
			return this->b > obj.b;
		}
		return this->a > obj.a;
	}
	bool operator <= (const trio& obj) { return !(*this > obj); }
	bool operator >= (const trio& obj) { return !(*this < obj); }
};

