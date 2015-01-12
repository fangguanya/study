// !< 叫名参数
var assertionsEnabled = true
// !< 使用时无法使用myAssert(x > 0),而必须用为myAssert(() => x > 0)
def myAssert(predicate: () => Boolean) = 
{
	if (assertionsEnabled && !predicate())
	{
		throw new AssertionError
	}
}

def byNameAssert(predicate: => Boolean) = 
{
	if (assertionsEnabled && !predicate)
	{
		throw new AssertionError
	}
}