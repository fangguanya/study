// !< 函数式编程

// !< 1.由于使用了'var',使其为指令式编程(不可重入)
def printArgs(args : Array[String]) : Unit =
{
	var i = 0
	while (i < args.length)
	{
		println(args(i))
	}
}

// !< 2.去掉了var-->函数式编程!
def printArgs1(args : Array[String]) : Unit =
{
	for (arg <- args) println(arg)
	// args.foreach(println)
}

// !< 3.在函数中使用其他的输出...等等...其实存在副作用,外界调用者无法控制..
// !<	去除了println,改为 输入-->输出 的映射式.
def printArgs2(args : Array[String]) = args.mkString("\n")