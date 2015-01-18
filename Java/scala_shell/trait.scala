// !< 特质....
// !< 关键字:trait
trait Philosophical
{
	def philosophize()
	{
		println("I consume memory, therefore I am!")
	}
}

// !< 特质的'混入'
class Frog extends Philosophical
{
	override def toString = "green"
}

frog = new Frog
frog.philosophize()

// !< 特质的'混入'2
class Animal
trait HasLegs
class Frog2 extends Animal with Philosophical with HasLegs
{
	override def toString = "red"
	override def philosophize()
	{
		println("It ain't easy being " + toString + "!")
	}
}