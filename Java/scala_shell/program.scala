// !< 一个scala程序
import ChecksumAccmulator.calculate
object Summer
{
	def main(args : Array[String])
	{
		for (arg <- args)
		{
			println(arg + ":" + calculate(arg))
		}
	}
}