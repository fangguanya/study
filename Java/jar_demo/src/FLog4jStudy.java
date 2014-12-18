import org.apache.log4j.Logger;
import org.apache.log4j.PropertyConfigurator;

public class FLog4jStudy
{
    static Logger logger = Logger.getLogger(FLog4jStudy.class);
    public static void main(String[] args)
    {
        // !< 初始化?对静态变量会有影响吗?
        PropertyConfigurator.configure("log4jconfig.txt");

        logger.info("start log4j!");
        logger.warn("test warn!");
        logger.error("test error!");
    }
}