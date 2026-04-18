class Solution(object):
    def productExceptSelf(self, nums):
        n = len(nums)
        answer = [0] * n  
        prefix = 1
        for i, k in enumerate(nums):
            answer[i] = prefix
            prefix *= k
        suffix = 1
        for i in reversed(range(n)):
            answer[i] *= suffix
            suffix *= nums[i]    
        return answer
        