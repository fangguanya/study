// !< 函数文本

// !< 将x映射为x+1,,类似LAMDA表达式
(x :Int) => x + 1

var increase = (x : Int) => x + 1
increase(10)

// !< var可以再次赋值..
increase = (x : Int) => x + 9999
increase(10)

// !< 复杂的函数文本
increase = (x : Int) =>
	{
		println("We")
		println("are")
		println("here!")
		x + 1
	}
increase(10)

// !< 占位符语法
val f = (_:Int) + (_:Int)
f(5,10)

// !< 偏应用参数
def sum(a:Int, b:Int, c:Int) = a + b + c
sum(1,2,3)
// !< --- 替换任意参数..
val a = sum _
a(1,2,3) // === a.apply(1,2,3), 将参数应用上去

val b = sum(1, _:Int, 3)
b(5)
