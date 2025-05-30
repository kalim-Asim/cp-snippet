
// • __builtin_clz(x): the number of zeros at the beginning of the number // -> high bit
// • __builtin_ctz(x): the number of zeros at the end of the number  // -> low bit
// • __builtin_popcount(x): the number of ones in the number
// • __builtin_parity(x): the parity (even or odd) of the number of ones // -> 1 for odd no. of ones

// no. of different pos
int hamming(int a, int b) {
return __builtin_popcount(a^b);
}

// subset generation { 0, 1, 2, ..., n-1 }
for (int b = 0; b < (1<<n); b++) {
	vector<int> subset;
	for (int i = 0; i < n; i++) {
		if (b&(1<<i)) subset.push_back(i);
	}
}

