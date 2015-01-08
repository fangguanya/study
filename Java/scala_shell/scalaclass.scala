// !< 类的定义...
class ChecksumAccumulator
{
	var sum=0
	private var pri_sum=1
	
	def add(b: Byte) : Unit = 
	{
		pri_sum += b
	}
	def checksum() : Int = 
	{
		return ~(pri_sum & 0xFF) + 1
	}
}

val acc = new ChecksumAccumulator
val csa = new ChecksumAccumulator