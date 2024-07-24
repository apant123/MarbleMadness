class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        output = []
        q = collections.deque()
        l,r = 0,0
        
        while r < len(nums):
            while q and nums[r] > q[-1][1]:
                q.pop()
            q.append((r,nums[r]))

            if k == r - l + 1:
                output.append(q[0][1])
                l +=1
                while q and l > q[0][0]:
                    q.popleft()
            r +=1


        return output


