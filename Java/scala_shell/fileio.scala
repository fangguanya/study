// !< 文件处理
import scala.io.Source

def widthOfLength(s : String) = s.length.toString.length

if (args.length > 0)
{
	val lines = Source.fromFile(args(0)).getLines.toList
	//var maxWidth = 0
	//for (line <- lines)
	//{
	//	maxWidth = maxWidth.max(widthOfLength(line))
	//}
	val longestLine = lines.reduceLeft((a,b) => if (a.length > b.length) a else b)
	val maxWidth = widthOfLength(longestLine)
	for (line <- lines)
	{
		val numSpaces = maxWidth - widthOfLength(line)
		val padding = " " * numSpaces
		print(padding + line.length + " | " + line + "\n")
	}
}
else
{
	Console.err.println("请输入文件名!")
}