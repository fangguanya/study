// !< List是unmutable的,无法修改!!所有操作都返回新的List
// !< :::
// !< ::
val oneTwo = List(1,2)
val threeFour = List(3,4)
val oneTwoThreeFour = oneTwo ::: threeFour

println("after combine oneTwo=" + oneTwo)
println("threeFour=" + threeFour)
println("oneTwoThreeFour=" + oneTwoThreeFour)

val twoThree = List(2,3)
val oneTwoThree = 1 :: twoThree
println("after insert oneTwoThree=" + oneTwoThree)

// !< 灵活使用Nil
val oneTwoThreeNil = 1 :: 2 :: 3 :: Nil
println("with nill oneTwoThreeNil=" + oneTwoThreeNil)