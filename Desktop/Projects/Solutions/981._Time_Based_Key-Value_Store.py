class TimeMap:
    def __init__(self):
        self.hashmap = {} # key -> list of [value,timestamp]

    def set(self, key: str, value: str, timestamp: int) -> None:
        if key not in self.hashmap:
            self.hashmap[key] = []
        self.hashmap[key].append([value,timestamp])

    def get(self, key: str, timestamp: int) -> str:
        result = ""
        values = self.hashmap.get(key, [])
        left = 0
        right = len(values) - 1
        while left <= right:
            mid = (left + right) // 2
            if timestamp < values[mid][1]:
                right = mid - 1
            else:
                result = values[mid][0]
                left = mid + 1
        return result





        
# Your TimeMap object will be instantiated and called as such:
# obj = TimeMap()
# obj.set(key,value,timestamp)
# param_2 = obj.get(key,timestamp)
