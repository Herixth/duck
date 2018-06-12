
class Solution(object):
	def __init__(self):
		pass

	def twoSum(self, nums, target):
		"""
		:type  nums:   List[int]
		:type  target: int
		:rtype List[int]
		"""

		ans = []
		for inc in range (len(nums)):
			for incc in range (inc + 1, len(nums)):
				if nums[inc] + nums[incc] == target:
					ans.append(inc)
					ans.append(incc)

		return ans

