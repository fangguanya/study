// !< 使用Application特质
import ChecksumAccumulator.calculate

object FallWinterSprintSummer extends Application
{
	for (season <- List("fall", "winter", "sprint"))
	{
		println(season + ": " + calculate(season))
	}
}