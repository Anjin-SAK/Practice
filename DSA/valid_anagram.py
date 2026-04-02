class Solution(object):
    def isAnagram(self, s, t):
        if len(s) != len(t):
            return False
        group1 , group2 = {} , {}
        for x in range(0,len(s)):
            group1[s[x]]= group1.get(s[x],0)+1
            group2[t[x]]= group2.get(t[x],0)+1
        return group1 == group2 
        