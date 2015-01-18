// !< 队列特质..
import scala.collection.mutable.ArrayBuffer
abstract class IntQueue
{
	def get(): Int
	def put(x: Int)
}

class BasicIntQueue extends IntQueue
{
	private val buf = new ArrayBuffer[Int]
	def get() = buf.remove(0)
	def put(x: Int) { buf += x }
}

// !< 特质1..
trait Doubling extends IntQueue
{
	// !< 动态绑定!!
	abstract override def put(x: Int) { super.put(2 * x) }
}
// !< 特质2..
trait Incrementing extends IntQueue
{
	abstract override def put(x: Int) { super.put(x + 1) }
}
// !< 特质3..
trait Filtering extends IntQueue
{
	abstract override def put(x: Int) { if (x >= 0) super.put(x) }
}

// !< 堆叠特质!!!!!!!
class MyQueue extends BasicIntQueue with Doubling with Incrementing with Filtering
{
}

val queue = new BasicIntQueue
queue.put(10)
queue.put(20)
queue.get()
queue.get()

val myqueue = new MyQueue
myqueue.put(10)
println(myqueue.get())