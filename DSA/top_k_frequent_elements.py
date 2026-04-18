class Solution(object):
    def topKFrequent(self, nums, k):
        group = {}
        for x in nums:
            if x not in group:
                group[x] = 1
            else:
                group[x] += 1
        top_k_list = sorted(group, key=group.get, reverse=True)[:k]
        return top_k_list