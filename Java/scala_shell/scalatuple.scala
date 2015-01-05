
// !< 创建只需将不同类型的数值赋值给一个变量即可!
val pair = (99, "Luftballons")

// !< 通过调用'_N'来获取,注意:索引从1开始!不能使用同一的'()'函数(apply)的原因是所有成员均可能不是一种类型
// !< 	那么返回值也就不是一种类型了
print(pair._1)
print(pair._2)

pair.foreach(print)