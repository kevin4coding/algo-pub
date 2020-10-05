class Solution:
    def findLongestChain(self, pairs: List[List[int]]) -> int:
        pairs.sort(key = lambda o : (o[0], o[1]))
        p = []
        for pair in pairs:
            if len(p) == 0:
                p.append(pair[1])
            else:
                idx = bisect.bisect_left(p, pair[0])
                if idx == len(p):
                    p.append(pair[1])
                else:
                    p[idx] = min(p[idx], pair[1])
        return len(p)
            
        
