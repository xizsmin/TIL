'''
Consider first two given coordinates (x1, y1) and (x2, y2):
1) if x1 == x2:  as both are on a horizontal line, the rests must be too
        i.e., xn == x1 for all coords.
2) else: f(x) = mx + a
   where m = (y2-y1)/(x2-x1), a = y1-m*x1
   
'''
class Solution:
        
    def checkStraightLine(self, coordinates: List[List[int]]) -> bool:
        if coordinates[1][0] == coordinates[0][0]:
            for i, coord in enumerate(coordinates):
                if coord[0] != coordinates[1][0]:
                    return False
            return True
        else:
            slope = (coordinates[1][1] - coordinates[0][1])/(coordinates[1][0] - coordinates[0][0])
            const = coordinates[0][1] - slope*coordinates[0][0]
            print('slope:',slope,'const:',const)
            for i,coord in enumerate(coordinates):
                if slope*coord[0] + const != coord[1]:
                    return False
                
            return True
        
        
