class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:

        # flist = [element for sublist in matrix for element in sublist]
        # i = 0
        # j = len(flist) - 1
        # while i <= j:
        #     mid = (j + i) // 2
        #     if flist[mid] == target:
        #         return True
        #     elif flist[mid] < target:
        #         i = mid + 1
        #     else:
        #         j = mid - 1
        # return False

        rows, colums = len(matrix), len(matrix[0])
        top, bottom = 0, rows - 1
        while top <= bottom:
            mid = (top + bottom) // 2
            if target < matrix[mid][0]:
                bottom = mid - 1
            elif target > matrix[mid][-1]:
                top = mid + 1
            else:
                break
        if (bottom < top):
            return False
        
        left = 0
        mid = (top + bottom) // 2
        right = colums - 1
        while (left <= right):
            mid2 = (left + right) // 2
            if matrix[mid][mid2] == target:
                return True
            elif target < matrix[mid][mid2]:
                right = mid2 - 1
            else:
                left = mid2 + 1

        return False


