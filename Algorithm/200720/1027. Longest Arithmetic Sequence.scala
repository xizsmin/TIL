// 주어진 Array 중 가장 큰 값 2개를 뽑아서 1씩 감소시킨 값의 곱

object Solution {
    def maxProduct(nums: Array[Int]): Int = {
        val sorted_list = nums.sorted(Ordering[Int].reverse)
        (sorted_list(0)-1) * (sorted_list(1)-1)
    }
}

