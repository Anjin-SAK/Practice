class Solution(object):
    def isAnagram(self, s, t):
        if len(s) != len(t):  # If lengths are different, they cannot be anagrams
        # anagrams must use exactly the same characters
        # the same number of times.
            return False
        group1 , group2 = {} , {}
        for x in range(0,len(s)):
            group1[s[x]]= group1.get(s[x],0)+1 # s[x] → current character
            # group1.get(s[x], 0) → get current count of that character
            # if not present, default = 0
            # +1 → increment count
            # So this line counts frequency of each character in string s
            group2[t[x]]= group2.get(t[x],0)+1
        return group1 == group2 