sort(a: int[]) {
  i:int = 0
  n:int = length(a)
  while (i < n) {
      j:int = i
      while (j > 0) {
        if (a[j-1] > a[j]) {
            swap:int = a[j]
            a[j] = a[j-1]
            a[j-1] = swap
        }
        j = j-1
      }
      i = i+1
  }
}
