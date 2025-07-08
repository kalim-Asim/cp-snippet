
/*
	// op:1 => a[i] = x
	// op:2 => sum[l,r] = ?
	
	// rightmost bit set -> x & (-x)
	// to unset it -> x - (x & (-x))
	
	// (i, j) j = remove last of i, j = i - (i&(-i))
	// bit[i] => j+1->i tk ka sum
	
	// 12(i) = 1100 -> j = 1000(8) -> bit[12] = 9->12 tk ka sum
	// sum[1, 13] = bit[13] + bit[12] + bit[8]
*/	


// Binary Indexed Tree - Luv sir
const int N = 1e5+10;
int bit[N];

void update(int i, int x){
    for(; i < N; i += (i&-i))
        bit[i] += x;
}

int sum(int i){
    int ans = 0;
    for(; i > 0; i -= (i&-i))
        ans += bit[i];
    return ans;
}





/*
	Question 1 Given array of size N and Q querries Solve two type of quereies
	Type1 : i x : replace ith index by value x
	Type 2 : l r : find sum from l to r
*/
int main(){
    int n, q;
    cin >> n >> q;
    int a[n + 10];
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        update(i, a[i]);
    }

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int i, x; cin >> i >> x;
            update(i, x - a[i]);
            a[i] = x;
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << sum(r) - sum(l-1) << endl;
        }
    }
}




/*
	Question 2 find inversion count of array ((a[i] > a[j] and i < j)) how many i's are index j -> summation
*/
int main(){
    int n;
    cin >> n;
    long long a[n + 10];
    map<long long,int> mp;
    for(int i = 1;i <= n; ++i){
        cin >> a[i];
        mp[a[i]];
    }

    // compression of numbers for the case where a[i] > 10 ^ 6
    int ptr = 1;
    for(auto &pr : mp){
        pr.second = ptr++;
    }

    for(int i = 1; i <= n; ++i){
        a[i] = mp[a[i]];
    }

    int inversion_ct = 0;
    for(int i = 1; i<= n; ++i){
        inversion_ct += (sum(N-5) - sum(a[i]));
        update(a[i], 1);
    }

    cout << inversion_ct << endl;
}

/************************************************************************************************************************************************/

// to find occurence of a no. when we are incrementing count of no. in [L,R] by 1
class BIT {
public:
    vector<int> bit;
    int n;

    BIT(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    // Add value 'val' at position 'index'
    void update(int index, int val) {
        while (index <= n) {
            bit[index] += val;
            index += index & -index; 
        }
    }

    // Get the prefix sum from 1 to index
    int sum(int index) {
        int result = 0;
        while (index > 0) {
            result += bit[index];
            index -= index & -index; 
        }
        return result;
    }

    // Get the sum from [L, R]
    int rangeSum(int L, int R) {
        return sum(R) - sum(L - 1);
    }
};
int main() {
    int n = 10;  // Assuming numbers are between 1 and 10
    BIT bit(n);
    vector<pair<int, int>> intervals = {{1, 5}, {2, 7}, {4, 9}};
    for (auto [L,R] : intervals) {
        bit.update(L, 1); 
        if (R + 1 <= n) {
            bit.update(R + 1, -1); 
        }
    }

    // Queries to find how many times a number appears
    vector<int> queries = {1, 5, 6, 9};

    for (int x : queries) {
        int count = bit.sum(x); // Count the occurrences of x
        cout << "Number " << x << " appears " << count << " times in the intervals." << endl;
    }

    return 0;
}

/************************************************************************************************************************************************/
// range sum query - mutable (Leetcode)
class NumArray {
private:
    vector<int> bit; 
    vector<int> nums; 
    int n;
    void add(int index, int delta) {
        index++; // BIT is 1-indexed
        while (index <= n) {
            bit[index] += delta;
            index += index & -index;
        }
    }
    int sum(int index) {
        index++;  // 1-indexed
        int result = 0;
        while (index > 0) {
            result += bit[index];
            index -= index & -index;
        }
        return result;
    }

public:
    NumArray(vector<int>& nums) {
        this->nums = nums;
        n = nums.size();
        bit.assign(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            add(i, nums[i]);
        }
    }
    void update(int index, int val) {
        int delta = val - nums[index];
        nums[index] = val;
        add(index, delta);
    }
    int sumRange(int left, int right) {
        return sum(right) - sum(left - 1);
    }
};
