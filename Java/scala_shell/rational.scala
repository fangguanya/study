// !< 分数的scala式样书
// !<	分数的+,-,*,%...
// !< 	val的类型(自己不改变,产生新的对象)
class Rational (n : Int, d: Int)
{
	// !< 先决条件检查
	require(d != 0)
	
	// !< 从构造器
	def this(n : Int) = this(n, 1)
	
	// !< 不是字段的部分,自动添加到创造的构造函数当中去
	// !< 	注意:由于numer/denom对其的依赖,务必最先定义
	println("Created " + n + "/" + d)

	// !< 成员定义
	val numer : Int = n / g
	val denom : Int = d / g
	// !< 最大公约数
	private val g = gcd(n.abs, d.abs)

	// !< 方法重载
	override def toString = n + "/" + d
	
	// !< 加法重载
	def +(that: Rational): Rational =
		new Rational(
			numer * that.denom + that.numer * denom,
			denom * that.denom
		)
		
	// !< 加法重载
	def +(i: Int): Rational =
		new Rational(numer + i * denom, denom)
	
	// !< 减法重载
	def -(that: Rational): Rational =
		new Rational(
			numer * that.denom - that.numer * denom,
			denom * that.denom
		)
	
	// !< 减法重载
	def -(i: Int): Rational =
		new Rational(numer - i* denom, denom)
		
	// !< 乘法重载
	def *(that: Rational): Rational =
		new Rational(numer * that.numer, denom * that.denom)
		
	// !< 乘法重载
	def *(i: Int): Rational =
		new Rational(numer * i, denom)
	
	// !< 除法重载
	def /(that: Rational): Rational =
		new Rational(numer * that.denom, denom * that.numer)
		
	// !< 除法重载
	def /(i: Int): Rational =
		new Rational(numer, denom * i)
	
	def <(that : Rational) = 
	{
		that.numer * that.danom < that.numer * this.danom
	}
	def max(that : Rational) = 
	{
		if (lessThan(that)) that else this
	}
	private def gcd(a: Int, b: Int) =
	{
		if (b == 0) a else gcd(b, a%b)
	}
}

// !< 隐式转换,只能在这里定义,如果在Rational类中定义,则范围不对!
implicit def intToRational(x : Int) = new Rational(x)

def useRational() =
{
	val oneHalf = new Rational(1, 2)
	val twoThirds = new Ratio (2, 3)
	
	(oneHalf / 7) + (1 twoThirds)
}