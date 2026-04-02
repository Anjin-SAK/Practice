class Solution(object):
    def twoSum(self, nums, target):
        prevMap = {}
        for x, k in enumerate(nums):
            diff = target - k
            if diff in prevMap:
                return [prevMap[diff], x]
            prevMap[k] = x
        return
        