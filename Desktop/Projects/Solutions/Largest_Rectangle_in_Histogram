class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        stack = [] # (index, height)
        maxArea = 0
        for i,v in enumerate(heights):
            if stack and v < stack[-1][1]:
                while stack and v < stack[-1][1]:
                    area = (i - stack[-1][0]) * (stack[-1][1])
                    maxArea = max(maxArea,area)
                    prevIndex = stack[-1][0]
                    stack.pop()
                stack.append((prevIndex,v))
            else :
                stack.append((i,v))

        for i,v in enumerate(stack):
            area = (len(heights) - stack[i][0]) * (stack[i][1])
            maxArea = max(area,maxArea)
        return maxArea



    
        

