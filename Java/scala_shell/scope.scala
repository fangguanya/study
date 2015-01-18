// !< 作用域<scope>
package bobsrockets
{
	package navigation
	{
		// !< 指定类型Navigator在bobsrockets的作用域中访问为public
		private[bobsrockets] class Navigator
		{
			protected[navigation] def useStarChart() {}
			class LegOfJourney
			{
				private[Navigator] val distance = 100
			}
			// !< 只能在同一实例中访问!
			private[this] var speed = 200
		}
	}
	package launch
	{
		import navigation._
		object Vehicle
		{
			private[launch] val guide = new Navigator
		}
	}
}