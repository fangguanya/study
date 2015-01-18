// !< 使用引用..
// <可访问Fruit>
import bobsdelights.Fruit
// <可访问所有bobsdelights的成员>
import bobsdelights._
// <访问Fruit的成员>
import bobsdelights.Fruit._

def showFruit(fruit: Fruit)
{
	import fruit._
	println(name +"s are " + color)
}