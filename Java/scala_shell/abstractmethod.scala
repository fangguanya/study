// !< 简单面向对象版本(文件搜索)
object FileMatcher 
{
	private def filesHere = (new java.io.File(".")).listFiles
	
	// !< 文件类型查找
	def filesEnding(query: String) =
	{
		for (file <- filesHere; if file.getName.endsWith(query))
		yield file
	}
	
	// !< 文件名称查找
	def filesContaining(query: String) =
	{
		for (file <- filesHere; if file.getName.contains(query))
		yield file
	}
	
	// !< 正则表达式查找
	def filesRegex(query: String) =
	{
		for (file <- filesHere; if file.getName.matches(query))
		yield file
	}
	
}

object FileMatcherNew
{
	private def filesHere = (new java.io.File(".")).listFiles
	// !<--抽象相同部分----Scala不是动态语言,不支持运行时粘合代码!
	//def filesMatching(query: String, method) =
	//{
	//	for (file <- filesHere; if file.getName.method(query))
	//	yield file
	//}
	// !< 使用函数值
	def filesMatching(query: String, matcher: (String, String) => Boolean) = 
	{
		for (file <- filesHere; if matcher(file.getName, query))
		{
			yield file
		}
	}
	
	// !< 使用了_,要求函数自动匹配的顺序也要一致!
	def filesEnding(query: String) =
		filesMatching(query, _.endsWith(_))
	def filesContaining(query: String) =
		filesMatching(query, _.contains(_))
	def filesRegex(query: String) =
		filesMatching(query, _.matches(_))
}