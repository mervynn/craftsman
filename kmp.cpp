#include <iostream>
#include <vector>
using namespace std;
vector<int> getNext(string str){
	int len = str.size(), i = 0, j = -1;
	vector<int> next;
	if(!len) return next;
	next.resize(len, -1);
	while(i < len){
		if(j == -1 || str[i] == str[j]){
			i++;
			j++;
			if(str[i] != str[j]) next[i] = j;
			else next[i] = next[j];
		}else{
			j = next[j];
		}
	}
	return next;
}

int findIndex(string str, string pattern){
	int res, i = 0, j = 0, lens = str.size(), lenp = pattern.size();
	vector<int> next = getNext(pattern);
	while(i < lens && j < lenp){
		if(str[i] == pattern[j]){
			i++;
			j++;
		}else if(0 == j){
			i++;
		}else{
			j = next[j - 1] + 1;
		}
	}
	if(j == lenp) res = i - lenp;
	else res = -1;
	return res;
}
int main(){
	string s = "aaaabdddffadfasdfbaaxabaddxx";
	string p = "abababa";
	cout<<findIndex(s, p)<<endl;
}


