// !< 调用超类构造器
abstract class Element
{
	def contents: Array[String]
	def width: Int =
		if (height == 0) 0 else contents(0).length
	def height: Int = contents.length

	// !< ++ 完成字符串的链接...
	def above(that: Element): Element = 
	{
		new ArrayElement(this.contents ++ that.contents)
	}
	def beside(that: Element) : Element = 
	{
		val contents = new Array[String](this.contents.length)
		for (i <- 0 util this.contents.length)
		{
			contents(i) = this.contents(i) + that.contents(i)
		}
		new ArrayElement(contents)
		
		// !< 函数式编程风格
		//new ArrayElement(
		//	for ((line1, line2) <- this.contents zip that.contents)
		//		yield line1 + line2
		//)
	}
	
	// !< 字符串输出
	override def toString = contents mkString "\n"
}

// !< 工厂对象
object Element
{
	def elem(contents: Array[String]): Element = 
	{
		new ArrayElement(contents)
	}
	def elem(chr: Char, width: Int, height: Int): Element =
	{
		new UniformElement(chr, width, height)
	}
	def elem(line: String): Element =
	{
		new LineElement(line)
	}
}

class ArrayElement(int capacity) extends Element
{
	final val Capacity = capacity
}

class LineElement(s: String) extends ArrayElement(Array(s))
{
	override def width = s.length
	override def height = 1
}

class UniformElement
(
	ch: Char,
	override val width: Int,
	override val height: Int
) extends Element
{
	private val line = ch.toString * width
	def contents = Array.make(height, line)
}