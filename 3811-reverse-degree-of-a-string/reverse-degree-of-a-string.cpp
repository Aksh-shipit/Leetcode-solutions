class Solution {
public:
    int reverseDegree(string s) {
        
        map<char,int> alpha_map;
        for(char ch='A';ch<='Z';ch++){
            alpha_map[ch]='Z'-ch+1;
        }

        int n=s.length();
        long long sum=0;
        for(int i=0;i<n;i++){
            char upper_ch=toupper(s[i]);
            if(alpha_map.find(upper_ch)!=alpha_map.end()){
            long long product=(long long)(i+1)*alpha_map[upper_ch];
                sum+=product;
            }

        }
        return sum;
    }
};