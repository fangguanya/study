// !< 作为脚本,可以读取传入的参数 args()
// !< 这里的数组访问使用的是'('')',而不是[]
var i = 0
while (i < args.length)
{
	if (i != 0) print(" ")
	print(args(i) + "!")
	i += 1
}
