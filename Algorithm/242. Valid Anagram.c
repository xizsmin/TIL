/**
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
*/

int s_map[26]; 
int t_map[26]; 

bool isAnagram(char * s, char * t){
      
    memset(s_map, 0, sizeof(int)*26);
    memset(t_map, 0, sizeof(int)*26);
    
    char *p = s;
    
    while (*p != '\0') {
        s_map[*p-'a']++;
        p++;
    }
      
    p = t;
    while (*p != '\0') {
        t_map[*p-'a']++;
        p++;
    }
    
    return !memcmp(s_map, t_map, sizeof(int)*26);

}

