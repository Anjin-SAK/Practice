class Solution(object):
    def twoSum(self, nums, target):
        prevMap = {}
        for x, k in enumerate(nums):
            diff = target - k
            if diff in prevMap:# check's if required number was seen before
            # if yes we found two numbers that add up to target
            # prevMap[diff] gives index of previous number
            # x is current index
                return [prevMap[diff], x]
            prevMap[k] = x
        return
        