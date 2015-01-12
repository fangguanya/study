// !< 方法的使用....
import scala.io.Source

// !< (单例)
object LongLines
{
	def processFile(filename: String, width: Int)
	{
		val source = Source.fromFile(filename)
		for (line <- source.getLines)
		{
			processLine(filename, width, line)
		}
	}
	
	// !< 打印出长度超过指定长度的字符串(所在文件)
	private def processLine(filename: String, width: Int, line: String)
	{
		if (line.length > width)
		{
			println(filename + " :" + line.trim)
		}
	}
}

// !< 从控制台输入(单例)
object FindLongLines
{
	def main(args : Array[String])
	{
		val width = args(0).toInt
		for (arg <- args.drop(1))
		{
			LongLines.processFile(arg, width)
		}
	}
}