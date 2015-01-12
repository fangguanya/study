// !< 闭包
def makeIncreaser(more: Int) = (x: Int) => x + more
// !< 因为返回了一个闭包,所以inc1 和 inc9999都是一个闭包的函数!!!
val inc1 = makeIncreaser(1)
val inc9999 = makeIncreaser(9999)

inc1(10)
inc9999(10)

// !< 重复参数
def echo(args: String*) = 
{
	for (arg <- args)
	{
		println(arg)
	}
}
echo()
echo("one")

// !< 数组传入
val arr = Array("What's", "up", "doc?")
echo(arr:_*)

// !< 尾递归
def approximate(guess: Double):Double = 
{
	if (isGoodEnough(guess)) guess
	else approximate(improve(guess))
}

def boom(x: Int) :Int=
{
	if (x == 0) throw new Exception("boom!")
	else boom(x - 1) + 1	// !< 去掉+1则在崩溃的时候,堆栈只有自己一个调用.
}