

def push(val, heap):
    heap.append(val)
    i = len(heap)-1

    while i > 0 and heap[int((i-1)/2)] <= val:
        tmp = heap[int((i-1)/2)]
        heap[int((i-1)/2)] = heap[i]
        heap[i] = tmp

        i = int((i-1)/2)
    print('->', heap)

def pop(heap):
    ret = heap[0]
    heap[0] = heap[-1]
    heap.pop()

    i=0
    while (2*i +1 < len(heap) and heap[i] < heap[2*i + 1]) or (2*i + 2 < len(heap) and heap[i] < heap[2*i +2]):
        j = 2*i + 1  if heap[2*i + 1] > heap[2*i+2] else 2*i+2
        tmp = heap[j]
        heap[j] = heap[i]
        heap[i] = tmp
        i = j

    return ret


    

heap = []
push(10, heap)
push(2, heap)
push(3, heap)
push(21, heap)
push(5, heap)
push(6, heap)

pop(heap)
print(heap)
pop(heap)
print(heap)
pop(heap)
print(heap)

    
