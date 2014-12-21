package com.fanggang.annotation;
 
import java.util.HashMap;
import java.util.Map;

/**
 * 这个类专门用来测试注解使用
 * @author tmser
 */
//使用了类注解
@TestA
public class UserAnnotation {
    
    @TestA //使用了类成员注解
    private Integer age;
    
    @TestA //使用了构造方法注解
    public UserAnnotation(){
        
    }
    @TestA //使用了类方法注解
    public void a(){
        @TestA //使用了局部变量注解
        Map m = new HashMap(0);
    }
    
    public void b(@TestA Integer a){ //使用了方法参数注解
        
    }
}
/**
 * 这个类专门用来测试注解使用
 * @author tmser
 */
 
@TestAObject(name="type",gid=Long.class) //类成员注解
public class UserAnnotationObject {
	
	@TestAObject(name="param",id=1,gid=Long.class) //类成员注解
	private Integer age;
	
	@TestAObject(name="construct",id=2,gid=Long.class)//构造方法注解
	public UserAnnotation(){
		
	}
	@TestAObject(name="public method",id=3,gid=Long.class) //类方法注解
	public void a(){
		Map<String,String> m = new HashMap<String,String>(0);
	}
	
	@TestAObject(name="protected method",id=4,gid=Long.class) //类方法注解
	protected void b(){
		Map<String,String> m = new HashMap<String,String>(0);
	}
	
	@TestAObject(name="private method",id=5,gid=Long.class) //类方法注解
	private void c(){
		Map<String,String> m = new HashMap<String,String>(0);
	}
	
	public void b(Integer a){ 
		
	}
}