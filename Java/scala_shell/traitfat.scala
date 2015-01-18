// !< 特质<扩展胖接口>

class Point(val x: Int, val y: Int)
// !< JAVA实现
class Rectangle( val topLeft: Point, val bottomRight: Point)
{
	def left = topLeft.x
	def right = bottomRight.x
	def width = right - left
}

// !< SCALA实现
// abstract class Component
// {
	// def topLeft: Point
	// def bottomRight: Point
	// def left = topLeft.x
	// def right = bottomRight.x
	// def width = right - left
// }
trait Rectangular
{
	def topLeft: Point
	def bottomRight: Point
	def left = topLeft.x
	def right = bottomRight.x
	def width = right - left
}
abstract class Component extends Rectangular
{}

// !< 类的扩展
class Rectangle(val topLeft: Point, val bottomRight: Point) extends Rectangular
{}
val rect = new Rectangle(new Point(1,1), new Point(10,10))
rect.left
rect.right
rect.width
