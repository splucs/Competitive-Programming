template <typename T>
void circularconvolution(vector<T> a, vector<T> b, vector<T> & res) {
	int n = a.size();
	b.insert(b.end(), b.begin(), b.end());
	convolution(a, b, res);
	res = vector<T>(res.begin()+n, res.begin()+(2*n));
}