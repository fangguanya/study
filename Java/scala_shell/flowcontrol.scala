// !< 控制语句
import java.io.FileReader
import java.io.FileNotFoundException
import java.io.IOException

// !< 使用了if的产出值(并让变量的定义使用了val!!!!!!!!)
val filename = if (!args.isEmpty) args(0)
	else "default.txt"
	
// !< 尽量少用while循环(经常不得不带入var变量!!!)---在while()中的a=b是不能继续使用a的.
def gcdLoop(x: Long, y: Long): Long = 
{
	var a = x
	var b = y
	while (a != 0) 
	{
		val temp = a
		a = b % a
		b = temp
	}
	b
}

// !< for中可以添加if子句
val filesHere = (new java.io.File(".")).listFiles
for (file <- filesHere if file.getName.endsWith(".scala"); if file.isFile)
{
	println(file)
}

// !< for中可以添加多个<-子句
def fileLines(file : java.io.File) = 
{
	scala.io.Source.fromFile(file).getLines.toList
}
def grep(pattern : String) =
{
	// !< 居然可以使用{}来代替()..
	for {file <- filesHere
		if file.getName.endsWith(".scala")
		line <- fileLines(file)
		if line.trim.matches(pattern)}
	println(file + ": " + line.trim)
}
grep(".*gcd.*")

// !< for循环体产生值
def scalaFiles =
{
	for {
		file <- filesHere
		if file.getName.endsWith(".scala")
	}
	yield
	{
		println("file=" + file.getName)
		// !< for需要记录的数据为for循环体的最后语句!!!
		file
	}	
}

// !< try&catch
try
{
	val f = new FileReader("input.txt")
}
catch
{
	case ex : FileNotFoundException => // handle missing file
	case ex : IOException => // Handle other I/O error	
}
finally
{
	// !< 务必处理的..
}

// !< match匹配处理
val firstArg = if (args.length > 0) args(0) else ""
firstArg match
{
	case "salt" => println("pepper")
	case "chips" => println("salsa")
	case "eggs" => println("bacon")
	case _ => println("huh?")
}

// !< match产生值
val friend =
	firstArg match {
		case "salt" => "pepper"
		case "chips" => "salsa"
		case "eggs" => "bacon"
		case _ => "huh?"
	}

// !< 打印乘法表
def makeRowSeq(row : Int) = 
{
	for (col <- 1 to 10) yield
	{
		val prod = (row * col).toString
		val padding = " " * (4 - prod.length)
		padding + prod
	}
}
def makeRow(row : Int) = makeRowSeq(row).mkString
def multiTable() = 
{
	val tableSeq = for (row <- 1 to 10)
		yield makeRow(row)
	tableSeq.mkString("\n")
}

