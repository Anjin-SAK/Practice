class Solution(object):
    def groupAnagrams(self, strs):
        group = {}
        for x in strs:
            key = "".join(sorted(x))
            if key not in group:
                group[key] = []         
            group[key].append(x)        

        return list(group.values())
        