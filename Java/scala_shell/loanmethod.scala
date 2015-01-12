// !< 贷出模式
def withPrintWriter(file: File, op:PrintWriter => Unit)
{
	val writer = new PrintWriter(file)
	try
	{
		op(writer)
	}
	finally
	{
		writer.close();
	}
}

// !< 框架处理了资源的申请,释放等,逻辑层只用负责逻辑!
withPrintWriter(new File("data.txt"), writer => writer.println(new java.util.Date))

// !< 括号替代的 版本
def withPrintWriterNew(file :File)(op:PrintWriter => Unit)
{
	val writer = new PrintWriter(file)
	try
	{
		op(writer)
	}
	finally
	{
		writer.close()
	}
}
val file = new File("data.txt")
withPrintWriterNew(file)
{	
	writer => writer.println(new java.util.Date)
}