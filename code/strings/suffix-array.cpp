/**
 * DO NOT USE
 * Use https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/SuffixArray.h 
 * until this is updated
**/

class SuffixArray{
private:
	int n;
	string s;
	vi arr;
public:
	SuffixArray(string &_s) : s(_s + "$"){
		n = sz(s);
		arr.resize(n); iota(all(arr), 0);
		int iters = n; 
		while(__builtin_popcount(iters) > 1) iters++;

		vi equiv(n); 
		vii b(n);
		sort(all(arr), [this](int &a, int &b) { return s[a] < s[b]; });
		for(int i=1; i<n; i++) equiv[i] = equiv[i-1] + (s[arr[i-1]] != s[arr[i]]);

		for(int k=1; k<=iters; k <<= 1){
			for(int i=0; i<n; i++) b[i] = {equiv[i], equiv[i+(1<<(k-1))]};
			sort(all(arr), [&b](int &x, int &y){ 
				if(b[x].ff == b[y].ff) return b[x].ss < b[y].ss;
				else return b[x].ff < b[y].ff;
			});
			equiv[arr[0]] = 0;
			for(int i=1; i<n; i++) equiv[arr[i]] = equiv[arr[i-1]] + (b[arr[i]] != b[arr[i-1]]);
		}
	}

	void print(){
		for(int i=0; i<n; i++){
			cout<<s.substr(arr[i], n-arr[i])<<endl;
		}
	}
};

int main(void){

	string s = "ababba";
	SuffixArray SA(s);
	SA.print();

}