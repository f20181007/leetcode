class Solution {
    using int64_t = long long;
private:
    int32_t n, elem;
    std::vector<int32_t> divCount, answer; 
    std::vector<int64_t> gcdCount, preSum;

public:
    vector<int32_t> gcdValues(vector<int32_t>& nums, vector<int64_t>& queries) {
        n = nums.size();
        elem = *std::max_element(nums.begin(), nums.end());

        divCount.assign(elem + 1, 0); 
        for(int32_t& i: nums) {
            for(int32_t j = 1; j * j <= i; j++) {
                if(i % j != 0) continue;

                int32_t x = j, y = i / j;
                if(x == y) ++divCount[x & y];
                else { ++divCount[x]; ++divCount[y]; }
            }
        }

        gcdCount.assign(elem + 1, 0LL);
        for(int32_t i = elem; i > 0; i--) {
            int64_t cnt = 1LL * divCount[i] * (divCount[i] - 1) / 2;
            for(int32_t j = 2 * i; j <= elem; j += i) {
                cnt -= gcdCount[j];
            }
            gcdCount[i] = cnt;
        }

        preSum.assign(elem + 1, 0LL);
        for(int32_t i = 1; i <= elem; i++) preSum[i] = gcdCount[i] + preSum[i - 1];
        
        std::vector<int64_t> :: iterator it;
        for(int64_t& q: queries) {
            it = std::lower_bound(preSum.begin() + 1, preSum.end(), q + 1);
            answer.push_back(std::distance(preSum.begin() + 1, it) + 1);
        }
        return answer;
    }
};
