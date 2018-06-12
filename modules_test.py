from sys import path
path.append('./modules/')
from modules import Solution


way = Solution()

num = [1, 2, 3, 4, 5]
target = 4

print (way.twoSum(num, target))


