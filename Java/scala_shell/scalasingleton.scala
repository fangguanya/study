import scala.collection.mutable.Map

// !< 我了个去,单例对象居然可以合普通的class重名@!#?
object ChecksumAccumulator
{
	private val cache = Map[String, Int]()
	def calculate(s : String) : Int = 
	{
		if (cache.contains(s))
		{
			cache(s)
		}
		else
		{
			val acc = new ChecksumAccumulator
			for (c < -s)
			{
				acc.add(c.toByte)
			}
			val cs = acc.checksum()
			cache += (s -> cs)
			cs
		}
	}
}