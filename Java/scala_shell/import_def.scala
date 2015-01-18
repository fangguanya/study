// !< 引用
package bobsdelights
abstract class Fruit( val name: String,val color: String)

object Fruit
{
	object Apple extends Fruit("apple", "red")
	object Orange extends Fruit("orange", "orange")
	object Pear extends Fruit("pear", "yellowish")
	val menu = List(Apple, Orange, Pear)
}