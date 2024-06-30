# Assert

!!! info "Ref"
    [Geeks](https://www.geeksforgeeks.org/assertions-cc/)

Assert 更经常用于一些底层的检查、Debug过程中，而异常检测常常是在一些接口调用时由上层判断

assert可以关闭

```c++
// The below program runs fine because NDEBUG is defined
# define NDEBUG
# include <assert.h>
 
int main()
{
    int x = 7;
    assert (x==5);
    return 0;
}
```

## 单元测试

下面这一段以gtest为例

```c++
#include "gtest/gtest.h"
void CheckTxnLockSize(Txn &txn, size_t shared_expected, size_t exclusive_expected) {
  ASSERT_EQ(shared_expected, txn.GetSharedLockSet().size());
  ASSERT_EQ(exclusive_expected, txn.GetExclusiveLockSet().size());
}
```

