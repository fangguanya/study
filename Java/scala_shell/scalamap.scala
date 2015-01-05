import scala.collection.mutable.Map

// !< 可用Array类似的方式创建
val treasureMap = Map[Int, String]()
treasureMap += (1 -> "Go to island")
treasureMap += (2 -> "Find big X on ground")
treasureMap += (3 -> "Dig.")

println(treasureMap)

// !< 也可以穷举创建!
val romanNumeral = Map(1 -> "I", 2 -> "II", 3 -> "III", 4 -> "IV", 5 -> "V")