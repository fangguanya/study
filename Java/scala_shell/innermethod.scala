// !< 内嵌函数
// !< 内部函数可以直接访问外部函数的作用域内变量
import scala.io.Source
object LongLines
{
	def processFile(filename: String, width: Int)
	{
		def processLine(line: String)
		{
			if (line.length > width)
			{
				println(filename + ":" + line)
			}			
		}
		val source = Source.fromFile(filename)
		for (line <- source.getLines)
		{
			processLine(line)
		}
	}
}