class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num) {
            return "";
        }
        
        // Calculate the maximum number of 9s we can use
        int nines = sum / 9;
        // Calculate the single remainder digit
        int rem = sum % 9;
        // The remaining positions are filled with 0s
        int zeros = num - nines - (rem > 0 ? 1 : 0);
        
        // Construct the largest possible number string
        string ans = "";
        ans.append(nines, '9');
        if (rem > 0) {
            ans.push_back('0' + rem);
        }
        ans.append(zeros, '0');
        
        return ans;
    }
};