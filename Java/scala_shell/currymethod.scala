// !< 函数curry化
// !< 老的函数
def plainOldSum(x:Int, y:Int) = x + y
plainOldSum(1, 2)

def curriedSum(x:Int)(y:Int) = x + y
curriedSum(1)(2)
// !< 等同于def curriedSum(x:Int) = (y:Int) => x+y