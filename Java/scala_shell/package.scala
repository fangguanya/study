// !< 包和引用
package bobsrockets
{
	package navigation 
	{
		class Navigator
	}
	package launch 
	{
		class Booster 
		{
			// 不用写bobsrockets.navigation.Navigator
			val nav = new navigation.Navigator
		}
	}
}