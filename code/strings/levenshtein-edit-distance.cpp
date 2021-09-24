#define sz(X) (int) X.size()
const int INFTY = 1e8

int edit_distance(string &a, string &b){
	vector<vector<int>> dp(2, vector<int>(sz(a)+1, 0));
	int p = 0;

	for(int i=0; i<=sz(b); i++){
		for(int j=0; j<=sz(a); j++){
			if(i==0) dp[p][j] = j;
			else if(j==0) dp[p][j] = i;

			else if(a[j-1]==b[i-1])
				dp[p][j] = dp[p^1][j-1];

			else
				dp[p][j] = 1 + min({dp[p][j-1], dp[p^1][j], dp[p^1][j-1]});
		}
		p ^= 1;
	}
	
	return dp[p^1][sz(a)];
}
