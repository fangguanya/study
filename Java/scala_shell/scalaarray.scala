// !< 数组的使用....Array需要指定类型..(不然无法推断.)
val greetStrings = new Array[String](3)
greetStrings(0) = "hello"
greetStrings(1) = ","
greetStrings(2) = "world!\n"

for (idx <- 0 to 2) print(greetStrings(idx))