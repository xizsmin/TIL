'''
Let all given numbers be in matching parentheses of its depth:

Given arr, iterate as:
1st element - arr[i] opening parentheses
smaller than the previous - (arr[i-1]-arr[i])closing parentheses + arr[i]
larger than the previous - (arr[i]-arr[i-1])closing parentheses + arr[i]
same with the previous - arr[i]

After iteration finishes:
put the rest closing parentheses to match

'''


T=input()


def f(_list):
	ret = ''
	cnt_opening = 0
	cnt_closing = 0
	for i in range(len(_list)):
		if i==0:
			ret += '('*_list[i]
			cnt_opening += _list[i]
			ret += str(_list[i])
		else:
			if _list[i] < _list[i-1]:
				ret += ')'*(_list[i-1]-_list[i])
				ret += str(_list[i])
				cnt_closing += (_list[i-1]-_list[i])
			elif _list[i] == _list[i-1]:
				ret += str(_list[i])
			else:
				ret += '('*(_list[i]-_list[i-1])
				ret += str(_list[i])
				cnt_opening += (_list[i]-_list[i-1])

	ret += ')'*(cnt_opening - cnt_closing)
	return ret

			

for t in range(int(T)):
	input_nums = input()
	list_nums = [int(d) for d in str(input_nums)]
	print('Case #'+str(t+1)+':',f(list_nums))




