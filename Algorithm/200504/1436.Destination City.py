// Find the city without any outgoing path, i.e., appears as second but not as first
// achieve this with getting set difference

class Solution:
    def destCity(self, paths: List[List[str]]) -> str:
        return (list(set([item[1] for item in paths]) - set([item[0] for item in paths]))[0])
